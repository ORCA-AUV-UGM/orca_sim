#!/usr/bin/env python3
import pygame
import rclpy
from rclpy.node import Node
from orca_msgs_sim.msg import OrcaControl

class Keyboard(Node):
    def __init__(self):
        super().__init__('keyboard')

        self.step_pwm = 10
        self.pwm_min = 1100
        self.pwm_max = 1900

        pygame.init()
        self.screen = pygame.display.set_mode((150, 150))
        pygame.display.set_caption('ORCA Keyboard Control')

        self.publisher_ = self.create_publisher(OrcaControl, '/manual/control', 10)
        self.get_logger().info(
            'Keyboard aktif.\n'
            '- W/S: Forward/Backward\n'
            '- A/D: Lateral Left/Right\n'
            '- ↑/↓: Throttle Up/Down\n'
            '- ←/→: Yaw Left/Right\n'
            '- T/G: Pitch Up/Down\n'
            '- F/H: Roll Left/Right\n'
            '- L:   Gripper Open/Close\n'
            '- J:   Arm/Disarm\n'
            '- K:   Mode MANUAL/DEPTH_HOLD'
        )

        self.axis_pwm = {
            'pitch': 1500,
            'roll': 1500,
            'forward': 1500,
            'lateral': 1500,
            'yaw': 1500,
            'throttle': 1500
        }
        self.axis_dir = {
            'pitch': 0,
            'roll': 0,
            'forward': 0,
            'lateral': 0,
            'yaw': 0,
            'throttle': 0
        }
        self.arm_toggle = 'disarm'
        self.control_modes = ['MANUAL', 'ALT_HOLD']
        self.control_mode_idx = 0

        self.gripper_states = ['close', 'open']
        self.gripper_idx = 0

        self.create_timer(1.0 / max(1.0, 20.0), self.key_callback)

    def key_callback(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                raise KeyboardInterrupt

            if event.type == pygame.KEYDOWN:
                # Gripper control: L = toggle open <-> close
                if event.key == pygame.K_l:
                    self.gripper_idx = 1 - self.gripper_idx
                    self.get_logger().info(f'Gripper: {self.gripper_states[self.gripper_idx].upper()}')

                # System toggles
                elif event.key == pygame.K_j:
                    self.arm_toggle = 'arm' if self.arm_toggle == 'disarm' else 'disarm'
                elif event.key == pygame.K_k:
                    self.control_mode_idx = (self.control_mode_idx + 1) % len(self.control_modes)

                # Movement - Forward/Backward
                elif event.key == pygame.K_w:
                    self.axis_dir['forward'] = 1
                elif event.key == pygame.K_s:
                    self.axis_dir['forward'] = -1

                # Movement - Lateral
                elif event.key == pygame.K_d:
                    self.axis_dir['lateral'] = 1
                elif event.key == pygame.K_a:
                    self.axis_dir['lateral'] = -1

                # Movement - Yaw
                elif event.key == pygame.K_RIGHT:
                    self.axis_dir['yaw'] = 1
                elif event.key == pygame.K_LEFT:
                    self.axis_dir['yaw'] = -1

                # Movement - Throttle
                elif event.key == pygame.K_UP:
                    self.axis_dir['throttle'] = 1
                elif event.key == pygame.K_DOWN:
                    self.axis_dir['throttle'] = -1

                # Movement - Pitch
                elif event.key == pygame.K_t:
                    self.axis_dir['pitch'] = 1
                elif event.key == pygame.K_g:
                    self.axis_dir['pitch'] = -1

                # Movement - Roll
                elif event.key == pygame.K_h:
                    self.axis_dir['roll'] = 1
                elif event.key == pygame.K_f:
                    self.axis_dir['roll'] = -1

            elif event.type == pygame.KEYUP:
                if event.key in [pygame.K_w, pygame.K_s]:
                    self.axis_dir['forward'] = 0
                elif event.key in [pygame.K_a, pygame.K_d]:
                    self.axis_dir['lateral'] = 0
                elif event.key in [pygame.K_LEFT, pygame.K_RIGHT]:
                    self.axis_dir['yaw'] = 0
                elif event.key in [pygame.K_UP, pygame.K_DOWN]:
                    self.axis_dir['throttle'] = 0
                elif event.key in [pygame.K_t, pygame.K_g]:
                    self.axis_dir['pitch'] = 0
                elif event.key in [pygame.K_f, pygame.K_h]:
                    self.axis_dir['roll'] = 0

        self.update_axis_pwm()

        msg = OrcaControl()
        msg.pitch = self.axis_pwm['pitch']
        msg.roll = self.axis_pwm['roll']
        msg.forward = self.axis_pwm['forward']
        msg.lateral = self.axis_pwm['lateral']
        msg.yaw = self.axis_pwm['yaw']
        msg.throttle = self.axis_pwm['throttle']
        msg.arm_mode = self.arm_toggle
        msg.control_mode = self.control_modes[self.control_mode_idx]
        msg.gripper_mode = self.gripper_states[self.gripper_idx]
        msg.source = 'manual_keyboard'
        self.publisher_.publish(msg)

    def update_axis_pwm(self):
        for axis in self.axis_pwm:
            direction = self.axis_dir[axis]
            if direction == 1:
                self.axis_pwm[axis] += self.step_pwm
            elif direction == -1:
                self.axis_pwm[axis] -= self.step_pwm
            else:
                if self.axis_pwm[axis] > 1500:
                    self.axis_pwm[axis] -= self.step_pwm
                elif self.axis_pwm[axis] < 1500:
                    self.axis_pwm[axis] += self.step_pwm
            self.axis_pwm[axis] = max(self.pwm_min, min(self.pwm_max, self.axis_pwm[axis]))

    def destroy_node(self):
        pygame.quit()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = Keyboard()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()