// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from orca_msgs_sim:msg/OrcaProximity.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "orca_msgs_sim/msg/orca_proximity.hpp"


#ifndef ORCA_MSGS_SIM__MSG__DETAIL__ORCA_PROXIMITY__STRUCT_HPP_
#define ORCA_MSGS_SIM__MSG__DETAIL__ORCA_PROXIMITY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__orca_msgs_sim__msg__OrcaProximity __attribute__((deprecated))
#else
# define DEPRECATED__orca_msgs_sim__msg__OrcaProximity __declspec(deprecated)
#endif

namespace orca_msgs_sim
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct OrcaProximity_
{
  using Type = OrcaProximity_<ContainerAllocator>;

  explicit OrcaProximity_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->triggered = false;
    }
  }

  explicit OrcaProximity_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->triggered = false;
    }
  }

  // field types and members
  using _triggered_type =
    bool;
  _triggered_type triggered;

  // setters for named parameter idiom
  Type & set__triggered(
    const bool & _arg)
  {
    this->triggered = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator> *;
  using ConstRawPtr =
    const orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__orca_msgs_sim__msg__OrcaProximity
    std::shared_ptr<orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__orca_msgs_sim__msg__OrcaProximity
    std::shared_ptr<orca_msgs_sim::msg::OrcaProximity_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const OrcaProximity_ & other) const
  {
    if (this->triggered != other.triggered) {
      return false;
    }
    return true;
  }
  bool operator!=(const OrcaProximity_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct OrcaProximity_

// alias to use template instance with default allocator
using OrcaProximity =
  orca_msgs_sim::msg::OrcaProximity_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace orca_msgs_sim

#endif  // ORCA_MSGS_SIM__MSG__DETAIL__ORCA_PROXIMITY__STRUCT_HPP_
