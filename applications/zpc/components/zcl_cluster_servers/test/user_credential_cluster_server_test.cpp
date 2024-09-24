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

// Cpp
#include <stdlib.h>
#include "workaround_for_test.hpp"
#include "attribute.hpp"

extern "C" {
#include "user_credential_cluster_server.h"
#include "zwave_command_class_user_credential.h"
#include "unity.h"

// Definitions
#include "dotdot_cluster_id_definitions.h"
#include "attribute_store_defined_attribute_types.h"
#include "zwave_command_class_association_types.h"
#include "zap-types.h"
#include "zwave_command_class_version_types.h"

// ZPC Components
#include "zpc_attribute_store_type_registration.h"

// Test helpers
#include "zpc_attribute_store_test_helper.h"
#include "sl_log.h"

// Unify components
#include "datastore.h"
#include "attribute_store.h"
#include "attribute_store_helper.h"
#include "attribute_store_fixt.h"
#include "unify_dotdot_attribute_store_node_state.h"

// Mocks
#include "dotdot_mqtt_mock.h"
#include "uic_mqtt_mock.h"

// Attribute macro, shortening those long defines for attribute types:
#define ATTRIBUTE(type) ATTRIBUTE_COMMAND_CLASS_USER_CREDENTIAL_##type

// Useful definitions
attribute_store::attribute cpp_endpoint_node;

// Header declarations
void mock_deletion_user_mqtt_topic(user_credential_user_unique_id_t user_id);
void mock_deletion_cred_mqtt_topic(user_credential_user_unique_id_t user_id,
                                   user_credential_type_t credential_type,
                                   user_credential_slot_t credential_slot);
void mock_deletion_cred_rule_mqtt_topic(user_credential_type_t credential_type);
void setup_user_capabilities();
void setup_cred_capabilities();

// Keep a reference to the mqtt topics we want to test
// Stored as <topic, payload>
static std::vector<std::pair<std::string, std::string>> mqtt_topics;
static std::vector<user_credential_user_unique_id_t> created_user_id;
static std::vector<std::tuple<user_credential_user_unique_id_t,
                              user_credential_type_t,
                              user_credential_slot_t>>
  created_credential_ids;
static std::vector<user_credential_type_t> created_supported_credential_types;

// Callback functions
// clang-format off
uic_mqtt_dotdot_user_credential_add_user_callback_t add_user_command = NULL;
uic_mqtt_dotdot_user_credential_delete_user_callback_t delete_user_command = NULL;
uic_mqtt_dotdot_user_credential_modify_user_callback_t modify_user_command = NULL;
uic_mqtt_dotdot_user_credential_add_credential_callback_t add_credential_command = NULL;
uic_mqtt_dotdot_user_credential_modify_credential_callback_t modify_credential_command = NULL;
uic_mqtt_dotdot_user_credential_delete_credential_callback_t delete_credential_command = NULL;
uic_mqtt_dotdot_user_credential_delete_all_users_callback_t delete_all_users_command = NULL;
uic_mqtt_dotdot_user_credential_delete_all_credentials_callback_t delete_all_credentials_command = NULL;
uic_mqtt_dotdot_user_credential_delete_all_credentials_by_type_callback_t delete_all_credentials_by_type_command = NULL;
uic_mqtt_dotdot_user_credential_delete_all_credentials_for_user_callback_t delete_all_credentials_for_user_command = NULL;
uic_mqtt_dotdot_user_credential_delete_all_credentials_for_user_by_type_callback_t delete_all_credentials_for_user_by_type_command = NULL;
uic_mqtt_dotdot_user_credential_credential_learn_start_add_callback_t credential_learn_start_add_command = NULL;
uic_mqtt_dotdot_user_credential_credential_learn_start_modify_callback_t credential_learn_start_modify_command = NULL;
uic_mqtt_dotdot_user_credential_credential_learn_stop_callback_t credential_learn_stop_command = NULL;
uic_mqtt_dotdot_user_credential_credential_association_callback_t credential_association_command = NULL;
uic_mqtt_dotdot_user_credential_get_user_checksum_callback_t get_user_checksum_command = NULL;
uic_mqtt_dotdot_user_credential_get_credential_checksum_callback_t get_credential_checksum_command = NULL;
uic_mqtt_dotdot_user_credential_get_all_users_checksum_callback_t get_all_users_checksum_command = NULL;
uic_mqtt_dotdot_user_credential_set_admin_pin_code_callback_t set_admin_pin_code_command = NULL;
uic_mqtt_dotdot_user_credential_deactivate_admin_pin_code_callback_t deactivate_admin_pin_code_command = NULL;
// clang-format on

// Stub functions for intercepting callback registration.
void uic_mqtt_dotdot_user_credential_add_user_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_add_user_callback_t callback,
  int cmock_num_calls)
{
  add_user_command = callback;
}

void uic_mqtt_dotdot_user_credential_delete_user_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_delete_user_callback_t callback,
  int cmock_num_calls)
{
  delete_user_command = callback;
}

void uic_mqtt_dotdot_user_credential_modify_user_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_modify_user_callback_t callback,
  int cmock_num_calls)
{
  modify_user_command = callback;
}

void uic_mqtt_dotdot_user_credential_add_credential_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_add_credential_callback_t callback,
  int cmock_num_calls)
{
  add_credential_command = callback;
}
void uic_mqtt_dotdot_user_credential_modify_credential_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_add_credential_callback_t callback,
  int cmock_num_calls)
{
  modify_credential_command = callback;
}
void uic_mqtt_dotdot_user_credential_delete_credential_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_delete_credential_callback_t callback,
  int cmock_num_calls)
{
  delete_credential_command = callback;
}
void uic_mqtt_dotdot_user_credential_delete_all_users_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_delete_all_users_callback_t callback,
  int cmock_num_calls)
{
  delete_all_users_command = callback;
}
void uic_mqtt_dotdot_user_credential_delete_all_credentials_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_delete_all_credentials_callback_t
    callback,
  int cmock_num_calls)
{
  delete_all_credentials_command = callback;
}
void uic_mqtt_dotdot_user_credential_delete_all_credentials_by_type_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_delete_all_credentials_by_type_callback_t
    callback,
  int cmock_num_calls)
{
  delete_all_credentials_by_type_command = callback;
}
void uic_mqtt_dotdot_user_credential_delete_all_credentials_for_user_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_delete_all_credentials_for_user_callback_t
    callback,
  int cmock_num_calls)
{
  delete_all_credentials_for_user_command = callback;
}
void uic_mqtt_dotdot_user_credential_delete_all_credentials_for_user_by_type_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_delete_all_credentials_for_user_by_type_callback_t
    callback,
  int cmock_num_calls)
{
  delete_all_credentials_for_user_by_type_command = callback;
}

void uic_mqtt_dotdot_user_credential_credential_learn_start_add_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_credential_learn_start_add_callback_t
    callback,
  int cmock_num_calls)
{
  credential_learn_start_add_command = callback;
}

void uic_mqtt_dotdot_user_credential_credential_learn_start_modify_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_credential_learn_start_modify_callback_t
    callback,
  int cmock_num_calls)
{
  credential_learn_start_modify_command = callback;
}

void uic_mqtt_dotdot_user_credential_credential_learn_stop_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_credential_learn_stop_callback_t
    callback,
  int cmock_num_calls)
{
  credential_learn_stop_command = callback;
}

void uic_mqtt_dotdot_user_credential_credential_association_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_credential_association_callback_t
    callback,
  int cmock_num_calls)
{
  credential_association_command = callback;
}

void uic_mqtt_dotdot_user_credential_get_user_checksum_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_get_user_checksum_callback_t callback,
  int cmock_num_calls)
{
  get_user_checksum_command = callback;
}

void uic_mqtt_dotdot_user_credential_get_credential_checksum_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_get_credential_checksum_callback_t
    callback,
  int cmock_num_calls)
{
  get_credential_checksum_command = callback;
}

void uic_mqtt_dotdot_user_credential_get_all_users_checksum_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_get_all_users_checksum_callback_t
    callback,
  int cmock_num_calls)
{
  get_all_users_checksum_command = callback;
}

void uic_mqtt_dotdot_user_credential_set_admin_pin_code_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_set_admin_pin_code_callback_t callback,
  int cmock_num_calls)
{
  set_admin_pin_code_command = callback;
}

void uic_mqtt_dotdot_user_credential_deactivate_admin_pin_code_callback_set_stub(
  const uic_mqtt_dotdot_user_credential_deactivate_admin_pin_code_callback_t
    callback,
  int cmock_num_calls)
{
  deactivate_admin_pin_code_command = callback;
}

/// Setup the test suite (called once before all test_xxx functions are called)
void suiteSetUp()
{
  datastore_init(":memory:");
  attribute_store_init();
  zpc_attribute_store_register_known_attribute_types();
  zwave_unid_set_home_id(home_id);
}

/// Teardown the test suite (called once after all test_xxx functions are called)
int suiteTearDown(int num_failures)
{
  attribute_store_teardown();
  datastore_teardown();
  return num_failures;
}

/// Called before each and every test
void setUp()
{
  sl_log_set_level(sl_log_level::SL_LOG_INFO);

  // If you can to enable MQTT topics logs :
  // sl_log_set_tag_level("user_credential_cluster_server",
  //                      sl_log_level::SL_LOG_DEBUG);

  sl_log_set_tag_level("zwave_command_class_user_credential",
                       sl_log_level::SL_LOG_DEBUG);
  sl_log_set_tag_level("attribute_store", sl_log_level::SL_LOG_DEBUG);

  // WARNING : Order matters here
  // Check if credential rules need to be removed
  for (auto cred_type: created_supported_credential_types) {
    mock_deletion_cred_rule_mqtt_topic(cred_type);
  }
  // Check if any users that need to be removed
  for (auto user_id: created_user_id) {
    // Check if MQTT topics for deletion are correctly published
    mock_deletion_user_mqtt_topic(user_id);
  }
  for (auto cred_id: created_credential_ids) {
    mock_deletion_cred_mqtt_topic(std::get<0>(cred_id),
                                  std::get<1>(cred_id),
                                  std::get<2>(cred_id));
  }

  zpc_attribute_store_test_helper_create_network();

  // Intercept the dotdot MQTT callbacks
  add_user_command       = NULL;
  modify_user_command    = NULL;
  delete_user_command    = NULL;
  add_credential_command = NULL;

  mqtt_topics.clear();
  created_user_id.clear();
  created_credential_ids.clear();
  created_supported_credential_types.clear();
  // clang-format off
  // User
  uic_mqtt_dotdot_user_credential_add_user_callback_set_Stub(&uic_mqtt_dotdot_user_credential_add_user_callback_set_stub);
  uic_mqtt_dotdot_user_credential_delete_user_callback_set_Stub(&uic_mqtt_dotdot_user_credential_delete_user_callback_set_stub);  
  uic_mqtt_dotdot_user_credential_modify_user_callback_set_Stub(&uic_mqtt_dotdot_user_credential_modify_user_callback_set_stub); 
  // Credentials
  uic_mqtt_dotdot_user_credential_add_credential_callback_set_Stub(&uic_mqtt_dotdot_user_credential_add_credential_callback_set_stub);
  uic_mqtt_dotdot_user_credential_modify_credential_callback_set_Stub(&uic_mqtt_dotdot_user_credential_modify_credential_callback_set_stub);
  uic_mqtt_dotdot_user_credential_delete_credential_callback_set_Stub(&uic_mqtt_dotdot_user_credential_delete_credential_callback_set_stub);
  // Delete all
  uic_mqtt_dotdot_user_credential_delete_all_users_callback_set_Stub(&uic_mqtt_dotdot_user_credential_delete_all_users_callback_set_stub);
  uic_mqtt_dotdot_user_credential_delete_all_credentials_callback_set_Stub(&uic_mqtt_dotdot_user_credential_delete_all_credentials_callback_set_stub);
  uic_mqtt_dotdot_user_credential_delete_all_credentials_by_type_callback_set_Stub(&uic_mqtt_dotdot_user_credential_delete_all_credentials_by_type_callback_set_stub);
  uic_mqtt_dotdot_user_credential_delete_all_credentials_for_user_callback_set_Stub(&uic_mqtt_dotdot_user_credential_delete_all_credentials_for_user_callback_set_stub);
  uic_mqtt_dotdot_user_credential_delete_all_credentials_for_user_by_type_callback_set_Stub(&uic_mqtt_dotdot_user_credential_delete_all_credentials_for_user_by_type_callback_set_stub);
  // Credential learn
  uic_mqtt_dotdot_user_credential_credential_learn_start_add_callback_set_Stub(&uic_mqtt_dotdot_user_credential_credential_learn_start_add_callback_set_stub);
  uic_mqtt_dotdot_user_credential_credential_learn_start_modify_callback_set_Stub(&uic_mqtt_dotdot_user_credential_credential_learn_start_modify_callback_set_stub);
  uic_mqtt_dotdot_user_credential_credential_learn_stop_callback_set_Stub(&uic_mqtt_dotdot_user_credential_credential_learn_stop_callback_set_stub);
  // UUIC association
  uic_mqtt_dotdot_user_credential_credential_association_callback_set_Stub(&uic_mqtt_dotdot_user_credential_credential_association_callback_set_stub);
  // User checksum
  uic_mqtt_dotdot_user_credential_get_user_checksum_callback_set_Stub(&uic_mqtt_dotdot_user_credential_get_user_checksum_callback_set_stub);
  // Credential checksum
  uic_mqtt_dotdot_user_credential_get_credential_checksum_callback_set_Stub(&uic_mqtt_dotdot_user_credential_get_credential_checksum_callback_set_stub);
  uic_mqtt_dotdot_user_credential_get_all_users_checksum_callback_set_Stub(&uic_mqtt_dotdot_user_credential_get_all_users_checksum_callback_set_stub);
  // Admin code
  uic_mqtt_dotdot_user_credential_set_admin_pin_code_callback_set_Stub(&uic_mqtt_dotdot_user_credential_set_admin_pin_code_callback_set_stub);
  uic_mqtt_dotdot_user_credential_deactivate_admin_pin_code_callback_set_Stub(&uic_mqtt_dotdot_user_credential_deactivate_admin_pin_code_callback_set_stub);
  // clang-format on

  // Run the component init
  TEST_ASSERT_EQUAL(SL_STATUS_OK, user_credential_cluster_server_init());

  // We are not here to test user capabilities, so we need to set them up to
  // accept our test data
  setup_user_capabilities();
  // Need to call this after init() to have the mqtt callback initialized
  setup_cred_capabilities();

  // Setup helper
  cpp_endpoint_node = attribute_store::attribute(endpoint_id_node);

  // Setup global cred capabilities
  cpp_endpoint_node.emplace_node(ATTRIBUTE(SUPPORT_ADMIN_PIN_CODE),
                                 static_cast<uint8_t>(1));
  cpp_endpoint_node.emplace_node(ATTRIBUTE(SUPPORT_CREDENTIAL_CHECKSUM),
                                 static_cast<uint8_t>(1));
  cpp_endpoint_node.emplace_node(ATTRIBUTE(SUPPORT_ADMIN_PIN_CODE_DEACTIVATION),
                                 static_cast<uint8_t>(1));

  // Set command class version
  cpp_endpoint_node.emplace_node(ATTRIBUTE(VERSION)).set_reported(1);
}



/////////////////////////////////////////////////////////////////////////
// Mqtt topics helpers
/////////////////////////////////////////////////////////////////////////
std::string get_base_topic(bool include_user = true)
{
  const std::string user_str = include_user ? "/User" : "";
  const std::string base = "ucl/by-unid/%1%/ep%2%/UserCredential/Attributes%3%";
  return (boost::format(base) % supporting_node_unid % (unsigned int)endpoint_id
          % user_str)
    .str();
}

std::string
  get_user_attribute_mqtt_topic(user_credential_user_unique_id_t user_unique_id,
                                const std::string &attribute_name)
{
  const std::string base = "%1%/%2%/%3%/Reported";
  return (boost::format(base) % get_base_topic() % user_unique_id
          % attribute_name)
    .str();
}

std::string
  get_cred_attribute_mqtt_topic(user_credential_user_unique_id_t user_unique_id,
                                user_credential_type_t credential_type,
                                user_credential_slot_t credential_slot,
                                const std::string &attribute_name)
{
  const std::string base = "%1%/%2%/Credential/%3%/%4%/%5%/Reported";
  return (boost::format(base) % get_base_topic() % user_unique_id
          % cred_type_get_enum_value_name(credential_type) % credential_slot
          % attribute_name)
    .str();
}

std::string get_cred_rule_mqtt_topic(user_credential_type_t credential_type,
                                     const std::string &attribute_name)
{
  const std::string base = "%1%/Credentials/%2%/%3%/Reported";
  return (boost::format(base) % get_base_topic(false)
          % cred_type_get_enum_value_name(credential_type) % attribute_name)
    .str();
}

}  // extern "C"

template<typename T> std::string get_payload(T value)
{
  nlohmann::json json_payload;
  json_payload["value"] = value;
  return json_payload.dump();
}

/////////////////////////////////////////////////////////////////////////
// MOCK HELPERS
/////////////////////////////////////////////////////////////////////////
template<typename T>
void mock_expected_user_mqtt_topic(user_credential_user_unique_id_t user_id,
                                   const std::string &attribute_name,
                                   T payload_value)
{
  // This way we make sure that we have valid reference to our strings
  mqtt_topics.push_back({get_user_attribute_mqtt_topic(user_id, attribute_name),
                         get_payload<T>(payload_value)});

  uic_mqtt_publish_Expect(mqtt_topics.back().first.c_str(),
                          mqtt_topics.back().second.c_str(),
                          mqtt_topics.back().second.size(),
                          true);
}
template<typename T>
void mock_expected_cred_mqtt_topic(user_credential_user_unique_id_t user_id,
                                   user_credential_type_t credential_type,
                                   user_credential_slot_t credential_slot,
                                   const std::string &attribute_name,
                                   T payload_value)
{
  // This way we make sure that we have valid reference to our strings
  mqtt_topics.push_back({get_cred_attribute_mqtt_topic(user_id,
                                                       credential_type,
                                                       credential_slot,
                                                       attribute_name),
                         get_payload<T>(payload_value)});

  uic_mqtt_publish_Expect(mqtt_topics.back().first.c_str(),
                          mqtt_topics.back().second.c_str(),
                          mqtt_topics.back().second.size(),
                          true);
}
template<typename T>
void mock_expected_cred_rule_mqtt_topic(user_credential_type_t credential_type,
                                        const std::string &attribute_name,
                                        T payload_value)
{
  // This way we make sure that we have valid reference to our strings
  mqtt_topics.push_back(
    {get_cred_rule_mqtt_topic(credential_type, attribute_name),
     get_payload<T>(payload_value)});

  uic_mqtt_publish_Expect(mqtt_topics.back().first.c_str(),
                          mqtt_topics.back().second.c_str(),
                          mqtt_topics.back().second.size(),
                          true);
}
void mock_deletion_user_mqtt_topic(user_credential_user_unique_id_t user_id)
{
  // WARNING : Order here matters based on their initialization order in the add_complete_user function
  std::vector<std::string> attribute_names = {"UserType",
                                              "CredentialRule",
                                              "UserActiveState",
                                              "ExpiringTimeoutMinutes",
                                              "UserNameEncoding",
                                              "UserName",
                                              "UserModifierNodeId",
                                              "UserModifierType",
                                              "UserChecksum",
                                              "UserChecksumError"};
  for (auto &attribute_name: attribute_names) {
    mqtt_topics.push_back(
      {get_user_attribute_mqtt_topic(user_id, attribute_name), ""});
    uic_mqtt_publish_Expect(mqtt_topics.back().first.c_str(),
                            mqtt_topics.back().second.c_str(),
                            mqtt_topics.back().second.size(),
                            true);
  }
}

void mock_deletion_cred_mqtt_topic(user_credential_user_unique_id_t user_id,
                                   user_credential_type_t credential_type,
                                   user_credential_slot_t credential_slot)
{
  // WARNING : Order here matters based on their initialization order in the add_complete_credential function
  std::vector<std::string> attribute_names = {"CredentialData",
                                              "AssociationStatus",
                                              "CredentialLearnStatus",
                                              "CredentialModifierNodeId",
                                              "CredentialModifierType"};
  for (auto &attribute_name: attribute_names) {
    mqtt_topics.push_back({get_cred_attribute_mqtt_topic(user_id,
                                                         credential_type,
                                                         credential_slot,
                                                         attribute_name),
                           ""});
    uic_mqtt_publish_Expect(mqtt_topics.back().first.c_str(),
                            mqtt_topics.back().second.c_str(),
                            mqtt_topics.back().second.size(),
                            true);
  }
}

void mock_deletion_cred_rule_mqtt_topic(user_credential_type_t credential_type)
{
  // WARNING : Order here matters based on their initialization order in the add_complete_credential function
  std::vector<std::string> attribute_names = {"LearnSupport",
                                              "SupportedSlotCount",
                                              "CredentialMinLength",
                                              "CredentialMaxLength",
                                              "LearnRecommendedTimeout",
                                              "LearnNumberOfSteps"};
  for (auto &attribute_name: attribute_names) {
    mqtt_topics.push_back(
      {get_cred_rule_mqtt_topic(credential_type, attribute_name), ""});
    uic_mqtt_publish_Expect(mqtt_topics.back().first.c_str(),
                            mqtt_topics.back().second.c_str(),
                            mqtt_topics.back().second.size(),
                            true);
  }
}
/////////////////////////////////////////////////////////////////////////
// Capabilities Helper
/////////////////////////////////////////////////////////////////////////
void setup_user_capabilities()
{
  uint16_t number_of_users                                       = 12;
  user_credential_supported_credential_rules_t cred_rule_bitmask = 0x0F;
  uint8_t username_max_length                                    = 112;
  uint8_t support_user_schedule                                  = 0;
  uint8_t support_all_users_checksum                             = 0;
  uint8_t support_user_checksum                                  = 0;
  user_credential_supported_user_type_bitmask_t supported_user_types_bitmask
    = 0xFF;

  attribute_store_emplace(endpoint_id_node,
                          ATTRIBUTE(NUMBER_OF_USERS),
                          &number_of_users,
                          sizeof(number_of_users));

  attribute_store_emplace(endpoint_id_node,
                          ATTRIBUTE(SUPPORTED_CREDENTIAL_RULES),
                          &cred_rule_bitmask,
                          sizeof(cred_rule_bitmask));

  attribute_store_emplace(endpoint_id_node,
                          ATTRIBUTE(MAX_USERNAME_LENGTH),
                          &username_max_length,
                          sizeof(username_max_length));

  attribute_store_emplace(endpoint_id_node,
                          ATTRIBUTE(SUPPORT_USER_SCHEDULE),
                          &support_user_schedule,
                          sizeof(support_user_schedule));

  attribute_store_emplace(endpoint_id_node,
                          ATTRIBUTE(SUPPORT_ALL_USERS_CHECKSUM),
                          &support_all_users_checksum,
                          sizeof(support_all_users_checksum));

  attribute_store_emplace(endpoint_id_node,
                          ATTRIBUTE(SUPPORT_USER_CHECKSUM),
                          &support_user_checksum,
                          sizeof(support_user_checksum));

  attribute_store_emplace(endpoint_id_node,
                          ATTRIBUTE(SUPPORTED_USER_TYPES),
                          &supported_user_types_bitmask,
                          sizeof(supported_user_types_bitmask));
}

void setup_cred_capabilities()
{
  // Supports ZCL_CRED_TYPE_PIN_CODE..ZCL_CRED_TYPE_UWB
  // Adjust if needed, we don't need to test all types and this outputs a lot of noise on the logs
  uint8_t max_cred_type = ZCL_CRED_TYPE_UWB;
  for (uint8_t i = ZCL_CRED_TYPE_PIN_CODE; i <= max_cred_type; i++) {
    user_credential_type_t cred_type = static_cast<user_credential_type_t>(i);

    auto supported_cred_type_node
      = attribute_store_emplace(endpoint_id_node,
                                ATTRIBUTE(SUPPORTED_CREDENTIAL_TYPE),
                                &cred_type,
                                sizeof(cred_type));
    uint8_t crb_support      = 1;
    uint16_t slot_supported  = 0xFFFF;
    uint8_t cred_min_length = 0;
    uint8_t cred_max_length = 0xFF;
    uint8_t learn_timeout    = 112;
    uint8_t learn_steps      = 12;

    mock_expected_cred_rule_mqtt_topic(cred_type,
                                       "LearnSupport",
                                       (bool)crb_support);
    attribute_store_emplace(supported_cred_type_node,
                            ATTRIBUTE(CREDENTIAL_LEARN_SUPPORT),
                            &crb_support,
                            sizeof(crb_support));

    mock_expected_cred_rule_mqtt_topic(cred_type,
                                       "SupportedSlotCount",
                                       slot_supported);

    attribute_store_emplace(supported_cred_type_node,
                            ATTRIBUTE(CREDENTIAL_SUPPORTED_SLOT_COUNT),
                            &slot_supported,
                            sizeof(slot_supported));
    mock_expected_cred_rule_mqtt_topic(cred_type,
                                       "CredentialMinLength",
                                       cred_min_length);

    attribute_store_emplace(supported_cred_type_node,
                            ATTRIBUTE(CREDENTIAL_MIN_LENGTH),
                            &cred_min_length,
                            sizeof(cred_min_length));

    mock_expected_cred_rule_mqtt_topic(cred_type,
                                       "CredentialMaxLength",
                                       cred_max_length);
    attribute_store_emplace(supported_cred_type_node,
                            ATTRIBUTE(CREDENTIAL_MAX_LENGTH),
                            &cred_max_length,
                            sizeof(cred_max_length));

    mock_expected_cred_rule_mqtt_topic(cred_type,
                                       "LearnRecommendedTimeout",
                                       learn_timeout);
    attribute_store_emplace(supported_cred_type_node,
                            ATTRIBUTE(CREDENTIAL_LEARN_RECOMMENDED_TIMEOUT),
                            &learn_timeout,
                            sizeof(learn_timeout));

    mock_expected_cred_rule_mqtt_topic(cred_type,
                                       "LearnNumberOfSteps",
                                       learn_steps);
    attribute_store_emplace(supported_cred_type_node,
                            ATTRIBUTE(CREDENTIAL_LEARN_NUMBER_OF_STEPS),
                            &learn_steps,
                            sizeof(learn_steps));

    // Will allow to test deletion of attributes
    created_supported_credential_types.push_back(cred_type);
  }
}

/////////////////////////////////////////////////////////////////////////
// HELPERS
/////////////////////////////////////////////////////////////////////////
extern "C" {

void helper_test_operation_type(attribute_store_node_t parent_node,
                                user_credential_operation_type_t operation_type,
                                attribute_store_type_t tested_attribute_type
                                = 0)
{
  if (tested_attribute_type == 0) {
    tested_attribute_type = ATTRIBUTE(USER_OPERATION_TYPE);
    // If we are testing a credential we test its attribute instead
    if (attribute_store_get_node_type(parent_node)
        != ATTRIBUTE(USER_UNIQUE_ID)) {
      tested_attribute_type = ATTRIBUTE(CREDENTIAL_OPERATION_TYPE);
    }
  }
  attribute_store_node_t operation_type_node
    = attribute_store_get_first_child_by_type(parent_node,
                                              tested_attribute_type);
  user_credential_operation_type_t reported_operation_type;
  attribute_store_get_desired(operation_type_node,
                              &reported_operation_type,
                              sizeof(reported_operation_type));

  TEST_ASSERT_EQUAL_MESSAGE(operation_type,
                            reported_operation_type,
                            "Operation Type mismatch");
}

attribute_store_node_t
  helper_add_user_id(user_credential_user_unique_id_t user_unique_id)
{
  return attribute_store_emplace(endpoint_id_node,
                                 ATTRIBUTE(USER_UNIQUE_ID),
                                 &user_unique_id,
                                 sizeof(user_unique_id));
}

// This function will test the MQTT topics for an user
attribute_store_node_t helper_add_complete_user(
  user_credential_user_unique_id_t user_id,
  user_credential_type_t user_type,
  user_credential_rule_t credential_rule,
  user_credential_user_active_state_t user_active_state,
  user_credential_expiring_timeout_minutes_t expiring_timeout,
  user_credential_user_name_encoding_t user_name_encoding,
  const char *user_name)
{
  attribute_store_node_t user_id_node = helper_add_user_id(user_id);

  mock_expected_user_mqtt_topic(user_id,
                                "UserType",
                                user_type_enum_get_enum_value_name(user_type));
  attribute_store_emplace(user_id_node,
                          ATTRIBUTE(USER_TYPE),
                          &user_type,
                          sizeof(user_type));

  mock_expected_user_mqtt_topic(user_id,
                                "CredentialRule",
                                cred_rule_get_enum_value_name(credential_rule));
  attribute_store_emplace(user_id_node,
                          ATTRIBUTE(CREDENTIAL_RULE),
                          &credential_rule,
                          sizeof(credential_rule));

  mock_expected_user_mqtt_topic(user_id,
                                "UserActiveState",
                                static_cast<bool>(user_active_state));
  attribute_store_emplace(user_id_node,
                          ATTRIBUTE(USER_ACTIVE_STATE),
                          &user_active_state,
                          sizeof(user_active_state));

  mock_expected_user_mqtt_topic(user_id,
                                "ExpiringTimeoutMinutes",
                                static_cast<uint32_t>(expiring_timeout));
  attribute_store_emplace(user_id_node,
                          ATTRIBUTE(USER_EXPIRING_TIMEOUT_MINUTES),
                          &expiring_timeout,
                          sizeof(expiring_timeout));

  mock_expected_user_mqtt_topic(
    user_id,
    "UserNameEncoding",
    user_name_encoding_type_get_enum_value_name(user_name_encoding));
  attribute_store_emplace(user_id_node,
                          ATTRIBUTE(USER_NAME_ENCODING),
                          &user_name_encoding,
                          sizeof(user_name_encoding));

  std::string cpp_str_username(user_name);
  mock_expected_user_mqtt_topic(user_id, "UserName", cpp_str_username);
  attribute_store_node_t user_name_node
    = attribute_store_add_node(ATTRIBUTE(USER_NAME), user_id_node);
  attribute_store_set_reported_string(user_name_node, user_name);

  // Reported attributes by the end device
  // Need those to test MQTT topics
  user_credential_modifier_node_id_t modifier_node_id = 1212;
  user_credential_modifier_type_t modifier_type
    = ZCL_USER_MODIFIER_TYPE_LOCALLY;
  mock_expected_user_mqtt_topic(user_id,
                                "UserModifierNodeId",
                                static_cast<uint32_t>(modifier_node_id));
  attribute_store_emplace(user_id_node,
                          ATTRIBUTE(USER_MODIFIER_NODE_ID),
                          &modifier_node_id,
                          sizeof(modifier_node_id));
  mock_expected_user_mqtt_topic(
    user_id,
    "UserModifierType",
    user_modifier_type_get_enum_value_name(modifier_type));
  attribute_store_emplace(user_id_node,
                          ATTRIBUTE(USER_MODIFIER_TYPE),
                          &modifier_type,
                          sizeof(modifier_type));

  // Only used to see if they are correctly exposed
  user_credential_checksum_t user_checksum = 0xABCD;
  mock_expected_user_mqtt_topic(
    user_id,
    "UserChecksum",
    user_checksum);
  attribute_store_emplace(user_id_node,
                          ATTRIBUTE(USER_CHECKSUM),
                          &user_checksum,
                          sizeof(user_checksum));
  user_credential_checksum_t computed_checksum = 0xFFFF;
  mock_expected_user_mqtt_topic(
    user_id,
    "UserChecksumError",
    computed_checksum);
  attribute_store_emplace(user_id_node,
                          ATTRIBUTE(USER_CHECKSUM_MISMATCH_ERROR),
                          &computed_checksum,
                          sizeof(computed_checksum));

  // Cleanup : this will automatically test the MQTT deletion messages
  created_user_id.push_back(user_id);

  return user_id_node;
}

// This function will test the MQTT topics for a credential
attribute_store_node_t
  helper_add_complete_credential(user_credential_user_unique_id_t user_id,
                                 user_credential_type_t credential_type,
                                 user_credential_slot_t credential_slot,
                                 const char *credential_data)
{
  attribute_store_node_t user_id_node = helper_add_user_id(user_id);

  attribute_store_node_t credential_type_node
    = attribute_store_emplace(user_id_node,
                              ATTRIBUTE(CREDENTIAL_TYPE),
                              &credential_type,
                              sizeof(credential_type));

  attribute_store_node_t credential_slot_node
    = attribute_store_emplace(credential_type_node,
                              ATTRIBUTE(CREDENTIAL_SLOT),
                              &credential_slot,
                              sizeof(credential_slot));

  std::vector<uint8_t> credential_data_vector;
  std::string cpp_str_credential_data(credential_data);

  if (credential_type == ZCL_CRED_TYPE_PASSWORD) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cnv;
    std::u16string credential_data_utf16
      = cnv.from_bytes(cpp_str_credential_data);

    for (const auto &c: credential_data_utf16) {
      credential_data_vector.push_back((uint8_t)(c >> 8));
      credential_data_vector.push_back((uint8_t)c);
    }
  } else {
    credential_data_vector
      = std::vector<uint8_t>(cpp_str_credential_data.begin(),
                             cpp_str_credential_data.end());
  }

  mock_expected_cred_mqtt_topic(
    user_id,
    credential_type,
    credential_slot,
    "CredentialData",
    // Credential data is published in UTF-8 no matter what the encoding is
    cpp_str_credential_data);
  attribute_store_emplace(credential_slot_node,
                          ATTRIBUTE(CREDENTIAL_DATA),
                          credential_data_vector.data(),
                          credential_data_vector.size());

  // Test association status exposure (will not be used anywhere, it is here to test the MQTT exposure)
  uint8_t association_status = 0;
  mock_expected_cred_mqtt_topic(
    user_id,
    credential_type,
    credential_slot,
    "AssociationStatus",
    association_status);
  attribute_store_emplace(credential_slot_node,
                          ATTRIBUTE(ASSOCIATION_STATUS),
                          &association_status,
                          sizeof(association_status));

  // Test credential learn status exposure (will not be used anywhere, it is here to test the MQTT exposure)
  uint8_t credential_learn_status = 1;
  mock_expected_cred_mqtt_topic(
    user_id,
    credential_type,
    credential_slot,
    "CredentialLearnStatus",
    credential_learn_status);
  attribute_store_emplace(credential_slot_node,
                          ATTRIBUTE(CREDENTIAL_LEARN_STATUS),
                          &credential_learn_status,
                          sizeof(credential_learn_status));

  // Generated by end device
  user_credential_modifier_node_id_t modifier_node_id = 1212;
  user_credential_modifier_type_t modifier_type = ZCL_USER_MODIFIER_TYPE_DNE;

  mock_expected_cred_mqtt_topic(user_id,
                                credential_type,
                                credential_slot,
                                "CredentialModifierNodeId",
                                static_cast<uint32_t>(modifier_node_id));
  attribute_store_emplace(credential_slot_node,
                          ATTRIBUTE(CREDENTIAL_MODIFIER_NODE_ID),
                          &modifier_node_id,
                          sizeof(modifier_node_id));
  mock_expected_cred_mqtt_topic(
    user_id,
    credential_type,
    credential_slot,
    "CredentialModifierType",
    user_modifier_type_get_enum_value_name(modifier_type));
  attribute_store_emplace(credential_slot_node,
                          ATTRIBUTE(CREDENTIAL_MODIFIER_TYPE),
                          &modifier_type,
                          sizeof(modifier_type));

  // Cleanup : this will automatically test the MQTT deletion messages
  created_credential_ids.push_back({user_id, credential_type, credential_slot});

  return user_id_node;
}

void helper_test_desired_user_attributes(
  attribute_store_node_t user_id_node,
  UserTypeEnum user_type,
  bool user_active_state,
  CredRule credential_rule,
  const char *user_name,
  UserNameEncodingType user_name_encoding,
  uint16_t expiring_timeout)
{
  // User Type
  attribute_store_node_t user_type_node
    = attribute_store_get_first_child_by_type(user_id_node,
                                              ATTRIBUTE(USER_TYPE));
  user_credential_type_t reported_user_type;
  attribute_store_get_desired(user_type_node,
                              &reported_user_type,
                              sizeof(reported_user_type));
  TEST_ASSERT_EQUAL_MESSAGE(user_type,
                            reported_user_type,
                            "User Type mismatch");

  // User Active State
  attribute_store_node_t user_active_state_node
    = attribute_store_get_first_child_by_type(user_id_node,
                                              ATTRIBUTE(USER_ACTIVE_STATE));
  user_credential_user_active_state_t reported_user_active_state;
  attribute_store_get_desired(user_active_state_node,
                              &reported_user_active_state,
                              sizeof(reported_user_active_state));
  TEST_ASSERT_EQUAL_MESSAGE(user_active_state,
                            reported_user_active_state,
                            "User Active State mismatch");
  // Credential rule
  attribute_store_node_t credential_rule_node
    = attribute_store_get_first_child_by_type(user_id_node,
                                              ATTRIBUTE(CREDENTIAL_RULE));
  user_credential_rule_t reported_credential_rule;
  attribute_store_get_desired(credential_rule_node,
                              &reported_credential_rule,
                              sizeof(reported_credential_rule));
  TEST_ASSERT_EQUAL_MESSAGE(credential_rule,
                            reported_credential_rule,
                            "Credential Rule mismatch");

  // User Name
  attribute_store_node_t user_name_node
    = attribute_store_get_first_child_by_type(user_id_node,
                                              ATTRIBUTE(USER_NAME));
  char reported_user_name[255];
  attribute_store_get_desired_string(user_name_node, reported_user_name, 255);
  TEST_ASSERT_EQUAL_STRING_MESSAGE(user_name,
                                   reported_user_name,
                                   "User Name mismatch");

  // User Name Encoding
  attribute_store_node_t user_name_encoding_node
    = attribute_store_get_first_child_by_type(user_id_node,
                                              ATTRIBUTE(USER_NAME_ENCODING));
  user_credential_user_name_encoding_t reported_user_name_encoding;
  attribute_store_get_desired(user_name_encoding_node,
                              &reported_user_name_encoding,
                              sizeof(reported_user_name_encoding));
  TEST_ASSERT_EQUAL_MESSAGE(user_name_encoding,
                            reported_user_name_encoding,
                            "User Name Encoding mismatch");

  // Expiring Timeout
  attribute_store_node_t expiring_timeout_node
    = attribute_store_get_first_child_by_type(
      user_id_node,
      ATTRIBUTE(USER_EXPIRING_TIMEOUT_MINUTES));
  user_credential_expiring_timeout_minutes_t reported_expiring_timeout;
  attribute_store_get_desired(expiring_timeout_node,
                              &reported_expiring_timeout,
                              sizeof(reported_expiring_timeout));
  TEST_ASSERT_EQUAL_MESSAGE(expiring_timeout,
                            reported_expiring_timeout,
                            "Expiring Timeout mismatch");
}

void helper_test_desired_credential_attributes(
  user_credential_user_unique_id_t user_id_node,
  user_credential_type_t credential_type,
  user_credential_slot_t credential_slot,
  const char *credential_data,
  bool desired_credential_identifiers,
  user_credential_operation_type_t credential_operation_type)
{
  attribute_store_node_value_state_t credential_identifier_state
    = desired_credential_identifiers ? DESIRED_ATTRIBUTE : REPORTED_ATTRIBUTE;

  // Credential type
  attribute_store_node_t credential_type_node
    = attribute_store_get_first_child_by_type(user_id_node,
                                              ATTRIBUTE(CREDENTIAL_TYPE));
  user_credential_type_t reported_credential_type;
  attribute_store_read_value(credential_type_node,
                             REPORTED_ATTRIBUTE,
                             &reported_credential_type,
                             sizeof(reported_credential_type));
  TEST_ASSERT_EQUAL_MESSAGE(credential_type,
                            reported_credential_type,
                            "Credential Type mismatch");

  // Credential Slot
  attribute_store_node_t credential_slot_node
    = attribute_store_get_first_child_by_type(credential_type_node,
                                              ATTRIBUTE(CREDENTIAL_SLOT));
  user_credential_slot_t reported_credential_slot;
  attribute_store_read_value(credential_slot_node,
                             credential_identifier_state,
                             &reported_credential_slot,
                             sizeof(reported_credential_slot));
  TEST_ASSERT_EQUAL_MESSAGE(credential_slot,
                            reported_credential_slot,
                            "Credential Slot mismatch");

  std::vector<uint8_t> expected_credential_data_vector;
  std::string str_credential_data(credential_data);

  // CC:0083.01.0A.11.021 Passwords MUST be transmitted in Unicode UTF-16 format, in big endian order
  if (credential_type == ZCL_CRED_TYPE_PASSWORD) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cnv;
    std::u16string utf16_cred_data = cnv.from_bytes(str_credential_data);
    if (cnv.converted() < str_credential_data.size())
      TEST_FAIL_MESSAGE("Can't convert password to utf-16");

    for (const auto &c: utf16_cred_data) {
      expected_credential_data_vector.push_back((uint8_t)(c >> 8));
      expected_credential_data_vector.push_back((uint8_t)c);
    }
  } else {
    expected_credential_data_vector
      = std::vector<uint8_t>(str_credential_data.begin(),
                             str_credential_data.end());
  }

  // Credential Data
  attribute_store::attribute credential_data_node
    = attribute_store_get_first_child_by_type(credential_slot_node,
                                              ATTRIBUTE(CREDENTIAL_DATA));
  std::vector<uint8_t> reported_credential_data
    = credential_data_node
        .desired<std::vector<uint8_t>>();

  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(expected_credential_data_vector.data(),
                                        reported_credential_data.data(),
                                        expected_credential_data_vector.size(),
                                        "Credential Data mismatch");

  // Operation type
  helper_test_operation_type(credential_slot_node, credential_operation_type);
}

void helper_test_user_id(attribute_store_node_t user_id_node,
                         user_credential_user_unique_id_t user_unique_id,
                         attribute_store_node_value_state_t value_state)
{
  user_credential_user_unique_id_t reported_user_id;
  attribute_store_read_value(user_id_node,
                             value_state,
                             &reported_user_id,
                             sizeof(reported_user_id));
  TEST_ASSERT_EQUAL_MESSAGE(user_unique_id,
                            reported_user_id,
                            "User ID mismatch");
}

/////////////////////////////////////////////////////////////////////////
// Test cases
/////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////
// Add user
///////////////////////////////////////////////////
void test_user_credential_cluster_add_user_not_supported()
{
  // Simulate user
  user_credential_user_unique_id_t user_unique_id = 12;
  UserTypeEnum user_type                  = ZCL_USER_TYPE_ENUM_PROGRAMMING_USER;
  CredRule credential_rule                = ZCL_CRED_RULE_DUAL;
  bool user_active_state                  = false;
  uint16_t expiring_timeout               = 0;
  UserNameEncodingType user_name_encoding = ZCL_USER_NAME_ENCODING_TYPE_UTF_16;
  const char *user_name                   = "V16 TUNING PRO MAX";

  // Support check
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    add_user_command(supporting_node_unid,
                     endpoint_id,
                     UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                     0,  // User ID 0 is reserved
                     user_type,
                     user_active_state,
                     credential_rule,
                     user_name,
                     expiring_timeout,
                     user_name_encoding),
    "User 0 is reserved so it should "
    "return SL_STATUS_FAIL");

  // Simulate user
  helper_add_user_id(user_unique_id);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    add_user_command(supporting_node_unid,
                     endpoint_id,
                     UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                     user_unique_id,
                     user_type,
                     user_active_state,
                     credential_rule,
                     user_name,
                     expiring_timeout,
                     user_name_encoding),
    "User 12 is existing so it should return SL_STATUS_FAIL");
}

void test_user_credential_cluster_add_user_happy_case()
{
  // Simulate user
  user_credential_user_unique_id_t user_unique_id = 12;
  UserTypeEnum user_type                  = ZCL_USER_TYPE_ENUM_PROGRAMMING_USER;
  CredRule credential_rule                = ZCL_CRED_RULE_DUAL;
  bool user_active_state                  = false;
  uint16_t expiring_timeout               = 0;
  UserNameEncodingType user_name_encoding = ZCL_USER_NAME_ENCODING_TYPE_UTF_16;
  const char *user_name                   = "ENDIVE BOOSTER TURBO MAX";

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    add_user_command(supporting_node_unid,
                     endpoint_id,
                     UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                     user_unique_id,
                     user_type,
                     user_active_state,
                     credential_rule,
                     user_name,
                     expiring_timeout,
                     user_name_encoding),
    "User 12 is not existing so it should return SL_STATUS_OK");

  // Test attribute tree state
  // All attributes should be set as desired
  // User ID
  attribute_store_node_t user_id_node
    = attribute_store_get_first_child_by_type(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID));

  helper_test_user_id(user_id_node, user_unique_id, DESIRED_ATTRIBUTE);
  helper_test_desired_user_attributes(user_id_node,
                                      user_type,
                                      user_active_state,
                                      credential_rule,
                                      user_name,
                                      user_name_encoding,
                                      expiring_timeout);

  helper_test_operation_type(user_id_node, USER_CREDENTIAL_OPERATION_TYPE_ADD);
}

///////////////////////////////////////////////////
// Modify user
///////////////////////////////////////////////////
void test_user_credential_cluster_modify_user_not_supported()
{
  // Simulate user
  user_credential_user_unique_id_t user_unique_id = 12;
  UserTypeEnum user_type                  = ZCL_USER_TYPE_ENUM_PROGRAMMING_USER;
  CredRule credential_rule                = ZCL_CRED_RULE_DUAL;
  bool user_active_state                  = false;
  uint16_t expiring_timeout               = 0;
  UserNameEncodingType user_name_encoding = ZCL_USER_NAME_ENCODING_TYPE_UTF_16;
  const char *user_name                   = "VROUM VROUM";

  // Support check
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    modify_user_command(supporting_node_unid,
                        endpoint_id,
                        UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                        user_unique_id,
                        user_type,
                        user_active_state,
                        credential_rule,
                        user_name,
                        expiring_timeout,
                        user_name_encoding),
    "User 12 doesn't exists so it should return SL_STATUS_FAIL");
}

void test_user_credential_cluster_modify_user_with_expiring_timeout()
{
  // Simulate user
  user_credential_user_unique_id_t user_unique_id = 12;
  UserTypeEnum user_type                  = ZCL_USER_TYPE_ENUM_EXPIRING_USER;
  CredRule credential_rule                = ZCL_CRED_RULE_SINGLE;
  bool user_active_state                  = true;
  uint16_t expiring_timeout               = 50;
  UserNameEncodingType user_name_encoding = ZCL_USER_NAME_ENCODING_TYPE_ASCII;
  const char *user_name                   = "TURBO MAX CANON";
  // Since we are updating to a ZCL_USER_TYPE_ENUM_DISPOSABLE_USER, expiring_timeout should not be updated
  attribute_store_node_t user_id_node
    = helper_add_complete_user(user_unique_id,
                               ZCL_USER_TYPE_ENUM_DISPOSABLE_USER,
                               ZCL_CRED_RULE_TRIPLE,
                               user_active_state,
                               expiring_timeout,
                               user_name_encoding,
                               "DEFINITELY NOT TURBO");

  // Execute command
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    modify_user_command(supporting_node_unid,
                        endpoint_id,
                        UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                        user_unique_id,
                        user_type,
                        user_active_state,
                        credential_rule,
                        user_name,
                        expiring_timeout,
                        user_name_encoding),
    "User 12 exists so it should return SL_STATUS_OK");

  // Test attribute tree state
  // All attributes should be set as desired except for user id
  helper_test_user_id(user_id_node, user_unique_id, REPORTED_ATTRIBUTE);
  helper_test_desired_user_attributes(user_id_node,
                                      user_type,
                                      user_active_state,
                                      credential_rule,
                                      user_name,
                                      user_name_encoding,
                                      expiring_timeout);
  helper_test_operation_type(user_id_node,
                             USER_CREDENTIAL_OPERATION_TYPE_MODIFY);
}

void test_user_credential_cluster_modify_user_without_expiring_timeout()
{
  // Simulate user
  user_credential_user_unique_id_t user_unique_id = 12;
  UserTypeEnum user_type                  = ZCL_USER_TYPE_ENUM_DISPOSABLE_USER;
  CredRule credential_rule                = ZCL_CRED_RULE_SINGLE;
  bool user_active_state                  = true;
  uint16_t expiring_timeout               = 50;
  UserNameEncodingType user_name_encoding = ZCL_USER_NAME_ENCODING_TYPE_ASCII;
  const char *user_name                   = "Test User";

  attribute_store_node_t user_id_node
    = helper_add_complete_user(user_unique_id,
                               ZCL_USER_TYPE_ENUM_EXPIRING_USER,
                               ZCL_CRED_RULE_DUAL,
                               user_active_state,
                               0,
                               user_name_encoding,
                               "Test User Original");

  // Force timeout attribute to 0 and we'll check if that has moved or not
  expiring_timeout = 0;
  attribute_store_set_child_desired(user_id_node,
                                    ATTRIBUTE(USER_EXPIRING_TIMEOUT_MINUTES),
                                    &expiring_timeout,
                                    sizeof(expiring_timeout));
  // Execute command
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    modify_user_command(supporting_node_unid,
                        endpoint_id,
                        UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                        user_unique_id,
                        user_type,
                        user_active_state,
                        credential_rule,
                        user_name,
                        expiring_timeout,
                        user_name_encoding),
    "User 12 exists so it should return SL_STATUS_OK");

  // Test attribute tree state
  // All attributes should be set as desired except for user id
  helper_test_user_id(user_id_node, user_unique_id, REPORTED_ATTRIBUTE);
  helper_test_desired_user_attributes(
    user_id_node,
    user_type,
    user_active_state,
    credential_rule,
    user_name,
    user_name_encoding,
    // Force to 0 here since it should not be modified
    0);
  helper_test_operation_type(user_id_node,
                             USER_CREDENTIAL_OPERATION_TYPE_MODIFY);
}

///////////////////////////////////////////////////
// Delete user
///////////////////////////////////////////////////

void test_user_credential_cluster_delete_user_not_supported()
{
  // Support check
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    delete_user_command(supporting_node_unid,
                        endpoint_id,
                        UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                        12),
    "User 12 doesn't exists so it should return SL_STATUS_FAIL");
}

void test_user_credential_cluster_delete_user_happy_case()
{
  // Simulate user
  user_credential_user_unique_id_t user_unique_id = 12;
  UserTypeEnum user_type                  = ZCL_USER_TYPE_ENUM_EXPIRING_USER;
  CredRule credential_rule                = ZCL_CRED_RULE_SINGLE;
  bool user_active_state                  = true;
  uint16_t expiring_timeout               = 50;
  UserNameEncodingType user_name_encoding = ZCL_USER_NAME_ENCODING_TYPE_ASCII;
  const char *user_name                   = "RIP JACKIE TUNNING";

  auto user_unique_id_node = helper_add_complete_user(user_unique_id,
                                                      user_type,
                                                      credential_rule,
                                                      user_active_state,
                                                      expiring_timeout,
                                                      user_name_encoding,
                                                      user_name);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    delete_user_command(supporting_node_unid,
                        endpoint_id,
                        UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                        user_unique_id),
    "Should be able to mark user 12 for deletion");

  helper_test_operation_type(user_unique_id_node,
                             USER_CREDENTIAL_OPERATION_TYPE_DELETE);
}

///////////////////////////////////////////////////
// Add credential
///////////////////////////////////////////////////
void test_user_credential_cluster_add_credential_not_supported()
{
  // Simulate user
  user_credential_user_unique_id_t user_unique_id = 12;

  // Support check
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    add_credential_command(supporting_node_unid,
                           endpoint_id,
                           UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                           user_unique_id,  // Non existing user
                           CredType::ZCL_CRED_TYPE_BLE,
                           1,
                           "Test Credential"),
    "User 12 is not existing so it should return SL_STATUS_FAIL");

  // Simulate user
  helper_add_user_id(user_unique_id);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    add_credential_command(supporting_node_unid,
                           endpoint_id,
                           UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                           user_unique_id,
                           static_cast<CredType>(0),  // Reserved
                           1,
                           "Test Credential"),
    "Credential type 0 is reserved so it should return SL_STATUS_FAIL");

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    add_credential_command(supporting_node_unid,
                           endpoint_id,
                           UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                           user_unique_id,
                           CredType::ZCL_CRED_TYPE_PIN_CODE,
                           0,  // Reserved
                           "Test Credential"),
    "Credential slot 0 is reserved so it should return SL_STATUS_FAIL");

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    add_credential_command(supporting_node_unid,
                           endpoint_id,
                           UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                           user_unique_id,
                           CredType::ZCL_CRED_TYPE_PIN_CODE,
                           1,
                           "1234567ABCDEF"),
    "PINCode contains invalid char, it should return SL_STATUS_FAIL");
}

void test_user_credential_cluster_add_credential_pin_code_happy_case()
{
  // Simulate user
  user_credential_user_unique_id_t user_unique_id = 12;
  CredType credential_type               = CredType::ZCL_CRED_TYPE_PIN_CODE;
  user_credential_slot_t credential_slot = 1;
  const char *credential_data            = "123456789";

  // Add simple user
  helper_add_user_id(user_unique_id);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    add_credential_command(supporting_node_unid,
                           endpoint_id,
                           UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                           user_unique_id,
                           credential_type,
                           credential_slot,
                           credential_data),
    "Should be able to add a new credential");

  // Test attribute tree state
  // All attributes should be set as desired
  // User ID
  attribute_store_node_t user_id_node
    = attribute_store_get_first_child_by_type(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID));

  helper_test_user_id(user_id_node, user_unique_id, REPORTED_ATTRIBUTE);
  helper_test_desired_credential_attributes(user_id_node,
                                            credential_type,
                                            credential_slot,
                                            credential_data,
                                            true,
                                            USER_CREDENTIAL_OPERATION_TYPE_ADD);
}

void test_user_credential_cluster_add_credential_password_happy_case()
{
  // Simulate user
  user_credential_user_unique_id_t user_unique_id = 12;
  CredType credential_type               = CredType::ZCL_CRED_TYPE_PASSWORD;
  user_credential_slot_t credential_slot = 1;
  const char *credential_data            = "hunter2";

  // Add simple user
  helper_add_user_id(user_unique_id);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    add_credential_command(supporting_node_unid,
                           endpoint_id,
                           UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                           user_unique_id,
                           credential_type,
                           credential_slot,
                           credential_data),
    "Should be able to add a new credential");

  // Test attribute tree state
  // All attributes should be set as desired
  // User ID
  attribute_store_node_t user_id_node
    = attribute_store_get_first_child_by_type(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID));

  helper_test_user_id(user_id_node, user_unique_id, REPORTED_ATTRIBUTE);
  helper_test_desired_credential_attributes(user_id_node,
                                            credential_type,
                                            credential_slot,
                                            credential_data,
                                            true,
                                            USER_CREDENTIAL_OPERATION_TYPE_ADD);
}

void test_user_credential_cluster_add_credential_others_happy_case()
{
  // Simulate user
  user_credential_user_unique_id_t user_unique_id = 12;
  CredType credential_type               = CredType::ZCL_CRED_TYPE_RFID_CODE;
  user_credential_slot_t credential_slot = 1;
  const char *credential_data            = "hunter2";

  // Add simple user
  helper_add_user_id(user_unique_id);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    add_credential_command(supporting_node_unid,
                           endpoint_id,
                           UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                           user_unique_id,
                           credential_type,
                           credential_slot,
                           credential_data),
    "Should be able to add a new credential");

  // Test attribute tree state
  // All attributes should be set as desired
  // User ID
  attribute_store_node_t user_id_node
    = attribute_store_get_first_child_by_type(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID));

  helper_test_user_id(user_id_node, user_unique_id, REPORTED_ATTRIBUTE);
  helper_test_desired_credential_attributes(user_id_node,
                                            credential_type,
                                            credential_slot,
                                            credential_data,
                                            true,
                                            USER_CREDENTIAL_OPERATION_TYPE_ADD);
}

///////////////////////////////////////////////////
// Modify credential
///////////////////////////////////////////////////
void test_user_credential_cluster_modify_credential_not_supported()
{
  // Simulate Credential
  user_credential_user_unique_id_t user_unique_id = 12;
  CredType credential_type               = CredType::ZCL_CRED_TYPE_PIN_CODE;
  user_credential_slot_t credential_slot = 1;

  // Support check
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    modify_credential_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id,  // Non existing user
                              credential_type,
                              credential_slot,
                              ""),
    "User 12 doesn't exists so it should return SL_STATUS_FAIL");

  // Simulate user
  auto user_id_node = helper_add_user_id(user_unique_id);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    modify_credential_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id,
                              credential_type,
                              credential_slot,
                              ""),
    "Credential type doesn't exists so it should return SL_STATUS_FAIL");

  user_credential_type_t credential_type_c
    = static_cast<user_credential_type_t>(credential_type);
  auto credential_type_node
    = attribute_store_emplace(user_id_node,
                              ATTRIBUTE(CREDENTIAL_TYPE),
                              &credential_type_c,
                              sizeof(credential_type_c));

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    modify_credential_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id,
                              credential_type,
                              credential_slot,
                              ""),
    "Credential slot doesn't exists so it should return SL_STATUS_FAIL");

  attribute_store_emplace(credential_type_node,
                          ATTRIBUTE(CREDENTIAL_SLOT),
                          &credential_slot,
                          sizeof(credential_slot));

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    modify_credential_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id,
                              CredType::ZCL_CRED_TYPE_PIN_CODE,
                              1,
                              "1234567ABCDEF"),
    "PINCode contains invalid char, it should return SL_STATUS_FAIL");
}

void test_user_credential_cluster_modify_credential_pin_code_happy_case()
{
  user_credential_user_unique_id_t user_unique_id = 12;
  CredType credential_type               = CredType::ZCL_CRED_TYPE_PIN_CODE;
  user_credential_slot_t credential_slot = 1;
  std::string credential_data            = "123456789";

  auto user_id_node = helper_add_complete_credential(user_unique_id,
                                                     credential_type,
                                                     credential_slot,
                                                     credential_data.c_str());

  credential_data = "12";
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    modify_credential_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id,
                              credential_type,
                              credential_slot,
                              credential_data.c_str()),
    "Should be able to modify a credential");

  helper_test_desired_credential_attributes(
    user_id_node,
    credential_type,
    credential_slot,
    credential_data.c_str(),
    false,
    USER_CREDENTIAL_OPERATION_TYPE_MODIFY);
}

void test_user_credential_cluster_modify_credential_password_happy_case()
{
  user_credential_user_unique_id_t user_unique_id = 12;
  CredType credential_type               = CredType::ZCL_CRED_TYPE_PASSWORD;
  user_credential_slot_t credential_slot = 12;
  std::string credential_data            = "hunter2";

  auto user_id_node = helper_add_complete_credential(user_unique_id,
                                                     credential_type,
                                                     credential_slot,
                                                     credential_data.c_str());
  // Test UTF-16 conversion for password
  credential_data = "🔥MAX SPEED TURBO🔥";
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    modify_credential_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id,
                              credential_type,
                              credential_slot,
                              credential_data.c_str()),
    "Should be able to modify a credential");

  helper_test_desired_credential_attributes(
    user_id_node,
    credential_type,
    credential_slot,
    credential_data.c_str(),
    false,
    USER_CREDENTIAL_OPERATION_TYPE_MODIFY);
}

void test_user_credential_cluster_modify_credential_others_happy_case()
{
  user_credential_user_unique_id_t user_unique_id = 12;
  CredType credential_type                        = CredType::ZCL_CRED_TYPE_BLE;
  user_credential_slot_t credential_slot          = 2;
  std::string credential_data = "FAST TURBO ENGINE DOG PRO MAX";

  auto user_id_node = helper_add_complete_credential(user_unique_id,
                                                     credential_type,
                                                     credential_slot,
                                                     credential_data.c_str());
  // Test UTF-16 conversion for password
  credential_data = "FAE124A54E5F9325874A23E3646B";
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    modify_credential_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id,
                              credential_type,
                              credential_slot,
                              credential_data.c_str()),
    "Should be able to modify a credential");

  helper_test_desired_credential_attributes(
    user_id_node,
    credential_type,
    credential_slot,
    credential_data.c_str(),
    false,
    USER_CREDENTIAL_OPERATION_TYPE_MODIFY);
}

///////////////////////////////////////////////////
// Delete credential
///////////////////////////////////////////////////
void test_user_credential_cluster_delete_credential_not_supported()
{
  // Simulate Credential
  user_credential_user_unique_id_t user_unique_id = 12;
  CredType credential_type               = CredType::ZCL_CRED_TYPE_PIN_CODE;
  user_credential_slot_t credential_slot = 1;

  // Support check
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    delete_credential_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id,  // Non existing user
                              credential_type,
                              credential_slot),
    "User 12 doesn't exists so it should return SL_STATUS_FAIL");

  // Simulate user
  auto user_id_node = helper_add_user_id(user_unique_id);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    delete_credential_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id,
                              credential_type,
                              credential_slot),
    "Credential type doesn't exists so it should return SL_STATUS_FAIL");

  user_credential_type_t credential_type_c
    = static_cast<user_credential_type_t>(credential_type);
  auto credential_type_node
    = attribute_store_emplace(user_id_node,
                              ATTRIBUTE(CREDENTIAL_TYPE),
                              &credential_type_c,
                              sizeof(credential_type_c));

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    delete_credential_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id,
                              credential_type,
                              credential_slot),
    "Credential slot doesn't exists so it should return SL_STATUS_FAIL");

  attribute_store_emplace(credential_type_node,
                          ATTRIBUTE(CREDENTIAL_SLOT),
                          &credential_slot,
                          sizeof(credential_slot));
}

void test_user_credential_cluster_delete_credential_happy_case()
{
  user_credential_user_unique_id_t user_unique_id = 12;
  CredType credential_type               = CredType::ZCL_CRED_TYPE_PIN_CODE;
  user_credential_slot_t credential_slot = 1;
  std::string credential_data            = "12121212";

  auto user_id_node = helper_add_complete_credential(user_unique_id,
                                                     credential_type,
                                                     credential_slot,
                                                     credential_data.c_str());

  auto credential_type_node
    = attribute_store_get_first_child_by_type(user_id_node,
                                              ATTRIBUTE(CREDENTIAL_TYPE));
  auto credential_slot_node
    = attribute_store_get_first_child_by_type(credential_type_node,
                                              ATTRIBUTE(CREDENTIAL_SLOT));

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    delete_credential_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id,
                              credential_type,
                              credential_slot),
    "Should be able to mark credential for deletion");

  helper_test_operation_type(credential_slot_node,
                             USER_CREDENTIAL_OPERATION_TYPE_DELETE);
}

void test_user_credential_cluster_delete_all_users_happy_case()
{
  // Simulate user
  user_credential_user_unique_id_t user_unique_id = 12;
  UserTypeEnum user_type                  = ZCL_USER_TYPE_ENUM_EXPIRING_USER;
  CredRule credential_rule                = ZCL_CRED_RULE_SINGLE;
  bool user_active_state                  = true;
  uint16_t expiring_timeout               = 50;
  UserNameEncodingType user_name_encoding = ZCL_USER_NAME_ENCODING_TYPE_ASCII;
  const char *user_name                   = "RIP JACKIE TUNNING";

  helper_add_complete_user(user_unique_id,
                           user_type,
                           credential_rule,
                           user_active_state,
                           expiring_timeout,
                           user_name_encoding,
                           user_name);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    delete_all_users_command(supporting_node_unid,
                             endpoint_id,
                             UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL),
    "Should be able to setup attribute store for all user deletion");

  user_unique_id = 0;
  auto deletion_user_node
    = attribute_store_get_node_child_by_value(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&user_unique_id,
                                              sizeof(user_unique_id),
                                              0);

  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_user_node),
                           "Should be one user node with desired value of 0 to "
                           "perform user interview");
  helper_test_operation_type(deletion_user_node,
                             USER_CREDENTIAL_OPERATION_TYPE_DELETE);
}

void test_user_credential_cluster_delete_all_credential_happy_case()
{
  user_credential_user_unique_id_t user_unique_id = 0;
  user_credential_type_t credential_type          = 0;
  user_credential_slot_t credential_slot          = 0;

  std::vector<user_credential_user_unique_id_t> user_ids = {12, 12, 12, 15, 19};
  std::vector<user_credential_type_t> credential_types   = {1, 1, 2, 5, 1};
  std::vector<user_credential_slot_t> credential_slots   = {1, 2, 2, 1, 3};

  // WARNING : Make sure that all the vector above have the same size
  const size_t expected_credential_count = user_ids.size();
  for (size_t i = 0; i < expected_credential_count; i++) {
    helper_add_complete_credential(user_ids[i],
                                   credential_types[i],
                                   credential_slots[i],
                                   "1");
  }

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    delete_all_credentials_command(supporting_node_unid,
                                   endpoint_id,
                                   UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL),
    "Should be able to setup attribute store for all credential deletion");

  auto deletion_user_node
    = attribute_store_get_node_child_by_value(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&user_unique_id,
                                              sizeof(user_unique_id),
                                              0);
  auto deletion_cred_type_node
    = attribute_store_get_node_child_by_value(deletion_user_node,
                                              ATTRIBUTE(CREDENTIAL_TYPE),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_type,
                                              sizeof(credential_type),
                                              0);
  auto deletion_cred_slot_node
    = attribute_store_get_node_child_by_value(deletion_cred_type_node,
                                              ATTRIBUTE(CREDENTIAL_SLOT),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_slot,
                                              sizeof(credential_slot),
                                              0);
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_user_node),
                           "User node with id 0 should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_cred_type_node),
                           "Credential type node with id 0 should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_cred_slot_node),
                           "Credential slot node with id 0 should exists");

  helper_test_operation_type(deletion_cred_slot_node,
                             USER_CREDENTIAL_OPERATION_TYPE_DELETE);
}

void test_user_credential_cluster_delete_all_credential_for_user_happy_case()
{
  user_credential_user_unique_id_t user_unique_id = 12;
  user_credential_type_t credential_type          = 0;
  user_credential_slot_t credential_slot          = 0;

  std::vector<user_credential_user_unique_id_t> user_ids
    = {user_unique_id, user_unique_id, user_unique_id, 15, 19};
  std::vector<user_credential_type_t> credential_types = {1, 1, 2, 5, 1};
  std::vector<user_credential_slot_t> credential_slots = {1, 2, 2, 1, 3};

  // WARNING : Make sure that all the vector above have the same size
  const size_t expected_credential_count = user_ids.size();
  for (size_t i = 0; i < expected_credential_count; i++) {
    helper_add_complete_credential(user_ids[i],
                                   credential_types[i],
                                   credential_slots[i],
                                   "1");
  }

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    delete_all_credentials_for_user_command(
      supporting_node_unid,
      endpoint_id,
      UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
      user_unique_id),
    "Should be able to setup attribute store for all credential deletion");

  auto deletion_user_node
    = attribute_store_get_node_child_by_value(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&user_unique_id,
                                              sizeof(user_unique_id),
                                              0);
  auto deletion_cred_type_node
    = attribute_store_get_node_child_by_value(deletion_user_node,
                                              ATTRIBUTE(CREDENTIAL_TYPE),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_type,
                                              sizeof(credential_type),
                                              0);
  auto deletion_cred_slot_node
    = attribute_store_get_node_child_by_value(deletion_cred_type_node,
                                              ATTRIBUTE(CREDENTIAL_SLOT),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_slot,
                                              sizeof(credential_slot),
                                              0);
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_user_node),
                           "User node should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_cred_type_node),
                           "Credential type node with id 0 should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_cred_slot_node),
                           "Credential slot node with id 0 should exists");

  helper_test_operation_type(deletion_cred_slot_node,
                             USER_CREDENTIAL_OPERATION_TYPE_DELETE);
}

void test_user_credential_cluster_delete_all_credential_for_user_by_type_happy_case()
{
  user_credential_user_unique_id_t user_unique_id = 12;
  user_credential_type_t credential_type          = 1;
  user_credential_slot_t credential_slot          = 0;

  std::vector<user_credential_user_unique_id_t> user_ids
    = {user_unique_id, user_unique_id, user_unique_id, 15, 19};
  std::vector<user_credential_type_t> credential_types
    = {credential_type, credential_type, 2, 5, credential_type};
  std::vector<user_credential_slot_t> credential_slots = {1, 2, 2, 1, 3};

  // WARNING : Make sure that all the vector above have the same size
  const size_t expected_credential_count = user_ids.size();
  for (size_t i = 0; i < expected_credential_count; i++) {
    helper_add_complete_credential(user_ids[i],
                                   credential_types[i],
                                   credential_slots[i],
                                   "1");
  }

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    delete_all_credentials_for_user_by_type_command(
      supporting_node_unid,
      endpoint_id,
      UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
      user_unique_id,
      static_cast<CredType>(credential_type)),
    "Should be able to setup attribute store for all credential deletion");

  auto deletion_user_node
    = attribute_store_get_node_child_by_value(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&user_unique_id,
                                              sizeof(user_unique_id),
                                              0);
  auto deletion_cred_type_node
    = attribute_store_get_node_child_by_value(deletion_user_node,
                                              ATTRIBUTE(CREDENTIAL_TYPE),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_type,
                                              sizeof(credential_type),
                                              0);
  auto deletion_cred_slot_node
    = attribute_store_get_node_child_by_value(deletion_cred_type_node,
                                              ATTRIBUTE(CREDENTIAL_SLOT),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_slot,
                                              sizeof(credential_slot),
                                              0);
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_user_node),
                           "User node should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_cred_type_node),
                           "Credential type node should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_cred_slot_node),
                           "Credential slot node with id 0 should exists");

  helper_test_operation_type(deletion_cred_slot_node,
                             USER_CREDENTIAL_OPERATION_TYPE_DELETE);
}

void test_user_credential_cluster_delete_all_credential_by_type_happy_case()
{
  user_credential_user_unique_id_t user_unique_id = 0;
  user_credential_type_t credential_type          = 1;
  user_credential_slot_t credential_slot          = 0;

  std::vector<user_credential_user_unique_id_t> user_ids = {12, 12, 12, 15, 19};
  std::vector<user_credential_type_t> credential_types
    = {credential_type, credential_type, 2, 5, credential_type};
  std::vector<user_credential_slot_t> credential_slots = {1, 2, 2, 1, 3};

  // WARNING : Make sure that all the vector above have the same size
  const size_t expected_credential_count = user_ids.size();
  for (size_t i = 0; i < expected_credential_count; i++) {
    helper_add_complete_credential(user_ids[i],
                                   credential_types[i],
                                   credential_slots[i],
                                   "1");
  }

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    delete_all_credentials_by_type_command(
      supporting_node_unid,
      endpoint_id,
      UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
      static_cast<CredType>(credential_type)),
    "Should be able to setup attribute store for all credential deletion");

  auto deletion_user_node
    = attribute_store_get_node_child_by_value(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&user_unique_id,
                                              sizeof(user_unique_id),
                                              0);
  auto deletion_cred_type_node
    = attribute_store_get_node_child_by_value(deletion_user_node,
                                              ATTRIBUTE(CREDENTIAL_TYPE),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_type,
                                              sizeof(credential_type),
                                              0);
  auto deletion_cred_slot_node
    = attribute_store_get_node_child_by_value(deletion_cred_type_node,
                                              ATTRIBUTE(CREDENTIAL_SLOT),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_slot,
                                              sizeof(credential_slot),
                                              0);
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_user_node),
                           "User node with id 0 should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_cred_type_node),
                           "Credential type node should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(deletion_cred_slot_node),
                           "Credential slot node with id 0 should exists");

  helper_test_operation_type(deletion_cred_slot_node,
                             USER_CREDENTIAL_OPERATION_TYPE_DELETE);
}

///////////////////////////////////////////////////
// Learn Start
///////////////////////////////////////////////////
void test_user_credential_cluster_learn_start_add_happy_case()
{
  user_credential_user_unique_id_t user_unique_id  = 12;
  user_credential_type_t credential_type           = ZCL_CRED_TYPE_PIN_CODE;
  user_credential_slot_t credential_slot           = 1;
  user_credential_learn_timeout_t expected_timeout = 30;

  helper_add_user_id(user_unique_id);
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    credential_learn_start_add_command(supporting_node_unid,
                                       endpoint_id,
                                       UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                                       user_unique_id,
                                       static_cast<CredType>(credential_type),
                                       credential_slot,
                                       expected_timeout),
    "Should be able to setup attribute store for learn start");

  auto user_id_node
    = attribute_store_get_node_child_by_value(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&user_unique_id,
                                              sizeof(user_unique_id),
                                              0);
  auto credential_type_node
    = attribute_store_get_node_child_by_value(user_id_node,
                                              ATTRIBUTE(CREDENTIAL_TYPE),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_type,
                                              sizeof(credential_type),
                                              0);
  auto credential_slot_node
    = attribute_store_get_node_child_by_value(credential_type_node,
                                              ATTRIBUTE(CREDENTIAL_SLOT),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_slot,
                                              sizeof(credential_slot),
                                              0);
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(user_id_node),
                           "User node should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(credential_type_node),
                           "Credential type node should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(credential_slot_node),
                           "Credential slot should exists");

  helper_test_operation_type(credential_slot_node,
                             USER_CREDENTIAL_OPERATION_TYPE_ADD,
                             ATTRIBUTE(CREDENTIAL_LEARN_OPERATION_TYPE));
  user_credential_learn_timeout_t timeout = 0;
  attribute_store_get_child_reported(credential_slot_node,
                                     ATTRIBUTE(CREDENTIAL_LEARN_TIMEOUT),
                                     &timeout,
                                     sizeof(timeout));
  TEST_ASSERT_EQUAL_MESSAGE(expected_timeout,
                            timeout,
                            "Timeout value mismatch");
}

void test_user_credential_cluster_learn_start_modify_happy_case()
{
  user_credential_user_unique_id_t user_unique_id  = 12;
  user_credential_type_t credential_type           = ZCL_CRED_TYPE_PIN_CODE;
  user_credential_slot_t credential_slot           = 1;
  user_credential_learn_timeout_t expected_timeout = 30;

  helper_add_user_id(user_unique_id);
  helper_add_complete_credential(user_unique_id,
                                 credential_type,
                                 credential_slot,
                                 "1234");
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    credential_learn_start_modify_command(
      supporting_node_unid,
      endpoint_id,
      UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
      user_unique_id,
      static_cast<CredType>(credential_type),
      credential_slot,
      expected_timeout),
    "Should be able to setup attribute store for learn start");

  auto user_id_node
    = attribute_store_get_node_child_by_value(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&user_unique_id,
                                              sizeof(user_unique_id),
                                              0);
  auto credential_type_node
    = attribute_store_get_node_child_by_value(user_id_node,
                                              ATTRIBUTE(CREDENTIAL_TYPE),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_type,
                                              sizeof(credential_type),
                                              0);
  auto credential_slot_node
    = attribute_store_get_node_child_by_value(credential_type_node,
                                              ATTRIBUTE(CREDENTIAL_SLOT),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_slot,
                                              sizeof(credential_slot),
                                              0);
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(user_id_node),
                           "User node should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(credential_type_node),
                           "Credential type node should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(credential_slot_node),
                           "Credential slot should exists");

  helper_test_operation_type(credential_slot_node,
                             USER_CREDENTIAL_OPERATION_TYPE_MODIFY,
                             ATTRIBUTE(CREDENTIAL_LEARN_OPERATION_TYPE));
  uint8_t timeout = 0;
  attribute_store_get_child_reported(credential_slot_node,
                                     ATTRIBUTE(CREDENTIAL_LEARN_TIMEOUT),
                                     &timeout,
                                     sizeof(timeout));
  TEST_ASSERT_EQUAL_MESSAGE(expected_timeout,
                            timeout,
                            "Timeout value mismatch");
}

void test_user_credential_cluster_learn_stop_happy_case()
{
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    credential_learn_stop_command(supporting_node_unid,
                                  endpoint_id,
                                  UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL),
    "Should be able to setup attribute store for learn stop");

  uint8_t stop_flag = 0;
  auto stop_node
    = attribute_store_get_node_child_by_type(endpoint_id_node,
                                             ATTRIBUTE(CREDENTIAL_LEARN_STOP),
                                             0);
  attribute_store_get_desired(stop_node, &stop_flag, sizeof(stop_flag));
  TEST_ASSERT_EQUAL_MESSAGE(1, stop_flag, "Stop flag should be set to 1");
}

void test_user_credential_cluster_credential_association_happy_case()
{
  user_credential_user_unique_id_t source_user_unique_id      = 12;
  user_credential_user_unique_id_t destination_user_unique_id = 12;
  user_credential_type_t credential_type             = ZCL_CRED_TYPE_PIN_CODE;
  user_credential_slot_t source_credential_slot      = 1;
  user_credential_slot_t destination_credential_slot = 2;

  helper_add_user_id(source_user_unique_id);
  helper_add_complete_credential(source_user_unique_id,
                                 credential_type,
                                 source_credential_slot,
                                 "1234");
  helper_add_user_id(destination_user_unique_id);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    credential_association_command(supporting_node_unid,
                                   endpoint_id,
                                   UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                                   static_cast<CredType>(credential_type),
                                   source_user_unique_id,
                                   source_credential_slot,
                                   destination_user_unique_id,
                                   destination_credential_slot),
    "Should be able to setup attribute store for credential_association");

  auto user_id_node
    = attribute_store_get_node_child_by_value(endpoint_id_node,
                                              ATTRIBUTE(USER_UNIQUE_ID),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&source_user_unique_id,
                                              sizeof(source_user_unique_id),
                                              0);
  auto credential_type_node
    = attribute_store_get_node_child_by_value(user_id_node,
                                              ATTRIBUTE(CREDENTIAL_TYPE),
                                              REPORTED_ATTRIBUTE,
                                              (uint8_t *)&credential_type,
                                              sizeof(credential_type),
                                              0);
  auto credential_slot_node = attribute_store_get_node_child_by_value(
    credential_type_node,
    ATTRIBUTE(CREDENTIAL_SLOT),
    REPORTED_ATTRIBUTE,
    (uint8_t *)&source_credential_slot,
    sizeof(source_credential_slot),
    0);
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(user_id_node),
                           "User node should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(credential_type_node),
                           "Credential type node should exists");
  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(credential_slot_node),
                           "Credential slot should exists");

  user_credential_user_unique_id_t reported_destination_user_id = 0;
  auto association_destination_user_node
    = attribute_store_get_node_child_by_type(
      credential_slot_node,
      ATTRIBUTE(ASSOCIATION_DESTINATION_USER_ID),
      0);
  attribute_store_get_desired(association_destination_user_node,
                              &reported_destination_user_id,
                              sizeof(reported_destination_user_id));
  TEST_ASSERT_EQUAL_MESSAGE(destination_user_unique_id,
                            reported_destination_user_id,
                            "Destination user id mismatch");

  user_credential_slot_t reported_destination_credential_slot = 0;
  auto association_destination_credential_slot_node
    = attribute_store_get_node_child_by_type(
      credential_slot_node,
      ATTRIBUTE(ASSOCIATION_DESTINATION_CREDENTIAL_SLOT),
      0);
  attribute_store_get_desired(association_destination_credential_slot_node,
                              &reported_destination_credential_slot,
                              sizeof(reported_destination_credential_slot));
  TEST_ASSERT_EQUAL_MESSAGE(destination_credential_slot,
                            reported_destination_credential_slot,
                            "Destination credential slot mismatch");
}

void test_user_credential_cluster_test_user_checksum_happy_case()
{
  user_credential_user_unique_id_t user_unique_id = 12;

  auto user_id_node = helper_add_user_id(user_unique_id);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    get_user_checksum_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id),
    "Should be able to setup attribute store for get_user_checksum");

  auto checksum_node
    = attribute_store_get_first_child_by_type(user_id_node,
                                              ATTRIBUTE(USER_CHECKSUM));

  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(checksum_node),
                           "Checksum node should exists");
  user_credential_checksum_t checksum = 1312;
  mock_expected_user_mqtt_topic(user_unique_id,
                                "UserChecksum",
                                checksum);
  attribute_store_set_reported(checksum_node, &checksum, sizeof(checksum));

  // Try a second time to see if we still have only one checksum node
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    get_user_checksum_command(supporting_node_unid,
                              endpoint_id,
                              UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                              user_unique_id),
    "Should be able to setup attribute store for get_user_checksum");

  auto checksum_count
    = attribute_store_get_node_child_count_by_type(user_id_node,
                                                   ATTRIBUTE(USER_CHECKSUM));

  TEST_ASSERT_EQUAL_MESSAGE(1,
                            checksum_count,
                            "Should have only one checksum attribute");

  checksum_node
    = attribute_store_get_first_child_by_type(user_id_node,
                                              ATTRIBUTE(USER_CHECKSUM));

  TEST_ASSERT_FALSE_MESSAGE(
    attribute_store_is_reported_defined(checksum_node),
    "Checksum node reported value should be not defined");
}

void test_user_credential_cluster_test_credential_checksum_happy_case()
{
  user_credential_type_t credential_type = ZCL_CRED_TYPE_PIN_CODE;

  auto credential_type_node
    = attribute_store_emplace(endpoint_id_node,
                              ATTRIBUTE(SUPPORTED_CREDENTIAL_TYPE),
                              &credential_type,
                              sizeof(credential_type));

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    get_credential_checksum_command(supporting_node_unid,
                                    endpoint_id,
                                    UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                                    static_cast<CredType>(credential_type)),
    "Should be able to setup attribute store for get_credential_checksum");

  auto checksum_node
    = attribute_store_get_first_child_by_type(credential_type_node,
                                              ATTRIBUTE(CREDENTIAL_CHECKSUM));

  TEST_ASSERT_TRUE_MESSAGE(attribute_store_node_exists(checksum_node),
                           "Checksum node should exists");

  user_credential_checksum_t checksum = 1312;
  mock_expected_cred_rule_mqtt_topic(credential_type,
                                     "CredentialChecksum",
                                     checksum);
  attribute_store_set_reported(checksum_node, &checksum, sizeof(checksum));

  // Try a second time to see if we still have only one checksum node
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    get_credential_checksum_command(supporting_node_unid,
                                    endpoint_id,
                                    UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                                    static_cast<CredType>(credential_type)),
    "Should be able to setup attribute store for get_credential_checksum");

  auto checksum_count
    = attribute_store_get_node_child_count_by_type(credential_type_node,
                                                   ATTRIBUTE(CREDENTIAL_CHECKSUM));

  TEST_ASSERT_EQUAL_MESSAGE(1,
                            checksum_count,
                            "Should have only one checksum attribute");

  checksum_node
    = attribute_store_get_first_child_by_type(credential_type_node,
                                              ATTRIBUTE(CREDENTIAL_CHECKSUM));

  TEST_ASSERT_FALSE_MESSAGE(
    attribute_store_is_reported_defined(checksum_node),
    "Checksum node reported value should be not defined");
}


void test_user_credential_cluster_test_all_users_checksum_happy_case()
{
  // Command not supported yet (default user capabilities SUPPORT_ALL_USERS_CHECKSUM set to 0)
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    get_all_users_checksum_command(supporting_node_unid,
                                   endpoint_id,
                                   UIC_MQTT_DOTDOT_CALLBACK_TYPE_SUPPORT_CHECK),
    "Not supported yet since we are missing the capability");

  cpp_endpoint_node.child_by_type(ATTRIBUTE(SUPPORT_ALL_USERS_CHECKSUM))
    .set_reported<uint8_t>(1);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    get_all_users_checksum_command(supporting_node_unid,
                                   endpoint_id,
                                   UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL),
    "Should be able to setup attribute store for get_all_users_checksum");

  auto checksum_node
    = cpp_endpoint_node.child_by_type(ATTRIBUTE(ALL_USERS_CHECKSUM));

  TEST_ASSERT_TRUE_MESSAGE(
    checksum_node.is_valid(),
    "All users checksum node should exists");

  checksum_node.set_desired<uint16_t>(1312);
  checksum_node.set_reported<uint16_t>(12);

  // Try a second time to see if we clear the attributes
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    get_all_users_checksum_command(supporting_node_unid,
                                   endpoint_id,
                                   UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL),
    "Should be able to setup attribute store for get_all_users_checksum");
  
  TEST_ASSERT_FALSE_MESSAGE(
    checksum_node.desired_exists(),
    "Checksum node desired value should NOT exists");

  TEST_ASSERT_FALSE_MESSAGE(
    checksum_node.reported_exists(),
    "Checksum node reported value should NOT exists");
}

void test_user_credential_cluster_test_admin_set_command_happy_case()
{
  auto support_admin_pin_code_node
    = cpp_endpoint_node.emplace_node(ATTRIBUTE(SUPPORT_ADMIN_PIN_CODE))
        .set_reported<uint8_t>(0);
  auto status
    = set_admin_pin_code_command(supporting_node_unid,
                                 endpoint_id,
                                 UIC_MQTT_DOTDOT_CALLBACK_TYPE_SUPPORT_CHECK,
                                 "");
  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    status,
    "Admin set should NOT be supported since SUPPORT_ADMIN_PIN_CODE is 0");

  support_admin_pin_code_node.set_reported<uint8_t>(1);

  status
    = set_admin_pin_code_command(supporting_node_unid,
                                 endpoint_id,
                                 UIC_MQTT_DOTDOT_CALLBACK_TYPE_SUPPORT_CHECK,
                                 "");

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    status,
    "Admin set should be supported since SUPPORT_ADMIN_PIN_CODE is 1");

  std::string expected_pin_code = "1234";
  status
    = set_admin_pin_code_command(supporting_node_unid,
                                 endpoint_id,
                                 UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL,
                                 expected_pin_code.c_str());

  auto raw_pin_code
    = cpp_endpoint_node.child_by_type(ATTRIBUTE(ADMIN_PIN_CODE))
        .desired<std::vector<uint8_t>>();
  
  std::string reported_pin_code;
  for (char c : raw_pin_code) {
    reported_pin_code += c;
  }

  TEST_ASSERT_EQUAL_STRING_MESSAGE(expected_pin_code.c_str(),
                                   reported_pin_code.c_str(),
                                   "Admin pin code mismatch");
}

void test_user_credential_cluster_test_admin_deactivate_command_happy_case()
{
  auto support_admin_deactivation_node
    = cpp_endpoint_node
        .emplace_node(ATTRIBUTE(SUPPORT_ADMIN_PIN_CODE_DEACTIVATION))
        .set_reported<uint8_t>(0);
  auto status = deactivate_admin_pin_code_command(
    supporting_node_unid,
    endpoint_id,
    UIC_MQTT_DOTDOT_CALLBACK_TYPE_SUPPORT_CHECK);
  TEST_ASSERT_EQUAL_MESSAGE(SL_STATUS_FAIL,
                            status,
                            "Admin deactivation should NOT be supported since "
                            "SUPPORT_ADMIN_PIN_CODE_DEACTIVATION is 0");

  support_admin_deactivation_node.set_reported<uint8_t>(1);

  status = deactivate_admin_pin_code_command(
    supporting_node_unid,
    endpoint_id,
    UIC_MQTT_DOTDOT_CALLBACK_TYPE_SUPPORT_CHECK);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    status,
    "Admin deactivation should be supported since SUPPORT_ADMIN_PIN_CODE is 1");

  status
    = deactivate_admin_pin_code_command(supporting_node_unid,
                                        endpoint_id,
                                        UIC_MQTT_DOTDOT_CALLBACK_TYPE_NORMAL);

  std::vector<uint8_t> expected_empty_pin_code = {0};
  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(
    expected_empty_pin_code.data(),
    cpp_endpoint_node.child_by_type(ATTRIBUTE(ADMIN_PIN_CODE))
      .desired<std::vector<uint8_t>>()
      .data(),
    expected_empty_pin_code.size(),
    "Admin pin code should be at empty value");
}

///////////////////////////////////////////////////
// Support tests
///////////////////////////////////////////////////

void test_user_credential_cluster_test_user_command_support_happy_case()
{
  // We don't care about those value it should not matter here
  user_credential_user_unique_id_t user_unique_id = 12;
  UserTypeEnum user_type                  = ZCL_USER_TYPE_ENUM_DISPOSABLE_USER;
  CredRule credential_rule                = ZCL_CRED_RULE_SINGLE;
  bool user_active_state                  = true;
  uint16_t expiring_timeout               = 50;
  UserNameEncodingType user_name_encoding = ZCL_USER_NAME_ENCODING_TYPE_ASCII;
  const char *user_name                   = "Test User";

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    add_user_command(supporting_node_unid,
                     endpoint_id,
                     UIC_MQTT_DOTDOT_CALLBACK_TYPE_SUPPORT_CHECK,
                     user_unique_id,
                     user_type,
                     user_active_state,
                     credential_rule,
                     user_name,
                     expiring_timeout,
                     user_name_encoding),
    "Add user should be supported");

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    modify_user_command(supporting_node_unid,
                        endpoint_id,
                        UIC_MQTT_DOTDOT_CALLBACK_TYPE_SUPPORT_CHECK,
                        user_unique_id,
                        user_type,
                        user_active_state,
                        credential_rule,
                        user_name,
                        expiring_timeout,
                        user_name_encoding),
    "Modify user should be supported");

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_OK,
    delete_user_command(supporting_node_unid,
                        endpoint_id,
                        UIC_MQTT_DOTDOT_CALLBACK_TYPE_SUPPORT_CHECK,
                        user_unique_id),
    "Delete user should be supported");
}

void test_user_credential_cluster_test_user_command_not_supported_happy_case()
{
  // We don't care about those value it should not matter here
  user_credential_user_unique_id_t user_unique_id = 12;
  UserTypeEnum user_type                  = ZCL_USER_TYPE_ENUM_DISPOSABLE_USER;
  CredRule credential_rule                = ZCL_CRED_RULE_SINGLE;
  bool user_active_state                  = true;
  uint16_t expiring_timeout               = 50;
  UserNameEncodingType user_name_encoding = ZCL_USER_NAME_ENCODING_TYPE_ASCII;
  const char *user_name                   = "Test User";

  // We don't want anything in the tree for this test
  // This way we can make support check fails
  // We need to inform the MQTT of the deleted credential type rules
  for (auto cred_type: created_supported_credential_types) {
    mock_deletion_cred_rule_mqtt_topic(cred_type);
  }
  // Delete all the nodes
  attribute_store_delete_all_children(endpoint_id_node);

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    add_user_command(supporting_node_unid,
                     endpoint_id,
                     UIC_MQTT_DOTDOT_CALLBACK_TYPE_SUPPORT_CHECK,
                     user_unique_id,
                     user_type,
                     user_active_state,
                     credential_rule,
                     user_name,
                     expiring_timeout,
                     user_name_encoding),
    "Check value : Add user should not be supported");

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    modify_user_command(supporting_node_unid,
                        endpoint_id,
                        UIC_MQTT_DOTDOT_CALLBACK_TYPE_SUPPORT_CHECK,
                        user_unique_id,
                        user_type,
                        user_active_state,
                        credential_rule,
                        user_name,
                        expiring_timeout,
                        user_name_encoding),
    "Modify user should not be supported");

  TEST_ASSERT_EQUAL_MESSAGE(
    SL_STATUS_FAIL,
    delete_user_command(supporting_node_unid,
                        endpoint_id,
                        UIC_MQTT_DOTDOT_CALLBACK_TYPE_SUPPORT_CHECK,
                        user_unique_id),
    "Delete user should not be supported");
}


}  // extern "C"