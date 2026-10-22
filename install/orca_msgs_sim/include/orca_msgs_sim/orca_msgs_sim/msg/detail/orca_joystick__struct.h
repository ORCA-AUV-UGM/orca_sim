// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from orca_msgs_sim:msg/OrcaJoystick.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "orca_msgs_sim/msg/orca_joystick.h"


#ifndef ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__STRUCT_H_
#define ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'arm_mode'
// Member 'control_mode'
// Member 'gripper_mode'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/OrcaJoystick in the package orca_msgs_sim.
/**
  * axes
 */
typedef struct orca_msgs_sim__msg__OrcaJoystick
{
  int16_t throttle;
  int16_t lateral;
  int16_t forward;
  int16_t yaw;
  int16_t roll;
  int16_t pitch;
  /// tombol
  ///  bool x_button
  ///  bool y_button
  ///  bool b_button
  ///  bool a_button
  ///  bool r2_button
  ///  bool l2_button
  ///  #not used tombol
  ///  bool r1_button
  ///  bool l1_button
  /// mode
  rosidl_runtime_c__String arm_mode;
  rosidl_runtime_c__String control_mode;
  rosidl_runtime_c__String gripper_mode;
} orca_msgs_sim__msg__OrcaJoystick;

// Struct for a sequence of orca_msgs_sim__msg__OrcaJoystick.
typedef struct orca_msgs_sim__msg__OrcaJoystick__Sequence
{
  orca_msgs_sim__msg__OrcaJoystick * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} orca_msgs_sim__msg__OrcaJoystick__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__STRUCT_H_
