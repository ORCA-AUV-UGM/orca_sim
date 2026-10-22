#!/usr/bin/env python3
import time
import rclpy
from enum import Enum
from rclpy.node import Node
from std_msgs.msg import String
from orca_msgs_sim.msg import OrcaAttitude, OrcaControl, OrcaDepth, OrcaVision, FlareSequence

class State(str, Enum):
    WAIT_ARM          = 'WAIT_ARM'
    INIT              = 'INIT'
    DIVE              = 'DIVE'
    HOLD              = 'HOLD'

    APPROACH_OBSTACLE = 'APPROACH_OBSTACLE'
    OBSTACLE_DETECT   = 'OBSTACLE_DETECT'
    AVOID_OBSTACLE    = 'AVOID_OBSTACLE'

    GATE_SEARCH       = 'GATE_SEARCH'
    FLARE_AVOID       = 'FLARE_AVOID'
    GATE_ALIGN        = 'GATE_ALIGN'

    BUCKET_SEARCH     = 'BUCKET_SEARCH'
    BUCKET_LATERAL    = 'BUCKET_LATERAL'
    BUCKET_APPROACH   = 'BUCKET_APPROACH'
    BUCKET_HOLD       = 'BUCKET_HOLD'

    UTURN             = 'UTURN'
    RETURN_TO_INIT    = 'RETURN_TO_INIT'
    GATE_SEARCH_2     = 'GATE_SEARCH_2'
    GATE_ALIGN_2      = 'GATE_ALIGN_2'

    FLARE_SEARCH      = 'FLARE_SEARCH'
    FLARE_ALIGN       = 'FLARE_ALIGN'
    FLARE_HIT         = 'FLARE_HIT'
    RETURN_INITIAL    = 'RETURN_INITIAL'

    STOP              = 'STOP'
    SURFACE           = 'SURFACE'
    END               = 'END'

class FinalSim(Node):
    def __init__(self):
        super().__init__('final_sim')

        self.target_depth   = 0.8
        self.neutral        = 1500
        self.forward_fast   = 1800
        self.forward_slow   = 1600
        self.forward_crawl  = 1550
        self.throttle_down  = 1350
        self.throttle_up    = 1650
        self.lateral_avoid  = 1650

        self.yaw_kp   = 6.0
        self.yaw_dead = 5.0

        self.pos_x = 0.0 
        self.pos_y = 0.0
        self.pos_z = 0.0

        self.return_x_threshold = 0.3
        self.return_y_kp   = 80.0
        self.return_y_dead = 0.15

        self.obstacle_detect_min_confidence = 0.6
        self.obstacle_detected              = False
        self.obstacle_cx_norm               = 0.0
        self.obstacle_area_ratio            = 0.0
        self.last_obstacle_seen_time        = 0.0
        self.avoid_direction                = 1
        self.obstacle_distance              = None

        self.gate_detect_min_confidence = 0.6
        self.gate_lateral_kp            = 300.0
        self.gate_lateral_dead          = 0.08
        self.last_gate_seen_time        = 0.0
        self.gate_detected              = False
        self.gate_cx_norm               = 0.0
        self.gate_confidence            = 0.0

        self.flare_detect_min_confidence = 0.6
        self.flare_avoid_direction       = 1

        self.red_detected        = False
        self.red_cx_norm         = 0.0
        self.last_red_seen_time  = 0.0

        self.yellow_detected        = False
        self.yellow_cx_norm         = 0.0
        self.last_yellow_seen_time  = 0.0

        self.blue_detected        = False
        self.blue_cx_norm         = 0.0
        self.last_blue_seen_time  = 0.0

        self.bucket_detect_min_confidence = 0.5
        self.bucket_lateral_kp            = 250.0
        self.bucket_lateral_dead          = 0.06
        self.bucket_area_threshold        = 0.22
        self.bucket_detected              = False
        self.bucket_cx_norm               = 0.0
        self.bucket_area_ratio            = 0.0
        self.last_bucket_seen_time        = 0.0

        self.flare_sequence     = []
        self.flare_index        = 0
        self.flare_hit_count    = 0
        self.flare_search_yaw   = 90
        self.flare_lateral_kp   = 250.0
        self.flare_lateral_dead = 0.08
        self.target_cx_norm     = 0.0
        self.target_detected    = False

        self.control_pub = self.create_publisher(OrcaControl, '/control/auto',     10)
        self.state_pub   = self.create_publisher(String,      '/mission/state',     10)
        self.flare_ack   = self.create_publisher(String,      '/mission/flare_ack', 10)

        self.create_subscription(OrcaDepth,     '/sensor/depth',            self.depth_cb,    10)
        self.create_subscription(OrcaAttitude,  '/sensor/attitude',         self.attitude_cb, 10)
        self.create_subscription(OrcaVision,    '/vision/orange_flare', self.obstacle_cb, 10)
        self.create_subscription(OrcaVision,    '/vision/gate_final',   self.gate_cb,     10)
        self.create_subscription(OrcaVision,    '/vision/red_flare',    self.red_cb,      10)
        self.create_subscription(OrcaVision,    '/vision/yellow_flare', self.yellow_cb,   10)
        self.create_subscription(OrcaVision,    '/vision/blue_flare',   self.blue_cb,     10)
        self.create_subscription(OrcaVision,    '/vision/bucket_blue',  self.bucket_cb,   10)
        self.create_subscription(FlareSequence, '/mission/flare_sequence',  self.seq_cb,      10)

        self.state       = State.WAIT_ARM
        self.state_since = time.time()
        self.arm_sent    = False
        self.disarm_sent = False
        self.depth       = None
        self.yaw         = None

        self.create_timer(0.1, self.update)
        self.get_logger().info("FINAL MISSION START")

    def depth_cb(self, msg):
        self.depth = msg.depth

    def attitude_cb(self, msg):
        self.yaw   = msg.initial_deg 
        self.pos_x = msg.initial_x   
        self.pos_y = msg.initial_y
        self.pos_z = msg.initial_z

    def obstacle_cb(self, msg: OrcaVision):
        if msg.detected and msg.confidence >= self.obstacle_detect_min_confidence:
            self.obstacle_detected       = True
            self.obstacle_cx_norm        = msg.center_x_norm
            self.obstacle_area_ratio     = msg.bbox_area_ratio
            self.obstacle_distance       = msg.distance
            self.last_obstacle_seen_time = time.time()
        else:
            self.obstacle_detected = False

    def gate_cb(self, msg: OrcaVision):
        if msg.detected and msg.confidence >= self.gate_detect_min_confidence:
            self.gate_detected       = True
            self.gate_cx_norm        = msg.center_x_norm
            self.gate_confidence     = msg.confidence
            self.last_gate_seen_time = time.time()
        else:
            self.gate_detected = False

    def red_cb(self, msg: OrcaVision):
        if msg.detected and msg.confidence >= self.flare_detect_min_confidence:
            self.red_detected       = True
            self.red_cx_norm        = msg.center_x_norm
            self.last_red_seen_time = time.time()
        else:
            self.red_detected = False

    def yellow_cb(self, msg: OrcaVision):
        if msg.detected and msg.confidence >= self.flare_detect_min_confidence:
            self.yellow_detected       = True
            self.yellow_cx_norm        = msg.center_x_norm
            self.last_yellow_seen_time = time.time()
        else:
            self.yellow_detected = False

    def blue_cb(self, msg: OrcaVision):
        if msg.detected and msg.confidence >= self.flare_detect_min_confidence:
            self.blue_detected       = True
            self.blue_cx_norm        = msg.center_x_norm
            self.last_blue_seen_time = time.time()
        else:
            self.blue_detected = False

    def bucket_cb(self, msg: OrcaVision):
        if msg.detected and msg.confidence >= self.bucket_detect_min_confidence:
            self.bucket_detected       = True
            self.bucket_cx_norm        = msg.center_x_norm
            self.bucket_area_ratio     = msg.bbox_area_ratio
            self.last_bucket_seen_time = time.time()
        else:
            self.bucket_detected = False

    def seq_cb(self, msg: FlareSequence):
        seq = msg.sequence.strip().lower()
        if seq and list(seq) != self.flare_sequence:
            self.flare_sequence  = list(seq)
            self.flare_index     = 0
            self.flare_hit_count = 0
            self.get_logger().info(f"[SEQ] Flare sequence: {seq.upper()}")

    def _any_avoid_flare(self):
        now = time.time()
        return (
            (self.red_detected    and now - self.last_red_seen_time    < 0.3) or
            (self.yellow_detected and now - self.last_yellow_seen_time < 0.3) or
            (self.blue_detected   and now - self.last_blue_seen_time   < 0.3)
        )

    def _avoid_flare_cx(self):
        now = time.time()
        if self.red_detected    and now - self.last_red_seen_time    < 0.3: return self.red_cx_norm
        if self.yellow_detected and now - self.last_yellow_seen_time < 0.3: return self.yellow_cx_norm
        if self.blue_detected   and now - self.last_blue_seen_time   < 0.3: return self.blue_cx_norm
        return 0.0

    def _current_target_color(self):
        if self.flare_index < len(self.flare_sequence):
            return self.flare_sequence[self.flare_index]
        return None

    def _update_target(self):
        color = self._current_target_color()
        now   = time.time()
        if color == 'r':
            self.target_detected = self.red_detected    and now - self.last_red_seen_time    < 0.5
            self.target_cx_norm  = self.red_cx_norm
        elif color == 'y':
            self.target_detected = self.yellow_detected and now - self.last_yellow_seen_time < 0.5
            self.target_cx_norm  = self.yellow_cx_norm
        elif color == 'b':
            self.target_detected = self.blue_detected   and now - self.last_blue_seen_time   < 0.5
            self.target_cx_norm  = self.blue_cx_norm
        else:
            self.target_detected = False
            self.target_cx_norm  = 0.0

    def _bucket_fresh(self):
        return self.bucket_detected and (time.time() - self.last_bucket_seen_time < 0.5)

    def publish(self, throttle=None, forward=None, lateral=None, yaw=None, mode='ALT_HOLD'):
        msg = OrcaControl()
        msg.throttle     = int(self.neutral if throttle is None else throttle)
        msg.forward      = int(self.neutral if forward  is None else forward)
        msg.lateral      = int(self.neutral if lateral  is None else lateral)
        msg.yaw          = int(self.neutral if yaw      is None else yaw)
        msg.control_mode = mode
        msg.arm_mode     = 'arm'
        msg.source       = 'auto'
        self.control_pub.publish(msg)

    def set_state(self, s):
        self.state       = s
        self.state_since = time.time()
        self.get_logger().info(f"STATE -> {s}")
        msg      = String()
        msg.data = str(s)
        self.state_pub.publish(msg)

    def elapsed(self):
        return time.time() - self.state_since

    def avoid_lateral_cmd(self):
        return int(self.lateral_avoid if self.avoid_direction > 0 else (3000 - self.lateral_avoid))

    def flare_avoid_lateral_cmd(self):
        return int(self.lateral_avoid if self.flare_avoid_direction > 0 else (3000 - self.lateral_avoid))

    def gate_lateral_cmd(self):
        cx = self.gate_cx_norm
        if abs(cx) < self.gate_lateral_dead: return self.neutral
        return max(1300, min(1700, self.neutral + int(self.gate_lateral_kp * cx)))

    def bucket_lateral_cmd(self):
        cx = self.bucket_cx_norm
        if abs(cx) < self.bucket_lateral_dead: return self.neutral
        return max(1300, min(1700, self.neutral + int(self.bucket_lateral_kp * cx)))

    def target_lateral_cmd(self):
        cx = self.target_cx_norm
        if abs(cx) < self.flare_lateral_dead: return self.neutral
        return max(1300, min(1700, self.neutral + int(self.flare_lateral_kp * cx)))

    def yaw_cmd(self, target_yaw=0.0):
        if self.yaw is None: return self.neutral
        err = target_yaw - self.yaw
        while err >  180: err -= 360
        while err < -180: err += 360
        if abs(err) < self.yaw_dead: return self.neutral
        return max(1300, min(1700, self.neutral + int(self.yaw_kp * err)))

    def _yaw_reached(self, target_yaw, tol=20):
        if self.yaw is None: return False
        err = target_yaw - self.yaw
        while err >  180: err -= 360
        while err < -180: err += 360
        return abs(err) < tol

    def return_y_lateral_cmd(self):
        err = self.pos_y   # target pos_y = 0
        if abs(err) < self.return_y_dead: return self.neutral
        cmd = self.neutral - int(self.return_y_kp * err)
        return max(1300, min(1700, cmd))

    def _send_ack(self, color):
        msg      = String()
        msg.data = color.upper()
        self.flare_ack.publish(msg)
        self.get_logger().info(f"[ACK] Flare {color.upper()} tertabrak")

    # ═══════════════════════════════════════════════════════
    # MAIN LOOP
    # ═══════════════════════════════════════════════════════
    def update(self):
        now = time.time()

        # ── WAIT ARM ─────────────────────────────────────────
        if self.state == State.WAIT_ARM:
            self.publish()
            if not self.arm_sent and self.elapsed() > 5:
                self.arm_sent = True
                self.get_logger().info("ARM READY")
                self.set_state(State.INIT)
            return

        # ── INIT ─────────────────────────────────────────────
        if self.state == State.INIT:
            if self.depth is not None:
                self.set_state(State.DIVE)
            return

        # ── DIVE ─────────────────────────────────────────────
        if self.state == State.DIVE:
            if self.depth < self.target_depth:
                self.publish(throttle=self.throttle_down)
            else:
                self.set_state(State.HOLD)
            return

        # ── HOLD ─────────────────────────────────────────────
        if self.state == State.HOLD:
            self.publish()
            if self.elapsed() > 1:
                self.set_state(State.APPROACH_OBSTACLE)
            return

        # ── APPROACH OBSTACLE ────────────────────────────────
        if self.state == State.APPROACH_OBSTACLE:
            self.publish(forward=self.forward_fast)
            if self.obstacle_detected and self.obstacle_distance is not None and self.obstacle_distance < 2:
                self.get_logger().info("Obstacle detected → OBSTACLE_DETECT")
                self.set_state(State.OBSTACLE_DETECT)
                return
            if self.elapsed() > 20:
                self.get_logger().warn("Obstacle not found → GATE_SEARCH")
                self.set_state(State.GATE_SEARCH)
            return

        # ── OBSTACLE DETECT ──────────────────────────────────
        if self.state == State.OBSTACLE_DETECT:
            self.publish()
            if self.elapsed() > 0.5:
                if self.obstacle_cx_norm >= 0:
                    self.avoid_direction = -1
                    self.get_logger().info("Obstacle RIGHT → lateral LEFT")
                else:
                    self.avoid_direction = 1
                    self.get_logger().info("Obstacle LEFT → lateral RIGHT")
                self.set_state(State.AVOID_OBSTACLE)
            return

        # ── AVOID OBSTACLE ───────────────────────────────────
        if self.state == State.AVOID_OBSTACLE:
            self.publish(lateral=self.avoid_lateral_cmd())
            if self.elapsed() > 1:
                self.set_state(State.GATE_SEARCH)
            return

        # ── GATE SEARCH ──────────────────────────────────────
        if self.state == State.GATE_SEARCH:
            self.publish(forward=self.forward_fast, yaw=self.yaw_cmd(0))
            if self._any_avoid_flare():
                cx = self._avoid_flare_cx()
                self.flare_avoid_direction = -1 if cx >= 0 else 1
                self.set_state(State.FLARE_AVOID)
                return
            if self.gate_detected and (now - self.last_gate_seen_time < 0.5):
                self.set_state(State.GATE_ALIGN)
                return
            if self.elapsed() > 40:
                self.get_logger().warn("Gate timeout → STOP")
                self.set_state(State.STOP)
            return

        # ── FLARE AVOID (saat cari gate) ─────────────────────
        if self.state == State.FLARE_AVOID:
            self.publish(
                forward=self.forward_slow,
                lateral=self.flare_avoid_lateral_cmd(),
                yaw=self.yaw_cmd(0)
            )
            if not self._any_avoid_flare() or self.elapsed() > 1.5:
                self.set_state(State.GATE_SEARCH)
            return

        # ── GATE ALIGN ───────────────────────────────────────
        if self.state == State.GATE_ALIGN:
            if self.gate_detected:
                self.publish(
                    forward=self.forward_slow,
                    lateral=self.gate_lateral_cmd(),
                    yaw=self.yaw_cmd(0)
                )
            else:
                self.publish(forward=self.forward_fast, yaw=self.yaw_cmd(0))
                if now - self.last_gate_seen_time > 3:
                    self.get_logger().info("Gate passed → BUCKET_SEARCH")
                    self.set_state(State.BUCKET_SEARCH)
            return

        # ── BUCKET SEARCH ─────────────────────────────────────
        if self.state == State.BUCKET_SEARCH:
            self.publish(forward=self.forward_slow, yaw=self.yaw_cmd(0))
            if self._bucket_fresh():
                self.get_logger().info("Bucket found → BUCKET_APPROACH")
                self.set_state(State.BUCKET_APPROACH)
                return
            if self.elapsed() > 10:
                self.get_logger().warn("Bucket timeout → UTURN")
                self.set_state(State.UTURN)
            return

        # ── BUCKET LATERAL ────────────────────────────────────
        if self.state == State.BUCKET_LATERAL:
            if self._bucket_fresh():
                self.publish(lateral=self.bucket_lateral_cmd(), yaw=self.yaw_cmd(0))
                if abs(self.bucket_cx_norm) < self.bucket_lateral_dead:
                    self.get_logger().info("Bucket centered → BUCKET_APPROACH")
                    self.set_state(State.BUCKET_APPROACH)
                    return
            else:
                self.publish()
                if self.elapsed() > 2.0:
                    self.set_state(State.BUCKET_SEARCH)
                return
            if self.elapsed() > 5:
                self.set_state(State.BUCKET_APPROACH)
            return

        # ── BUCKET APPROACH ───────────────────────────────────
        if self.state == State.BUCKET_APPROACH:
            if self._bucket_fresh():
                self.publish(
                    forward=self.forward_crawl,
                    lateral=self.bucket_lateral_cmd(),
                    yaw=self.yaw_cmd(0)
                )
                if self.bucket_area_ratio >= self.bucket_area_threshold:
                    self.get_logger().info("Bucket in position → BUCKET_HOLD")
                    self.set_state(State.BUCKET_HOLD)
            return

        # ── BUCKET HOLD ───────────────────────────────────────
        if self.state == State.BUCKET_HOLD:
            self.publish(lateral=self.bucket_lateral_cmd(), yaw=self.yaw_cmd(0))
            if self.elapsed() > 5:
                self.get_logger().info("Drop done → UTURN")
                self.set_state(State.UTURN)
            return

        # ══════════════════════════════════════════════════════
        # FLARE MISSION
        # ══════════════════════════════════════════════════════

        # ── UTURN ─────────────────────────────────────────────
        # Putar ke yaw 180° (balik arah)
        if self.state == State.UTURN:
            self.publish(yaw=self.yaw_cmd(180))

            if not self.flare_sequence:
                self.get_logger().warn("[UTURN] Waiting for flare sequence...")

            if self._yaw_reached(180, tol=20) and self.flare_sequence:
                self.get_logger().info(
                    f"U-turn done (yaw=180°) | pos_x={self.pos_x:.2f} → RETURN_TO_INIT")
                self.set_state(State.RETURN_TO_INIT)
            return

        # ── RETURN TO INIT ────────────────────────────────────
        # Maju sambil heading 180° sampai pos_x ≈ 0 (posisi awal X).
        # Koreksi lateral berdasarkan pos_y agar tidak melenceng.
        if self.state == State.RETURN_TO_INIT:
            lateral = self.return_y_lateral_cmd()
            self.publish(
                forward=self.forward_fast,
                lateral=lateral,
                yaw=self.yaw_cmd(180)
            )

            self.get_logger().debug(
                f"[RETURN_TO_INIT] pos_x={self.pos_x:.2f} pos_y={self.pos_y:.2f} "
                f"lateral={lateral}"
            )

            # Posisi X sudah kembali ke dekat awal (≤ threshold)
            # pos_x akan mendekati 0 saat robot kembali ke titik awal
            if abs(self.pos_x) <= self.return_x_threshold:
                self.get_logger().info(
                    f"Reached initial X (pos_x={self.pos_x:.2f}) → GATE_SEARCH_2")
                self.set_state(State.GATE_SEARCH_2)
                return

            # Timeout fallback: 30 detik
            if self.elapsed() > 30:
                self.get_logger().warn(
                    f"RETURN_TO_INIT timeout (pos_x={self.pos_x:.2f}) → GATE_SEARCH_2")
                self.set_state(State.GATE_SEARCH_2)
            return

        # ── GATE SEARCH 2 ─────────────────────────────────────
        # Cari gate dari arah balik (heading 180°)
        if self.state == State.GATE_SEARCH_2:
            self.publish(forward=self.forward_fast, yaw=self.yaw_cmd(180))
            if self.gate_detected and (now - self.last_gate_seen_time < 0.5):
                self.set_state(State.GATE_ALIGN_2)
                return
            if self.elapsed() > 20:
                self.get_logger().info("Gate not found → FLARE_SEARCH")
                self.flare_search_yaw = 90
                self.set_state(State.FLARE_SEARCH)
            return

        # ── GATE ALIGN 2 ──────────────────────────────────────
        if self.state == State.GATE_ALIGN_2:
            if self.gate_detected:
                self.publish(
                    forward=self.forward_slow,
                    lateral=self.gate_lateral_cmd(),
                    yaw=self.yaw_cmd(180)
                )
            else:
                self.publish(forward=self.forward_fast, yaw=self.yaw_cmd(180))
                if now - self.last_gate_seen_time > 3:
                    self.get_logger().info("Gate passed → FLARE_SEARCH")
                    self.flare_search_yaw = 90
                    self.set_state(State.FLARE_SEARCH)
            return

        # ── FLARE SEARCH ──────────────────────────────────────
        if self.state == State.FLARE_SEARCH:
            color = self._current_target_color()
            if color is None:
                self.get_logger().info("All flares hit → RETURN_INITIAL")
                self.set_state(State.RETURN_INITIAL)
                return

            self._update_target()
            self.publish(
                forward=self.forward_fast,
                yaw=self.yaw_cmd(self.flare_search_yaw)
            )
            self.get_logger().debug(
                f"[FLARE_SEARCH] target={color.upper()} yaw={self.flare_search_yaw}° "
                f"detected={self.target_detected} elapsed={self.elapsed():.1f}s"
            )

            if self.target_detected:
                self.get_logger().info(
                    f"Target flare {color.upper()} detected → FLARE_ALIGN")
                self.set_state(State.FLARE_ALIGN)
                return

            if self.elapsed() > 15:
                self.flare_search_yaw = 270 if self.flare_search_yaw == 90 else 90
                self.get_logger().info(
                    f"Search 15s → switch heading to {self.flare_search_yaw}°")
                self.set_state(State.FLARE_SEARCH)
            return

        # ── FLARE ALIGN ───────────────────────────────────────
        if self.state == State.FLARE_ALIGN:
            self._update_target()
            if self.target_detected:
                self.publish(
                    forward=self.forward_slow,
                    lateral=self.target_lateral_cmd(),
                    yaw=self.yaw_cmd(self.flare_search_yaw)
                )
                if abs(self.target_cx_norm) < self.flare_lateral_dead:
                    self.get_logger().info("Aligned → FLARE_HIT")
                    self.set_state(State.FLARE_HIT)
                    return
            else:
                if self.elapsed() > 1.0:
                    self.get_logger().info("Target lost (very close) → FLARE_HIT")
                    self.set_state(State.FLARE_HIT)
                    return
            if self.elapsed() > 10:
                self.get_logger().warn("FLARE_ALIGN timeout → FLARE_HIT")
                self.set_state(State.FLARE_HIT)
            return

        # ── FLARE HIT ─────────────────────────────────────────
        if self.state == State.FLARE_HIT:
            self.publish(
                forward=self.forward_fast,
                yaw=self.yaw_cmd(self.flare_search_yaw)
            )
            if self.elapsed() > 2:
                color = self._current_target_color()
                if color:
                    self._send_ack(color)
                    self.flare_index     += 1
                    self.flare_hit_count += 1
                if self.flare_index >= len(self.flare_sequence):
                    self.get_logger().info("All flares hit! → RETURN_INITIAL")
                    self.set_state(State.RETURN_INITIAL)
                else:
                    next_c = self.flare_sequence[self.flare_index]
                    self.get_logger().info(
                        f"Hit done → next: {next_c.upper()} → FLARE_SEARCH")
                    self.set_state(State.FLARE_SEARCH)
            return

        # ── RETURN INITIAL ────────────────────────────────────
        # Kembali ke heading 0°
        if self.state == State.RETURN_INITIAL:
            self.publish(yaw=self.yaw_cmd(0))
            if self._yaw_reached(0, tol=20):
                self.get_logger().info("Returned to heading 0° → STOP")
                self.set_state(State.STOP)
            elif self.elapsed() > 10:
                self.get_logger().warn("Return yaw timeout → STOP")
                self.set_state(State.STOP)
            return

        # ── STOP ─────────────────────────────────────────────
        if self.state == State.STOP:
            self.publish()
            if self.elapsed() > 1:
                self.set_state(State.SURFACE)
            return

        # ── SURFACE ──────────────────────────────────────────
        if self.state == State.SURFACE:
            if self.depth is not None and self.depth < 0.1:
                self.set_state(State.END)
                return
            self.publish(throttle=self.throttle_up)
            return

        # ── END ──────────────────────────────────────────────
        if self.state == State.END:
            self.publish()
            if not self.disarm_sent and self.elapsed() > 5:
                self.disarm_sent = True
                self.get_logger().info("MISSION COMPLETE")
            return


def main():
    rclpy.init()
    node = FinalSim()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()