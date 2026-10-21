#!/usr/bin/env python3
import math
import rclpy
from orca_msgs.msg import OrcaAttitude
from pymavlink import mavutil
from rclpy.node import Node

class AttitudeNode(Node):
    def __init__(self):
        super().__init__('attitude_node')

        self.publisher_ = self.create_publisher(OrcaAttitude, '/sensor/attitude', 10)
        self.master = mavutil.mavlink_connection('udpin:0.0.0.0:14553')
        self.master.wait_heartbeat()
        self.get_logger().info(f'Pixhawk attitude stream connected via {self.mavlink_url}')

        self.master.mav.request_data_stream_send(
            self.master.target_system,
            self.master.target_component,
            mavutil.mavlink.MAV_DATA_STREAM_EXTRA1,
            50,
            1,
        )

        self.initial_heading = None
        self.last_log_time = 0.0
        self.create_timer(0.02, self.poll_mavlink)

    @staticmethod
    def wrap_angle_deg(angle):
        return (angle + 180) % 360 - 180

    def poll_mavlink(self):
        while True:
            msg = self.master.recv_match(type='ATTITUDE', blocking=False)
            if msg is None:
                break

            raw_yaw = float(math.degrees(msg.yaw))

            if self.initial_heading is None:
                self.initial_heading = raw_yaw

            relative_yaw = raw_yaw - self.initial_heading
            relative_yaw = self.wrap_angle_deg(relative_yaw)

            out = OrcaAttitude()
            out.roll_deg = float(math.degrees(msg.roll))
            out.pitch_deg = float(math.degrees(msg.pitch))
            out.yaw_deg = raw_yaw
            out.initial_deg = relative_yaw
            out.rollspeed_deg_s = float(math.degrees(msg.rollspeed))
            out.pitchspeed_deg_s = float(math.degrees(msg.pitchspeed))
            out.yawspeed_deg_s = float(math.degrees(msg.yawspeed))

            self.publisher_.publish(out)

            now = self.get_clock().now().nanoseconds * 1e-9
            if now - self.last_log_time > 1.0:
                self.get_logger().info(f"""
                \n Initial heading: {out.initial_deg:.2f} deg
                \n Roll: {out.roll_deg:.2f} deg
                \n Pitch: {out.pitch_deg:.2f} deg
                \n Yaw: {out.yaw_deg:.2f} deg
                """)
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