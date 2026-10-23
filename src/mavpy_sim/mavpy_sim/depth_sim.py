#!/usr/bin/env python3
import random
import rclpy
from geometry_msgs.msg import Pose
from orca_msgs_sim.msg import OrcaDepth
from rclpy.node import Node
from rclpy.qos import qos_profile_sensor_data

class DepthSim(Node):
    def __init__(self):
        super().__init__('depth_sim')

        self.surface_z = -0.0862
        self.last_z = 0.0
        self.last_pose_time = 0.0
        self.last_log_time = 0.0
        self.noise_std = 0.0
        self.got_first_pose = False

        self.create_subscription(Pose, '/model/ORCA_V3/pose', self.pose_cb, qos_profile_sensor_data)
        self.depth_pub = self.create_publisher(OrcaDepth, '/sensor/depth', 10)
        self.create_timer(0.05, self.publish_depth)

        self.get_logger().info(f'Node depth_sim aktif: /model/ORCA_V3/pose -> /sensor/depth')

    def now_sec(self) -> float:
        return self.get_clock().now().nanoseconds * 1e-9

    def pose_cb(self, msg: Pose):
        self.last_z = float(msg.position.z)
        self.last_pose_time = self.now_sec()

        if not self.got_first_pose:
            self.got_first_pose = True
            self.get_logger().info(f'Pose pertama diterima, z model = {self.last_z:.3f} m')

    def compute_depth(self, z_model: float) -> float:
        depth = self.surface_z - z_model
        if self.noise_std > 0.0:
            depth += random.gauss(0.0, self.noise_std)
        if depth < 0.0:
            depth = 0.0
        return depth

    def publish_depth(self):
        if self.last_z is None:
            self.get_logger().warn(f'Menunggu pose di topic /model/ORCA_V3/pose Gazebo', throttle_duration_sec=5.0)
            return

        depth_m = self.compute_depth(self.last_z)
        pressure_mbar = 1013.25 + (1000 * 9.8 * depth_m) / 100

        msg = OrcaDepth()
        msg.depth = float(depth_m)
        msg.pressure = float(pressure_mbar)
        self.depth_pub.publish(msg)

        if self.now_sec() - self.last_pose_time > 1.0:
            self.get_logger().warn('Pose Gazebo tidak diperbarui!', throttle_duration_sec=5.0)
            return
        
        if self.now_sec() - self.last_log_time > 1.0:
            self.get_logger().info(f'\nDepth: {msg.depth} m | Pressure: {msg.pressure} mbar')
            self.last_log_time = self.now_sec()

def main(args=None):
    rclpy.init(args=args)
    node = DepthSim()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()