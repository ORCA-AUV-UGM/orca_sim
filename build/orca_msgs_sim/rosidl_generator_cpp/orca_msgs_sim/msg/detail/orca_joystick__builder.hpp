// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from orca_msgs_sim:msg/OrcaJoystick.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "orca_msgs_sim/msg/orca_joystick.hpp"


#ifndef ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__BUILDER_HPP_
#define ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "orca_msgs_sim/msg/detail/orca_joystick__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace orca_msgs_sim
{

namespace msg
{

namespace builder
{

class Init_OrcaJoystick_gripper_mode
{
public:
  explicit Init_OrcaJoystick_gripper_mode(::orca_msgs_sim::msg::OrcaJoystick & msg)
  : msg_(msg)
  {}
  ::orca_msgs_sim::msg::OrcaJoystick gripper_mode(::orca_msgs_sim::msg::OrcaJoystick::_gripper_mode_type arg)
  {
    msg_.gripper_mode = std::move(arg);
    return std::move(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaJoystick msg_;
};

class Init_OrcaJoystick_control_mode
{
public:
  explicit Init_OrcaJoystick_control_mode(::orca_msgs_sim::msg::OrcaJoystick & msg)
  : msg_(msg)
  {}
  Init_OrcaJoystick_gripper_mode control_mode(::orca_msgs_sim::msg::OrcaJoystick::_control_mode_type arg)
  {
    msg_.control_mode = std::move(arg);
    return Init_OrcaJoystick_gripper_mode(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaJoystick msg_;
};

class Init_OrcaJoystick_arm_mode
{
public:
  explicit Init_OrcaJoystick_arm_mode(::orca_msgs_sim::msg::OrcaJoystick & msg)
  : msg_(msg)
  {}
  Init_OrcaJoystick_control_mode arm_mode(::orca_msgs_sim::msg::OrcaJoystick::_arm_mode_type arg)
  {
    msg_.arm_mode = std::move(arg);
    return Init_OrcaJoystick_control_mode(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaJoystick msg_;
};

class Init_OrcaJoystick_pitch
{
public:
  explicit Init_OrcaJoystick_pitch(::orca_msgs_sim::msg::OrcaJoystick & msg)
  : msg_(msg)
  {}
  Init_OrcaJoystick_arm_mode pitch(::orca_msgs_sim::msg::OrcaJoystick::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_OrcaJoystick_arm_mode(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaJoystick msg_;
};

class Init_OrcaJoystick_roll
{
public:
  explicit Init_OrcaJoystick_roll(::orca_msgs_sim::msg::OrcaJoystick & msg)
  : msg_(msg)
  {}
  Init_OrcaJoystick_pitch roll(::orca_msgs_sim::msg::OrcaJoystick::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_OrcaJoystick_pitch(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaJoystick msg_;
};

class Init_OrcaJoystick_yaw
{
public:
  explicit Init_OrcaJoystick_yaw(::orca_msgs_sim::msg::OrcaJoystick & msg)
  : msg_(msg)
  {}
  Init_OrcaJoystick_roll yaw(::orca_msgs_sim::msg::OrcaJoystick::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_OrcaJoystick_roll(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaJoystick msg_;
};

class Init_OrcaJoystick_forward
{
public:
  explicit Init_OrcaJoystick_forward(::orca_msgs_sim::msg::OrcaJoystick & msg)
  : msg_(msg)
  {}
  Init_OrcaJoystick_yaw forward(::orca_msgs_sim::msg::OrcaJoystick::_forward_type arg)
  {
    msg_.forward = std::move(arg);
    return Init_OrcaJoystick_yaw(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaJoystick msg_;
};

class Init_OrcaJoystick_lateral
{
public:
  explicit Init_OrcaJoystick_lateral(::orca_msgs_sim::msg::OrcaJoystick & msg)
  : msg_(msg)
  {}
  Init_OrcaJoystick_forward lateral(::orca_msgs_sim::msg::OrcaJoystick::_lateral_type arg)
  {
    msg_.lateral = std::move(arg);
    return Init_OrcaJoystick_forward(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaJoystick msg_;
};

class Init_OrcaJoystick_throttle
{
public:
  Init_OrcaJoystick_throttle()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OrcaJoystick_lateral throttle(::orca_msgs_sim::msg::OrcaJoystick::_throttle_type arg)
  {
    msg_.throttle = std::move(arg);
    return Init_OrcaJoystick_lateral(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaJoystick msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::orca_msgs_sim::msg::OrcaJoystick>()
{
  return orca_msgs_sim::msg::builder::Init_OrcaJoystick_throttle();
}

}  // namespace orca_msgs_sim

#endif  // ORCA_MSGS_SIM__MSG__DETAIL__ORCA_JOYSTICK__BUILDER_HPP_
