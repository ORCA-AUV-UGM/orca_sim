// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from orca_msgs_sim:msg/OrcaJoystick.idl
// generated code does not contain a copyright notice

#ifndef ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include <cstddef>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "orca_msgs_sim/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "orca_msgs_sim/msg/detail/orca_joystick__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace orca_msgs_sim
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_orca_msgs_sim
cdr_serialize(
  const orca_msgs_sim::msg::OrcaJoystick & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_orca_msgs_sim
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  orca_msgs_sim::msg::OrcaJoystick & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_orca_msgs_sim
get_serialized_size(
  const orca_msgs_sim::msg::OrcaJoystick & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_orca_msgs_sim
max_serialized_size_OrcaJoystick(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_orca_msgs_sim
cdr_serialize_key(
  const orca_msgs_sim::msg::OrcaJoystick & ros_message,
  eprosima::fastcdr::Cdr &);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_orca_msgs_sim
get_serialized_size_key(
  const orca_msgs_sim::msg::OrcaJoystick & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_orca_msgs_sim
max_serialized_size_key_OrcaJoystick(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace orca_msgs_sim

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_orca_msgs_sim
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, orca_msgs_sim, msg, OrcaJoystick)();

#ifdef __cplusplus
}
#endif

#endif  // ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
