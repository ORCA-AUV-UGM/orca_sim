// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from orca_msgs_sim:msg/FailsafeTrigger.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "orca_msgs_sim/msg/failsafe_trigger.hpp"


#ifndef ORCA_MSGS_SIM__MSG__DETAIL__FAILSAFE_TRIGGER__TRAITS_HPP_
#define ORCA_MSGS_SIM__MSG__DETAIL__FAILSAFE_TRIGGER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "orca_msgs_sim/msg/detail/failsafe_trigger__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace orca_msgs_sim
{

namespace msg
{

inline void to_flow_style_yaml(
  const FailsafeTrigger & msg,
  std::ostream & out)
{
  out << "{";
  // member: active
  {
    out << "active: ";
    rosidl_generator_traits::value_to_yaml(msg.active, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FailsafeTrigger & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: active
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "active: ";
    rosidl_generator_traits::value_to_yaml(msg.active, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FailsafeTrigger & msg, bool use_flow_style = false)
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
  const orca_msgs_sim::msg::FailsafeTrigger & msg,
  std::ostream & out, size_t indentation = 0)
{
  orca_msgs_sim::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use orca_msgs_sim::msg::to_yaml() instead")]]
inline std::string to_yaml(const orca_msgs_sim::msg::FailsafeTrigger & msg)
{
  return orca_msgs_sim::msg::to_yaml(msg);
}

template<>
inline const char * data_type<orca_msgs_sim::msg::FailsafeTrigger>()
{
  return "orca_msgs_sim::msg::FailsafeTrigger";
}

template<>
inline const char * name<orca_msgs_sim::msg::FailsafeTrigger>()
{
  return "orca_msgs_sim/msg/FailsafeTrigger";
}

template<>
struct has_fixed_size<orca_msgs_sim::msg::FailsafeTrigger>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<orca_msgs_sim::msg::FailsafeTrigger>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<orca_msgs_sim::msg::FailsafeTrigger>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ORCA_MSGS_SIM__MSG__DETAIL__FAILSAFE_TRIGGER__TRAITS_HPP_
