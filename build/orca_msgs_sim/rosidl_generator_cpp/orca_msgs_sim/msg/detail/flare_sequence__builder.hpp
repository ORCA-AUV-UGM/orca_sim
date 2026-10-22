// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from orca_msgs_sim:msg/FlareSequence.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "orca_msgs_sim/msg/flare_sequence.hpp"


#ifndef ORCA_MSGS_SIM__MSG__DETAIL__FLARE_SEQUENCE__BUILDER_HPP_
#define ORCA_MSGS_SIM__MSG__DETAIL__FLARE_SEQUENCE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "orca_msgs_sim/msg/detail/flare_sequence__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace orca_msgs_sim
{

namespace msg
{

namespace builder
{

class Init_FlareSequence_sequence
{
public:
  Init_FlareSequence_sequence()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::orca_msgs_sim::msg::FlareSequence sequence(::orca_msgs_sim::msg::FlareSequence::_sequence_type arg)
  {
    msg_.sequence = std::move(arg);
    return std::move(msg_);
  }

private:
  ::orca_msgs_sim::msg::FlareSequence msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::orca_msgs_sim::msg::FlareSequence>()
{
  return orca_msgs_sim::msg::builder::Init_FlareSequence_sequence();
}

}  // namespace orca_msgs_sim

#endif  // ORCA_MSGS_SIM__MSG__DETAIL__FLARE_SEQUENCE__BUILDER_HPP_
