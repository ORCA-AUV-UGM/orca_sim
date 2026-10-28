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
      0xe0, 0x5d, 0x22, 0xb1, 0xb0, 0xfd, 0xd0, 0x2e,
      0xf5, 0xc3, 0xbb, 0xe4, 0xba, 0x10, 0x38, 0x6b,
      0x9f, 0x26, 0x05, 0xc5, 0xc3, 0x27, 0xf7, 0x14,
      0xb7, 0xdb, 0x76, 0x14, 0xc3, 0x92, 0xc2, 0x00,
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
static char orca_msgs_sim__msg__OrcaProximity__FIELD_NAME__triggered[] = "triggered";

static rosidl_runtime_c__type_description__Field orca_msgs_sim__msg__OrcaProximity__FIELDS[] = {
  {
    {orca_msgs_sim__msg__OrcaProximity__FIELD_NAME__triggered, 9, 9},
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
  "bool triggered";

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
    {toplevel_type_raw_source, 14, 14},
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
