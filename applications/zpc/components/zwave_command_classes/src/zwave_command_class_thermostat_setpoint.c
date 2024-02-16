/******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 ******************************************************************************
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 *****************************************************************************/

// Includes from this component
#include "zwave_command_class_thermostat_setpoint.h"
#include "zwave_command_classes_utils.h"

// Includes from other components
#include "sl_log.h"
#include "sl_status.h"
#include "zwave_command_class_indices.h"
#include "ZW_classcmd.h"
#include "zwave_command_handler.h"
#include "zpc_attribute_store_network_helper.h"
#include "attribute_store_defined_attribute_types.h"

#include "attribute_store_helper.h"
#include "attribute_store.h"
#include "attribute_resolver.h"

// Generic includes
#include <assert.h>

// Log define
#define LOG_TAG "zwave_command_class_thermostat_setpoint"

// Max values in Thermostat Setpoint Supported Report values
#define MAX_SUPPORTED_SETPOINT_MODES 16

#define ATTRIBUTE(type) ATTRIBUTE_COMMAND_CLASS_THERMOSTAT_SETPOINT_##type

static bool is_thermostat_setpoint_mode_compatible_with_version(
  uint8_t supported_setpoint_mode_type, zwave_cc_version_t current_version)
{
  bool compatibility = false;

  switch (current_version) {
    case 1:
      compatibility = (supported_setpoint_mode_type <= 0x0A);
      break;
    case 2:
      compatibility = (supported_setpoint_mode_type <= 0x0D);
      break;
    case 3:
      compatibility = (supported_setpoint_mode_type <= 0x0F);
      break;
    default:
      compatibility = false;
  }

  if (!compatibility) {
    sl_log_warning(LOG_TAG,
                   "Thermostat SetPoint mode %#04x is not compatible with "
                   "Thermostat SetPoint Version %d",
                   supported_setpoint_mode_type,
                   current_version);
  }

  return compatibility;
}

///////////////////////////////////////////////////////////////////////////////
// Attribute creation functions
///////////////////////////////////////////////////////////////////////////////
static attribute_store_node_t
  zwave_command_class_thermostat_setpoint_create_type(
    attribute_store_node_t endpoint_node, uint8_t type)
{
  zwave_cc_version_t current_version;
  attribute_store_get_child_reported(endpoint_node,
                                     ATTRIBUTE(VERSION),
                                     &current_version,
                                     sizeof(current_version));

  // Check compatibility
  if (!is_thermostat_setpoint_mode_compatible_with_version(type,
                                                           current_version)) {
    return ATTRIBUTE_STORE_INVALID_NODE;
  }

  // Do we already have the node ?
  attribute_store_node_t type_node = attribute_store_emplace(endpoint_node,
                                                             ATTRIBUTE(TYPE),
                                                             &type,
                                                             sizeof(type));

  // Add the six other nodes under the type.
  const attribute_store_type_t additional_nodes[]
    = {ATTRIBUTE(VALUE),
       ATTRIBUTE(VALUE_SCALE),
       ATTRIBUTE(MIN_VALUE),
       ATTRIBUTE(MIN_VALUE_SCALE),
       ATTRIBUTE(MAX_VALUE),
       ATTRIBUTE(MAX_VALUE_SCALE)};
  attribute_store_add_if_missing(type_node,
                                 additional_nodes,
                                 COUNT_OF(additional_nodes));
  return type_node;
}

///////////////////////////////////////////////////////////////////////////////
// Private helper functions
///////////////////////////////////////////////////////////////////////////////
static void zwave_command_class_thermostat_setpoint_set_default_capabilities(
  attribute_store_node_t type_node)
{
  attribute_store_node_t min_value_node
    = attribute_store_get_first_child_by_type(type_node, ATTRIBUTE(MIN_VALUE));

  int32_t min_value = DEFAULT_MIN_VALUE;
  attribute_store_set_reported(min_value_node, &min_value, sizeof(min_value));

  attribute_store_node_t max_value_node
    = attribute_store_get_first_child_by_type(type_node, ATTRIBUTE(MAX_VALUE));

  int32_t max_value = DEFAULT_MAX_VALUE;
  attribute_store_set_reported(max_value_node, &max_value, sizeof(max_value));

  attribute_store_node_t min_value_scale_node
    = attribute_store_get_first_child_by_type(type_node,
                                              ATTRIBUTE(MIN_VALUE_SCALE));

  int32_t scale = DEFAULT_SCALE;
  attribute_store_set_reported(min_value_scale_node, &scale, sizeof(scale));

  attribute_store_node_t max_value_scale_node
    = attribute_store_get_first_child_by_type(type_node,
                                              ATTRIBUTE(MAX_VALUE_SCALE));

  attribute_store_set_reported(max_value_scale_node, &scale, sizeof(scale));
}

/**
 * @brief Checks the desired value of a setpoint and validate if it is within
 * the valid range.
 *
 * @param value_node      Attribute Store node for the value to apply.
 * @returns int32_t valid desired value
 */
static int32_t thermostat_setpoint_get_valid_desired_setpoint_value(
  attribute_store_node_t value_node)
{
  int32_t value_to_set = 0;
  attribute_store_get_desired_else_reported(value_node,
                                            &value_to_set,
                                            sizeof(value_to_set));

  zwave_cc_version_t supporting_node_version
    = zwave_command_class_get_version_from_node(
      value_node,
      COMMAND_CLASS_THERMOSTAT_SETPOINT_V3);
  // V1-v2, we don't know the capabilities, so we allow to try anything:
  if (3 > supporting_node_version) {
    return value_to_set;
  }

  // V3 nodes, fetch min/max
  attribute_store_node_t setpoint_type_node
    = attribute_store_get_first_parent_with_type(value_node, ATTRIBUTE(TYPE));
  uint32_t value_scale = CELSIUS_SCALE;
  attribute_store_get_child_reported(setpoint_type_node,
                                     ATTRIBUTE(VALUE_SCALE),
                                     &value_scale,
                                     sizeof(value_scale));
  if (value_scale == FAHRENHEIT_SCALE) {
    value_to_set = FAHRENHEIT_TO_DEGREES(value_to_set)
  }

  int32_t min_value = DEFAULT_MIN_VALUE;
  attribute_store_get_child_reported(setpoint_type_node,
                                     ATTRIBUTE(MIN_VALUE),
                                     &min_value,
                                     sizeof(min_value));
  uint32_t min_value_scale = CELSIUS_SCALE;
  attribute_store_get_child_reported(setpoint_type_node,
                                     ATTRIBUTE(MIN_VALUE_SCALE),
                                     &min_value_scale,
                                     sizeof(min_value_scale));
  if (min_value_scale == FAHRENHEIT_SCALE) {
    min_value = FAHRENHEIT_TO_DEGREES(min_value)
  }

  // Lower bound validation:
  if (value_to_set < min_value) {
    sl_log_debug(LOG_TAG,
                 "Attempting to set a setpoint (%d) lower than the "
                 "minimum (%d). Using the minimum value.",
                 value_to_set,
                 min_value);
    return min_value;
  }

  int32_t max_value = DEFAULT_MAX_VALUE;
  attribute_store_get_child_reported(setpoint_type_node,
                                     ATTRIBUTE(MAX_VALUE),
                                     &max_value,
                                     sizeof(max_value));
  uint32_t max_value_scale = CELSIUS_SCALE;
  attribute_store_get_child_reported(setpoint_type_node,
                                     ATTRIBUTE(MAX_VALUE_SCALE),
                                     &max_value_scale,
                                     sizeof(max_value_scale));
  if (max_value_scale == FAHRENHEIT_SCALE) {
    max_value = FAHRENHEIT_TO_DEGREES(max_value)
  }
  // Upper bound validation:
  if (value_to_set > max_value) {
    sl_log_debug(LOG_TAG,
                 "Attempting to set a setpoint (%d) higher than the "
                 "maximum (%d). Using the maximum value.",
                 value_to_set,
                 max_value);
    return max_value;
  }

  return value_to_set;
}

bool use_b_interpretation(attribute_store_node_t supported_setpoint_types_node)
{
  uint8_t use_b_interpretation = 0;
  attribute_store_get_child_reported(supported_setpoint_types_node,
                                     ATTRIBUTE(USE_B_INTERPRETATION),
                                     &use_b_interpretation,
                                     sizeof(use_b_interpretation));

  return use_b_interpretation > 0;
}

// Remove all ATTRIBUTE(TYPE) from attribute store
void remove_all_thermostat_setpoint_type_attributes(
  attribute_store_node_t endpoint_node)
{
  attribute_store_node_t type_node;
  do {
    type_node = attribute_store_get_node_child_by_type(endpoint_node,
                                                       ATTRIBUTE(TYPE),
                                                       0);
    attribute_store_delete_node(type_node);
  } while (type_node != ATTRIBUTE_STORE_INVALID_NODE);
}

// Create ATTRIBUTE(TYPE) based on bitmask in supported_types
// This function will also check version
void create_all_supported_humidity_setpoint_type(
  attribute_store_node_t endpoint_node,
  uint32_t supported_types,
  bool using_b_interpretation)
{
  // Contains current bit tested
  uint32_t setpoint_mode_current_bit = 0x0;
  // Start with 1 since bit 0 is N/A
  for (uint8_t i = 1; i < MAX_SUPPORTED_SETPOINT_MODES; i++) {
    setpoint_mode_current_bit = 1 << i;
    setpoint_mode_current_bit &= supported_types;
    uint8_t current_type;

    // This bit is marked as not supported so we continue
    if (setpoint_mode_current_bit == 0) {
      continue;
      // THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_COOLING_1 && THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_HEATING_1
      // are the same interpretation.
    } else if (i <= THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_COOLING_1
               || using_b_interpretation) {
      current_type = i;
    } else {  // Shift 4 for standard interpretation for all values after 0x02
      current_type = i + 4;
    }

    // Those values are undefined so we ignore them
    if (current_type >= THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_NOT_SUPPORTED1
        && current_type
             <= THERMOSTAT_SETPOINT_REPORT_SETPOINT_TYPE_NOT_SUPPORTED4) {
      continue;
    }

    // If we are here that means we want to create a setpoint type
    zwave_command_class_thermostat_setpoint_create_type(endpoint_node,
                                                        current_type);
  }
}

sl_status_t
  create_setpoint_type_attributes(attribute_store_node_t endpoint_node)
{
  attribute_store_node_t supported_setpoint_types_node
    = attribute_store_get_first_child_by_type(
      endpoint_node,
      ATTRIBUTE(SUPPORTED_SETPOINT_TYPES));

  // We might not be ready yet, no worries
  if (supported_setpoint_types_node == ATTRIBUTE_STORE_INVALID_NODE) {
    return SL_STATUS_IS_WAITING;
  }

  // Reported bitmask
  uint32_t supported_setpoint_mode_bitmask;
  sl_status_t status
    = attribute_store_get_reported(supported_setpoint_types_node,
                                   &supported_setpoint_mode_bitmask,
                                   sizeof(supported_setpoint_mode_bitmask));

  // We might not be ready yet, no worries
  if (status != SL_STATUS_OK) {
    return SL_STATUS_IS_WAITING;
  }

  // First remove all existing type node
  // This is done to easily update the bitmask or bitmask interpretation so
  // we don't have any leftovers.
  remove_all_thermostat_setpoint_type_attributes(endpoint_node);

  // Check if we need to use B Interpretation
  const bool using_b_interpretation
    = use_b_interpretation(supported_setpoint_types_node);
  // Then create attributed based on supported types
  create_all_supported_humidity_setpoint_type(endpoint_node,
                                              supported_setpoint_mode_bitmask,
                                              using_b_interpretation);
  return SL_STATUS_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Attribute Callback functions
///////////////////////////////////////////////////////////////////////////////
static void
  zwave_command_class_thermostat_setpoint_on_b_interpretation_attribute_update(
    attribute_store_node_t updated_node, attribute_store_change_t change)
{
  if (change != ATTRIBUTE_UPDATED) {
    return;
  }

  attribute_store_node_t endpoint_node
    = attribute_store_get_first_parent_with_type(updated_node,
                                                 ATTRIBUTE_ENDPOINT_ID);

  if (endpoint_node == ATTRIBUTE_STORE_INVALID_NODE) {
    sl_log_warning(LOG_TAG,
                   "Can't get endpoint node associated with b interpretation "
                   "flag. Aborting generation.");
    return;
  }

  // Might fail if some attribute are not ready yet and it's ok, we'll try that later
  create_setpoint_type_attributes(endpoint_node);
}

static void zwave_command_class_thermostat_setpoint_on_version_attribute_update(
  attribute_store_node_t updated_node, attribute_store_change_t change)
{
  if (change == ATTRIBUTE_DELETED) {
    return;
  }

  if (is_zwave_command_class_filtered_for_root_device(
        COMMAND_CLASS_THERMOSTAT_SETPOINT_V3,
        updated_node)
      == true) {
    return;
  }

  // Check that we have the right type of attribute.
  assert(ATTRIBUTE(VERSION) == attribute_store_get_node_type(updated_node));

  uint8_t supporting_node_version = 0;
  attribute_store_read_value(updated_node,
                             REPORTED_ATTRIBUTE,
                             &supporting_node_version,
                             sizeof(supporting_node_version));

  if (supporting_node_version == 0) {
    // Wait for the version to be known.
    return;
  }

  // Now we know we have a supporting node.
  // Just check that the suported setpoint type attribute is present.
  attribute_store_node_t endpoint_node
    = attribute_store_get_node_parent(updated_node);

  // Let the rest of the command class perform the job.
  attribute_store_type_t supported_sensor_types[]
    = {ATTRIBUTE(SUPPORTED_SETPOINT_TYPES)};

  attribute_store_add_if_missing(endpoint_node,
                                 supported_sensor_types,
                                 COUNT_OF(supported_sensor_types));

  // Create B interpretation flag and set default value
  // It is located underneath ATTRIBUTE(SUPPORTED_SETPOINT_TYPES)
  attribute_store_type_t supported_node
    = attribute_store_get_node_child_by_type(
      endpoint_node,
      ATTRIBUTE(SUPPORTED_SETPOINT_TYPES),
      0);

  // Create the attribute and set default value if not already there
  if (attribute_store_get_node_child_by_type(supported_node,
                                             ATTRIBUTE(USE_B_INTERPRETATION),
                                             0)
      == ATTRIBUTE_STORE_INVALID_NODE) {
    // Default value for b interpretation (off)
    uint8_t default_b_interpretation_value = 0;
    // Will create the node if not existant
    attribute_store_set_child_reported(supported_node,
                                       ATTRIBUTE(USE_B_INTERPRETATION),
                                       &default_b_interpretation_value,
                                       sizeof(default_b_interpretation_value));
  }
}

///////////////////////////////////////////////////////////////////////////////
// Attribute resolution functions
///////////////////////////////////////////////////////////////////////////////
sl_status_t zwave_command_class_thermostat_setpoint_supported_get(
  attribute_store_node_t node, uint8_t *frame, uint16_t *frame_len)
{
  // Check that we have the right type of attribute.
  assert(ATTRIBUTE(SUPPORTED_SETPOINT_TYPES)
         == attribute_store_get_node_type(node));

  // Default frame length in case of error
  *frame_len = 0;

  // Supported Get is the same for all versions.
  ZW_THERMOSTAT_SETPOINT_SUPPORTED_GET_V3_FRAME *supported_get_frame
    = (ZW_THERMOSTAT_SETPOINT_SUPPORTED_GET_V3_FRAME *)frame;

  supported_get_frame->cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT_V3;
  supported_get_frame->cmd      = THERMOSTAT_SETPOINT_SUPPORTED_GET_V3;

  *frame_len = sizeof(ZW_THERMOSTAT_SETPOINT_SUPPORTED_GET_V3_FRAME);
  return SL_STATUS_OK;
}

// FIXME: This will be failing CL:0043.01.21.02.1
sl_status_t zwave_command_class_thermostat_setpoint_capabilities_get(
  attribute_store_node_t node, uint8_t *frame, uint16_t *frame_len)
{
  // Check that we have the right type of attribute.
  assert(ATTRIBUTE(MIN_VALUE) == attribute_store_get_node_type(node));
  // Default frame length in case of error
  *frame_len = 0;

  attribute_store_node_t type_node = attribute_store_get_node_parent(node);
  attribute_store_node_t endpoint_node
    = attribute_store_get_node_parent(type_node);
  attribute_store_node_t version_node = attribute_store_get_first_child_by_type(
    endpoint_node,
    ATTRIBUTE_COMMAND_CLASS_THERMOSTAT_SETPOINT_VERSION);

  uint8_t supporting_node_version = 0;
  attribute_store_read_value(version_node,
                             REPORTED_ATTRIBUTE,
                             &supporting_node_version,
                             sizeof(supporting_node_version));

  if (supporting_node_version == 0) {
    // Something weird happened. Bail out.
    sl_log_warning(LOG_TAG, "Cannot read supporting node version.");
    return SL_STATUS_FAIL;
  }

  if (supporting_node_version <= 2) {
    // In version 1-2, they do not have a supported get.
    // here there is no substitution, we we will just return no
    // frame and fill up dummy values ourselves
    zwave_command_class_thermostat_setpoint_set_default_capabilities(type_node);
    return SL_STATUS_ALREADY_EXISTS;

  } else {
    // From version 3, we can ask nodes what they support.
    ZW_THERMOSTAT_SETPOINT_CAPABILITIES_GET_V3_FRAME
    *capabilities_get_frame
      = (ZW_THERMOSTAT_SETPOINT_CAPABILITIES_GET_V3_FRAME *)frame;

    capabilities_get_frame->cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT_V3;
    capabilities_get_frame->cmd      = THERMOSTAT_SETPOINT_CAPABILITIES_GET_V3;
    attribute_store_read_value(type_node,
                               REPORTED_ATTRIBUTE,
                               &capabilities_get_frame->properties1,
                               sizeof(capabilities_get_frame->properties1));

    *frame_len = sizeof(ZW_THERMOSTAT_SETPOINT_CAPABILITIES_GET_V3_FRAME);
    return SL_STATUS_OK;
  }
}

sl_status_t zwave_command_class_thermostat_setpoint_get(
  attribute_store_node_t node, uint8_t *frame, uint16_t *frame_len)
{
  // Check that we have the right type of attribute.
  assert(ATTRIBUTE_COMMAND_CLASS_THERMOSTAT_SETPOINT_VALUE
         == attribute_store_get_node_type(node));

  // Default frame length in case of error
  *frame_len = 0;

  attribute_store_node_t type_node = attribute_store_get_node_parent(node);

  ZW_THERMOSTAT_SETPOINT_GET_V3_FRAME *get_frame
    = (ZW_THERMOSTAT_SETPOINT_GET_V3_FRAME *)frame;

  get_frame->cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT_V3;
  get_frame->cmd      = THERMOSTAT_SETPOINT_GET_V3;
  // get_frame->level ? This is called 4 bits reserved / 4 bits setpoint type.
  attribute_store_read_value(type_node,
                             REPORTED_ATTRIBUTE,
                             &get_frame->level,
                             sizeof(get_frame->level));

  *frame_len = sizeof(ZW_THERMOSTAT_SETPOINT_GET_V3_FRAME);
  return SL_STATUS_OK;
}

sl_status_t zwave_command_class_thermostat_setpoint_set(
  attribute_store_node_t node, uint8_t *frame, uint16_t *frame_len)
{
  // Check that we have the right type of attribute.
  assert(ATTRIBUTE_COMMAND_CLASS_THERMOSTAT_SETPOINT_VALUE
         == attribute_store_get_node_type(node));

  // Default frame length in case of error
  *frame_len = 0;

  attribute_store_node_t type_node  = attribute_store_get_node_parent(node);
  attribute_store_node_t scale_node = attribute_store_get_first_child_by_type(
    type_node,
    ATTRIBUTE_COMMAND_CLASS_THERMOSTAT_SETPOINT_VALUE_SCALE);

  // We will just always use 4 bytes, precision 2.
  ZW_THERMOSTAT_SETPOINT_SET_4BYTE_V3_FRAME *set_frame
    = (ZW_THERMOSTAT_SETPOINT_SET_4BYTE_V3_FRAME *)frame;

  set_frame->cmdClass = COMMAND_CLASS_THERMOSTAT_SETPOINT_V3;
  set_frame->cmd      = THERMOSTAT_SETPOINT_SET_V3;
  // set_frame->level ? This is 4 bits reserved / 4 bits setpoint type.
  set_frame->level = 0;
  attribute_store_get_reported(type_node,
                               &set_frame->level,
                               sizeof(set_frame->level));

  // set_frame->level2 ? This is Precision (3 bits) / Scale (2 bits) / size (3 bits)
  uint32_t setpoint_value_scale = 0;
  // Reuse the same scale as current value.
  attribute_store_get_reported(scale_node,
                               &setpoint_value_scale,
                               sizeof(setpoint_value_scale));

  set_frame->level2 = SET_DEFAULT_PRECISION;
  set_frame->level2 |= SET_DEFAULT_SIZE;
  set_frame->level2 |= ((setpoint_value_scale << 3) & SCALE_MASK);

  int32_t setpoint_value_integer
    = thermostat_setpoint_get_valid_desired_setpoint_value(node);

  set_frame->value1 = (setpoint_value_integer & 0xFF000000) >> 24;  // MSB
  set_frame->value2 = (setpoint_value_integer & 0x00FF0000) >> 16;
  set_frame->value3 = (setpoint_value_integer & 0x0000FF00) >> 8;
  set_frame->value4 = (setpoint_value_integer & 0x000000FF);  // LSB

  *frame_len = sizeof(ZW_THERMOSTAT_SETPOINT_SET_4BYTE_V3_FRAME);
  return SL_STATUS_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Command Handler functions
///////////////////////////////////////////////////////////////////////////////
static sl_status_t zwave_command_class_thermostat_setpoint_handle_report(
  const zwave_controller_connection_info_t *connection_info,
  const uint8_t *frame_data,
  uint16_t frame_length)
{
  // We expect to have at least 1 byte of value
  if (frame_length <= REPORT_VALUE_INDEX) {
    return SL_STATUS_FAIL;
  }

  attribute_store_node_t endpoint_node
    = zwave_command_class_get_endpoint_node(connection_info);

  uint8_t received_type
    = frame_data[REPORT_SETPOINT_TYPE_INDEX] & SETPOINT_TYPE_MASK;

  attribute_store_node_t type_node = attribute_store_get_node_child_by_value(
    endpoint_node,
    ATTRIBUTE_COMMAND_CLASS_THERMOSTAT_SETPOINT_TYPE,
    REPORTED_ATTRIBUTE,
    &received_type,
    sizeof(uint8_t),
    0);

  uint8_t size = frame_data[REPORT_PRECISION_SCALE_SIZE_INDEX] & SIZE_MASK;
  int32_t scale
    = (frame_data[REPORT_PRECISION_SCALE_SIZE_INDEX] & SCALE_MASK) >> 3;
  uint8_t precision
    = (frame_data[REPORT_PRECISION_SCALE_SIZE_INDEX] & PRECISION_MASK) >> 5;

  // FIXME: Here we just ignore this requirement from the CC spec:
  // A receiving node MUST ignore values outside the range advertised in the Thermostat Setpoint
  // Capabilities Report Command for the actual Setpoint type.
  // Save the scale directly
  attribute_store_node_t scale_node = attribute_store_get_first_child_by_type(
    type_node,
    ATTRIBUTE_COMMAND_CLASS_THERMOSTAT_SETPOINT_VALUE_SCALE);

  attribute_store_set_reported(scale_node, &scale, sizeof(scale));

  int32_t setpoint_value
    = command_class_get_int32_value(size,
                                    precision,
                                    &frame_data[REPORT_VALUE_INDEX]);
  sl_log_debug(LOG_TAG,
               "NodeID %d:%d - Thermostat current setpoint value: %.1f",
               (int)connection_info->remote.node_id,
               (int)connection_info->remote.endpoint_id,
               setpoint_value / 1000.0f);

  // Save it in the attribute store, save the value after the scale, that's what the
  // mapper is listening to and the scale has to be correct when they get the callback.
  attribute_store_node_t setpoint_value_node
    = attribute_store_get_first_child_by_type(
      type_node,
      ATTRIBUTE_COMMAND_CLASS_THERMOSTAT_SETPOINT_VALUE);

  attribute_store_set_reported(setpoint_value_node,
                               &setpoint_value,
                               sizeof(setpoint_value));
  // We have a set function for this attribute, so we also align the desired value
  attribute_store_set_desired_as_reported(setpoint_value_node);

  return SL_STATUS_OK;
}

static sl_status_t
  zwave_command_class_thermostat_setpoint_handle_supported_report(
    const zwave_controller_connection_info_t *connection_info,
    const uint8_t *frame_data,
    uint16_t frame_length)
{
  // We expect to have at least 1 bitmask
  if (frame_length <= SUPPORTED_REPORT_BITMASK_INDEX) {
    return SL_STATUS_FAIL;
  }

  // First up, save our supported types in the Attribute Store.
  attribute_store_node_t endpoint_node
    = zwave_command_class_get_endpoint_node(connection_info);

  attribute_store_node_t supported_bitmask_node
    = attribute_store_get_first_child_by_type(
      endpoint_node,
      ATTRIBUTE(SUPPORTED_SETPOINT_TYPES));

  uint32_t supported_setpoint_mode_bits = 0x0000;
  uint8_t bitmask_length                = frame_length - 2;

  // Since we are using uint32_t we can't have more that 4 bit mask
  if (bitmask_length > 4) {
    sl_log_error(
      LOG_TAG,
      "Supported Thermostat SetPoint type Bit Mask length is not supported\n");
    return SL_STATUS_FAIL;
  }

  for (int i = bitmask_length; i > 0; i--) {
    supported_setpoint_mode_bits
      = (supported_setpoint_mode_bits << 8) | frame_data[1 + i];
  }

  attribute_store_set_reported(supported_bitmask_node,
                               &supported_setpoint_mode_bits,
                               sizeof(supported_setpoint_mode_bits));

  return create_setpoint_type_attributes(endpoint_node);
}

static sl_status_t
  zwave_command_class_thermostat_setpoint_handle_capabilities_report(
    const zwave_controller_connection_info_t *connection_info,
    const uint8_t *frame_data,
    uint16_t frame_length)
{
  // Frame too short, ignore
  if (frame_length <= CAPABILITIES_REPORT_MIN_PRECISION_SCALE_SIZE_INDEX) {
    return SL_STATUS_FAIL;
  }

  // Just retrieve the data and save it.
  attribute_store_node_t endpoint_node
    = zwave_command_class_get_endpoint_node(connection_info);

  int8_t received_setpoint_type
    = frame_data[CAPABILITIES_REPORT_SETPOINT_TYPE_INDEX] & SETPOINT_TYPE_MASK;
  attribute_store_node_t type_node = attribute_store_get_node_child_by_value(
    endpoint_node,
    ATTRIBUTE_COMMAND_CLASS_THERMOSTAT_SETPOINT_TYPE,
    REPORTED_ATTRIBUTE,
    (uint8_t *)&received_setpoint_type,
    sizeof(int8_t),
    0);

  if (type_node == ATTRIBUTE_STORE_INVALID_NODE) {
    // Hmm it seems that it's a type that we don't know of.
    // Let's be nice and create it.
    zwave_command_class_thermostat_setpoint_create_type(
      endpoint_node,
      received_setpoint_type);  // Force version 3 to have max compatibility
  }

  // Save the Min value
  attribute_store_node_t supported_min_value_scale_node
    = attribute_store_get_first_child_by_type(
      type_node,
      ATTRIBUTE_COMMAND_CLASS_THERMOSTAT_SETPOINT_MIN_VALUE_SCALE);

  if (supported_min_value_scale_node == ATTRIBUTE_STORE_INVALID_NODE) {
    return SL_STATUS_FAIL;
  }

  uint32_t received_min_value_scale
    = (frame_data[CAPABILITIES_REPORT_MIN_PRECISION_SCALE_SIZE_INDEX]
       & SCALE_MASK)
      >> 3;
  attribute_store_set_reported(supported_min_value_scale_node,
                               &received_min_value_scale,
                               sizeof(received_min_value_scale));

  attribute_store_node_t supported_min_value_node
    = attribute_store_get_first_child_by_type(
      type_node,
      ATTRIBUTE_COMMAND_CLASS_THERMOSTAT_SETPOINT_MIN_VALUE);
  int32_t received_min_value_size
    = frame_data[CAPABILITIES_REPORT_MIN_PRECISION_SCALE_SIZE_INDEX]
      & SIZE_MASK;
  int32_t received_min_value_precision
    = (frame_data[CAPABILITIES_REPORT_MIN_PRECISION_SCALE_SIZE_INDEX]
       & PRECISION_MASK)
      >> 5;

  int32_t received_min_value = command_class_get_int32_value(
    received_min_value_size,
    received_min_value_precision,
    &frame_data[CAPABILITIES_REPORT_MIN_VALUE_INDEX]);

  sl_log_debug(LOG_TAG,
               "NodeID %d:%d - Thermostat Min supported temperature "
               "(3 decimal digits): %d",
               (int)connection_info->remote.node_id,
               (int)connection_info->remote.endpoint_id,
               received_min_value);

  attribute_store_set_reported(supported_min_value_node,
                               &received_min_value,
                               sizeof(received_min_value));

  // Save the Max value
  int32_t max_value_precision_scale_size_index
    = CAPABILITIES_REPORT_MIN_PRECISION_SCALE_SIZE_INDEX
      + received_min_value_size + 1;
  attribute_store_node_t supported_max_value_scale_node
    = attribute_store_get_first_child_by_type(type_node,
                                              ATTRIBUTE(MAX_VALUE_SCALE));

  if (supported_max_value_scale_node == ATTRIBUTE_STORE_INVALID_NODE) {
    return SL_STATUS_FAIL;
  }

  int32_t received_max_value_scale
    = (frame_data[max_value_precision_scale_size_index] & SCALE_MASK) >> 3;
  attribute_store_set_reported(supported_max_value_scale_node,
                               &received_max_value_scale,
                               sizeof(received_max_value_scale));

  attribute_store_node_t supported_max_value_node
    = attribute_store_get_first_child_by_type(type_node, ATTRIBUTE(MAX_VALUE));
  int32_t received_max_value_size
    = frame_data[max_value_precision_scale_size_index] & SIZE_MASK;
  int32_t received_max_value_precision
    = (frame_data[max_value_precision_scale_size_index] & PRECISION_MASK) >> 5;

  int32_t received_max_value = command_class_get_int32_value(
    received_max_value_size,
    received_max_value_precision,
    &frame_data[max_value_precision_scale_size_index + 1]);

  sl_log_debug(LOG_TAG,
               "NodeID %d:%d - Thermostat Max supported temperature "
               "(3 decimal digits): %d",
               (int)connection_info->remote.node_id,
               (int)connection_info->remote.endpoint_id,
               received_max_value);

  attribute_store_set_reported(supported_max_value_node,
                               &received_max_value,
                               sizeof(received_max_value));

  return SL_STATUS_OK;
}

static sl_status_t zwave_command_class_thermostat_setpoint_control_handler(
  const zwave_controller_connection_info_t *connection_info,
  const uint8_t *frame_data,
  uint16_t frame_length)
{
  // Frame too short, it should have not come here.
  if (frame_length <= COMMAND_INDEX) {
    return SL_STATUS_NOT_SUPPORTED;
  }
  assert(frame_data[COMMAND_CLASS_INDEX]
         == COMMAND_CLASS_THERMOSTAT_SETPOINT_V3);

  switch (frame_data[COMMAND_INDEX]) {
    case THERMOSTAT_SETPOINT_REPORT_V3:
      return zwave_command_class_thermostat_setpoint_handle_report(
        connection_info,
        frame_data,
        frame_length);

    case THERMOSTAT_SETPOINT_SUPPORTED_REPORT_V3:
      return zwave_command_class_thermostat_setpoint_handle_supported_report(
        connection_info,
        frame_data,
        frame_length);

    case THERMOSTAT_SETPOINT_CAPABILITIES_REPORT_V3:
      return zwave_command_class_thermostat_setpoint_handle_capabilities_report(
        connection_info,
        frame_data,
        frame_length);

    default:
      return SL_STATUS_NOT_SUPPORTED;
  }
}

///////////////////////////////////////////////////////////////////////////////
// Init functions
///////////////////////////////////////////////////////////////////////////////

sl_status_t zwave_command_class_thermostat_setpoint_init()
{
  // Resolver functions.
  attribute_resolver_register_rule(
    ATTRIBUTE(SUPPORTED_SETPOINT_TYPES),
    NULL,
    zwave_command_class_thermostat_setpoint_supported_get);

  attribute_resolver_register_rule(
    ATTRIBUTE(MIN_VALUE),
    NULL,
    zwave_command_class_thermostat_setpoint_capabilities_get);

  attribute_resolver_register_rule(ATTRIBUTE(VALUE),
                                   zwave_command_class_thermostat_setpoint_set,
                                   zwave_command_class_thermostat_setpoint_get);

  // Listening for supporting nodes
  attribute_store_register_callback_by_type(
    &zwave_command_class_thermostat_setpoint_on_version_attribute_update,
    ATTRIBUTE(VERSION));
  attribute_store_register_callback_by_type(
    &zwave_command_class_thermostat_setpoint_on_b_interpretation_attribute_update,
    ATTRIBUTE(USE_B_INTERPRETATION));

  // Register Thermostat Setpoint CC handler to the Z-Wave CC framework
  zwave_command_handler_t handler = {};
  handler.control_handler
    = &zwave_command_class_thermostat_setpoint_control_handler;
  handler.minimal_scheme             = ZWAVE_CONTROLLER_ENCAPSULATION_NONE;
  handler.command_class              = COMMAND_CLASS_THERMOSTAT_SETPOINT_V3;
  handler.version                    = THERMOSTAT_SETPOINT_VERSION_V3;
  handler.manual_security_validation = false;
  handler.command_class_name         = "Thermostat Setpoint";
  handler.comments                   = "Partial Control: <br>"
                                       "1. Only a few setpoints can be configured. <br>"
                                       "2. Precision/size fields in the set are determined <br>"
                                       "automatically by the controller. ";

  zwave_command_handler_register_handler(handler);

  return SL_STATUS_OK;
}