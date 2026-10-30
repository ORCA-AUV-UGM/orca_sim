#!/usr/bin/env python3
import os
import sys
import time
import termios
import tty
import rclpy
from rclpy.node import Node
from orca_msgs_sim.msg import OrcaProximity

TOGGLE_KEY = 'j'
DEBOUNCE_SEC = 0.25
HEARTBEAT_SEC = 0.2

class ProximitySim(Node):
    def __init__(self):
        super().__init__('proximity_sim')

        self.pub = self.create_publisher(OrcaProximity, '/proximity/start_trigger', 10)
        fields = OrcaProximity.get_fields_and_field_types()

        if 'arm_mode' in fields:
            self.field = 'arm_mode'
        elif 'triggered' in fields:
            self.field = 'triggered'
        else:
            raise RuntimeError(
                f"OrcaProximity tidak punya field arm_mode/triggered. Field yang ada: {fields}"
            )

        self.state = False
        self.last_toggle = 0.0
        self.fd = None
        self.old_term = None

        if sys.stdin.isatty():
            self.fd = sys.stdin.fileno()
            self.old_term = termios.tcgetattr(self.fd)
            tty.setcbreak(self.fd)
        else:
            self.get_logger().warn("Keyboard tidak bisa dibaca!")

        self.create_timer(0.05, self.key_cb)
        self.create_timer(HEARTBEAT_SEC, self.publish_state)

        self.publish_state()
        self.get_logger().info(f"PROXIMITY SIM READY — tekan '{TOGGLE_KEY}' untuk toggle | status: OFF")

    def key_cb(self):
        if self.fd is None:
            return
        while self._key_ready():
            ch = os.read(self.fd, 1).decode(errors='ignore')
            if ch.lower() == TOGGLE_KEY:
                self.toggle()

    def _key_ready(self):
        import select
        return bool(select.select([self.fd], [], [], 0)[0])

    def toggle(self):
        now = time.time()
        if now - self.last_toggle < DEBOUNCE_SEC:
            return
        self.last_toggle = now

        self.state = not self.state
        self.publish_state()
        if self.state:
            self.get_logger().info("PROXIMITY ON  → arm")
        else:
            self.get_logger().info("PROXIMITY OFF → disarm")

    def publish_state(self):
        msg = OrcaProximity()
        setattr(msg, self.field, self.state)
        self.pub.publish(msg)

    def restore_terminal(self):
        if self.fd is not None and self.old_term is not None:
            termios.tcsetattr(self.fd, termios.TCSADRAIN, self.old_term)
            self.old_term = None

def main():
    rclpy.init()
    node = ProximitySim()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.restore_terminal()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()