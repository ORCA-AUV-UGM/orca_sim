// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from orca_msgs_sim:msg/OrcaJoystick.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "orca_msgs_sim/msg/orca_joystick.hpp"


#ifndef ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__TRAITS_HPP_
#define ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "orca_msgs_sim/msg/detail/orca_joystick__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace orca_msgs_sim
{

namespace msg
{

inline void to_flow_style_yaml(
  const OrcaJoystick & msg,
  std::ostream & out)
{
  out << "{";
  // member: throttle
  {
    out << "throttle: ";
    rosidl_generator_traits::value_to_yaml(msg.throttle, out);
    out << ", ";
  }

  // member: lateral
  {
    out << "lateral: ";
    rosidl_generator_traits::value_to_yaml(msg.lateral, out);
    out << ", ";
  }

  // member: forward
  {
    out << "forward: ";
    rosidl_generator_traits::value_to_yaml(msg.forward, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << ", ";
  }

  // member: roll
  {
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << ", ";
  }

  // member: pitch
  {
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << ", ";
  }

  // member: arm_mode
  {
    out << "arm_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.arm_mode, out);
    out << ", ";
  }

  // member: control_mode
  {
    out << "control_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.control_mode, out);
    out << ", ";
  }

  // member: gripper_mode
  {
    out << "gripper_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.gripper_mode, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const OrcaJoystick & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: throttle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "throttle: ";
    rosidl_generator_traits::value_to_yaml(msg.throttle, out);
    out << "\n";
  }

  // member: lateral
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lateral: ";
    rosidl_generator_traits::value_to_yaml(msg.lateral, out);
    out << "\n";
  }

  // member: forward
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "forward: ";
    rosidl_generator_traits::value_to_yaml(msg.forward, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }

  // member: roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "roll: ";
    rosidl_generator_traits::value_to_yaml(msg.roll, out);
    out << "\n";
  }

  // member: pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch, out);
    out << "\n";
  }

  // member: arm_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arm_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.arm_mode, out);
    out << "\n";
  }

  // member: control_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "control_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.control_mode, out);
    out << "\n";
  }

  // member: gripper_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gripper_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.gripper_mode, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const OrcaJoystick & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace orca_msgs_sim

namespace rosidl_generator_traits
{

[[deprecated("use orca_msgs_sim::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const orca_msgs_sim::msg::OrcaJoystick & msg,
  std::ostream & out, size_t indentation = 0)
{
  orca_msgs_sim::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use orca_msgs_sim::msg::to_yaml() instead")]]
inline std::string to_yaml(const orca_msgs_sim::msg::OrcaJoystick & msg)
{
  return orca_msgs_sim::msg::to_yaml(msg);
}

template<>
inline const char * data_type<orca_msgs_sim::msg::OrcaJoystick>()
{
  return "orca_msgs_sim::msg::OrcaJoystick";
}

template<>
inline const char * name<orca_msgs_sim::msg::OrcaJoystick>()
{
  return "orca_msgs_sim/msg/OrcaJoystick";
}

template<>
struct has_fixed_size<orca_msgs_sim::msg::OrcaJoystick>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<orca_msgs_sim::msg::OrcaJoystick>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<orca_msgs_sim::msg::OrcaJoystick>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__TRAITS_HPP_
