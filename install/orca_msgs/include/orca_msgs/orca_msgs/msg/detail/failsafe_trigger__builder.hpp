// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from orca_msgs:msg/FailsafeTrigger.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "orca_msgs/msg/failsafe_trigger.hpp"


#ifndef ORCA_MSGS__MSG__DETAIL__FAILSAFE_TRIGGER__BUILDER_HPP_
#define ORCA_MSGS__MSG__DETAIL__FAILSAFE_TRIGGER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "orca_msgs/msg/detail/failsafe_trigger__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace orca_msgs
{

namespace msg
{

namespace builder
{

class Init_FailsafeTrigger_active
{
public:
  Init_FailsafeTrigger_active()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::orca_msgs::msg::FailsafeTrigger active(::orca_msgs::msg::FailsafeTrigger::_active_type arg)
  {
    msg_.active = std::move(arg);
    return std::move(msg_);
  }

private:
  ::orca_msgs::msg::FailsafeTrigger msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::orca_msgs::msg::FailsafeTrigger>()
{
  return orca_msgs::msg::builder::Init_FailsafeTrigger_active();
}

}  // namespace orca_msgs

#endif  // ORCA_MSGS__MSG__DETAIL__FAILSAFE_TRIGGER__BUILDER_HPP_
