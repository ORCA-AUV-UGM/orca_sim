// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from orca_msgs:msg/FailsafeTrigger.idl
// generated code does not contain a copyright notice

#include "orca_msgs/msg/detail/failsafe_trigger__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_orca_msgs
const rosidl_type_hash_t *
orca_msgs__msg__FailsafeTrigger__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xde, 0x31, 0x2d, 0x57, 0x2b, 0xbc, 0x14, 0x32,
      0xcf, 0x37, 0x58, 0xd5, 0x34, 0x83, 0x9f, 0x5c,
      0x67, 0x1f, 0x3c, 0x0a, 0xd5, 0x02, 0x18, 0xef,
      0x9a, 0x2e, 0xb7, 0xc4, 0xaa, 0x5b, 0x7c, 0x17,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char orca_msgs__msg__FailsafeTrigger__TYPE_NAME[] = "orca_msgs/msg/FailsafeTrigger";

// Define type names, field names, and default values
static char orca_msgs__msg__FailsafeTrigger__FIELD_NAME__active[] = "active";

static rosidl_runtime_c__type_description__Field orca_msgs__msg__FailsafeTrigger__FIELDS[] = {
  {
    {orca_msgs__msg__FailsafeTrigger__FIELD_NAME__active, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
orca_msgs__msg__FailsafeTrigger__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {orca_msgs__msg__FailsafeTrigger__TYPE_NAME, 29, 29},
      {orca_msgs__msg__FailsafeTrigger__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "bool active";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
orca_msgs__msg__FailsafeTrigger__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {orca_msgs__msg__FailsafeTrigger__TYPE_NAME, 29, 29},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 11, 11},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
orca_msgs__msg__FailsafeTrigger__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *orca_msgs__msg__FailsafeTrigger__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
