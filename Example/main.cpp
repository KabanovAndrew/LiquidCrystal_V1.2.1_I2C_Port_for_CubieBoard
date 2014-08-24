// -------------------------------------------------------------------------------------------
// Port for CubieBoard a library LiquidCrystal version 1.2.1 to drive the PCF8574* I2C
//
// @version API 1.0.0
//
// @author Kabanov Andrew - andrew3007@kabit.ru
// -------------------------------------------------------------------------------------------

#include "LCD.h"

#define I2C_NUM_BUS 1
#define I2C_DEV_ADDR 0x27

#define RS_PIN 0
#define RW_PIN 1
#define EN_PIN 2
#define BL_PIN 3
#define D4_PIN 4
#define D5_PIN 5
#define D6_PIN 6
#define D7_PIN 7

/*!
    Define Character bitmap of new characters.
*/
const uint8_t charBitmap[][8] =
{
   { 31, 30, 28, 24, 16, 16, 16, 16 },
   { 16, 16, 16,  16, 24, 28, 30, 31 },
   { 31, 15, 7, 3, 1, 1, 1, 1 },
   { 1, 1, 1, 1, 3, 7, 15, 31 },

   { 31, 0, 0, 0, 0, 0, 0, 0 },
   { 0, 0, 0, 0, 0, 0, 0, 31 },
   { 1, 1, 1, 1, 1, 1, 1, 1 },
   { 16, 16, 16, 16, 16, 16, 16, 16 }
};

int main()
{
	LCD lcd(I2C_NUM_BUS, I2C_DEV_ADDR,
			RS_PIN, RW_PIN, EN_PIN,
			D4_PIN, D5_PIN, D6_PIN, D7_PIN,
			BL_PIN, POSITIVE);

	lcd.begin(20, 4, LCD_5x8DOTS);

	lcd.display();

	/***************************************************************************************/
	/*								Write bitmap of new characters.						   */
	/***************************************************************************************/
	const int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));
	for(int i = 0; i < charBitmapSize; i++)
	{
		lcd.createChar(i, (uint8_t *)charBitmap[i]);
	}

	/***************************************************************************************/
	/*									   Print Lines.						   			   */
	/***************************************************************************************/
	lcd.setCursor(0, 0);
	lcd.write(0);

	lcd.setCursor(0, 3);
	lcd.write(1);

	lcd.setCursor(19, 0);
	lcd.write(2);

	lcd.setCursor(19, 3);
	lcd.write(3);

	for(int i = 1; i <= 18; i++)
	{
		lcd.setCursor(i, 0);
		lcd.write(4);
	}

	for(int i = 1; i <= 18; i++)
	{
		lcd.setCursor(i, 3);
		lcd.write(5);
	}

	for(int i = 1; i <= 2; i++)
	{
		lcd.setCursor(19, i);
		lcd.write(6);
	}

	for(int i = 1; i <= 2; i++)
	{
		lcd.setCursor(0, i);
		lcd.write(7);
	}

	/***************************************************************************************/
	/*											Print text.						   		   */
	/***************************************************************************************/
	lcd.setCursor(5, 1);
	lcd.print("It works!!");

	lcd.setCursor(4, 2);
	lcd.print("Hello world!");

	return 0;
}
