/******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
 ******************************************************************************
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 *****************************************************************************/

/**
 * @defgroup zwave_command_class_thermostat_operating_state
 * @brief Thermostat Operating State Command Class handlers and control function
 *
 * This module implement some of the functions to control the
 * Thermostat Operating State Command Class
 *
 * @{
 */

#ifndef ZWAVE_COMMAND_CLASS_THERMOSTAT_OPERATING_STATE_H
#define ZWAVE_COMMAND_CLASS_THERMOSTAT_OPERATING_STATE_H

#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

sl_status_t zwave_command_class_thermostat_operating_state_init();

#ifdef __cplusplus
}
#endif

#endif  //ZWAVE_COMMAND_CLASS_THERMOSTAT_OPERATING_STATE_H
/** @} end zwave_command_class_thermostat_operating_state */