#include <DAVE.h>

int distance = 0;

int cooldown = 0;

void EchoReceivedFromSensor(){
	if(PIN_INTERRUPT_GetPinValue(&PIN_INTERRUPT_ECHO_MEASURE)){
		TIMER_Clear(&TIMER_DISTANCE);
		TIMER_Start(&TIMER_DISTANCE);
	}else{
		distance = TIMER_GetTime(&TIMER_DISTANCE);
		TIMER_Stop(&TIMER_DISTANCE);
	}
}


int main(void){
	DAVE_STATUS_t status;

	status = DAVE_Init();

	if(status != DAVE_STATUS_SUCCESS){
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while(1U){

		}
	}

	while(1U){
		if(distance < 100000){
			cooldown = 3000000;
		}
		if(cooldown > 0){
			DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_LED_OUTPUT);
		}else{
			DIGITAL_IO_SetOutputLow(&DIGITAL_IO_LED_OUTPUT);
		}
		--cooldown;
	}
}
