/*
 * lora_module.c
 *
 * Created: 05-10-2021 15:57:06
 *  Author: Mainframe
 */ 

#include "lora_module.h"
#include "join_network/join_network.h"
#include "send_uplink/send_uplink.h"


LM_STATUS LM_join_network(){
	return JN_join_network();
}

LM_STATUS LM_send_uplink(uint8_t data[], uint8_t length){
	return SU_send_uplink(LORA_PORT, data, length);
}

