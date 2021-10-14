/*
 * test_SCD30_module.c
 *
 * Created: 14-10-2021 08:42:54
 *  Author: Mainframe
 */ 


#define F_CPU 8000000UL	

#include <xc.h>
#include <util/delay.h>



#include "test_SCD30_module.h"
#include "../../HAL/TWI/TWI_HAL.h"
#include "../../HAL/UART0/UART0_HAL.h"

void test_HAL();
void read_firmware();
void throw_error(uint8_t status, uint8_t index);

void test_SCD30_module_start(){
	uart0_hal_init();
	
		while(1){
			//test_HAL();
			read_firmware();
			_delay_ms(3000);
		}
	
	
}

void read_firmware(){
	uint8_t status;
	uint8_t data[]={0x00, 0x00, 0x00};
	
	TWI_HAL_init();
	
	status=TWI_HAL_start(0x61, WRITE);
	if(status!=1) 
		return throw_error(status, 0);
		
	status=TWI_HAL_write_byte(0xD1);
	if(status!=1)
		return throw_error(status, 1);
		
	status=TWI_HAL_write_byte(0x00);
	if(status!=1)
		return throw_error(status, 2);
		
	TWI_HAL_stop();
	_delay_ms(5);
	
	status=TWI_HAL_start(0x61, READ);
	if(status!=1)
		return throw_error(status, 3);
		
	data[0]=TWI_HAL_read_byte_ack();
	data[1]=TWI_HAL_read_byte_ack();
	data[2]=TWI_HAL_read_byte_nack();
	
	TWI_HAL_stop();
	
	uart0_hal_send_message(data, 3);
	
}

void throw_error(uint8_t status, uint8_t index){
	uint8_t msg[3];
	msg[0]=status;
	msg[1]=index;
	msg[2]=0xFF;
	uart0_hal_send_message(msg, 3);
}

void test_HAL(){
	TWI_HAL_init();
	uint8_t status=TWI_HAL_start(0x61, WRITE);
	uint8_t msg[2];
	msg[0]=status;
	msg[1]=0xff;
	uart0_hal_send_message(msg, 2);
	//if(status==0){
		//char msg[]="0 ";
		//uart0_hal_send_message((uint8_t*)msg, 3);
	//}else if(status==1){
		//char msg[]="OK";
		//uart0_hal_send_message((uint8_t*)msg, 5);
	//}else {
		//char msg[]="OK";
		//uart0_hal_send_message((uint8_t*)msg, 5);
	//}
}