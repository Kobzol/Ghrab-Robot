/*
 * motor.c
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
	ZAPNI(MOTOR_LEVY_1_DDR, MOTOR_LEVY_1);
	ZAPNI(MOTOR_LEVY_2_DDR, MOTOR_LEVY_2);
	ZAPNI(MOTOR_PRAVY_1_DDR, MOTOR_PRAVY_1);
	ZAPNI(MOTOR_PRAVY_2_DDR, MOTOR_PRAVY_2);
}
void motor_levy_vpred()
{  
	ZAPNI(MOTOR_LEVY_1_PORT, MOTOR_LEVY_1);
	VYPNI(MOTOR_LEVY_2_PORT, MOTOR_LEVY_2);	
}
void motor_levy_vzad()
{  
	VYPNI(MOTOR_LEVY_1_PORT, MOTOR_LEVY_1);
	ZAPNI(MOTOR_LEVY_2_PORT, MOTOR_LEVY_2); 
}
void motor_levy_stop()
{  
	VYPNI(MOTOR_LEVY_1_PORT, MOTOR_LEVY_1);
	VYPNI(MOTOR_LEVY_2_PORT, MOTOR_LEVY_2);
}
void motor_pravy_vpred()
{
	ZAPNI(MOTOR_PRAVY_1_PORT, MOTOR_PRAVY_1);
	VYPNI(MOTOR_PRAVY_2_PORT, MOTOR_PRAVY_2);
}
void motor_pravy_vzad()
{
	VYPNI(MOTOR_PRAVY_1_PORT, MOTOR_PRAVY_1);
	ZAPNI(MOTOR_PRAVY_2_PORT, MOTOR_PRAVY_2);
}
void motor_pravy_stop()
{
	VYPNI(MOTOR_PRAVY_1_PORT, MOTOR_PRAVY_1);
	VYPNI(MOTOR_PRAVY_2_PORT, MOTOR_PRAVY_2);
}
void motor_jed_dopredu()
{
	motor_levy_vpred();
	motor_pravy_vpred();
}
void motor_jed_dozadu()
{
	motor_levy_vzad();
	motor_pravy_vzad();
}
void motor_zastav()
{
	motor_levy_stop();
	motor_pravy_stop();
}
void motor_toc_doprava()
{
	motor_levy_vpred();
	motor_pravy_vzad();
	
	pockej(MOTOR_CAS_MEZI_OTOCENIM);
	
	motor_levy_stop();
	motor_pravy_stop();
}
void motor_toc_doleva()
{
	motor_pravy_vpred();
	motor_levy_vzad();
	
	pockej(MOTOR_CAS_MEZI_OTOCENIM);
	
	motor_levy_stop();
	motor_pravy_stop();
}
void motor_toc_uhel(uint cilovy_uhel)
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
			//motor_toc_doprava();
			motor_motor_levy_vpred();
			motor_pravy_vzad();
		}
		else 
		{
			motor_pravy_vpred();
			motor_levy_vzad();
			//motor_toc_doprava();
		}*/
		
		motor_pravy_vpred();
		motor_levy_vzad();
		
		uhel = kompas_zmerUhel(); // zm��en� nov�ho �hlu, dalo by se nahradit odhadem zm�n�n� pozice
	}
	
	motor_zastav();
}