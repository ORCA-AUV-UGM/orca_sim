#!/usr/bin/env python3
import rclpy
import time
from enum import Enum
from rclpy.node import Node
from std_msgs.msg import String
from orca_msgs_sim.msg import OrcaAttitude, OrcaControl, OrcaDepth, OrcaProximity

class State(str, Enum):
    WAIT_ARM = 'WAIT_ARM'
    INIT = 'INIT'
    DIVE = 'DIVE'
    HOLD = 'HOLD'
    FORWARD_1 = 'FORWARD_1'
    STOP_1 = 'STOP_1'
    UTURN = 'UTURN'
    FORWARD_2 = 'FORWARD_2'
    STOP_2 = 'STOP_2'
    SURFACE = 'SURFACE'
    RESET_MISSION = 'RESET_MISSION'

class QualificationTsSim(Node):
    def __init__(self):
        super().__init__('qualification_ts_sim')

        self.target_depth = 0.65
        self.neutral = 1500
        self.forward_fast = 1850
        self.throttle_down = 1350
        self.throttle_up = 1600

        self.state = State.WAIT_ARM
        self.state_since = time.time()
        self.depth = None
        self.yaw = None
        self.is_armed = False
        self.initial_heading = None

        self.control_pub = self.create_publisher(OrcaControl, '/auto/control', 10)
        self.state_pub = self.create_publisher(String, '/mission/state', 10)

        self.create_subscription(OrcaDepth, '/sensor/depth', self.depth_cb, 10)
        self.create_subscription(OrcaAttitude, '/sensor/attitude', self.attitude_cb, 10)
        self.create_subscription(OrcaProximity, '/start_trigger', self.proximity_cb,10)

        self.create_timer(0.1, self.update)
        self.get_logger().info("MISSION READY — waiting for proximity trigger")

    def depth_cb(self, msg: OrcaDepth):
        self.depth = msg.depth

    def attitude_cb(self, msg: OrcaAttitude):
        self.yaw = msg.yaw_deg
        self.roll = msg.roll_deg
        self.pitch = msg.pitch_deg
        self.initial_heading = msg.initial_heading

    def proximity_cb(self, msg: OrcaProximity):
        prev = self.is_armed
        self.is_armed = msg.triggered
        if self.is_armed and not prev:
            self.get_logger().info("PROXIMITY ON → arm & start mission")
        if not self.is_armed and prev:
            self.get_logger().warn("PROXIMITY OFF → disarm & reset mission")

    def publish(self, throttle=None, forward=None, yaw=None, mode='ALT_HOLD'):
        msg = OrcaControl()
        msg.throttle = int(self.neutral if throttle is None else throttle)
        msg.forward = int(self.neutral if forward  is None else forward)
        msg.lateral = int(self.neutral)
        msg.yaw = int(self.neutral if yaw is None else yaw)
        msg.control_mode = mode
        msg.arm_mode = 'arm' if self.is_armed else 'disarm'
        msg.source = 'auto'
        self.control_pub.publish(msg)

    def set_state(self, s: State):
        self.state = s
        self.state_since = time.time()
        self.get_logger().info(f"STATE → {s}")
        msg = String(); msg.data = str(s)
        self.state_pub.publish(msg)

    def reset_vars(self):
        self.initial_heading = None
        self.get_logger().info("Mission variables reset")

    def elapsed(self):
        return time.time() - self.state_since

    def update(self):
        if not self.is_armed and self.state not in (State.WAIT_ARM, State.RESET_MISSION):
            self.reset_vars()
            self.set_state(State.WAIT_ARM)
            self.publish(mode='MANUAL')
            return

        if self.state == State.WAIT_ARM:
            self.publish(mode='MANUAL')
            if self.is_armed:
                self.set_state(State.INIT)
            return

        if self.state == State.INIT:
            if self.depth is not None:
                self.set_state(State.DIVE)
            return

        if self.state == State.DIVE:
            self.publish(throttle=self.throttle_down, mode='MANUAL')
            if self.depth > self.target_depth:
                self.set_state(State.HOLD)
            return

        if self.state == State.HOLD:
            self.publish()
            if self.elapsed() > 4.0:
                self.set_state(State.FORWARD_1)
            return

        if self.state == State.FORWARD_1:
            self.publish(forward=self.forward_fast)
            if self.elapsed() > 20.0:
                self.set_state(State.STOP_1)
            return

        if self.state == State.STOP_1:
            self.publish()
            if self.elapsed() > 1.0:
                self.set_state(State.UTURN)
            return

        if self.state == State.UTURN:
            if self.initial_heading is None:
                return
            if self.initial_heading > 170:
                self.get_logger().info("U-turn selesai → FORWARD_2")
                self.publish()
                self.set_state(State.FORWARD_2)
                return
            self.publish(yaw=1650)
            return

        if self.state == State.FORWARD_2:
            self.publish(forward=self.forward_fast)
            if self.elapsed() > 10.0:
                self.set_state(State.STOP_2)
            return

        if self.state == State.STOP_2:
            self.publish()
            if self.elapsed() > 1.0:
                self.set_state(State.SURFACE)
            return

        if self.state == State.SURFACE:
            if self.elapsed() > 1.0:
                self.set_state(State.RESET_MISSION)
                return
            self.publish(throttle=self.throttle_up, mode='MANUAL')
            return

        if self.state == State.RESET_MISSION:
            self.publish(mode='MANUAL')
            if not self.is_armed:
                self.get_logger().info("PROXIMITY OFF → mission reset → WAIT_ARM")
                self.reset_vars()
                self.set_state(State.WAIT_ARM)
            else:
                self.get_logger().info(
                    "MISSION COMPLETE — ketuk proximity untuk reset",
                    throttle_duration_sec=5
                )
            return

def main():
    rclpy.init()
    node = QualificationTsSim()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()