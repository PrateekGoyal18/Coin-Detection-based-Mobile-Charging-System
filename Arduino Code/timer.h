#include <LiquidCrystal.h>

void stopwatch(int time)
{
	int a = time;
	i = a/1000;
	
	lcd.setCursor(1,0);
	lcd.print(i);
	lcd.setCursor(11,0);
	lcd.print("Sec's");
	delay(100);
}
