/*
 * test_lora_module.c
 *
 * Created: 04-10-2021 16:51:38
 *  Author: Mainframe
 */ 
#define F_CPU 8000000UL	
#include "test_lora_module.h"
#include "../../HAL/UART0/UART0_HAL.h"
#include <util/delay.h>
#include "../../MODULES/lora_module/lora_module.h"
#include "../../MODULES/lora_module/RN2483_protocol/RN2483_protocol.h"

void test_lora_module_start(){
	
	uart0_hal_init();
	
	while(1){
		const char msg[200];
		int16_t len=cmd_with_ending(msg, SYS_GET_HW_EUI_CMD);
		
		uart0_hal_send_message((uint8_t *) msg, len);
		_delay_ms(1000);
	}
}
