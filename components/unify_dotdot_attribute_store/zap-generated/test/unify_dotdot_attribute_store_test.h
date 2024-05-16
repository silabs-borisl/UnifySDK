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
// clang-format off
// This file is generated by ZCL Advanced Platform generator. Please don't edit manually.

#ifndef UNIFY_DOTDOT_ATTRIBUTE_STORE_TEST_H
#define UNIFY_DOTDOT_ATTRIBUTE_STORE_TEST_H

#include "dotdot_mqtt_mock.h"


  uic_mqtt_dotdot_basic_force_read_attributes_callback_t get_uic_mqtt_dotdot_basic_force_read_attributes_callback();
  uic_mqtt_dotdot_basic_write_attributes_callback_t get_uic_mqtt_dotdot_basic_write_attributes_callback();


  uic_mqtt_dotdot_basic_reset_to_factory_defaults_callback_t get_uic_mqtt_dotdot_basic_reset_to_factory_defaults_callback();


  uic_mqtt_dotdot_power_configuration_force_read_attributes_callback_t get_uic_mqtt_dotdot_power_configuration_force_read_attributes_callback();
  uic_mqtt_dotdot_power_configuration_write_attributes_callback_t get_uic_mqtt_dotdot_power_configuration_write_attributes_callback();


  uic_mqtt_dotdot_device_temperature_configuration_force_read_attributes_callback_t get_uic_mqtt_dotdot_device_temperature_configuration_force_read_attributes_callback();
  uic_mqtt_dotdot_device_temperature_configuration_write_attributes_callback_t get_uic_mqtt_dotdot_device_temperature_configuration_write_attributes_callback();


  uic_mqtt_dotdot_identify_force_read_attributes_callback_t get_uic_mqtt_dotdot_identify_force_read_attributes_callback();
  uic_mqtt_dotdot_identify_write_attributes_callback_t get_uic_mqtt_dotdot_identify_write_attributes_callback();


  uic_mqtt_dotdot_identify_identify_callback_t get_uic_mqtt_dotdot_identify_identify_callback();


  uic_mqtt_dotdot_identify_identify_query_response_callback_t get_uic_mqtt_dotdot_identify_identify_query_response_callback();


  uic_mqtt_dotdot_identify_identify_query_callback_t get_uic_mqtt_dotdot_identify_identify_query_callback();


  uic_mqtt_dotdot_identify_trigger_effect_callback_t get_uic_mqtt_dotdot_identify_trigger_effect_callback();


  uic_mqtt_dotdot_groups_force_read_attributes_callback_t get_uic_mqtt_dotdot_groups_force_read_attributes_callback();
  uic_mqtt_dotdot_groups_write_attributes_callback_t get_uic_mqtt_dotdot_groups_write_attributes_callback();


  uic_mqtt_dotdot_groups_add_group_callback_t get_uic_mqtt_dotdot_groups_add_group_callback();


  uic_mqtt_dotdot_groups_add_group_response_callback_t get_uic_mqtt_dotdot_groups_add_group_response_callback();


  uic_mqtt_dotdot_groups_view_group_callback_t get_uic_mqtt_dotdot_groups_view_group_callback();


  uic_mqtt_dotdot_groups_view_group_response_callback_t get_uic_mqtt_dotdot_groups_view_group_response_callback();


  uic_mqtt_dotdot_groups_get_group_membership_callback_t get_uic_mqtt_dotdot_groups_get_group_membership_callback();


  uic_mqtt_dotdot_groups_get_group_membership_response_callback_t get_uic_mqtt_dotdot_groups_get_group_membership_response_callback();


  uic_mqtt_dotdot_groups_remove_group_callback_t get_uic_mqtt_dotdot_groups_remove_group_callback();


  uic_mqtt_dotdot_groups_remove_group_response_callback_t get_uic_mqtt_dotdot_groups_remove_group_response_callback();


  uic_mqtt_dotdot_groups_remove_all_groups_callback_t get_uic_mqtt_dotdot_groups_remove_all_groups_callback();


  uic_mqtt_dotdot_groups_add_group_if_identifying_callback_t get_uic_mqtt_dotdot_groups_add_group_if_identifying_callback();


  uic_mqtt_dotdot_scenes_force_read_attributes_callback_t get_uic_mqtt_dotdot_scenes_force_read_attributes_callback();
  uic_mqtt_dotdot_scenes_write_attributes_callback_t get_uic_mqtt_dotdot_scenes_write_attributes_callback();


  uic_mqtt_dotdot_scenes_add_scene_callback_t get_uic_mqtt_dotdot_scenes_add_scene_callback();


  uic_mqtt_dotdot_scenes_add_scene_response_callback_t get_uic_mqtt_dotdot_scenes_add_scene_response_callback();


  uic_mqtt_dotdot_scenes_view_scene_callback_t get_uic_mqtt_dotdot_scenes_view_scene_callback();


  uic_mqtt_dotdot_scenes_view_scene_response_callback_t get_uic_mqtt_dotdot_scenes_view_scene_response_callback();


  uic_mqtt_dotdot_scenes_remove_scene_callback_t get_uic_mqtt_dotdot_scenes_remove_scene_callback();


  uic_mqtt_dotdot_scenes_remove_scene_response_callback_t get_uic_mqtt_dotdot_scenes_remove_scene_response_callback();


  uic_mqtt_dotdot_scenes_remove_all_scenes_callback_t get_uic_mqtt_dotdot_scenes_remove_all_scenes_callback();


  uic_mqtt_dotdot_scenes_remove_all_scenes_response_callback_t get_uic_mqtt_dotdot_scenes_remove_all_scenes_response_callback();


  uic_mqtt_dotdot_scenes_store_scene_callback_t get_uic_mqtt_dotdot_scenes_store_scene_callback();


  uic_mqtt_dotdot_scenes_store_scene_response_callback_t get_uic_mqtt_dotdot_scenes_store_scene_response_callback();


  uic_mqtt_dotdot_scenes_recall_scene_callback_t get_uic_mqtt_dotdot_scenes_recall_scene_callback();


  uic_mqtt_dotdot_scenes_get_scene_membership_callback_t get_uic_mqtt_dotdot_scenes_get_scene_membership_callback();


  uic_mqtt_dotdot_scenes_get_scene_membership_response_callback_t get_uic_mqtt_dotdot_scenes_get_scene_membership_response_callback();


  uic_mqtt_dotdot_scenes_enhanced_add_scene_callback_t get_uic_mqtt_dotdot_scenes_enhanced_add_scene_callback();


  uic_mqtt_dotdot_scenes_enhanced_add_scene_response_callback_t get_uic_mqtt_dotdot_scenes_enhanced_add_scene_response_callback();


  uic_mqtt_dotdot_scenes_enhanced_view_scene_callback_t get_uic_mqtt_dotdot_scenes_enhanced_view_scene_callback();


  uic_mqtt_dotdot_scenes_enhanced_view_scene_response_callback_t get_uic_mqtt_dotdot_scenes_enhanced_view_scene_response_callback();


  uic_mqtt_dotdot_scenes_copy_scene_callback_t get_uic_mqtt_dotdot_scenes_copy_scene_callback();


  uic_mqtt_dotdot_scenes_copy_scene_response_callback_t get_uic_mqtt_dotdot_scenes_copy_scene_response_callback();


  uic_mqtt_dotdot_on_off_force_read_attributes_callback_t get_uic_mqtt_dotdot_on_off_force_read_attributes_callback();
  uic_mqtt_dotdot_on_off_write_attributes_callback_t get_uic_mqtt_dotdot_on_off_write_attributes_callback();


  uic_mqtt_dotdot_on_off_off_callback_t get_uic_mqtt_dotdot_on_off_off_callback();


  uic_mqtt_dotdot_on_off_on_callback_t get_uic_mqtt_dotdot_on_off_on_callback();


  uic_mqtt_dotdot_on_off_toggle_callback_t get_uic_mqtt_dotdot_on_off_toggle_callback();


  uic_mqtt_dotdot_on_off_off_with_effect_callback_t get_uic_mqtt_dotdot_on_off_off_with_effect_callback();


  uic_mqtt_dotdot_on_off_on_with_recall_global_scene_callback_t get_uic_mqtt_dotdot_on_off_on_with_recall_global_scene_callback();


  uic_mqtt_dotdot_on_off_on_with_timed_off_callback_t get_uic_mqtt_dotdot_on_off_on_with_timed_off_callback();


  uic_mqtt_dotdot_level_force_read_attributes_callback_t get_uic_mqtt_dotdot_level_force_read_attributes_callback();
  uic_mqtt_dotdot_level_write_attributes_callback_t get_uic_mqtt_dotdot_level_write_attributes_callback();


  uic_mqtt_dotdot_level_move_to_level_callback_t get_uic_mqtt_dotdot_level_move_to_level_callback();


  uic_mqtt_dotdot_level_move_callback_t get_uic_mqtt_dotdot_level_move_callback();


  uic_mqtt_dotdot_level_step_callback_t get_uic_mqtt_dotdot_level_step_callback();


  uic_mqtt_dotdot_level_stop_callback_t get_uic_mqtt_dotdot_level_stop_callback();


  uic_mqtt_dotdot_level_move_to_level_with_on_off_callback_t get_uic_mqtt_dotdot_level_move_to_level_with_on_off_callback();


  uic_mqtt_dotdot_level_move_with_on_off_callback_t get_uic_mqtt_dotdot_level_move_with_on_off_callback();


  uic_mqtt_dotdot_level_step_with_on_off_callback_t get_uic_mqtt_dotdot_level_step_with_on_off_callback();


  uic_mqtt_dotdot_level_stop_with_on_off_callback_t get_uic_mqtt_dotdot_level_stop_with_on_off_callback();


  uic_mqtt_dotdot_level_move_to_closest_frequency_callback_t get_uic_mqtt_dotdot_level_move_to_closest_frequency_callback();


  uic_mqtt_dotdot_alarms_force_read_attributes_callback_t get_uic_mqtt_dotdot_alarms_force_read_attributes_callback();
  uic_mqtt_dotdot_alarms_write_attributes_callback_t get_uic_mqtt_dotdot_alarms_write_attributes_callback();


  uic_mqtt_dotdot_alarms_reset_alarm_callback_t get_uic_mqtt_dotdot_alarms_reset_alarm_callback();


  uic_mqtt_dotdot_alarms_alarm_callback_t get_uic_mqtt_dotdot_alarms_alarm_callback();


  uic_mqtt_dotdot_alarms_reset_all_alarms_callback_t get_uic_mqtt_dotdot_alarms_reset_all_alarms_callback();


  uic_mqtt_dotdot_alarms_get_alarm_response_callback_t get_uic_mqtt_dotdot_alarms_get_alarm_response_callback();


  uic_mqtt_dotdot_alarms_get_alarm_callback_t get_uic_mqtt_dotdot_alarms_get_alarm_callback();


  uic_mqtt_dotdot_alarms_reset_alarm_log_callback_t get_uic_mqtt_dotdot_alarms_reset_alarm_log_callback();


  uic_mqtt_dotdot_time_force_read_attributes_callback_t get_uic_mqtt_dotdot_time_force_read_attributes_callback();
  uic_mqtt_dotdot_time_write_attributes_callback_t get_uic_mqtt_dotdot_time_write_attributes_callback();


  uic_mqtt_dotdot_poll_control_force_read_attributes_callback_t get_uic_mqtt_dotdot_poll_control_force_read_attributes_callback();
  uic_mqtt_dotdot_poll_control_write_attributes_callback_t get_uic_mqtt_dotdot_poll_control_write_attributes_callback();


  uic_mqtt_dotdot_poll_control_check_in_callback_t get_uic_mqtt_dotdot_poll_control_check_in_callback();


  uic_mqtt_dotdot_poll_control_check_in_response_callback_t get_uic_mqtt_dotdot_poll_control_check_in_response_callback();


  uic_mqtt_dotdot_poll_control_fast_poll_stop_callback_t get_uic_mqtt_dotdot_poll_control_fast_poll_stop_callback();


  uic_mqtt_dotdot_poll_control_set_long_poll_interval_callback_t get_uic_mqtt_dotdot_poll_control_set_long_poll_interval_callback();


  uic_mqtt_dotdot_poll_control_set_short_poll_interval_callback_t get_uic_mqtt_dotdot_poll_control_set_short_poll_interval_callback();


  uic_mqtt_dotdot_shade_configuration_force_read_attributes_callback_t get_uic_mqtt_dotdot_shade_configuration_force_read_attributes_callback();
  uic_mqtt_dotdot_shade_configuration_write_attributes_callback_t get_uic_mqtt_dotdot_shade_configuration_write_attributes_callback();


  uic_mqtt_dotdot_door_lock_force_read_attributes_callback_t get_uic_mqtt_dotdot_door_lock_force_read_attributes_callback();
  uic_mqtt_dotdot_door_lock_write_attributes_callback_t get_uic_mqtt_dotdot_door_lock_write_attributes_callback();


  uic_mqtt_dotdot_door_lock_lock_door_callback_t get_uic_mqtt_dotdot_door_lock_lock_door_callback();


  uic_mqtt_dotdot_door_lock_lock_door_response_callback_t get_uic_mqtt_dotdot_door_lock_lock_door_response_callback();


  uic_mqtt_dotdot_door_lock_unlock_door_callback_t get_uic_mqtt_dotdot_door_lock_unlock_door_callback();


  uic_mqtt_dotdot_door_lock_unlock_door_response_callback_t get_uic_mqtt_dotdot_door_lock_unlock_door_response_callback();


  uic_mqtt_dotdot_door_lock_toggle_callback_t get_uic_mqtt_dotdot_door_lock_toggle_callback();


  uic_mqtt_dotdot_door_lock_toggle_response_callback_t get_uic_mqtt_dotdot_door_lock_toggle_response_callback();


  uic_mqtt_dotdot_door_lock_unlock_with_timeout_callback_t get_uic_mqtt_dotdot_door_lock_unlock_with_timeout_callback();


  uic_mqtt_dotdot_door_lock_unlock_with_timeout_response_callback_t get_uic_mqtt_dotdot_door_lock_unlock_with_timeout_response_callback();


  uic_mqtt_dotdot_door_lock_get_log_record_callback_t get_uic_mqtt_dotdot_door_lock_get_log_record_callback();


  uic_mqtt_dotdot_door_lock_get_log_record_response_callback_t get_uic_mqtt_dotdot_door_lock_get_log_record_response_callback();


  uic_mqtt_dotdot_door_lock_set_pin_code_callback_t get_uic_mqtt_dotdot_door_lock_set_pin_code_callback();


  uic_mqtt_dotdot_door_lock_set_pin_code_response_callback_t get_uic_mqtt_dotdot_door_lock_set_pin_code_response_callback();


  uic_mqtt_dotdot_door_lock_get_pin_code_callback_t get_uic_mqtt_dotdot_door_lock_get_pin_code_callback();


  uic_mqtt_dotdot_door_lock_get_pin_code_response_callback_t get_uic_mqtt_dotdot_door_lock_get_pin_code_response_callback();


  uic_mqtt_dotdot_door_lock_clear_pin_code_callback_t get_uic_mqtt_dotdot_door_lock_clear_pin_code_callback();


  uic_mqtt_dotdot_door_lock_clear_pin_code_response_callback_t get_uic_mqtt_dotdot_door_lock_clear_pin_code_response_callback();


  uic_mqtt_dotdot_door_lock_clear_all_pin_codes_callback_t get_uic_mqtt_dotdot_door_lock_clear_all_pin_codes_callback();


  uic_mqtt_dotdot_door_lock_clear_all_pin_codes_response_callback_t get_uic_mqtt_dotdot_door_lock_clear_all_pin_codes_response_callback();


  uic_mqtt_dotdot_door_lock_set_user_status_callback_t get_uic_mqtt_dotdot_door_lock_set_user_status_callback();


  uic_mqtt_dotdot_door_lock_set_user_status_response_callback_t get_uic_mqtt_dotdot_door_lock_set_user_status_response_callback();


  uic_mqtt_dotdot_door_lock_get_user_status_callback_t get_uic_mqtt_dotdot_door_lock_get_user_status_callback();


  uic_mqtt_dotdot_door_lock_get_user_status_response_callback_t get_uic_mqtt_dotdot_door_lock_get_user_status_response_callback();


  uic_mqtt_dotdot_door_lock_set_weekday_schedule_callback_t get_uic_mqtt_dotdot_door_lock_set_weekday_schedule_callback();


  uic_mqtt_dotdot_door_lock_set_weekday_schedule_response_callback_t get_uic_mqtt_dotdot_door_lock_set_weekday_schedule_response_callback();


  uic_mqtt_dotdot_door_lock_get_weekday_schedule_callback_t get_uic_mqtt_dotdot_door_lock_get_weekday_schedule_callback();


  uic_mqtt_dotdot_door_lock_get_weekday_schedule_response_callback_t get_uic_mqtt_dotdot_door_lock_get_weekday_schedule_response_callback();


  uic_mqtt_dotdot_door_lock_clear_weekday_schedule_callback_t get_uic_mqtt_dotdot_door_lock_clear_weekday_schedule_callback();


  uic_mqtt_dotdot_door_lock_clear_weekday_schedule_response_callback_t get_uic_mqtt_dotdot_door_lock_clear_weekday_schedule_response_callback();


  uic_mqtt_dotdot_door_lock_set_year_day_schedule_callback_t get_uic_mqtt_dotdot_door_lock_set_year_day_schedule_callback();


  uic_mqtt_dotdot_door_lock_set_year_day_schedule_response_callback_t get_uic_mqtt_dotdot_door_lock_set_year_day_schedule_response_callback();


  uic_mqtt_dotdot_door_lock_get_year_day_schedule_callback_t get_uic_mqtt_dotdot_door_lock_get_year_day_schedule_callback();


  uic_mqtt_dotdot_door_lock_get_year_day_schedule_response_callback_t get_uic_mqtt_dotdot_door_lock_get_year_day_schedule_response_callback();


  uic_mqtt_dotdot_door_lock_clear_year_day_schedule_callback_t get_uic_mqtt_dotdot_door_lock_clear_year_day_schedule_callback();


  uic_mqtt_dotdot_door_lock_clear_year_day_schedule_response_callback_t get_uic_mqtt_dotdot_door_lock_clear_year_day_schedule_response_callback();


  uic_mqtt_dotdot_door_lock_set_holiday_schedule_callback_t get_uic_mqtt_dotdot_door_lock_set_holiday_schedule_callback();


  uic_mqtt_dotdot_door_lock_set_holiday_schedule_response_callback_t get_uic_mqtt_dotdot_door_lock_set_holiday_schedule_response_callback();


  uic_mqtt_dotdot_door_lock_get_holiday_schedule_callback_t get_uic_mqtt_dotdot_door_lock_get_holiday_schedule_callback();


  uic_mqtt_dotdot_door_lock_get_holiday_schedule_response_callback_t get_uic_mqtt_dotdot_door_lock_get_holiday_schedule_response_callback();


  uic_mqtt_dotdot_door_lock_clear_holiday_schedule_callback_t get_uic_mqtt_dotdot_door_lock_clear_holiday_schedule_callback();


  uic_mqtt_dotdot_door_lock_clear_holiday_schedule_response_callback_t get_uic_mqtt_dotdot_door_lock_clear_holiday_schedule_response_callback();


  uic_mqtt_dotdot_door_lock_set_user_type_callback_t get_uic_mqtt_dotdot_door_lock_set_user_type_callback();


  uic_mqtt_dotdot_door_lock_set_user_type_response_callback_t get_uic_mqtt_dotdot_door_lock_set_user_type_response_callback();


  uic_mqtt_dotdot_door_lock_get_user_type_callback_t get_uic_mqtt_dotdot_door_lock_get_user_type_callback();


  uic_mqtt_dotdot_door_lock_get_user_type_response_callback_t get_uic_mqtt_dotdot_door_lock_get_user_type_response_callback();


  uic_mqtt_dotdot_door_lock_set_rfid_code_callback_t get_uic_mqtt_dotdot_door_lock_set_rfid_code_callback();


  uic_mqtt_dotdot_door_lock_set_rfid_code_response_callback_t get_uic_mqtt_dotdot_door_lock_set_rfid_code_response_callback();


  uic_mqtt_dotdot_door_lock_get_rfid_code_callback_t get_uic_mqtt_dotdot_door_lock_get_rfid_code_callback();


  uic_mqtt_dotdot_door_lock_get_rfid_code_response_callback_t get_uic_mqtt_dotdot_door_lock_get_rfid_code_response_callback();


  uic_mqtt_dotdot_door_lock_clear_rfid_code_callback_t get_uic_mqtt_dotdot_door_lock_clear_rfid_code_callback();


  uic_mqtt_dotdot_door_lock_clear_rfid_code_response_callback_t get_uic_mqtt_dotdot_door_lock_clear_rfid_code_response_callback();


  uic_mqtt_dotdot_door_lock_clear_all_rfid_codes_callback_t get_uic_mqtt_dotdot_door_lock_clear_all_rfid_codes_callback();


  uic_mqtt_dotdot_door_lock_clear_all_rfid_codes_response_callback_t get_uic_mqtt_dotdot_door_lock_clear_all_rfid_codes_response_callback();


  uic_mqtt_dotdot_door_lock_set_user_callback_t get_uic_mqtt_dotdot_door_lock_set_user_callback();


  uic_mqtt_dotdot_door_lock_get_user_callback_t get_uic_mqtt_dotdot_door_lock_get_user_callback();


  uic_mqtt_dotdot_door_lock_get_user_response_callback_t get_uic_mqtt_dotdot_door_lock_get_user_response_callback();


  uic_mqtt_dotdot_door_lock_clear_user_callback_t get_uic_mqtt_dotdot_door_lock_clear_user_callback();


  uic_mqtt_dotdot_door_lock_operating_event_notification_callback_t get_uic_mqtt_dotdot_door_lock_operating_event_notification_callback();


  uic_mqtt_dotdot_door_lock_programming_event_notification_callback_t get_uic_mqtt_dotdot_door_lock_programming_event_notification_callback();


  uic_mqtt_dotdot_door_lock_set_credential_callback_t get_uic_mqtt_dotdot_door_lock_set_credential_callback();


  uic_mqtt_dotdot_door_lock_set_credential_response_callback_t get_uic_mqtt_dotdot_door_lock_set_credential_response_callback();


  uic_mqtt_dotdot_door_lock_get_credential_status_callback_t get_uic_mqtt_dotdot_door_lock_get_credential_status_callback();


  uic_mqtt_dotdot_door_lock_get_credential_status_response_callback_t get_uic_mqtt_dotdot_door_lock_get_credential_status_response_callback();


  uic_mqtt_dotdot_door_lock_clear_credential_callback_t get_uic_mqtt_dotdot_door_lock_clear_credential_callback();


  uic_mqtt_dotdot_door_lock_unbolt_door_callback_t get_uic_mqtt_dotdot_door_lock_unbolt_door_callback();


  uic_mqtt_dotdot_window_covering_force_read_attributes_callback_t get_uic_mqtt_dotdot_window_covering_force_read_attributes_callback();
  uic_mqtt_dotdot_window_covering_write_attributes_callback_t get_uic_mqtt_dotdot_window_covering_write_attributes_callback();


  uic_mqtt_dotdot_window_covering_up_or_open_callback_t get_uic_mqtt_dotdot_window_covering_up_or_open_callback();


  uic_mqtt_dotdot_window_covering_down_or_close_callback_t get_uic_mqtt_dotdot_window_covering_down_or_close_callback();


  uic_mqtt_dotdot_window_covering_stop_callback_t get_uic_mqtt_dotdot_window_covering_stop_callback();


  uic_mqtt_dotdot_window_covering_go_to_lift_value_callback_t get_uic_mqtt_dotdot_window_covering_go_to_lift_value_callback();


  uic_mqtt_dotdot_window_covering_go_to_lift_percentage_callback_t get_uic_mqtt_dotdot_window_covering_go_to_lift_percentage_callback();


  uic_mqtt_dotdot_window_covering_go_to_tilt_value_callback_t get_uic_mqtt_dotdot_window_covering_go_to_tilt_value_callback();


  uic_mqtt_dotdot_window_covering_go_to_tilt_percentage_callback_t get_uic_mqtt_dotdot_window_covering_go_to_tilt_percentage_callback();


  uic_mqtt_dotdot_barrier_control_force_read_attributes_callback_t get_uic_mqtt_dotdot_barrier_control_force_read_attributes_callback();
  uic_mqtt_dotdot_barrier_control_write_attributes_callback_t get_uic_mqtt_dotdot_barrier_control_write_attributes_callback();


  uic_mqtt_dotdot_barrier_control_go_to_percent_callback_t get_uic_mqtt_dotdot_barrier_control_go_to_percent_callback();


  uic_mqtt_dotdot_barrier_control_stop_callback_t get_uic_mqtt_dotdot_barrier_control_stop_callback();


  uic_mqtt_dotdot_pump_configuration_and_control_force_read_attributes_callback_t get_uic_mqtt_dotdot_pump_configuration_and_control_force_read_attributes_callback();
  uic_mqtt_dotdot_pump_configuration_and_control_write_attributes_callback_t get_uic_mqtt_dotdot_pump_configuration_and_control_write_attributes_callback();


  uic_mqtt_dotdot_thermostat_force_read_attributes_callback_t get_uic_mqtt_dotdot_thermostat_force_read_attributes_callback();
  uic_mqtt_dotdot_thermostat_write_attributes_callback_t get_uic_mqtt_dotdot_thermostat_write_attributes_callback();


  uic_mqtt_dotdot_thermostat_setpoint_raise_or_lower_callback_t get_uic_mqtt_dotdot_thermostat_setpoint_raise_or_lower_callback();


  uic_mqtt_dotdot_thermostat_get_weekly_schedule_response_callback_t get_uic_mqtt_dotdot_thermostat_get_weekly_schedule_response_callback();


  uic_mqtt_dotdot_thermostat_set_weekly_schedule_callback_t get_uic_mqtt_dotdot_thermostat_set_weekly_schedule_callback();


  uic_mqtt_dotdot_thermostat_get_relay_status_log_response_callback_t get_uic_mqtt_dotdot_thermostat_get_relay_status_log_response_callback();


  uic_mqtt_dotdot_thermostat_get_weekly_schedule_callback_t get_uic_mqtt_dotdot_thermostat_get_weekly_schedule_callback();


  uic_mqtt_dotdot_thermostat_clear_weekly_schedule_callback_t get_uic_mqtt_dotdot_thermostat_clear_weekly_schedule_callback();


  uic_mqtt_dotdot_thermostat_get_relay_status_log_callback_t get_uic_mqtt_dotdot_thermostat_get_relay_status_log_callback();


  uic_mqtt_dotdot_fan_control_force_read_attributes_callback_t get_uic_mqtt_dotdot_fan_control_force_read_attributes_callback();
  uic_mqtt_dotdot_fan_control_write_attributes_callback_t get_uic_mqtt_dotdot_fan_control_write_attributes_callback();


  uic_mqtt_dotdot_dehumidification_control_force_read_attributes_callback_t get_uic_mqtt_dotdot_dehumidification_control_force_read_attributes_callback();
  uic_mqtt_dotdot_dehumidification_control_write_attributes_callback_t get_uic_mqtt_dotdot_dehumidification_control_write_attributes_callback();


  uic_mqtt_dotdot_thermostat_user_interface_configuration_force_read_attributes_callback_t get_uic_mqtt_dotdot_thermostat_user_interface_configuration_force_read_attributes_callback();
  uic_mqtt_dotdot_thermostat_user_interface_configuration_write_attributes_callback_t get_uic_mqtt_dotdot_thermostat_user_interface_configuration_write_attributes_callback();


  uic_mqtt_dotdot_color_control_force_read_attributes_callback_t get_uic_mqtt_dotdot_color_control_force_read_attributes_callback();
  uic_mqtt_dotdot_color_control_write_attributes_callback_t get_uic_mqtt_dotdot_color_control_write_attributes_callback();


  uic_mqtt_dotdot_color_control_move_to_hue_callback_t get_uic_mqtt_dotdot_color_control_move_to_hue_callback();


  uic_mqtt_dotdot_color_control_move_hue_callback_t get_uic_mqtt_dotdot_color_control_move_hue_callback();


  uic_mqtt_dotdot_color_control_step_hue_callback_t get_uic_mqtt_dotdot_color_control_step_hue_callback();


  uic_mqtt_dotdot_color_control_move_to_saturation_callback_t get_uic_mqtt_dotdot_color_control_move_to_saturation_callback();


  uic_mqtt_dotdot_color_control_move_saturation_callback_t get_uic_mqtt_dotdot_color_control_move_saturation_callback();


  uic_mqtt_dotdot_color_control_step_saturation_callback_t get_uic_mqtt_dotdot_color_control_step_saturation_callback();


  uic_mqtt_dotdot_color_control_move_to_hue_and_saturation_callback_t get_uic_mqtt_dotdot_color_control_move_to_hue_and_saturation_callback();


  uic_mqtt_dotdot_color_control_move_to_color_callback_t get_uic_mqtt_dotdot_color_control_move_to_color_callback();


  uic_mqtt_dotdot_color_control_move_color_callback_t get_uic_mqtt_dotdot_color_control_move_color_callback();


  uic_mqtt_dotdot_color_control_step_color_callback_t get_uic_mqtt_dotdot_color_control_step_color_callback();


  uic_mqtt_dotdot_color_control_move_to_color_temperature_callback_t get_uic_mqtt_dotdot_color_control_move_to_color_temperature_callback();


  uic_mqtt_dotdot_color_control_enhanced_move_to_hue_callback_t get_uic_mqtt_dotdot_color_control_enhanced_move_to_hue_callback();


  uic_mqtt_dotdot_color_control_enhanced_move_hue_callback_t get_uic_mqtt_dotdot_color_control_enhanced_move_hue_callback();


  uic_mqtt_dotdot_color_control_enhanced_step_hue_callback_t get_uic_mqtt_dotdot_color_control_enhanced_step_hue_callback();


  uic_mqtt_dotdot_color_control_enhanced_move_to_hue_and_saturation_callback_t get_uic_mqtt_dotdot_color_control_enhanced_move_to_hue_and_saturation_callback();


  uic_mqtt_dotdot_color_control_color_loop_set_callback_t get_uic_mqtt_dotdot_color_control_color_loop_set_callback();


  uic_mqtt_dotdot_color_control_stop_move_step_callback_t get_uic_mqtt_dotdot_color_control_stop_move_step_callback();


  uic_mqtt_dotdot_color_control_move_color_temperature_callback_t get_uic_mqtt_dotdot_color_control_move_color_temperature_callback();


  uic_mqtt_dotdot_color_control_step_color_temperature_callback_t get_uic_mqtt_dotdot_color_control_step_color_temperature_callback();


  uic_mqtt_dotdot_ballast_configuration_force_read_attributes_callback_t get_uic_mqtt_dotdot_ballast_configuration_force_read_attributes_callback();
  uic_mqtt_dotdot_ballast_configuration_write_attributes_callback_t get_uic_mqtt_dotdot_ballast_configuration_write_attributes_callback();


  uic_mqtt_dotdot_illuminance_measurement_force_read_attributes_callback_t get_uic_mqtt_dotdot_illuminance_measurement_force_read_attributes_callback();
  uic_mqtt_dotdot_illuminance_measurement_write_attributes_callback_t get_uic_mqtt_dotdot_illuminance_measurement_write_attributes_callback();


  uic_mqtt_dotdot_illuminance_level_sensing_force_read_attributes_callback_t get_uic_mqtt_dotdot_illuminance_level_sensing_force_read_attributes_callback();
  uic_mqtt_dotdot_illuminance_level_sensing_write_attributes_callback_t get_uic_mqtt_dotdot_illuminance_level_sensing_write_attributes_callback();


  uic_mqtt_dotdot_temperature_measurement_force_read_attributes_callback_t get_uic_mqtt_dotdot_temperature_measurement_force_read_attributes_callback();
  uic_mqtt_dotdot_temperature_measurement_write_attributes_callback_t get_uic_mqtt_dotdot_temperature_measurement_write_attributes_callback();


  uic_mqtt_dotdot_pressure_measurement_force_read_attributes_callback_t get_uic_mqtt_dotdot_pressure_measurement_force_read_attributes_callback();
  uic_mqtt_dotdot_pressure_measurement_write_attributes_callback_t get_uic_mqtt_dotdot_pressure_measurement_write_attributes_callback();


  uic_mqtt_dotdot_flow_measurement_force_read_attributes_callback_t get_uic_mqtt_dotdot_flow_measurement_force_read_attributes_callback();
  uic_mqtt_dotdot_flow_measurement_write_attributes_callback_t get_uic_mqtt_dotdot_flow_measurement_write_attributes_callback();


  uic_mqtt_dotdot_relativity_humidity_force_read_attributes_callback_t get_uic_mqtt_dotdot_relativity_humidity_force_read_attributes_callback();
  uic_mqtt_dotdot_relativity_humidity_write_attributes_callback_t get_uic_mqtt_dotdot_relativity_humidity_write_attributes_callback();


  uic_mqtt_dotdot_occupancy_sensing_force_read_attributes_callback_t get_uic_mqtt_dotdot_occupancy_sensing_force_read_attributes_callback();
  uic_mqtt_dotdot_occupancy_sensing_write_attributes_callback_t get_uic_mqtt_dotdot_occupancy_sensing_write_attributes_callback();


  uic_mqtt_dotdot_soil_moisture_force_read_attributes_callback_t get_uic_mqtt_dotdot_soil_moisture_force_read_attributes_callback();
  uic_mqtt_dotdot_soil_moisture_write_attributes_callback_t get_uic_mqtt_dotdot_soil_moisture_write_attributes_callback();


  uic_mqtt_dotdot_ph_measurement_force_read_attributes_callback_t get_uic_mqtt_dotdot_ph_measurement_force_read_attributes_callback();
  uic_mqtt_dotdot_ph_measurement_write_attributes_callback_t get_uic_mqtt_dotdot_ph_measurement_write_attributes_callback();


  uic_mqtt_dotdot_electrical_conductivity_measurement_force_read_attributes_callback_t get_uic_mqtt_dotdot_electrical_conductivity_measurement_force_read_attributes_callback();
  uic_mqtt_dotdot_electrical_conductivity_measurement_write_attributes_callback_t get_uic_mqtt_dotdot_electrical_conductivity_measurement_write_attributes_callback();


  uic_mqtt_dotdot_wind_speed_measurement_force_read_attributes_callback_t get_uic_mqtt_dotdot_wind_speed_measurement_force_read_attributes_callback();
  uic_mqtt_dotdot_wind_speed_measurement_write_attributes_callback_t get_uic_mqtt_dotdot_wind_speed_measurement_write_attributes_callback();


  uic_mqtt_dotdot_carbon_monoxide_force_read_attributes_callback_t get_uic_mqtt_dotdot_carbon_monoxide_force_read_attributes_callback();
  uic_mqtt_dotdot_carbon_monoxide_write_attributes_callback_t get_uic_mqtt_dotdot_carbon_monoxide_write_attributes_callback();


  uic_mqtt_dotdot_carbon_dioxide_force_read_attributes_callback_t get_uic_mqtt_dotdot_carbon_dioxide_force_read_attributes_callback();
  uic_mqtt_dotdot_carbon_dioxide_write_attributes_callback_t get_uic_mqtt_dotdot_carbon_dioxide_write_attributes_callback();


  uic_mqtt_dotdot_pm25_force_read_attributes_callback_t get_uic_mqtt_dotdot_pm25_force_read_attributes_callback();
  uic_mqtt_dotdot_pm25_write_attributes_callback_t get_uic_mqtt_dotdot_pm25_write_attributes_callback();


  uic_mqtt_dotdot_ias_zone_force_read_attributes_callback_t get_uic_mqtt_dotdot_ias_zone_force_read_attributes_callback();
  uic_mqtt_dotdot_ias_zone_write_attributes_callback_t get_uic_mqtt_dotdot_ias_zone_write_attributes_callback();


  uic_mqtt_dotdot_ias_zone_zone_enroll_response_callback_t get_uic_mqtt_dotdot_ias_zone_zone_enroll_response_callback();


  uic_mqtt_dotdot_ias_zone_zone_status_change_notification_callback_t get_uic_mqtt_dotdot_ias_zone_zone_status_change_notification_callback();


  uic_mqtt_dotdot_ias_zone_initiate_normal_operation_mode_callback_t get_uic_mqtt_dotdot_ias_zone_initiate_normal_operation_mode_callback();


  uic_mqtt_dotdot_ias_zone_zone_enroll_request_callback_t get_uic_mqtt_dotdot_ias_zone_zone_enroll_request_callback();


  uic_mqtt_dotdot_ias_zone_initiate_test_mode_callback_t get_uic_mqtt_dotdot_ias_zone_initiate_test_mode_callback();


  uic_mqtt_dotdot_iaswd_force_read_attributes_callback_t get_uic_mqtt_dotdot_iaswd_force_read_attributes_callback();
  uic_mqtt_dotdot_iaswd_write_attributes_callback_t get_uic_mqtt_dotdot_iaswd_write_attributes_callback();


  uic_mqtt_dotdot_iaswd_start_warning_callback_t get_uic_mqtt_dotdot_iaswd_start_warning_callback();


  uic_mqtt_dotdot_iaswd_squawk_callback_t get_uic_mqtt_dotdot_iaswd_squawk_callback();


  uic_mqtt_dotdot_metering_force_read_attributes_callback_t get_uic_mqtt_dotdot_metering_force_read_attributes_callback();
  uic_mqtt_dotdot_metering_write_attributes_callback_t get_uic_mqtt_dotdot_metering_write_attributes_callback();


  uic_mqtt_dotdot_electrical_measurement_force_read_attributes_callback_t get_uic_mqtt_dotdot_electrical_measurement_force_read_attributes_callback();
  uic_mqtt_dotdot_electrical_measurement_write_attributes_callback_t get_uic_mqtt_dotdot_electrical_measurement_write_attributes_callback();


  uic_mqtt_dotdot_electrical_measurement_get_profile_info_response_callback_t get_uic_mqtt_dotdot_electrical_measurement_get_profile_info_response_callback();


  uic_mqtt_dotdot_electrical_measurement_get_profile_info_callback_t get_uic_mqtt_dotdot_electrical_measurement_get_profile_info_callback();


  uic_mqtt_dotdot_electrical_measurement_get_measurement_profile_response_callback_t get_uic_mqtt_dotdot_electrical_measurement_get_measurement_profile_response_callback();


  uic_mqtt_dotdot_electrical_measurement_get_measurement_profile_callback_t get_uic_mqtt_dotdot_electrical_measurement_get_measurement_profile_callback();


  uic_mqtt_dotdot_diagnostics_force_read_attributes_callback_t get_uic_mqtt_dotdot_diagnostics_force_read_attributes_callback();
  uic_mqtt_dotdot_diagnostics_write_attributes_callback_t get_uic_mqtt_dotdot_diagnostics_write_attributes_callback();


  uic_mqtt_dotdot_protocol_controller_rf_telemetry_force_read_attributes_callback_t get_uic_mqtt_dotdot_protocol_controller_rf_telemetry_force_read_attributes_callback();
  uic_mqtt_dotdot_protocol_controller_rf_telemetry_write_attributes_callback_t get_uic_mqtt_dotdot_protocol_controller_rf_telemetry_write_attributes_callback();


  uic_mqtt_dotdot_protocol_controller_rf_telemetry_tx_report_callback_t get_uic_mqtt_dotdot_protocol_controller_rf_telemetry_tx_report_callback();


  uic_mqtt_dotdot_state_force_read_attributes_callback_t get_uic_mqtt_dotdot_state_force_read_attributes_callback();
  uic_mqtt_dotdot_state_write_attributes_callback_t get_uic_mqtt_dotdot_state_write_attributes_callback();


  uic_mqtt_dotdot_state_remove_callback_t get_uic_mqtt_dotdot_state_remove_callback();


  uic_mqtt_dotdot_state_remove_offline_callback_t get_uic_mqtt_dotdot_state_remove_offline_callback();


  uic_mqtt_dotdot_state_discover_neighbors_callback_t get_uic_mqtt_dotdot_state_discover_neighbors_callback();


  uic_mqtt_dotdot_state_interview_callback_t get_uic_mqtt_dotdot_state_interview_callback();


  uic_mqtt_dotdot_state_discover_security_callback_t get_uic_mqtt_dotdot_state_discover_security_callback();


  uic_mqtt_dotdot_binding_force_read_attributes_callback_t get_uic_mqtt_dotdot_binding_force_read_attributes_callback();
  uic_mqtt_dotdot_binding_write_attributes_callback_t get_uic_mqtt_dotdot_binding_write_attributes_callback();


  uic_mqtt_dotdot_binding_bind_callback_t get_uic_mqtt_dotdot_binding_bind_callback();


  uic_mqtt_dotdot_binding_unbind_callback_t get_uic_mqtt_dotdot_binding_unbind_callback();


  uic_mqtt_dotdot_binding_bind_to_protocol_controller_callback_t get_uic_mqtt_dotdot_binding_bind_to_protocol_controller_callback();


  uic_mqtt_dotdot_binding_unbind_from_protocol_controller_callback_t get_uic_mqtt_dotdot_binding_unbind_from_protocol_controller_callback();


  uic_mqtt_dotdot_system_metrics_force_read_attributes_callback_t get_uic_mqtt_dotdot_system_metrics_force_read_attributes_callback();
  uic_mqtt_dotdot_system_metrics_write_attributes_callback_t get_uic_mqtt_dotdot_system_metrics_write_attributes_callback();


  uic_mqtt_dotdot_application_monitoring_force_read_attributes_callback_t get_uic_mqtt_dotdot_application_monitoring_force_read_attributes_callback();
  uic_mqtt_dotdot_application_monitoring_write_attributes_callback_t get_uic_mqtt_dotdot_application_monitoring_write_attributes_callback();


  uic_mqtt_dotdot_application_monitoring_log_entry_callback_t get_uic_mqtt_dotdot_application_monitoring_log_entry_callback();


  uic_mqtt_dotdot_name_and_location_force_read_attributes_callback_t get_uic_mqtt_dotdot_name_and_location_force_read_attributes_callback();
  uic_mqtt_dotdot_name_and_location_write_attributes_callback_t get_uic_mqtt_dotdot_name_and_location_write_attributes_callback();


  uic_mqtt_dotdot_configuration_parameters_force_read_attributes_callback_t get_uic_mqtt_dotdot_configuration_parameters_force_read_attributes_callback();
  uic_mqtt_dotdot_configuration_parameters_write_attributes_callback_t get_uic_mqtt_dotdot_configuration_parameters_write_attributes_callback();


  uic_mqtt_dotdot_configuration_parameters_discover_parameter_callback_t get_uic_mqtt_dotdot_configuration_parameters_discover_parameter_callback();


  uic_mqtt_dotdot_configuration_parameters_default_reset_all_parameters_callback_t get_uic_mqtt_dotdot_configuration_parameters_default_reset_all_parameters_callback();


  uic_mqtt_dotdot_configuration_parameters_set_parameter_callback_t get_uic_mqtt_dotdot_configuration_parameters_set_parameter_callback();


  uic_mqtt_dotdot_configuration_parameters_discover_parameter_range_callback_t get_uic_mqtt_dotdot_configuration_parameters_discover_parameter_range_callback();


  uic_mqtt_dotdot_aox_locator_force_read_attributes_callback_t get_uic_mqtt_dotdot_aox_locator_force_read_attributes_callback();
  uic_mqtt_dotdot_aox_locator_write_attributes_callback_t get_uic_mqtt_dotdot_aox_locator_write_attributes_callback();


  uic_mqtt_dotdot_aox_locator_iq_report_callback_t get_uic_mqtt_dotdot_aox_locator_iq_report_callback();


  uic_mqtt_dotdot_aox_locator_angle_report_callback_t get_uic_mqtt_dotdot_aox_locator_angle_report_callback();


  uic_mqtt_dotdot_aox_locator_angle_correction_callback_t get_uic_mqtt_dotdot_aox_locator_angle_correction_callback();


  uic_mqtt_dotdot_aox_position_estimation_force_read_attributes_callback_t get_uic_mqtt_dotdot_aox_position_estimation_force_read_attributes_callback();
  uic_mqtt_dotdot_aox_position_estimation_write_attributes_callback_t get_uic_mqtt_dotdot_aox_position_estimation_write_attributes_callback();


  uic_mqtt_dotdot_protocol_controller_network_management_force_read_attributes_callback_t get_uic_mqtt_dotdot_protocol_controller_network_management_force_read_attributes_callback();
  uic_mqtt_dotdot_protocol_controller_network_management_write_attributes_callback_t get_uic_mqtt_dotdot_protocol_controller_network_management_write_attributes_callback();


  uic_mqtt_dotdot_protocol_controller_network_management_write_callback_t get_uic_mqtt_dotdot_protocol_controller_network_management_write_callback();


  uic_mqtt_dotdot_descriptor_force_read_attributes_callback_t get_uic_mqtt_dotdot_descriptor_force_read_attributes_callback();
  uic_mqtt_dotdot_descriptor_write_attributes_callback_t get_uic_mqtt_dotdot_descriptor_write_attributes_callback();


  uic_mqtt_dotdot_unify_fan_control_force_read_attributes_callback_t get_uic_mqtt_dotdot_unify_fan_control_force_read_attributes_callback();
  uic_mqtt_dotdot_unify_fan_control_write_attributes_callback_t get_uic_mqtt_dotdot_unify_fan_control_write_attributes_callback();


  uic_mqtt_dotdot_unify_fan_control_set_fan_mode_callback_t get_uic_mqtt_dotdot_unify_fan_control_set_fan_mode_callback();


  uic_mqtt_dotdot_unify_fan_control_turn_off_callback_t get_uic_mqtt_dotdot_unify_fan_control_turn_off_callback();

#endif // UNIFY_DOTDOT_ATTRIBUTE_STORE_TEST_H