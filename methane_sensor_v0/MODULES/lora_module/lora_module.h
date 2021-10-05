/*
 * lora_module.h
 *
 * Created: 04-10-2021 17:21:25
 *  Author: Mainframe
 */ 


#ifndef LORA_MODULE_H_
#define LORA_MODULE_H_

typedef enum {
	LM_STATUS_SUCCESS,
	LM_STATUS_ERROR,
	LM_STATUS_FATAL_ERROR,
	LM_STATUS_TRY_AGAIN
}LM_STATUS;

typedef enum {LM_EXACT, LM_BEGINS_WITH, LM_NO_TEST} LM_MATCH_CASES;

typedef struct __STATE_DATA{
	int success_state;
	int failure_state;
	LM_MATCH_CASES matchCase;
	const char *matchString;
}LM_STATE_DATA;

extern char lm_msg[200];
//extern LM_STATE_DATA lm_state_data_obj;

void LM_setPendingStates(LM_STATE_DATA *sd, int success, int failed);
void LM_setMatchCase(LM_STATE_DATA *sd, LM_MATCH_CASES matchCase, const char *matchString);
int LM_matchMessage(LM_STATE_DATA *sd, char *msg);
void LM_transmit_msg(char msg[]);
void LM_read_msg(char msg[]);


#endif /* LORA_MODULE_H_ */