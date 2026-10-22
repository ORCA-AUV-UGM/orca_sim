// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from orca_msgs_sim:msg/OrcaDepth.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "orca_msgs_sim/msg/orca_depth.hpp"


#ifndef ORCA_MSGS_SIM__MSG__DETAIL__ORCA_DEPTH__BUILDER_HPP_
#define ORCA_MSGS_SIM__MSG__DETAIL__ORCA_DEPTH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "orca_msgs_sim/msg/detail/orca_depth__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace orca_msgs_sim
{

namespace msg
{

namespace builder
{

class Init_OrcaDepth_pressure
{
public:
  explicit Init_OrcaDepth_pressure(::orca_msgs_sim::msg::OrcaDepth & msg)
  : msg_(msg)
  {}
  ::orca_msgs_sim::msg::OrcaDepth pressure(::orca_msgs_sim::msg::OrcaDepth::_pressure_type arg)
  {
    msg_.pressure = std::move(arg);
    return std::move(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaDepth msg_;
};

class Init_OrcaDepth_depth
{
public:
  Init_OrcaDepth_depth()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OrcaDepth_pressure depth(::orca_msgs_sim::msg::OrcaDepth::_depth_type arg)
  {
    msg_.depth = std::move(arg);
    return Init_OrcaDepth_pressure(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaDepth msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::orca_msgs_sim::msg::OrcaDepth>()
{
  return orca_msgs_sim::msg::builder::Init_OrcaDepth_depth();
}

}  // namespace orca_msgs_sim

#endif  // ORCA_MSGS_SIM__MSG__DETAIL__ORCA_DEPTH__BUILDER_HPP_
