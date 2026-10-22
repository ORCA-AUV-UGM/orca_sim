// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from orca_msgs_sim:msg/OrcaControl.idl
// generated code does not contain a copyright notice

#include "orca_msgs_sim/msg/detail/orca_control__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_orca_msgs_sim
const rosidl_type_hash_t *
orca_msgs_sim__msg__OrcaControl__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x55, 0x78, 0x95, 0x9c, 0x2c, 0xd4, 0xf7, 0x81,
      0x8f, 0x46, 0x10, 0xb7, 0x76, 0xf8, 0xec, 0xaf,
      0xfb, 0x61, 0x32, 0xd4, 0xee, 0xbe, 0xdb, 0x7b,
      0x0a, 0x52, 0x78, 0x81, 0x3e, 0x5f, 0xd5, 0x94,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char orca_msgs_sim__msg__OrcaControl__TYPE_NAME[] = "orca_msgs_sim/msg/OrcaControl";

// Define type names, field names, and default values
static char orca_msgs_sim__msg__OrcaControl__FIELD_NAME__throttle[] = "throttle";
static char orca_msgs_sim__msg__OrcaControl__FIELD_NAME__lateral[] = "lateral";
static char orca_msgs_sim__msg__OrcaControl__FIELD_NAME__forward[] = "forward";
static char orca_msgs_sim__msg__OrcaControl__FIELD_NAME__yaw[] = "yaw";
static char orca_msgs_sim__msg__OrcaControl__FIELD_NAME__pitch[] = "pitch";
static char orca_msgs_sim__msg__OrcaControl__FIELD_NAME__roll[] = "roll";
static char orca_msgs_sim__msg__OrcaControl__FIELD_NAME__arm_mode[] = "arm_mode";
static char orca_msgs_sim__msg__OrcaControl__FIELD_NAME__control_mode[] = "control_mode";
static char orca_msgs_sim__msg__OrcaControl__FIELD_NAME__gripper_mode[] = "gripper_mode";
static char orca_msgs_sim__msg__OrcaControl__FIELD_NAME__source[] = "source";

static rosidl_runtime_c__type_description__Field orca_msgs_sim__msg__OrcaControl__FIELDS[] = {
  {
    {orca_msgs_sim__msg__OrcaControl__FIELD_NAME__throttle, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaControl__FIELD_NAME__lateral, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaControl__FIELD_NAME__forward, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaControl__FIELD_NAME__yaw, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaControl__FIELD_NAME__pitch, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaControl__FIELD_NAME__roll, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaControl__FIELD_NAME__arm_mode, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaControl__FIELD_NAME__control_mode, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaControl__FIELD_NAME__gripper_mode, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaControl__FIELD_NAME__source, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
orca_msgs_sim__msg__OrcaControl__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {orca_msgs_sim__msg__OrcaControl__TYPE_NAME, 29, 29},
      {orca_msgs_sim__msg__OrcaControl__FIELDS, 10, 10},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "int16 throttle\n"
  "int16 lateral\n"
  "int16 forward\n"
  "\n"
  "int16 yaw\n"
  "int16 pitch\n"
  "int16 roll\n"
  "\n"
  "string arm_mode\n"
  "string control_mode\n"
  "string gripper_mode\n"
  "string source";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
orca_msgs_sim__msg__OrcaControl__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {orca_msgs_sim__msg__OrcaControl__TYPE_NAME, 29, 29},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 148, 148},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
orca_msgs_sim__msg__OrcaControl__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *orca_msgs_sim__msg__OrcaControl__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
