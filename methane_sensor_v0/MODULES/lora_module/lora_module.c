/*
 * lora_module.c
 *
 * Created: 05-10-2021 15:57:06
 *  Author: Mainframe
 */ 

#include "lora_module.h"
#include <string.h>
#include <stdbool.h>

char lm_msg[200];
//LM_STATE_DATA lm_state_data_obj;
static bool LM_strbeginswith(char *s1, const char *s2);


void LM_setPendingStates(LM_STATE_DATA *sd, int success, int failed){
	sd->success_state=success;
	sd->failure_state=failed;
}

void LM_setMatchCase(LM_STATE_DATA *sd, LM_MATCH_CASES matchCase, const char *matchString){
	sd->matchCase=matchCase;
	sd->matchString=matchString;
}

int LM_matchMessage(LM_STATE_DATA *sd, char *msg){
	switch(sd->matchCase){
		case LM_EXACT:
			return strcmp(msg, sd->matchString)==0?sd->success_state:sd->failure_state;

		case LM_BEGINS_WITH:
			return LM_strbeginswith(msg, sd->matchString)?sd->success_state:sd->failure_state;

		case LM_NO_TEST:
			return sd->success_state;
		default:
			return sd->failure_state;
	}
}

void LM_transmit_msg(char msg[]){
	uart0_hal_send_message(msg, strlen(msg));
}

void LM_read_msg(char msg[]){
	uart0_hal_read_message_as_str(msg);
}

static bool LM_strbeginswith(char *s1, const char *s2){
	return strncmp(s1, s2, strlen(s2))==0?true:false;
}

