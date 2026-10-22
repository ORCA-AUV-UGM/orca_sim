// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from orca_msgs_sim:msg/OrcaJoystick.idl
// generated code does not contain a copyright notice

#include "orca_msgs_sim/msg/detail/orca_joystick__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_orca_msgs_sim
const rosidl_type_hash_t *
orca_msgs_sim__msg__OrcaJoystick__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x72, 0x7e, 0x73, 0xc1, 0xe6, 0x76, 0xd4, 0x3b,
      0x26, 0x5c, 0x23, 0x00, 0x58, 0xc4, 0x91, 0xd8,
      0x7a, 0x9b, 0x40, 0xdb, 0x67, 0x5b, 0x1a, 0xa1,
      0x03, 0x61, 0x5b, 0xba, 0xf3, 0xfb, 0x37, 0xa1,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char orca_msgs_sim__msg__OrcaJoystick__TYPE_NAME[] = "orca_msgs_sim/msg/OrcaJoystick";

// Define type names, field names, and default values
static char orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__throttle[] = "throttle";
static char orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__lateral[] = "lateral";
static char orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__forward[] = "forward";
static char orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__yaw[] = "yaw";
static char orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__roll[] = "roll";
static char orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__pitch[] = "pitch";
static char orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__arm_mode[] = "arm_mode";
static char orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__control_mode[] = "control_mode";
static char orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__gripper_mode[] = "gripper_mode";

static rosidl_runtime_c__type_description__Field orca_msgs_sim__msg__OrcaJoystick__FIELDS[] = {
  {
    {orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__throttle, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__lateral, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__forward, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__yaw, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__roll, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__pitch, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__arm_mode, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__control_mode, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {orca_msgs_sim__msg__OrcaJoystick__FIELD_NAME__gripper_mode, 12, 12},
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
orca_msgs_sim__msg__OrcaJoystick__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {orca_msgs_sim__msg__OrcaJoystick__TYPE_NAME, 30, 30},
      {orca_msgs_sim__msg__OrcaJoystick__FIELDS, 9, 9},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "#axes\n"
  "int16 throttle\n"
  "int16 lateral\n"
  "int16 forward\n"
  "\n"
  "int16 yaw\n"
  "int16 roll\n"
  "int16 pitch\n"
  "\n"
  "#tombol\n"
  "# bool x_button\n"
  "# bool y_button\n"
  "# bool b_button\n"
  "# bool a_button\n"
  "# bool r2_button\n"
  "# bool l2_button\n"
  "\n"
  "# #not used tombol\n"
  "# bool r1_button\n"
  "# bool l1_button\n"
  "\n"
  "#mode\n"
  "string arm_mode\n"
  "string control_mode\n"
  "string gripper_mode";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
orca_msgs_sim__msg__OrcaJoystick__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {orca_msgs_sim__msg__OrcaJoystick__TYPE_NAME, 30, 30},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 306, 306},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
orca_msgs_sim__msg__OrcaJoystick__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *orca_msgs_sim__msg__OrcaJoystick__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
