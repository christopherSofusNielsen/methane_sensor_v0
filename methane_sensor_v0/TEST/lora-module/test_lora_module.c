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
#include "../../MODULES/lora_module/join_network/join_network.h"
#include "../../MODULES/lora_module/lora_module.h"
#include "../../HAL/RN2483/RN2483_HAL.h"


void test_lora_module_start(){
	
	uart0_hal_init();
	rn2483_init();
	
	while(1){
		LM_STATUS status=LM_join_network();
		if(status==LM_STATUS_SUCCESS){
			char msg[]="OK";
			uart0_hal_send_message((uint8_t*)msg, 3);
		}else{
			char msg[]="FAIL";
			uart0_hal_send_message((uint8_t*)msg, 5);
		}
		_delay_ms(3000);
	}
}
