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

LM_STATUS LM_join_network();


#endif /* LORA_MODULE_H_ */