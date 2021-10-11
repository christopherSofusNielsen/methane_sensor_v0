/*
 * lora_module.c
 *
 * Created: 05-10-2021 15:57:06
 *  Author: Mainframe
 */ 

#include "lora_module.h"
#include "join_network/join_network.h"


LM_STATUS LM_join_network(){
	return JN_join_network();
}

