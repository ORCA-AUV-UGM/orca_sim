#!/usr/bin/env python3
"""Deteksi warna semua objek arena SAUVC lewat kamera.

Subscribe /camera/image_raw, segmentasi HSV per warna rintangan, lalu terbitkan
bounding box tiap objek ke topik /vision/<nama> bertipe OrcaVision.

Objek yang dideteksi (sesuai arena hasil generate_sauvc.py):
  gate_main          -> /vision/gate_main          (tiang+palang hitam)
  gate_qualification -> /vision/gate_qualification (tiang oranye + palang putih)
  bucket_blue        -> /vision/bucket_blue        (ember biru, silinder pendek)
  bucket_red         -> /vision/bucket_red         (ember merah, silinder pendek)
  flare_orange       -> /vision/flare_orange       (silinder oranye tebal)
  flare_yellow       -> /vision/flare_yellow       (tiang kuning tipis)
  flare_red          -> /vision/flare_red          (tiang merah tipis)
  flare_blue         -> /vision/flare_blue         (tiang biru tipis)
  surfacing_square   -> /vision/surfacing_square   (frame putih + marker biru)
"""
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import numpy as np
from orca_msgs_sim.msg import OrcaVision

# ============ Rentang HSV (diwarisi dari node lama + putih) ============
# Oranye (tiang qualification gate + flare_orange)
ORANGE_LO = np.array([5, 100, 100])
ORANGE_HI = np.array([25, 255, 255])

# Gelap/hitam (gate utama)
DARK_LO = np.array([0, 0, 0])
DARK_HI = np.array([180, 80, 60])

# Merah (stripe gate, flare merah, ember merah) - dua rentang karena hue wrap
RED_LO1 = np.array([0, 150, 150])
RED_HI1 = np.array([12, 255, 255])
RED_LO2 = np.array([155, 150, 150])
RED_HI2 = np.array([180, 255, 255])

# Kuning (flare kuning)
YELLOW_LO = np.array([15, 100, 100])
YELLOW_HI = np.array([35, 255, 255])

# Biru flare (tiang tipis)
BLUE_FLARE_LO = np.array([85, 100, 150])
BLUE_FLARE_HI = np.array([125, 255, 255])

# Biru ember (drum)
BUCKET_LO = np.array([95, 120, 30])
BUCKET_HI = np.array([130, 255, 180])

# Putih (palang qualification gate + frame + dinding kolam)
WHITE_LO = np.array([0, 0, 180])
WHITE_HI = np.array([180, 30, 255])

# ============ Threshold geometri sederhana (pemisah objek sewarna) ============
MIN_AREA_BLOB = 100      # px^2 - kontur minimum umum
MIN_AREA_POST = 50       # px^2 - tiang tipis minimum
MIN_AREA_BAR = 50        # px^2 - palang minimum
POST_ASPECT_MIN = 1.5    # h/w minimum untuk objek vertikal (tiang/flare)
BAR_ASPECT_MAX = 0.8     # h/w maksimum untuk objek horizontal (palang)
BUCKET_ASPECT_MAX = 1.4  # h/w maksimum untuk ember (silinder pendek-lebar)
FLARE_ASPECT_MIN = 2.5   # h/w minimum untuk flare (tiang tinggi-tipis)
GAP_MIN_PX = 30          # jarak horizontal minimum antar tiang gate


class CameraSimSauvc(Node):
    def __init__(self):
        super().__init__('camera_sim_sauvc')
        self.bridge = CvBridge()
        self.sub = self.create_subscription(Image, '/camera/image_raw', self.image_callback, 10)

        self.pub_gate_main = self.create_publisher(OrcaVision, '/vision/gate_main', 10)
        self.pub_gate_qual = self.create_publisher(OrcaVision, '/vision/gate_qualification', 10)
        self.pub_bucket_blue = self.create_publisher(OrcaVision, '/vision/bucket_blue', 10)
        self.pub_bucket_red = self.create_publisher(OrcaVision, '/vision/bucket_red', 10)
        self.pub_flare_orange = self.create_publisher(OrcaVision, '/vision/flare_orange', 10)
        self.pub_flare_yellow = self.create_publisher(OrcaVision, '/vision/flare_yellow', 10)
        self.pub_flare_red = self.create_publisher(OrcaVision, '/vision/flare_red', 10)
        self.pub_flare_blue = self.create_publisher(OrcaVision, '/vision/flare_blue', 10)
        self.pub_surfacing = self.create_publisher(OrcaVision, '/vision/surfacing_square', 10)

        self.get_logger().info("Camera SAUVC SIM Node Started")

    # ================= Helper =================
    def _empty_msg(self, class_name):
        msg = OrcaVision()
        msg.detected = False
        msg.class_name = class_name
        msg.confidence = 0.0
        msg.center_x = 0.0
        msg.center_y = 0.0
        msg.center_x_norm = 0.0
        msg.bbox_width = 0.0
        msg.bbox_height = 0.0
        msg.bbox_area_ratio = 0.0
        msg.distance = 0.0
        return msg

    def _fill_msg(self, msg, box, frame_w, frame_h):
        fx, fy, fw, fh = box['x'], box['y'], box['w'], box['h']
        frame_cx = frame_w / 2.0
        frame_cy = frame_h / 2.0
        cx = fx + fw / 2.0
        cy = fy + fh / 2.0
        dx = cx - frame_cx
        dy = cy - frame_cy
        msg.detected = True
        msg.confidence = 1.0
        msg.center_x = float(cx)
        msg.center_y = float(cy)
        msg.center_x_norm = float(dx / (frame_w / 2.0))
        msg.bbox_width = float(fw)
        msg.bbox_height = float(fh)
        msg.bbox_area_ratio = float((fw * fh) / (frame_w * frame_h))
        msg.distance = float(np.sqrt(dx ** 2 + dy ** 2) / np.sqrt(frame_w ** 2 + frame_h ** 2))
        return msg, (int(cx), int(cy)), (int(dx), int(dy))

    def _clean(self, mask, k=5):
        kernel = np.ones((k, k), np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
        return mask

    def _merge(self, mask):
        kernel = np.ones((7, 7), np.uint8)
        merged = cv2.dilate(mask, kernel, iterations=3)
        merged = cv2.erode(merged, kernel, iterations=3)
        return merged

    def _dilate(self, mask, px=20):
        kernel = np.ones((px, px), np.uint8)
        return cv2.dilate(mask, kernel, iterations=2)

    def _exclude(self, mask, *exclude_masks):
        result = mask.copy()
        for ex in exclude_masks:
            if ex is not None:
                result = cv2.bitwise_and(result, cv2.bitwise_not(self._dilate(ex)))
        return result

    def _contours(self, mask):
        return cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]

    def _boxes(self, mask, min_area=MIN_AREA_BLOB):
        out = []
        for c in self._contours(mask):
            area = cv2.contourArea(c)
            if area < min_area:
                continue
            x, y, w, h = cv2.boundingRect(cv2.convexHull(c))
            out.append({'x': x, 'y': y, 'w': w, 'h': h, 'area': area,
                        'cx': x + w / 2.0, 'cy': y + h / 2.0})
        return out

    def _vertical(self, mask, min_area=MIN_AREA_POST, min_aspect=POST_ASPECT_MIN):
        out = []
        for b in self._boxes(mask, min_area):
            if b['h'] / max(b['w'], 1) >= min_aspect:
                out.append(b)
        return out

    def _horizontal(self, mask, min_area=MIN_AREA_BAR, max_aspect=BAR_ASPECT_MAX):
        out = []
        for b in self._boxes(mask, min_area):
            if b['h'] / max(b['w'], 1) <= max_aspect:
                out.append(b)
        return out

    def _best(self, boxes):
        return max(boxes, key=lambda b: b['area']) if boxes else None

    # ================= Mask warna =================
    def _raw_dark(self, hsv):
        return self._clean(cv2.inRange(hsv, DARK_LO, DARK_HI))

    def _raw_orange(self, hsv):
        return self._clean(cv2.inRange(hsv, ORANGE_LO, ORANGE_HI))

    def _raw_red(self, hsv):
        m1 = cv2.inRange(hsv, RED_LO1, RED_HI1)
        m2 = cv2.inRange(hsv, RED_LO2, RED_HI2)
        return self._clean(cv2.bitwise_or(m1, m2))

    def _raw_yellow(self, hsv):
        return self._clean(cv2.inRange(hsv, YELLOW_LO, YELLOW_HI))

    def _raw_blue_flare(self, hsv):
        return self._clean(cv2.inRange(hsv, BLUE_FLARE_LO, BLUE_FLARE_HI))

    def _raw_bucket_blue(self, hsv):
        return self._clean(cv2.inRange(hsv, BUCKET_LO, BUCKET_HI))

    def _raw_white(self, hsv):
        return self._clean(cv2.inRange(hsv, WHITE_LO, WHITE_HI))

    # ================= Detektor =================
    def _match_gate(self, posts, bars, frame_w, frame_h):
        """Cari pasangan tiang + palang di antaranya. Kembalikan bbox gate."""
        posts = sorted(posts, key=lambda b: b['area'], reverse=True)[:6]
        if len(posts) < 2 or len(bars) < 1:
            return None

        best = None
        best_score = -1
        for i in range(len(posts)):
            for j in range(i + 1, len(posts)):
                left = posts[i] if posts[i]['cx'] <= posts[j]['cx'] else posts[j]
                right = posts[i] if posts[i]['cx'] > posts[j]['cx'] else posts[j]

                gap = right['cx'] - left['cx']
                if gap < GAP_MIN_PX or gap > frame_w * 0.92:
                    continue
                if min(left['h'], right['h']) / max(left['h'], right['h']) < 0.4:
                    continue

                gate_top = min(left['y'], right['y'])
                gate_bottom = max(left['y'] + left['h'], right['y'] + right['h'])
                gate_left = left['x']
                gate_right = right['x'] + right['w']
                gw = gate_right - gate_left
                gh = gate_bottom - gate_top

                matched_bar = None
                for bar in bars:
                    if bar['cy'] > gate_top + gh * 0.4:
                        continue
                    ovl = min(bar['x'] + bar['w'], gate_right) - max(bar['x'], gate_left)
                    if ovl >= gw * 0.35:
                        matched_bar = bar
                        break
                if matched_bar is None:
                    continue

                score = gw * gh / (frame_w * frame_h)
                if score > best_score:
                    best_score = score
                    best = {'x': gate_left, 'y': gate_top, 'w': gw, 'h': gh,
                            'score': score}
        return best

    def _gate_msg(self, gate, class_name, frame_w, frame_h):
        msg = self._empty_msg(class_name)
        if gate is None:
            return msg
        msg, _, _ = self._fill_msg(msg, gate, frame_w, frame_h)
        return msg

    def detect_gate_main(self, hsv, frame_w, frame_h):
        """Gate utama: tiang hitam + palang hitam (stripe merah/hijau diabaikan)."""
        dark = self._merge(self._raw_dark(hsv))  # merge supaya stripe tidak memutus tiang
        posts = self._vertical(dark, min_area=MIN_AREA_POST, min_aspect=POST_ASPECT_MIN)
        bars = self._horizontal(dark, min_area=MIN_AREA_BAR, max_aspect=BAR_ASPECT_MAX)
        gate = self._match_gate(posts, bars, frame_w, frame_h)
        return self._gate_msg(gate, "gate_main", frame_w, frame_h)

    def detect_gate_qualification(self, hsv, frame_w, frame_h):
        """Qualification gate: tiang oranye tipis + palang putih."""
        orange = self._raw_orange(hsv)
        white = self._raw_white(hsv)
        posts = self._vertical(orange, min_area=MIN_AREA_POST, min_aspect=POST_ASPECT_MIN)
        bars = self._horizontal(white, min_area=MIN_AREA_BAR, max_aspect=BAR_ASPECT_MAX)
        gate = self._match_gate(posts, bars, frame_w, frame_h)
        return self._gate_msg(gate, "gate_qualification", frame_w, frame_h)

    def detect_bucket(self, mask, class_name, frame_w, frame_h, exclude=None):
        """Ember: silinder pendek-lebar (aspect <= BUCKET_ASPECT_MAX)."""
        m = self._exclude(mask, exclude) if exclude is not None else mask
        boxes = [b for b in self._boxes(m, MIN_AREA_BLOB)
                 if b['h'] / max(b['w'], 1) <= BUCKET_ASPECT_MAX]
        best = self._best(boxes)
        msg = self._empty_msg(class_name)
        if best is None:
            return msg
        msg, _, _ = self._fill_msg(msg, best, frame_w, frame_h)
        return msg

    def detect_flare(self, mask, class_name, frame_w, frame_h, exclude=None):
        """Flare: tiang tinggi-tipis (aspect >= FLARE_ASPECT_MIN)."""
        m = self._exclude(mask, exclude) if exclude is not None else mask
        boxes = [b for b in self._vertical(m, MIN_AREA_POST, FLARE_ASPECT_MIN)]
        best = self._best(boxes)
        msg = self._empty_msg(class_name)
        if best is None:
            return msg
        msg, _, _ = self._fill_msg(msg, best, frame_w, frame_h)
        return msg

    def detect_flare_orange(self, hsv, frame_w, frame_h):
        """Flare oranye: silinder oranye tebal (lebih gemuk dari tiang gate).
        Dipisah dari tiang qualification gate lewat area lebih besar."""
        orange = self._raw_orange(hsv)
        verts = self._vertical(orange, MIN_AREA_POST, POST_ASPECT_MIN)
        best = self._best(verts)
        msg = self._empty_msg("flare_orange")
        if best is not None and best['area'] >= 4 * MIN_AREA_POST:
            msg, _, _ = self._fill_msg(msg, best, frame_w, frame_h)
        return msg

    def detect_frame(self, hsv, class_name, frame_w, frame_h):
        """Frame putih (surfacing_square).
        CATATAN: dinding kolam juga putih, jadi deteksi ini kasar dan perlu tuning."""
        white = self._raw_white(hsv)
        boxes = self._boxes(white, MIN_AREA_BLOB)
        best = self._best(boxes)
        msg = self._empty_msg(class_name)
        if best is None:
            return msg
        msg, _, _ = self._fill_msg(msg, best, frame_w, frame_h)
        return msg

    # ================= Anotasi =================
    def _annotate(self, frame, msg, color, label, y_pos):
        if msg.detected:
            x = int(msg.center_x - msg.bbox_width / 2.0)
            y = int(msg.center_y - msg.bbox_height / 2.0)
            w = int(msg.bbox_width)
            h = int(msg.bbox_height)
            cv2.rectangle(frame, (x, y), (x + w, y + h), color, 2)
            cv2.circle(frame, (int(msg.center_x), int(msg.center_y)), 5, (0, 0, 255), -1)
            cv2.putText(frame, label, (x, max(y - 6, 12)),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.45, color, 1)
        else:
            cv2.putText(frame, label + " -", (10, y_pos),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.45, color, 1)

    # ================= Callback =================
    def image_callback(self, msg):
        frame = self.bridge.imgmsg_to_cv2(msg, 'bgr8')
        h, w, _ = frame.shape
        frame_cx = w / 2.0
        frame_cy = h / 2.0
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        cv2.circle(frame, (int(frame_cx), int(frame_cy)), 6, (0, 255, 255), -1)

        # 1. Gate utama
        msg_gate_main = self.detect_gate_main(hsv, w, h)

        # 2. Qualification gate
        msg_gate_qual = self.detect_gate_qualification(hsv, w, h)

        # 3. Ember biru
        msg_bucket_blue = self.detect_bucket(self._raw_bucket_blue(hsv), "bucket_blue", w, h,
                                             exclude=self._raw_blue_flare(hsv))

        # 4. Ember merah
        msg_bucket_red = self.detect_bucket(self._raw_red(hsv), "bucket_red", w, h)

        # 5. Flare oranye
        msg_flare_orange = self.detect_flare_orange(hsv, w, h)

        # 6. Flare kuning
        msg_flare_yellow = self.detect_flare(self._raw_yellow(hsv), "flare_yellow", w, h)

        # 7. Flare merah
        msg_flare_red = self.detect_flare(self._raw_red(hsv), "flare_red", w, h)

        # 8. Flare biru
        msg_flare_blue = self.detect_flare(self._raw_blue_flare(hsv), "flare_blue", w, h)

        # 9. Surfacing square
        msg_surfacing = self.detect_frame(hsv, "surfacing_square", w, h)

        # Publish
        self.pub_gate_main.publish(msg_gate_main)
        self.pub_gate_qual.publish(msg_gate_qual)
        self.pub_bucket_blue.publish(msg_bucket_blue)
        self.pub_bucket_red.publish(msg_bucket_red)
        self.pub_flare_orange.publish(msg_flare_orange)
        self.pub_flare_yellow.publish(msg_flare_yellow)
        self.pub_flare_red.publish(msg_flare_red)
        self.pub_flare_blue.publish(msg_flare_blue)
        self.pub_surfacing.publish(msg_surfacing)

        # Anotasi
        self._annotate(frame, msg_gate_main, (0, 255, 0), "GATE", 25)
        self._annotate(frame, msg_gate_qual, (0, 165, 255), "Q-GATE", 45)
        self._annotate(frame, msg_bucket_blue, (255, 180, 0), "BKT-B", 65)
        self._annotate(frame, msg_bucket_red, (0, 0, 200), "BKT-R", 85)
        self._annotate(frame, msg_flare_orange, (0, 165, 255), "FLR-O", 105)
        self._annotate(frame, msg_flare_yellow, (0, 220, 220), "FLR-Y", 125)
        self._annotate(frame, msg_flare_red, (0, 0, 220), "FLR-R", 145)
        self._annotate(frame, msg_flare_blue, (220, 100, 0), "FLR-B", 165)
        self._annotate(frame, msg_surfacing, (200, 200, 200), "SURF", 185)

        cv2.imshow("SAUVC Detection", frame)
        cv2.waitKey(1)


def main(args=None):
    rclpy.init(args=args)
    node = CameraSimSauvc()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
