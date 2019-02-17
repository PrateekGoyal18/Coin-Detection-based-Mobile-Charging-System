#include <LiquidCrystal.h>
#include <Countimer.h>

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
Countimer timer;

uint32_t period;
uint32_t i;
uint16_t h;
uint8_t m, s;

uint32_t timing(int);
void stopwatch(int);
void refreshClock();
void onComplete();

int coin_value;
int buzzer = A1;
int relay = 3;
int led1 = 10;  // LED1 for coin insertion
int led2 = 11;  // LED2 for coin inserted and value of coin detected
int led3 = 12;  // LED3 when charging starts
int led4 = 13;  // LED4 when charging completes 

void setup()
{
  Serial.begin(9600);
  pinMode(led1,OUTPUT);  
  pinMode(led2,OUTPUT);  
  pinMode(led3,OUTPUT);  
  pinMode(led4,OUTPUT);    
  pinMode(buzzer,OUTPUT); // Buzzer, for when charging completes
  pinMode(relay, OUTPUT); // Relay, for controlling the mobile charger
  
  lcd.begin(16,2);
  
  timer.setCounter(h, m, s, timer.COUNT_DOWN, onComplete);
  timer.setInterval(refreshClock, 1000);
          
  // Introduction
  for(int i=400; i<=410; i=i+1)
  {
    lcd.setCursor(0,0);
    lcd.print("Coin Detection Based");
    lcd.scrollDisplayRight();
    lcd.setCursor(0,1);
    lcd.print("Mobile Charging System");
    lcd.scrollDisplayRight();
    delay(i+5);

    lcd.setCursor(0,0);
    lcd.print("Coin Detection Based");
    lcd.scrollDisplayRight();
    lcd.setCursor(0,1);
    lcd.print("Mobile Charging System");
    lcd.scrollDisplayRight();
    delay(i+5);
  } 
  digitalWrite(relay, HIGH);
}

void loop()
{ 
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Insert a coin");
  delay(5000);
  digitalWrite(led1, HIGH);
  delay(3000);
  digitalWrite(led1, LOW);
  delay(3000);
  lcd.clear();
  
 
  char buffer[] = {' ',' ',' ',' ',' ',' ',' '}; // Receive up to 7 bytes
  while (!Serial.available()); // Wait for characters
  Serial.readBytesUntil('n', buffer, 7);
  int coin_value = atoi(buffer);
  Serial.println(coin_value);
  
  period = timing(coin_value);
  Serial.print(period);  
  
  digitalWrite(led2, HIGH);
  delay(3000);
  digitalWrite(led2, LOW);
  delay(3000);
  
  lcd.print("CHARGING STARTED");
  delay(2000);
  lcd.clear();
    
  switch (coin_value)
    {
      case 1:
        h=0; m=0; s=30;
        timer.setCounter(h, m, s, timer.COUNT_DOWN, onComplete);
        timer.setInterval(refreshClock, 1000);
        for( uint32_t tStart = millis();  (millis()-tStart) < period;  )
        {
          digitalWrite(relay, LOW);
          
          lcd.setCursor(1,0);
          lcd.print("Time Remaining:");
          lcd.setCursor(0,1);
          timer.run();
          if(!timer.isCounterCompleted())
          {
            timer.start();
          }
          
          digitalWrite(led3, HIGH);
        }
        digitalWrite(relay, HIGH);
        break;
        
      case 2:
        h=0; m=1; s=0;
        timer.setCounter(h, m, s, timer.COUNT_DOWN, onComplete);
        timer.setInterval(refreshClock, 1000);
        for( uint32_t tStart = millis();  (millis()-tStart) < period;  )
        {
          digitalWrite(relay, LOW);
          
          lcd.setCursor(0,1);
          lcd.print("Time Remaining:");
          lcd.setCursor(1,0);
          timer.run();
          if(!timer.isCounterCompleted()) 
          {
            timer.start();
          }
          
          digitalWrite(led3, HIGH);
        }
        digitalWrite(relay, HIGH);
        break;
      
      case 5:
        h=0; m=1; s=30;
        timer.setCounter(h, m, s, timer.COUNT_DOWN, onComplete);
        timer.setInterval(refreshClock, 1000);
        for( uint32_t tStart = millis();  (millis()-tStart) < period;  )
        {
          digitalWrite(relay, LOW);
          
          lcd.setCursor(0,1);
          lcd.print("Time Remaining:");
          lcd.setCursor(1,0);
          timer.run();
          if(!timer.isCounterCompleted()) 
          {
            timer.start();
          }
          
          digitalWrite(led3, HIGH);
        }
        digitalWrite(relay, HIGH);
        break;
       
      case 10:
        h=0; m=2; s=0;
        timer.setCounter(h, m, s, timer.COUNT_DOWN, onComplete);
        timer.setInterval(refreshClock, 1000);
        for( uint32_t tStart = millis();  (millis()-tStart) < period;  )
        {
          digitalWrite(relay, LOW);
          
          lcd.setCursor(0,1);
          lcd.print("Time Remaining:");
          lcd.setCursor(1,0);
          timer.run();
          if(!timer.isCounterCompleted()) 
          {
            timer.start();
          }
          
          digitalWrite(led3, HIGH);
        }
        digitalWrite(relay, HIGH);
        break;
    }
  
  digitalWrite(led4, HIGH);
  delay(3000);
  digitalWrite(led4, LOW);
  delay(3000);
}

uint32_t timing(int value)
{
  int v = value;
  switch (v)
  {
    case 1:
      i = 0.5 * 60000L; // Half minute (in ms)
      break;

    case 2:
      i = 1 * 60000L;
      break;

    case 5:
      i = 1.5 * 60000L;
      break;

    case 10:
      i = 2 * 60000L;
      break;    
  }
  delay(1);
  return i;
}

void refreshClock() 
{
  Serial.print("Current count time is: ");
  lcd.print("time: ");
  
  Serial.println(timer.getCurrentTime());
  lcd.print(timer.getCurrentTime());
}

void onComplete() 
{
  Serial.println("Complete!!!");
  lcd.print("Complete!!!");
}
