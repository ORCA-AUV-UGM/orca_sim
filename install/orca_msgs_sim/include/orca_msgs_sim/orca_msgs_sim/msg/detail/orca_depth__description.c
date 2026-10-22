// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from orca_msgs_sim:msg/OrcaDepth.idl
// generated code does not contain a copyright notice

#include "orca_msgs_sim/msg/detail/orca_depth__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_orca_msgs_sim
const rosidl_type_hash_t *
orca_msgs_sim__msg__OrcaDepth__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x0c, 0x75, 0x39, 0x1f, 0x22, 0x7d, 0x37, 0x8c,
      0x99, 0x34, 0x31, 0x2a, 0x1d, 0x35, 0x3f, 0x4e,
      0xf4, 0xcb, 0x73, 0x21, 0x27, 0x8f, 0x84, 0xd5,
      0x42, 0xcf, 0x39, 0xd4, 0x41, 0x3e, 0xb8, 0x5a,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char orca_msgs_sim__msg__OrcaDepth__TYPE_NAME[] = "orca_msgs_sim/msg/OrcaDepth";

// Define type names, field names, and default values
static char orca_msgs_sim__msg__OrcaDepth__FIELD_NAME__depth[] = "depth";
static char orca_msgs_sim__msg__OrcaDepth__FIELD_NAME__pressure[] = "pressure";

static rosidl_runtime_c__type_description__Field orca_msgs_sim__msg__OrcaDepth__FIELDS[] = {
  {
    {orca_msgs_sim__msg__OrcaDepth__FIELD_NAME__depth, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaDepth__FIELD_NAME__pressure, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
orca_msgs_sim__msg__OrcaDepth__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {orca_msgs_sim__msg__OrcaDepth__TYPE_NAME, 27, 27},
      {orca_msgs_sim__msg__OrcaDepth__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 depth\n"
  "float32 pressure";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
orca_msgs_sim__msg__OrcaDepth__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {orca_msgs_sim__msg__OrcaDepth__TYPE_NAME, 27, 27},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 30, 30},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
orca_msgs_sim__msg__OrcaDepth__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *orca_msgs_sim__msg__OrcaDepth__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
