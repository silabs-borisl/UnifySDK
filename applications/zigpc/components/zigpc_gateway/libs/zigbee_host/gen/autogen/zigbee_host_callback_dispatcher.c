/***************************************************************************//**
 * @file zigbee_host_callback_dispatcher.c
 * @brief ZigBee host dispatcher definitions.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include PLATFORM_HEADER
#include "zigbee_host_callback_dispatcher.h"


void sli_zb_af_ncp_init(void)
{
  sl_zigbee_af_address_table_ncp_init_cb();
  sl_zigbee_af_ncp_configuration_ncp_init_cb();
  emberAfNcpInitCallback();
}
