/*
 * Robot++.cpp
 *
 */ 

#include <avr/io.h>
#include "headers/funkce.h"
#include "headers/motor.h"
#include "headers/sonar.h"
#include "headers/kompas.h"
#include "headers/bluetooth.h"

class Motor {
	public:
	volatile uint8_t dopredu, dozadu, port;
	Motor(volatile uint8_t x, volatile uint8_t y, volatile uint8_t port)
	{
		 this->dopredu = x;
		 this->dozadu = y;
		 this->port = port;
	}
	void dopredu_jed()
	{
		ON(this->port, this->dopredu);
	}
};

int main(void)
{
	motor_init();
	sonar_init();
	//serial_init(9600);
	
	int* vzdalenosti = NULL;
	unsigned int uhel = 0;
	
	while (true)
	{
		vzdalenosti = sonary_zmer();
		
		if (vzdalenosti[1] < 300 || vzdalenosti[2] < 300)
		{
			levy_vpred();
			pravy_vzad();
		}
		else
		{
			levy_stop();
			pravy_stop();
		}
		
		free(vzdalenosti);
		
		/*uhel = zmerUhel();
		
		if (uhel > 0 && uhel < 180)
		{
			levy_vpred();
		}
		else levy_stop();*/
	}
}