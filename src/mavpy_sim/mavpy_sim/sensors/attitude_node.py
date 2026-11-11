#!/usr/bin/env python3
import math
import rclpy
from orca_msgs_sim.msg import OrcaAttitude
from pymavlink import mavutil
from rclpy.node import Node

class AttitudeNode(Node):
    def __init__(self):
        super().__init__('attitude_node')

        self.publisher_ = self.create_publisher(OrcaAttitude, '/sensor/attitude', 10)

        self.master = mavutil.mavlink_connection('udpin:0.0.0.0:14553')
        self.master.wait_heartbeat()
        self.get_logger().info('Pixhawk connected via udpin:0.0.0.0:14553')

        self.master.mav.request_data_stream_send(
            self.master.target_system,
            self.master.target_component,
            mavutil.mavlink.MAV_DATA_STREAM_EXTRA1,
            50,
            1,
        )

        self.master.mav.request_data_stream_send(
            self.master.target_system,
            self.master.target_component,
            mavutil.mavlink.MAV_DATA_STREAM_POSITION,
            10,
            1,
        )

        self.initial_yaw_deg = None
        self.local_origin = None
        self.latest_local_position = None
        self.last_log_time = 0.0

        self.create_timer(0.02, self.poll_mavlink)

    @staticmethod
    def wrap_angle_deg(angle):
        return (angle + 180.0) % 360.0 - 180.0

    def poll_mavlink(self):
        while True:
            msg = self.master.recv_match(
                type=['ATTITUDE', 'LOCAL_POSITION_NED'],
                blocking=False,
            )
            if msg is None:
                break

            now = self.get_clock().now().nanoseconds * 1e-9

            if msg.get_type() == 'LOCAL_POSITION_NED':
                self.latest_local_position = (
                    float(msg.x),
                    float(msg.y),
                    float(msg.z),
                )

                if self.local_origin is None:
                    self.local_origin = self.latest_local_position
                    self.get_logger().info(
                        'Local position origin set from first '
                        'LOCAL_POSITION_NED message'
                    )
                continue

            raw_yaw_deg = math.degrees(msg.yaw)
            if self.initial_yaw_deg is None:
                self.initial_yaw_deg = raw_yaw_deg

            relative_yaw_deg = self.wrap_angle_deg(raw_yaw_deg - self.initial_yaw_deg)

            out = OrcaAttitude()
            out.roll_deg = math.degrees(msg.roll)
            out.pitch_deg = math.degrees(msg.pitch)
            out.yaw_deg = raw_yaw_deg
            out.initial_heading = relative_yaw_deg
            out.rollspeed_deg_s = math.degrees(msg.rollspeed)
            out.pitchspeed_deg_s = math.degrees(msg.pitchspeed)
            out.yawspeed_deg_s = math.degrees(msg.yawspeed)
            self.publisher_.publish(out)

            if now - self.last_log_time >= 1.0:
                if (
                    self.local_origin is not None
                    and self.latest_local_position is not None
                ):
                    x0, y0, _ = self.local_origin
                    x, y, _ = self.latest_local_position

                    dx = x - x0  # North
                    dy = y - y0  # East
                    distance = math.hypot(dx, dy)

                    self.get_logger().info(
                        f'\nYaw: {raw_yaw_deg:.1f} deg'
                        f'\nInitial Heading: {relative_yaw_deg:.1f} deg'
                        f'\nPosisi lokal x={dx:.2f} m, y={dy:.2f} m'
                    )
                else:
                    self.get_logger().warning('Belum menerima LOCAL_POSITION_NED dari Pixhawk')

                self.last_log_time = now


def main(args=None):
    rclpy.init(args=args)
    node = AttitudeNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()