/*
 * main.c
 *
 * Created: 10/4/2021 4:27:30 PM
 *  Author: Mainframe
 */ 


#define F_CPU 8000000UL	

#include <xc.h>
#include "TEST/lora-module/test_lora_module.h"
#include "TEST/SCD_30_module/test_SCD30_module.h"

int main(void)
{
	//test_lora_module_start();
	test_SCD30_module_start();
    while(1)
    {
        //TODO:: Please write your application code 
    }
	
}