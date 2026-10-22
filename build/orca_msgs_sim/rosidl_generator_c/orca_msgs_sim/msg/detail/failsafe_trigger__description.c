// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from orca_msgs_sim:msg/FailsafeTrigger.idl
// generated code does not contain a copyright notice

#include "orca_msgs_sim/msg/detail/failsafe_trigger__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_orca_msgs_sim
const rosidl_type_hash_t *
orca_msgs_sim__msg__FailsafeTrigger__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x3a, 0xcb, 0x8d, 0x59, 0xae, 0x6f, 0x60, 0x1f,
      0xda, 0x2f, 0x96, 0xda, 0xfe, 0x56, 0x49, 0x3d,
      0x03, 0x27, 0x84, 0xf5, 0xef, 0x2c, 0x6f, 0x14,
      0x11, 0xb8, 0xa1, 0xcb, 0xc9, 0xa6, 0xd1, 0x95,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char orca_msgs_sim__msg__FailsafeTrigger__TYPE_NAME[] = "orca_msgs_sim/msg/FailsafeTrigger";

// Define type names, field names, and default values
static char orca_msgs_sim__msg__FailsafeTrigger__FIELD_NAME__active[] = "active";

static rosidl_runtime_c__type_description__Field orca_msgs_sim__msg__FailsafeTrigger__FIELDS[] = {
  {
    {orca_msgs_sim__msg__FailsafeTrigger__FIELD_NAME__active, 6, 6},
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
orca_msgs_sim__msg__FailsafeTrigger__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {orca_msgs_sim__msg__FailsafeTrigger__TYPE_NAME, 33, 33},
      {orca_msgs_sim__msg__FailsafeTrigger__FIELDS, 1, 1},
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
orca_msgs_sim__msg__FailsafeTrigger__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {orca_msgs_sim__msg__FailsafeTrigger__TYPE_NAME, 33, 33},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 11, 11},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
orca_msgs_sim__msg__FailsafeTrigger__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *orca_msgs_sim__msg__FailsafeTrigger__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
