/*
Código por Lucas Paiva da Silva
Microcontroladores
Prova 1
09/04/2019
*/

#include "def_principais.h"
#include "LCD.h"

char SecretDigits[] = {'p', 'a', 'i', 'v', 'a'};
char Digits[] = {'_', '_', '_', '_', '_'};
char Letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int LetterPosition = 0;
int lifes = 5;
int x = 0;
int y = 0;
int passed = 0;
int endGame = 0;
	
void Game(int Key)
{
	if (Key == 1)
	{
		if (LetterPosition == 25)
		{
			LetterPosition = 0;
		}
		else
		{
			LetterPosition = LetterPosition + 1;
		}
	}
	if (Key == 2)
	{
		if (LetterPosition ==  0)
		{
			LetterPosition = 25;
		}
		else
		{
			LetterPosition = LetterPosition - 1;
		}
	}
	if (Key == 3)
	{
		for (x=0;x<5;x++)
		{
			if (Letters[LetterPosition] == SecretDigits[x])
			{
				Digits[x] = Letters[LetterPosition];
				SecretDigits[x] = '*';
				passed = 1;
			}
		}
		if (passed == 0)
		{
			lifes = lifes - 1;
			if (lifes == 0)
			{
				endGame = 1;
			}
		}
		else{
			passed = 0;
		}
		
	}
	
	
	
	cmd_LCD(0x80, 0);
	cmd_LCD(Digits[0], 1);
	cmd_LCD(Digits[1], 1);
	cmd_LCD(Digits[2], 1);
	cmd_LCD(Digits[3], 1);
	cmd_LCD(Digits[4], 1);
	cmd_LCD(0xC0, 0);
	cmd_LCD(Letters[LetterPosition], 1);
	cmd_LCD(0xC7, 0);
	cmd_LCD('v', 1);
	cmd_LCD('i', 1);
	cmd_LCD('d', 1);
	cmd_LCD('a', 1);
	cmd_LCD('s', 1);
	cmd_LCD(':', 1);
	cmd_LCD((lifes + '0'), 1);

}


int main()
{
	DDRD = 0xFF; //PORTD como saída
	DDRB = 0xFF; //PORTB como saída
	//BOTÕES NO PC0, PC1 e PC2
	DDRC = 0x00; //PORTC como entrada
	PORTC = 0xFF;//Pull up
	inic_LCD_4bits(); //inicializa o LCD
	Game(0);
	while(1)
	{	
		if (!tst_bit(PINC, PC0)){Game(1);};
		if (!tst_bit(PINC, PC1)){Game(2);};
		if (!tst_bit(PINC, PC2)){Game(3);};
		if (endGame == 1)
		{
			cmd_LCD(1, 0);
			escreve_LCD("GAME OVER");
			_delay_ms(5000);
			break;
		}
		_delay_ms(250);
		
	}
}