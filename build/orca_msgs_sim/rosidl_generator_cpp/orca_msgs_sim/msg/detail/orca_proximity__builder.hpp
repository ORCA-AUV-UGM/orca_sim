// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from orca_msgs_sim:msg/OrcaProximity.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "orca_msgs_sim/msg/orca_proximity.hpp"


#ifndef ORCA_MSGS_SIM__MSG__DETAIL__ORCA_PROXIMITY__BUILDER_HPP_
#define ORCA_MSGS_SIM__MSG__DETAIL__ORCA_PROXIMITY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "orca_msgs_sim/msg/detail/orca_proximity__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace orca_msgs_sim
{

namespace msg
{

namespace builder
{

class Init_OrcaProximity_arm_mode
{
public:
  Init_OrcaProximity_arm_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::orca_msgs_sim::msg::OrcaProximity arm_mode(::orca_msgs_sim::msg::OrcaProximity::_arm_mode_type arg)
  {
    msg_.arm_mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaProximity msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::orca_msgs_sim::msg::OrcaProximity>()
{
  return orca_msgs_sim::msg::builder::Init_OrcaProximity_arm_mode();
}

}  // namespace orca_msgs_sim

#endif  // ORCA_MSGS_SIM__MSG__DETAIL__ORCA_PROXIMITY__BUILDER_HPP_
