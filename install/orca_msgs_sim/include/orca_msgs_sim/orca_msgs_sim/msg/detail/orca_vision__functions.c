// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from orca_msgs_sim:msg/OrcaVision.idl
// generated code does not contain a copyright notice
#include "orca_msgs_sim/msg/detail/orca_vision__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `class_name`
#include "rosidl_runtime_c/string_functions.h"

bool
orca_msgs_sim__msg__OrcaVision__init(orca_msgs_sim__msg__OrcaVision * msg)
{
  if (!msg) {
    return false;
  }
  // detected
  // class_name
  if (!rosidl_runtime_c__String__init(&msg->class_name)) {
    orca_msgs_sim__msg__OrcaVision__fini(msg);
    return false;
  }
  // confidence
  // center_x
  // center_y
  // center_x_norm
  // bbox_width
  // bbox_height
  // bbox_area_ratio
  // distance
  return true;
}

void
orca_msgs_sim__msg__OrcaVision__fini(orca_msgs_sim__msg__OrcaVision * msg)
{
  if (!msg) {
    return;
  }
  // detected
  // class_name
  rosidl_runtime_c__String__fini(&msg->class_name);
  // confidence
  // center_x
  // center_y
  // center_x_norm
  // bbox_width
  // bbox_height
  // bbox_area_ratio
  // distance
}

bool
orca_msgs_sim__msg__OrcaVision__are_equal(const orca_msgs_sim__msg__OrcaVision * lhs, const orca_msgs_sim__msg__OrcaVision * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // detected
  if (lhs->detected != rhs->detected) {
    return false;
  }
  // class_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->class_name), &(rhs->class_name)))
  {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  // center_x
  if (lhs->center_x != rhs->center_x) {
    return false;
  }
  // center_y
  if (lhs->center_y != rhs->center_y) {
    return false;
  }
  // center_x_norm
  if (lhs->center_x_norm != rhs->center_x_norm) {
    return false;
  }
  // bbox_width
  if (lhs->bbox_width != rhs->bbox_width) {
    return false;
  }
  // bbox_height
  if (lhs->bbox_height != rhs->bbox_height) {
    return false;
  }
  // bbox_area_ratio
  if (lhs->bbox_area_ratio != rhs->bbox_area_ratio) {
    return false;
  }
  // distance
  if (lhs->distance != rhs->distance) {
    return false;
  }
  return true;
}

bool
orca_msgs_sim__msg__OrcaVision__copy(
  const orca_msgs_sim__msg__OrcaVision * input,
  orca_msgs_sim__msg__OrcaVision * output)
{
  if (!input || !output) {
    return false;
  }
  // detected
  output->detected = input->detected;
  // class_name
  if (!rosidl_runtime_c__String__copy(
      &(input->class_name), &(output->class_name)))
  {
    return false;
  }
  // confidence
  output->confidence = input->confidence;
  // center_x
  output->center_x = input->center_x;
  // center_y
  output->center_y = input->center_y;
  // center_x_norm
  output->center_x_norm = input->center_x_norm;
  // bbox_width
  output->bbox_width = input->bbox_width;
  // bbox_height
  output->bbox_height = input->bbox_height;
  // bbox_area_ratio
  output->bbox_area_ratio = input->bbox_area_ratio;
  // distance
  output->distance = input->distance;
  return true;
}

orca_msgs_sim__msg__OrcaVision *
orca_msgs_sim__msg__OrcaVision__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  orca_msgs_sim__msg__OrcaVision * msg = (orca_msgs_sim__msg__OrcaVision *)allocator.allocate(sizeof(orca_msgs_sim__msg__OrcaVision), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(orca_msgs_sim__msg__OrcaVision));
  bool success = orca_msgs_sim__msg__OrcaVision__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
orca_msgs_sim__msg__OrcaVision__destroy(orca_msgs_sim__msg__OrcaVision * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    orca_msgs_sim__msg__OrcaVision__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
orca_msgs_sim__msg__OrcaVision__Sequence__init(orca_msgs_sim__msg__OrcaVision__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  orca_msgs_sim__msg__OrcaVision * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(orca_msgs_sim__msg__OrcaVision)) {
      return false;
    }
    data = (orca_msgs_sim__msg__OrcaVision *)allocator.zero_allocate(size, sizeof(orca_msgs_sim__msg__OrcaVision), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = orca_msgs_sim__msg__OrcaVision__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        orca_msgs_sim__msg__OrcaVision__fini(&data[i - 1]);
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
orca_msgs_sim__msg__OrcaVision__Sequence__fini(orca_msgs_sim__msg__OrcaVision__Sequence * array)
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
      orca_msgs_sim__msg__OrcaVision__fini(&array->data[i]);
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

orca_msgs_sim__msg__OrcaVision__Sequence *
orca_msgs_sim__msg__OrcaVision__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  orca_msgs_sim__msg__OrcaVision__Sequence * array = (orca_msgs_sim__msg__OrcaVision__Sequence *)allocator.allocate(sizeof(orca_msgs_sim__msg__OrcaVision__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = orca_msgs_sim__msg__OrcaVision__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
orca_msgs_sim__msg__OrcaVision__Sequence__destroy(orca_msgs_sim__msg__OrcaVision__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    orca_msgs_sim__msg__OrcaVision__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
orca_msgs_sim__msg__OrcaVision__Sequence__are_equal(const orca_msgs_sim__msg__OrcaVision__Sequence * lhs, const orca_msgs_sim__msg__OrcaVision__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!orca_msgs_sim__msg__OrcaVision__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
orca_msgs_sim__msg__OrcaVision__Sequence__copy(
  const orca_msgs_sim__msg__OrcaVision__Sequence * input,
  orca_msgs_sim__msg__OrcaVision__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(orca_msgs_sim__msg__OrcaVision)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(orca_msgs_sim__msg__OrcaVision);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    orca_msgs_sim__msg__OrcaVision * data =
      (orca_msgs_sim__msg__OrcaVision *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!orca_msgs_sim__msg__OrcaVision__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          orca_msgs_sim__msg__OrcaVision__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!orca_msgs_sim__msg__OrcaVision__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
