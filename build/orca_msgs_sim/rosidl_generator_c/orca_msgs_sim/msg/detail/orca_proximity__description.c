// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from orca_msgs_sim:msg/OrcaProximity.idl
// generated code does not contain a copyright notice

#include "orca_msgs_sim/msg/detail/orca_proximity__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_orca_msgs_sim
const rosidl_type_hash_t *
orca_msgs_sim__msg__OrcaProximity__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x29, 0x07, 0x6f, 0xbe, 0x70, 0x09, 0x03, 0x0c,
      0x2d, 0x9e, 0xf3, 0x13, 0xf5, 0xee, 0x33, 0x17,
      0xf0, 0x9a, 0xfb, 0x9b, 0x4e, 0x57, 0xf7, 0xf2,
      0x84, 0x3f, 0x99, 0x78, 0x36, 0xcb, 0xb1, 0xf9,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char orca_msgs_sim__msg__OrcaProximity__TYPE_NAME[] = "orca_msgs_sim/msg/OrcaProximity";

// Define type names, field names, and default values
static char orca_msgs_sim__msg__OrcaProximity__FIELD_NAME__arm_mode[] = "arm_mode";

static rosidl_runtime_c__type_description__Field orca_msgs_sim__msg__OrcaProximity__FIELDS[] = {
  {
    {orca_msgs_sim__msg__OrcaProximity__FIELD_NAME__arm_mode, 8, 8},
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
orca_msgs_sim__msg__OrcaProximity__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {orca_msgs_sim__msg__OrcaProximity__TYPE_NAME, 31, 31},
      {orca_msgs_sim__msg__OrcaProximity__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "bool arm_mode";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
orca_msgs_sim__msg__OrcaProximity__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {orca_msgs_sim__msg__OrcaProximity__TYPE_NAME, 31, 31},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 13, 13},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
orca_msgs_sim__msg__OrcaProximity__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *orca_msgs_sim__msg__OrcaProximity__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
