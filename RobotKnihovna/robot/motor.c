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

void motor_start()
{
	ZAPNI(MOTOR1_DDR, MOTOR1);
	ZAPNI(MOTOR2_DDR, MOTOR2);
	ZAPNI(MOTOR3_DDR, MOTOR3);
	ZAPNI(MOTOR4_DDR, MOTOR4);
}
void levy_vpred()
{  
	ZAPNI(MOTOR1_PORT, MOTOR1);
	VYPNI(MOTOR2_PORT, MOTOR2);	
}
void levy_vzad()
{  
	VYPNI(MOTOR1_PORT, MOTOR1);
	ZAPNI(MOTOR2_PORT, MOTOR2); 
}
void levy_stop()
{  
	VYPNI(MOTOR1_PORT, MOTOR1);
	VYPNI(MOTOR2_PORT, MOTOR2);
}
void pravy_vpred()
{
	ZAPNI(MOTOR3_PORT, MOTOR3);
	VYPNI(MOTOR4_PORT, MOTOR4);
}
void pravy_vzad()
{
	VYPNI(MOTOR3_PORT, MOTOR3);
	ZAPNI(MOTOR4_PORT, MOTOR4);
}
void pravy_stop()
{
	VYPNI(MOTOR3_PORT, MOTOR3);
	VYPNI(MOTOR4_PORT, MOTOR4);
}
void jed_dopredu()
{
	levy_vpred();
	pravy_vpred();
}
void jed_dozadu()
{
	levy_vzad();
	pravy_vzad();
}
void zastav()
{
	levy_stop();
	pravy_stop();
}
void toc_doprava()
{
	levy_vpred();
	pravy_vzad();
	
	pockej(MOTOR_CAS_MEZI_OTOCENIM);
	
	levy_stop();
	pravy_stop();
}
void toc_doleva()
{
	pravy_vpred();
	levy_vzad();
	
	pockej(MOTOR_CAS_MEZI_OTOCENIM);
	
	levy_stop();
	pravy_stop();
}
void toc_uhel(uint cilovy_uhel)
{
	cilovy_uhel = cilovy_uhel % 360;
	
	int doprava;
	int poSmeru = 0;
	int protiSmeru = 0;
	
	uint uhel = kompas_zmerUhel(); // po��te�n� phel
	uint vzdalenost = abs(cilovy_uhel - uhel); // absolutn� vzd�lenost mezi �hly
	
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