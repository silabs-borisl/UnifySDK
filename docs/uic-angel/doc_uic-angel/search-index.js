var searchIndex = JSON.parse('{\
"uic_angel":{"doc":"UIC ANGEL Is an UIC helper application that enables …","t":[17,17,0,5,5,0,0,5,5,5,3,3,6,11,11,11,11,11,11,12,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,11,11,11,11,11,11,11,11,12,11,11,12,11,11,11,11,11,11,11,12,11,11,3,3,8,8,6,3,11,11,11,11,11,11,12,11,11,10,11,11,11,11,11,11,11,11,11,10,11,11,12,12,12,11,10,12,11,10,11,11,11,11,11,12,10,11,11,10,11,11,11,11,11,11,11,11,11,11,11,11,3,17,11,11,12,11,11,11,12,11,11,11,11,11,11,11,12,12,11,11,12,11,11,11],"n":["APP_NAME","CONFIG_VERSION","cache","get_config","main","mqtt_client","mqtt_handler","ok_or_exit_with_message","parse_application_arguments","run","Cache","EntryChanged","UnidEpPair","borrow","borrow","borrow_mut","borrow_mut","clone","clone_into","endpoints","eq","eq","fmt","fmt","from","from","get_endpoint_cluster_supported_commands","get_endpoints_for_group","get_endpoints_supported_commands_per_cluster","get_group_list_for_node","get_group_name","get_group_supported_commands_per_cluster","group_id","group_names","groups_for_endpoints","into","into","is_unretain","make_changed_entries","ne","ne","new","remove_group_name","reverse_lookup","set_endpoint_cluster_supported_commands","set_group_list_for_node","supported_commands_for_endpoints","to_owned","try_from","try_from","try_into","try_into","type_id","type_id","unid","update_group_name","update_reverse_lookup","MosqMessage","MosquittoClient","MqttClient","MqttMessageReceived","Result","TopicMatcher","borrow","borrow","borrow","borrow_mut","borrow_mut","borrow_mut","client","clone","clone_into","connect","connect","drop","fmt","from","from","from","into","into","into","mainloop","mainloop","matches","mid","mosq","msg","new","on_message","owned","payload","publish","publish","qos","receive_many","receive_one","retained","sub","subscribe","subscribe","text","tls_set","tls_set","to_owned","topic","try_from","try_from","try_from","try_into","try_into","try_into","type_id","type_id","type_id","MqttHandler","TAG","borrow","borrow_mut","cache","from","get_unid_ep_of_topic","into","mqtt_client","new","on_group_list_reported","on_message","on_name_reported","on_supported_commands","process_message","publish_commands_by_cluster","reported_group_list_matcher","reported_names_matcher","send_add_group_if_required","send_group_name","supported_commands","try_from","try_into","type_id"],"q":["uic_angel","","","","","","","","","","uic_angel::cache","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","uic_angel::mqtt_client","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","uic_angel::mqtt_handler","","","","","","","","","","","","","","","","","","","","","","",""],"d":["","","Cache is an object that bookkeeps unid &amp; endpoint to group …","","","","","","","","","","","","","","","","","","","","","","","","Get the list of supported commands, for a given cluster, …","Get the list of endpoints that belong to group.","Get the list of commands supported by endpoint per …","Get a list of groups a node belongs to. Returns an empty …","","Get the list of commands supported by group per clusters.","","","","","","","creates EntryChanged objects for the records that will be …","","","","","","Update the list of supported-commands, per cluster, for …","Update the cache with new groups for an given key …","","","","","","","","","","returns true if the name was updated. returns false when …","rebuilds reverse_lookup completely from …","A mosquitto message","","interface wrapper of the mosquitto_client, so that we can …","","","Matching subscription topics. Returned from …","","","","","","","","","","","","","","","","","","","","","","true if a message matches a subscription topic","the subscription id.","","","","","","the payload as bytes","","","the quality-of-service of the message. The desired QoS is …","receive and return messages matching this topic, until …","receive and return exactly one message matching this topic","was the message retained by the broker? True if we …","","","","the payload as text. This will <strong>panic</strong> if the payload was …","","","","the topic of the message. This will <strong>panic</strong> if the topic isn…","","","","","","","","","","MqttHandler handles subscription messages related to UIC …","","","","Lookup cache for groups and unids","","parse group topic message and extract unid and endpoint id","","Reference counted to the mosquitto-client. Notice that its …","crate new handler to be passed into a MqttClient. The …","process a …","public function to be called by the mosquitto fwk on a …","handler for topic …","","","","","","add_group is only send when an update of an groupname is …","","","","",""],"i":[0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,2,1,1,1,1,2,1,2,1,2,2,2,2,2,2,2,1,2,2,1,2,1,2,1,2,2,2,2,2,2,2,1,1,2,1,2,1,2,1,2,2,0,0,0,0,0,0,3,4,5,3,4,5,3,4,4,6,3,4,4,3,4,5,3,4,5,6,3,5,5,5,4,3,7,4,4,6,3,4,5,5,4,5,6,3,4,6,3,4,4,3,4,5,3,4,5,3,4,5,0,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8],"f":[null,null,null,[[],[["config_status_t",4],["result",4,["config_status_t"]]]],[[],[["result",4,["i32"]],["i32",15]]],null,null,[[["result",4],["str",15],["display",8]],[["i32",15],["result",4,["i32"]]]],[[],[["config_status_t",4],["result",4,["config_status_t"]]]],[[["str",15],["i32",15]],["result",6]],null,null,null,[[]],[[]],[[]],[[]],[[],["entrychanged",3]],[[]],null,[[["entrychanged",3]],["bool",15]],[[["cache",3]],["bool",15]],[[["formatter",3]],["result",6]],[[["formatter",3]],["result",6]],[[]],[[]],[[["str",15]],[["option",4,["hashset"]],["hashset",3,["string"]]]],[[["u16",15]],[["vec",3],["option",4,["vec"]]]],[[["vec",3]],[["option",4,["btreemap"]],["btreemap",3,["string","hashset"]]]],[[["u16",15],["str",15]],[["u16",15],["vec",3,["u16"]]]],[[["u16",15]],[["option",4,["string"]],["string",3]]],[[["u16",15]],[["option",4,["btreemap"]],["btreemap",3,["string","hashset"]]]],null,null,null,[[]],[[]],[[],["bool",15]],[[],[["vec",3,["entrychanged"]],["entrychanged",3]]],[[["entrychanged",3]],["bool",15]],[[["cache",3]],["bool",15]],[[]],[[["u16",15]]],null,[[["hashset",3,["string"]],["str",15],["string",3]]],[[["u16",15],["str",15]],[["vec",3,["entrychanged"]],["entrychanged",3]]],null,[[]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["typeid",3]],[[],["typeid",3]],null,[[["u16",15],["str",15]],["bool",15]],[[]],null,null,null,null,null,null,[[]],[[]],[[]],[[]],[[]],[[]],null,[[],["mosqmessage",3]],[[]],[[["str",15],["u32",15]],["result",6]],[[["str",15],["u32",15]],["result",6]],[[]],[[["formatter",3]],[["result",4,["error"]],["error",3]]],[[]],[[]],[[]],[[]],[[]],[[]],[[],["result",6]],[[["mqtthandler",3]],["result",6]],[[["mosqmessage",3]],["bool",15]],null,null,null,[[["str",15]]],[[["mosqmessage",3]]],null,[[]],[[["u32",15],["bool",15],["str",15]],[["i32",15],["result",6,["i32"]]]],[[["u32",15],["bool",15],["str",15]],[["i32",15],["result",6,["i32"]]]],[[],["u32",15]],[[["i32",15]],[["result",4,["vec","error"]],["vec",3,["mosqmessage","global"]],["error",3]]],[[["i32",15]],[["result",4,["mosqmessage","error"]],["error",3],["mosqmessage",3]]],[[],["bool",15]],null,[[["str",15],["u32",15]],[["topicmatcher",3],["result",6,["topicmatcher"]]]],[[["str",15],["u32",15]],[["topicmatcher",3],["result",6,["topicmatcher"]]]],[[],["str",15]],[[["path",3]],["result",6]],[[["path",3]],["result",6]],[[]],[[],["str",15]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["result",4]],[[],["typeid",3]],[[],["typeid",3]],[[],["typeid",3]],null,null,[[]],[[]],null,[[]],[[["str",15]],[["result",4,["string"]],["string",3]]],[[]],null,[[["mqttclient",8],["rc",3,["mqttclient"]]]],[[["jsonvalue",4],["str",15]],[["result",4,["string"]],["string",3]]],[[["mosqmessage",3]]],[[["jsonvalue",4],["str",15]],[["result",4,["string"]],["string",3]]],[[["jsonvalue",4],["str",15]],[["result",4,["string"]],["string",3]]],[[["mosqmessage",3]],[["result",4,["string"]],["string",3]]],[[["u16",15],["hashset",3,["string"]],["bool",15],["btreemap",3,["string","hashset"]],["string",3]],[["result",4,["string"]],["string",3]]],null,null,[[["u16",15],["str",15]],[["result",4,["string"]],["string",3]]],[[["u16",15],["str",15]],[["result",4,["string"]],["string",3]]],null,[[],["result",4]],[[],["result",4]],[[],["typeid",3]]],"p":[[3,"EntryChanged"],[3,"Cache"],[3,"MosquittoClient"],[3,"MosqMessage"],[3,"TopicMatcher"],[8,"MqttClient"],[8,"MqttMessageReceived"],[3,"MqttHandler"]]}\
}');
if (window.initSearch) {window.initSearch(searchIndex)};