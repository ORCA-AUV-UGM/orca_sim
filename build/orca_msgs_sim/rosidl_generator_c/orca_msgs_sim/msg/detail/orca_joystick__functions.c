// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from orca_msgs_sim:msg/OrcaJoystick.idl
// generated code does not contain a copyright notice
#include "orca_msgs_sim/msg/detail/orca_joystick__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `arm_mode`
// Member `control_mode`
// Member `gripper_mode`
#include "rosidl_runtime_c/string_functions.h"

bool
orca_msgs_sim__msg__OrcaJoystick__init(orca_msgs_sim__msg__OrcaJoystick * msg)
{
  if (!msg) {
    return false;
  }
  // throttle
  // lateral
  // forward
  // yaw
  // roll
  // pitch
  // arm_mode
  if (!rosidl_runtime_c__String__init(&msg->arm_mode)) {
    orca_msgs_sim__msg__OrcaJoystick__fini(msg);
    return false;
  }
  // control_mode
  if (!rosidl_runtime_c__String__init(&msg->control_mode)) {
    orca_msgs_sim__msg__OrcaJoystick__fini(msg);
    return false;
  }
  // gripper_mode
  if (!rosidl_runtime_c__String__init(&msg->gripper_mode)) {
    orca_msgs_sim__msg__OrcaJoystick__fini(msg);
    return false;
  }
  return true;
}

void
orca_msgs_sim__msg__OrcaJoystick__fini(orca_msgs_sim__msg__OrcaJoystick * msg)
{
  if (!msg) {
    return;
  }
  // throttle
  // lateral
  // forward
  // yaw
  // roll
  // pitch
  // arm_mode
  rosidl_runtime_c__String__fini(&msg->arm_mode);
  // control_mode
  rosidl_runtime_c__String__fini(&msg->control_mode);
  // gripper_mode
  rosidl_runtime_c__String__fini(&msg->gripper_mode);
}

bool
orca_msgs_sim__msg__OrcaJoystick__are_equal(const orca_msgs_sim__msg__OrcaJoystick * lhs, const orca_msgs_sim__msg__OrcaJoystick * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // throttle
  if (lhs->throttle != rhs->throttle) {
    return false;
  }
  // lateral
  if (lhs->lateral != rhs->lateral) {
    return false;
  }
  // forward
  if (lhs->forward != rhs->forward) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // roll
  if (lhs->roll != rhs->roll) {
    return false;
  }
  // pitch
  if (lhs->pitch != rhs->pitch) {
    return false;
  }
  // arm_mode
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->arm_mode), &(rhs->arm_mode)))
  {
    return false;
  }
  // control_mode
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->control_mode), &(rhs->control_mode)))
  {
    return false;
  }
  // gripper_mode
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->gripper_mode), &(rhs->gripper_mode)))
  {
    return false;
  }
  return true;
}

bool
orca_msgs_sim__msg__OrcaJoystick__copy(
  const orca_msgs_sim__msg__OrcaJoystick * input,
  orca_msgs_sim__msg__OrcaJoystick * output)
{
  if (!input || !output) {
    return false;
  }
  // throttle
  output->throttle = input->throttle;
  // lateral
  output->lateral = input->lateral;
  // forward
  output->forward = input->forward;
  // yaw
  output->yaw = input->yaw;
  // roll
  output->roll = input->roll;
  // pitch
  output->pitch = input->pitch;
  // arm_mode
  if (!rosidl_runtime_c__String__copy(
      &(input->arm_mode), &(output->arm_mode)))
  {
    return false;
  }
  // control_mode
  if (!rosidl_runtime_c__String__copy(
      &(input->control_mode), &(output->control_mode)))
  {
    return false;
  }
  // gripper_mode
  if (!rosidl_runtime_c__String__copy(
      &(input->gripper_mode), &(output->gripper_mode)))
  {
    return false;
  }
  return true;
}

orca_msgs_sim__msg__OrcaJoystick *
orca_msgs_sim__msg__OrcaJoystick__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  orca_msgs_sim__msg__OrcaJoystick * msg = (orca_msgs_sim__msg__OrcaJoystick *)allocator.allocate(sizeof(orca_msgs_sim__msg__OrcaJoystick), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(orca_msgs_sim__msg__OrcaJoystick));
  bool success = orca_msgs_sim__msg__OrcaJoystick__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
orca_msgs_sim__msg__OrcaJoystick__destroy(orca_msgs_sim__msg__OrcaJoystick * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    orca_msgs_sim__msg__OrcaJoystick__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
orca_msgs_sim__msg__OrcaJoystick__Sequence__init(orca_msgs_sim__msg__OrcaJoystick__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  orca_msgs_sim__msg__OrcaJoystick * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(orca_msgs_sim__msg__OrcaJoystick)) {
      return false;
    }
    data = (orca_msgs_sim__msg__OrcaJoystick *)allocator.zero_allocate(size, sizeof(orca_msgs_sim__msg__OrcaJoystick), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = orca_msgs_sim__msg__OrcaJoystick__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        orca_msgs_sim__msg__OrcaJoystick__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
orca_msgs_sim__msg__OrcaJoystick__Sequence__fini(orca_msgs_sim__msg__OrcaJoystick__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      orca_msgs_sim__msg__OrcaJoystick__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

orca_msgs_sim__msg__OrcaJoystick__Sequence *
orca_msgs_sim__msg__OrcaJoystick__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  orca_msgs_sim__msg__OrcaJoystick__Sequence * array = (orca_msgs_sim__msg__OrcaJoystick__Sequence *)allocator.allocate(sizeof(orca_msgs_sim__msg__OrcaJoystick__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = orca_msgs_sim__msg__OrcaJoystick__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
orca_msgs_sim__msg__OrcaJoystick__Sequence__destroy(orca_msgs_sim__msg__OrcaJoystick__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    orca_msgs_sim__msg__OrcaJoystick__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
orca_msgs_sim__msg__OrcaJoystick__Sequence__are_equal(const orca_msgs_sim__msg__OrcaJoystick__Sequence * lhs, const orca_msgs_sim__msg__OrcaJoystick__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!orca_msgs_sim__msg__OrcaJoystick__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
orca_msgs_sim__msg__OrcaJoystick__Sequence__copy(
  const orca_msgs_sim__msg__OrcaJoystick__Sequence * input,
  orca_msgs_sim__msg__OrcaJoystick__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(orca_msgs_sim__msg__OrcaJoystick)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(orca_msgs_sim__msg__OrcaJoystick);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    orca_msgs_sim__msg__OrcaJoystick * data =
      (orca_msgs_sim__msg__OrcaJoystick *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!orca_msgs_sim__msg__OrcaJoystick__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          orca_msgs_sim__msg__OrcaJoystick__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!orca_msgs_sim__msg__OrcaJoystick__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
