// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from orca_msgs_sim:msg/OrcaAttitude.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "orca_msgs_sim/msg/orca_attitude.hpp"


#ifndef ORCA_MSGS_SIM__MSG__DETAIL__ORCA_ATTITUDE__BUILDER_HPP_
#define ORCA_MSGS_SIM__MSG__DETAIL__ORCA_ATTITUDE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "orca_msgs_sim/msg/detail/orca_attitude__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace orca_msgs_sim
{

namespace msg
{

namespace builder
{

class Init_OrcaAttitude_yawspeed_deg_s
{
public:
  explicit Init_OrcaAttitude_yawspeed_deg_s(::orca_msgs_sim::msg::OrcaAttitude & msg)
  : msg_(msg)
  {}
  ::orca_msgs_sim::msg::OrcaAttitude yawspeed_deg_s(::orca_msgs_sim::msg::OrcaAttitude::_yawspeed_deg_s_type arg)
  {
    msg_.yawspeed_deg_s = std::move(arg);
    return std::move(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaAttitude msg_;
};

class Init_OrcaAttitude_pitchspeed_deg_s
{
public:
  explicit Init_OrcaAttitude_pitchspeed_deg_s(::orca_msgs_sim::msg::OrcaAttitude & msg)
  : msg_(msg)
  {}
  Init_OrcaAttitude_yawspeed_deg_s pitchspeed_deg_s(::orca_msgs_sim::msg::OrcaAttitude::_pitchspeed_deg_s_type arg)
  {
    msg_.pitchspeed_deg_s = std::move(arg);
    return Init_OrcaAttitude_yawspeed_deg_s(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaAttitude msg_;
};

class Init_OrcaAttitude_rollspeed_deg_s
{
public:
  explicit Init_OrcaAttitude_rollspeed_deg_s(::orca_msgs_sim::msg::OrcaAttitude & msg)
  : msg_(msg)
  {}
  Init_OrcaAttitude_pitchspeed_deg_s rollspeed_deg_s(::orca_msgs_sim::msg::OrcaAttitude::_rollspeed_deg_s_type arg)
  {
    msg_.rollspeed_deg_s = std::move(arg);
    return Init_OrcaAttitude_pitchspeed_deg_s(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaAttitude msg_;
};

class Init_OrcaAttitude_pitch_deg
{
public:
  explicit Init_OrcaAttitude_pitch_deg(::orca_msgs_sim::msg::OrcaAttitude & msg)
  : msg_(msg)
  {}
  Init_OrcaAttitude_rollspeed_deg_s pitch_deg(::orca_msgs_sim::msg::OrcaAttitude::_pitch_deg_type arg)
  {
    msg_.pitch_deg = std::move(arg);
    return Init_OrcaAttitude_rollspeed_deg_s(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaAttitude msg_;
};

class Init_OrcaAttitude_roll_deg
{
public:
  explicit Init_OrcaAttitude_roll_deg(::orca_msgs_sim::msg::OrcaAttitude & msg)
  : msg_(msg)
  {}
  Init_OrcaAttitude_pitch_deg roll_deg(::orca_msgs_sim::msg::OrcaAttitude::_roll_deg_type arg)
  {
    msg_.roll_deg = std::move(arg);
    return Init_OrcaAttitude_pitch_deg(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaAttitude msg_;
};

class Init_OrcaAttitude_yaw_deg
{
public:
  explicit Init_OrcaAttitude_yaw_deg(::orca_msgs_sim::msg::OrcaAttitude & msg)
  : msg_(msg)
  {}
  Init_OrcaAttitude_roll_deg yaw_deg(::orca_msgs_sim::msg::OrcaAttitude::_yaw_deg_type arg)
  {
    msg_.yaw_deg = std::move(arg);
    return Init_OrcaAttitude_roll_deg(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaAttitude msg_;
};

class Init_OrcaAttitude_initial_heading
{
public:
  explicit Init_OrcaAttitude_initial_heading(::orca_msgs_sim::msg::OrcaAttitude & msg)
  : msg_(msg)
  {}
  Init_OrcaAttitude_yaw_deg initial_heading(::orca_msgs_sim::msg::OrcaAttitude::_initial_heading_type arg)
  {
    msg_.initial_heading = std::move(arg);
    return Init_OrcaAttitude_yaw_deg(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaAttitude msg_;
};

class Init_OrcaAttitude_initial_z
{
public:
  explicit Init_OrcaAttitude_initial_z(::orca_msgs_sim::msg::OrcaAttitude & msg)
  : msg_(msg)
  {}
  Init_OrcaAttitude_initial_heading initial_z(::orca_msgs_sim::msg::OrcaAttitude::_initial_z_type arg)
  {
    msg_.initial_z = std::move(arg);
    return Init_OrcaAttitude_initial_heading(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaAttitude msg_;
};

class Init_OrcaAttitude_initial_y
{
public:
  explicit Init_OrcaAttitude_initial_y(::orca_msgs_sim::msg::OrcaAttitude & msg)
  : msg_(msg)
  {}
  Init_OrcaAttitude_initial_z initial_y(::orca_msgs_sim::msg::OrcaAttitude::_initial_y_type arg)
  {
    msg_.initial_y = std::move(arg);
    return Init_OrcaAttitude_initial_z(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaAttitude msg_;
};

class Init_OrcaAttitude_initial_x
{
public:
  Init_OrcaAttitude_initial_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OrcaAttitude_initial_y initial_x(::orca_msgs_sim::msg::OrcaAttitude::_initial_x_type arg)
  {
    msg_.initial_x = std::move(arg);
    return Init_OrcaAttitude_initial_y(msg_);
  }

private:
  ::orca_msgs_sim::msg::OrcaAttitude msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::orca_msgs_sim::msg::OrcaAttitude>()
{
  return orca_msgs_sim::msg::builder::Init_OrcaAttitude_initial_x();
}

}  // namespace orca_msgs_sim

#endif  // ORCA_MSGS_SIM__MSG__DETAIL__ORCA_ATTITUDE__BUILDER_HPP_
