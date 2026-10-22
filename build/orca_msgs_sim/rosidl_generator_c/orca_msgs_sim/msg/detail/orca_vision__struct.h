// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from orca_msgs_sim:msg/OrcaVision.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "orca_msgs_sim/msg/orca_vision.h"


#ifndef ORCA_MSGS_SIM__MSG__DETAIL__ORCA_VISION__STRUCT_H_
#define ORCA_MSGS_SIM__MSG__DETAIL__ORCA_VISION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'class_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/OrcaVision in the package orca_msgs_sim.
typedef struct orca_msgs_sim__msg__OrcaVision
{
  bool detected;
  rosidl_runtime_c__String class_name;
  float confidence;
  float center_x;
  float center_y;
  float center_x_norm;
  float bbox_width;
  float bbox_height;
  float bbox_area_ratio;
  float distance;
} orca_msgs_sim__msg__OrcaVision;

// Struct for a sequence of orca_msgs_sim__msg__OrcaVision.
typedef struct orca_msgs_sim__msg__OrcaVision__Sequence
{
  orca_msgs_sim__msg__OrcaVision * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} orca_msgs_sim__msg__OrcaVision__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ORCA_MSGS_SIM__MSG__DETAIL__ORCA_VISION__STRUCT_H_
