/*
 * test_lora_module.c
 *
 * Created: 04-10-2021 16:51:38
 *  Author: Mainframe
 */ 
#define F_CPU 8000000UL	
#include <util/delay.h>
#include "test_lora_module.h"
#include "../../HAL/UART0/UART0_HAL.h"
#include "../../HAL/RN2483/RN2483_HAL.h"
#include "../../MODULES/lora_module/lora_module.h"

void test_join_network();

void test_lora_module_start(){
	
	uart0_hal_init();
	rn2483_init();
	
	while(1){
		test_join_network();
		_delay_ms(3000);
	}
}

void test_join_network(){
	LM_STATUS status=LM_join_network();
	if(status==LM_STATUS_SUCCESS){
		char msg[]="OK";
		uart0_hal_send_message((uint8_t*)msg, 3);
		}else if(status==LM_STATUS_TRY_AGAIN){
		char msg[]="TRY";
		uart0_hal_send_message((uint8_t*)msg, 4);
		}else{
		char msg[]="FAIL";
		uart0_hal_send_message((uint8_t*)msg, 5);
	}
}
