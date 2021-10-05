/*
 * join_network.c
 *
 * Created: 05-10-2021 14:57:07
 *  Author: Mainframe
 */ 

#include <string.h>
#include <stdio.h>
#include <util/delay.h>
#include "join_network.h"
#include "../lora_module.h"
#include "../../../HAL/RN2483/RN2483_HAL.h"
#include "../RN2483_protocol/RN2483_protocol.h"

LM_STATUS LM_join_network(){
	
	JN_STATES state=JN_HW_RESET_RN2483;
	LM_STATE_DATA stateData;
	
	
	while(1){
		switch(state){
			case JN_HW_RESET_RN2483:
				rn2483_reset_active();
				_delay_ms(1000);
				rn2483_reset_deactive();
				
				LM_setPendingStates(&stateData, JN_SOFT_RESET_LORA, JN_JOIN_FATAL_ERROR);
				LM_setMatchCase(&stateData, LM_BEGINS_WITH, RN2483);
				
				state=JN_WAIT_FOR_INCOMMING;
			break;
			
			case JN_SOFT_RESET_LORA:
				cmd_with_ending(lm_msg, MAC_RESET_TO_868_BAND);
				LM_transmit_msg(lm_msg);
				
				LM_setPendingStates(&stateData, JN_JOIN_SUCCESS, JN_JOIN_FATAL_ERROR);
				LM_setMatchCase(&stateData, LM_EXACT, OK);
				state=JN_WAIT_FOR_INCOMMING;
			break;
				
			case JN_JOIN_SUCCESS:
				return LM_STATUS_SUCCESS;
				
			case JN_JOIN_FATAL_ERROR:
				return LM_STATUS_FATAL_ERROR;
				
				
			case JN_WAIT_FOR_INCOMMING:
				if(uart0_hal_message_ready()){
					LM_read_msg(lm_msg);
					state=LM_matchMessage(&stateData, lm_msg);
				}
			break;
		}
	}
	return LM_STATUS_FATAL_ERROR;
}