/*
 * TWI_HAL.c
 *
 * Created: 14-10-2021 08:43:55
 *  Author: Mainframe
 */ 

#include "TWI_HAL.h"
#include "../../util/bit_operators.h"
#include <xc.h>
#define twi_read_status(Reg) (Reg & 0xF8)
#define twi_start_transmission (1<<TWINT)|(1<<TWEN)
#define TWI_CODE_START 0x08

#define TWI_CODE_ADDR_W_TRANS_ACK_REC 0x18
#define TWI_CODE_ADDR_W_TRANS_NACK_REC 0x20
#define TWI_CODE_ADDR_R_TRANS_ACK_REC 0x40
#define TWI_CODE_ADDR_R_TRANS_NACK_REC 0x48



#define TWI_CODE_DATA_TRANS_ACK_REC 0x28
#define TWI_CODE_DATA_TRANS_NACK_REC 0x30




void TWI_HAL_init(){
	TWBR0=TWI_TWBR; //Set bit generator
	if(TWI_PRESCALE==1)
		clear_byte(TWSR0, 0b00000011); //set prescale to 1
	
}

uint8_t TWI_HAL_start(uint8_t addr, TWI_HAL_START_TYPE type){
	uint8_t addr_type=(addr<<1) | type;
	uint8_t status;
	
	TWCR0=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //Send start condition
	
	while (!get_bit(TWCR0, TWINT)); //Wait to finish job
	status=twi_read_status(TWSR0);
	
	if(status != TWI_CODE_START) return 0; //Check status is success
	
	TWDR0=addr_type; //Set Write addr
	TWCR0=(1<<TWINT)|(1<<TWEN); //Start transmission of addr
	
	while (!get_bit(TWCR0, TWINT)); //Wait to finish job
	status=twi_read_status(TWSR0);
	
	if(status == TWI_CODE_ADDR_W_TRANS_ACK_REC || status==TWI_CODE_ADDR_R_TRANS_ACK_REC) return 1; //Success
	if(status == TWI_CODE_ADDR_W_TRANS_NACK_REC || TWI_CODE_ADDR_R_TRANS_NACK_REC) return 2; //Not response
	
	return 3; //Unknown error
}

uint8_t TWI_HAL_write_byte(uint8_t data){
	uint8_t status;
	
	TWDR0=data;	//Set data
	TWCR0=twi_start_transmission;
	
	while (!get_bit(TWCR0, TWINT)); 
	status=twi_read_status(TWSR0);
	
	if(status==TWI_CODE_DATA_TRANS_ACK_REC) return 1; //Success
	if(status==TWI_CODE_DATA_TRANS_NACK_REC) return 2; //No response
	return 3;
}

uint8_t TWI_HAL_read_byte_ack(){
	TWCR0=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	while (!get_bit(TWCR0, TWINT)); 
	
	return TWDR0;
}

uint8_t TWI_HAL_read_byte_nack(){
	TWCR0=(1<<TWEN)|(1<<TWINT);
	while (!get_bit(TWCR0, TWINT));
	
	return TWDR0;
}

void TWI_HAL_stop(){
	 TWCR0=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);
	 while(TWCR0&(1<<TWSTO));
}