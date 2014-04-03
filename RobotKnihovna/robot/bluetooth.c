/*
 * bluetooth.c
 *
 */ 

#include "bluetooth.h"

void bt_start(uint baud)
{
	// nastavení sériové linky
	uint16_t ubrr_value = ((RYCHLOST_PROCESORU) / (16UL * baud)) - 1;	
	
	// nastavení BAUDU
	UBRRL = ubrr_value;
	UBRRH = (ubrr_value >> 8);
	
	// asynchronous mode, 8 bitů, no parity, 1 stop bit 
	UCSRC = (1<<URSEL) | (3<<UCSZ0);
	UCSRB = (1<<RXEN) | (1<<TXEN);
	
	bt_vynulujBuffer();
	
	// povolení interruptu
	UCSRB |= (1 << RXCIE);
	
	sei();	
}

znak bt_prijmiZnak()
{
	if (UCSRA & (1<<RXC))
	{
		return UDR;						// vrátit přijatý znak
	}	
	else return BT_ZADNY_ZNAK;				// nepřijat žádný znak
}

void bt_posliZnak(znak znakZpravy)
{
	while( !(ZKONTROLUJ(UCSRA, UDRE)) );	// počkat, než bude buffer připraven
	UDR = znakZpravy;						// odeslání znaku
}

void bt_posliRetezec(const char * retezec)
{
	bt_posliNeukoncenyRetezec(retezec);
	bt_posliZnak(BT_TERMINACNI_ZNAK);
}

void bt_posliNeukoncenyRetezec(const char * retezec)
{
	while (*retezec != '\0')
	{
		bt_posliZnak(*retezec);
		
		retezec++;
	}
}

void bt_posliOdpoved(const char * kategorie, const char * hodnota)
{
	bt_posliNeukoncenyRetezec(kategorie);
	bt_posliNeukoncenyRetezec(BT_ROZDELOVACI_ZNAK_ODPOVEDI);
	bt_posliNeukoncenyRetezec(hodnota);
	bt_posliZnak(BT_TERMINACNI_ZNAK);
}

void bt_posliVzdalenost(const char * kategorie, Vzdalenost vzdalenost)
{
	char vzdalenosti[40] = { 0 };
	char vzdalenost_buffer[10] = { 0 };
	
	prevedNaRetezec(vzdalenost_buffer, vzdalenost.Vlevo);
	strcat(vzdalenosti, vzdalenost_buffer);
	strcat(vzdalenosti, BT_ROZDELOVACI_ZNAK_HODNOT);
	
	prevedNaRetezec(vzdalenost_buffer, vzdalenost.Vepredu);
	strcat(vzdalenosti, vzdalenost_buffer);
	strcat(vzdalenosti, BT_ROZDELOVACI_ZNAK_HODNOT);
	
	prevedNaRetezec(vzdalenost_buffer, vzdalenost.Vpravo);
	strcat(vzdalenosti, vzdalenost_buffer);
	
	bt_posliOdpoved(kategorie, vzdalenosti);
}

void bt_posliStavMotoru()
{
	char *levyMotor1;
	char *levyMotor2;
	
	char *pravyMotor1;
	char *pravyMotor2;
	
	if (ZKONTROLUJ(MOTOR_LEVY_1_PORT, MOTOR_LEVY_1))
	{
		levyMotor1 = "1";
	}
	else levyMotor1 = "0";
	
	if (ZKONTROLUJ(MOTOR_LEVY_2_PORT, MOTOR_LEVY_2))
	{
		levyMotor2 = "1";
	}
	else levyMotor2 = "0";
	
	if (ZKONTROLUJ(MOTOR_PRAVY_1_PORT, MOTOR_PRAVY_1))
	{
		pravyMotor1 = "1";
	}
	else pravyMotor1 = "0";
	
	if (ZKONTROLUJ(MOTOR_PRAVY_2_PORT, MOTOR_PRAVY_2))
	{
		pravyMotor2 = "1";
	}
	else pravyMotor2 = "0";
	
	char motory[10] = { 0 };
	
	strcat(motory, levyMotor1);
	strcat(motory, levyMotor2);
	strcat(motory, BT_ROZDELOVACI_ZNAK_HODNOT);
	strcat(motory, pravyMotor1);
	strcat(motory, pravyMotor2);
	
	bt_posliOdpoved(ODPOVED_MOTOR_STAV, motory);
}

void bt_vynulujBuffer()
{
	memset((void *) bt_vstup, 0, sizeof(*bt_vstup) * BT_VELIKOST_BUFFERU);
}

void bt_provedPrikaz()
{
	char * prikaz = strtok((char *) bt_vstup, BT_ROZDELOVACI_ZNAK_ODPOVEDI);
	char * hodnota = strtok(NULL, BT_ROZDELOVACI_ZNAK_ODPOVEDI);
	
	if (strcmp((const char *) prikaz, "ahoj") == 0)
	{
		bt_posliOdpoved(ODPOVED_KOMPAS_UHEL, "50");
	}
	else if (strcmp((const char *) prikaz, "kompasZmer") == 0)
	{
		ulong uhel = kompas_zmerUhel();
		char buffer[20];
		
		prevedNaRetezec(buffer, uhel);
		
		bt_posliOdpoved(ODPOVED_KOMPAS_UHEL, buffer);
	}
	else if (strcmp((const char *) prikaz, "sonaryZmer") == 0)
	{
		Vzdalenost vzdalenost = sonar_zmerVzdalenosti();
		bt_posliVzdalenost(ODPOVED_SONARY_VZDALENOSTI, vzdalenost);
	}
	else if (strcmp((const char *) prikaz, "motoryStav") == 0)
	{
		bt_posliStavMotoru();
	}
	else if (strcmp((const char *) prikaz, "motorLevyDopredu") == 0)
	{
		motor_levy_vpred();
	}
	else if (strcmp((const char *) prikaz, "motorLevyDozadu") == 0)
	{
		motor_levy_vzad();
	}
	else if (strcmp((const char *) prikaz, "motorPravyDopredu") == 0)
	{
		motor_pravy_vpred();
	}
	else if (strcmp((const char *) prikaz, "motorPravyDozadu") == 0)
	{
		motor_pravy_vzad();
	}
	else if (strcmp((const char *) prikaz, "motoryStop") == 0)
	{
		motor_zastav();
	}
}

ISR (USART_RXC_vect)
{
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		znak prijatyZnak;
		prijatyZnak = UDR; // uložení přijmutého znaku

		if (prijatyZnak == BT_TERMINACNI_ZNAK)
		{
			bt_provedPrikaz();
			bt_vynulujBuffer();
		}
		else
		{
			uint pocetZnaku = strlen((const char *) bt_vstup);
			
			if (pocetZnaku < BT_VELIKOST_BUFFERU)
			{
				bt_vstup[pocetZnaku] = prijatyZnak;
			}
			else bt_vynulujBuffer();
		}
	}
}