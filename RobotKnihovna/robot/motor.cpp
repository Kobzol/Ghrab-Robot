/*
 * motor.cpp
 *
 */

#include "motor.h"

///-------------------------------------------------------------------------------------------------
/// <summary>	Nastav� v�stupn� piny pro oba motory. </summary>
///
/// <remarks>	Jakub, 13.1.14. </remarks>
///-------------------------------------------------------------------------------------------------

void robot::motor_init()
{
	ON(MOTOR1_DDR, MOTOR1);
	ON(MOTOR2_DDR, MOTOR2);
	ON(MOTOR3_DDR, MOTOR3);
	ON(MOTOR4_DDR, MOTOR4);
}
void robot::levy_vpred()
{  
	ON(MOTOR1_PORT, MOTOR1);
	OFF(MOTOR2_PORT, MOTOR2);	
}
void robot::levy_vzad()
{  
	OFF(MOTOR1_PORT, MOTOR1);
	ON(MOTOR2_PORT, MOTOR2); 
}
void robot::levy_stop()
{  
	OFF(MOTOR1_PORT, MOTOR1);
	OFF(MOTOR2_PORT, MOTOR2);
}
void robot::pravy_vpred()
{
	ON(MOTOR3_PORT, MOTOR3);
	OFF(MOTOR4_PORT, MOTOR4);
}
void robot::pravy_vzad()
{
	OFF(MOTOR3_PORT, MOTOR3);
	ON(MOTOR4_PORT, MOTOR4);
}
void robot::pravy_stop()
{
	OFF(MOTOR3_PORT, MOTOR3);
	OFF(MOTOR4_PORT, MOTOR4);
}
void robot::jed_dopredu()
{
	levy_vpred();
	pravy_vpred();
}
void robot::jed_dozadu()
{
	levy_vzad();
	pravy_vzad();
}
void robot::zastav()
{
	levy_stop();
	pravy_stop();
}
void robot::toc_doprava()
{
	levy_vpred();
	pravy_vzad();
	
	delay(500);
	
	levy_stop();
	pravy_stop();
}
void robot::toc_doleva()
{
	pravy_vpred();
	levy_vzad();
	
	delay(500);
	
	levy_stop();
	pravy_stop();
}
void robot::toc_uhel(unsigned int cilovy_uhel)
{
	cilovy_uhel = cilovy_uhel % 360;
	
	bool doprava;
	int poSmeru = 0;
	int protiSmeru = 0;
	
	unsigned int uhel = kompas_zmerUhel(); // po��te�n� phel
	unsigned int vzdalenost = abs(cilovy_uhel - uhel); // absolutn� vzd�lenost mezi �hly
	
	/*// poSmeru - 0 ? 360, to�en� doprava
	if (cilovy_uhel > uhel)
	{
		poSmeru = cilovy_uhel - uhel;	// to�en� doprava, 20 ? 250
		protiSmeru = (360 + uhel) - cilovy_uhel;	// to�en� doleva, 250 ? 20 
	}
	else
	{
		poSmeru = (360 - uhel) + cilovy_uhel;	// to�en� doprava, 250 ? 20
		protiSmeru = uhel - cilovy_uhel;	// to�en� doleva, 20 ? 250
	}*/
	
	if (cilovy_uhel > uhel)
	{
		poSmeru = vzdalenost;
		protiSmeru = 360 - vzdalenost;
	}
	else if (cilovy_uhel < uhel)
	{
		poSmeru = 360 - vzdalenost;
		protiSmeru = vzdalenost;
	}
	else return;
	
	doprava = poSmeru < protiSmeru; // to��me doprava, pokud je to po sm�ru krat��
	
	while (abs(cilovy_uhel - uhel) > 10) // dokud nejsme srovnan�, tak to��me
	{
		/*if (doprava)
		{
			//toc_doprava();
			levy_vpred();
			pravy_vzad();
		}
		else 
		{
			pravy_vpred();
			levy_vzad();
			//toc_doprava();
		}*/
		
		pravy_vpred();
		levy_vzad();
		
		uhel = kompas_zmerUhel(); // zm��en� nov�ho �hlu, dalo by se nahradit odhadem zm�n�n� pozice
	}
	
	zastav();
}