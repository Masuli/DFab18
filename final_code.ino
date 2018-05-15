#include <LiquidCrystal.h>

const int buzzer = 9;

const int upButtonPin = 7;   
const int downButtonPin = 8;
const int startButtonPin = 6;
const int stopButtonPin = 10;

int setAlarm = 0;
int Position = 0;
int Alarm = 0;
int Alert = 0;
int hours = 0;
int minutes = 0;
int seconds = 0;

int downPress = 0;

int posChangeHours = 0;
int posChangeMinutes = 0;
int posChangeSeconds = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  //buttons
  pinMode(upButtonPin, INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(stopButtonPin, INPUT_PULLUP);
  //buzzer
  pinMode(buzzer, OUTPUT);
  //lcd
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

void loop() {
  if(!setAlarm)
  {
    lcd.setCursor(0,0);
    lcd.print("Set Alarm:     ");
    lcd.setCursor(0, 1); //2nd row
    lcd.print("00:00:00");
    delay(1000);
    while(!setAlarm)
    {
      if(!Position)
      {
        lcd.setCursor(11,0);
        lcd.print("H");
      }
      if(Position == 1)
      {
        lcd.setCursor(11,0);
        lcd.print("M");
      }
      if(Position == 2)
      {
        lcd.setCursor(11,0);
        lcd.print("S");
      }
      int upButtonValue = digitalRead(upButtonPin);
      if (upButtonValue == LOW)
      {
        if(Position == 0)
          hours++;
        if(Position == 1)
          minutes++;
        if(Position == 2)
          seconds++;
        delay(100);
      }
      int downButtonValue = digitalRead(downButtonPin);
      if (downButtonValue == LOW)
      {
       if(Position == 0)
          hours--;
        if(Position == 1)
          minutes--;
        if(Position == 2)
          seconds--;
        downPress = 1;
        delay(100);
      }
      int startButtonValue = digitalRead(startButtonPin);
      if(startButtonValue == LOW)
      {
        Position++;
        delay(1000);
      }
      if(Position > 2)
        setAlarm = 1;
      int stopButtonValue = digitalRead(stopButtonPin);
      if(stopButtonValue == LOW)
      {
        hours = 0;
        minutes = 0;
        seconds = 0;
        Position = 0;
        lcd.setCursor(0,1);
        lcd.print("00:00:00");
        delay(1000);
      }
      if(seconds >= 60)
        {
          posChangeSeconds = 1;
          minutes++;
          seconds = 0;
          delay(100);
        }
      if(minutes >= 60)
      {
        posChangeMinutes = 1;
        hours++;
        minutes = 0;
        delay(100);
      }
      if(hours > 24)
      {
        posChangeHours = 1;
        hours = 0;       
        delay(100);
      }
      if(seconds < 0)
      {
        posChangeSeconds = 1;
        minutes--;
        seconds = 59;     
        delay(100);
      }
      if(minutes < 0)
      {
        posChangeMinutes = 1;
        hours--;
        minutes = 59;   
        delay(100);
      }
      if(hours < 0)
      {
        posChangeHours = 1;
        hours = 24;
        delay(100);
      }
      if (posChangeHours)
      {
        lcd.setCursor(0,1);
        lcd.print("00");
        posChangeHours = 0;
      }
      
      if(hours < 9 && !downPress)
      {
        lcd.setCursor(1,1);
        lcd.print(hours);
      }

      if(hours < 9 && downPress)
      {
        lcd.setCursor(0,1);
        lcd.print("00");
        lcd.setCursor(1,1);
        lcd.print(hours);
      }
      if (hours > 9)
      {
        lcd.setCursor(0,1);
        lcd.print(hours);
      }

      if (posChangeMinutes)
      {
        lcd.setCursor(3,1);
        lcd.print("00");
        posChangeMinutes = 0;
      }
      
      if(minutes < 9 && !downPress)
      {
        lcd.setCursor(4,1);
        lcd.print(minutes);
      }

      if(minutes < 9 && downPress)
      {
        lcd.setCursor(3,1);
        lcd.print("00");
        lcd.setCursor(4,1);
        lcd.print(minutes);
      }
      if (minutes > 9)
      {
        lcd.setCursor(3,1);
        lcd.print(minutes);
      }


      // 6,1 7,1
      if (posChangeSeconds)
      {
        lcd.setCursor(6,1);
        lcd.print("00");
        posChangeSeconds = 0;
      }
      
      if(seconds < 9 && !downPress)
      {
        lcd.setCursor(7,1);
        lcd.print(seconds);
      }

      if(seconds < 9 && downPress)
      {
        lcd.setCursor(6,1);
        lcd.print("00");
        lcd.setCursor(7,1);
        lcd.print(seconds);
      }
      if (seconds > 9)
      {
        lcd.setCursor(6,1);
        lcd.print(seconds);
      }
      downPress = 0;
    }
    Position = 0;
  }
    if(setAlarm)
      Alarm = 1;
      lcd.setCursor(0,0);
      lcd.print("Time remaining:");
      while(Alarm)
      {
        int stopButtonValue = digitalRead(stopButtonPin);
        if(stopButtonValue == LOW)
        {
          hours = 0;
          minutes = 0;
          seconds = 0;
          Alarm = 0;
          delay(1000);
        }
           if(seconds >= 60)
        {
          posChangeSeconds = 1;
          minutes++;
          seconds = 0;
          delay(100);
        }
      if(minutes >= 60)
      {
        posChangeMinutes = 1;
        hours++;
        minutes = 0;
        delay(100);
      }
      if(hours > 24)
      {
        posChangeHours = 1;
        hours = 0;       
        delay(100);
      }
      if(seconds < 0)
      {
        posChangeSeconds = 1;
        minutes--;
        seconds = 59;     
        delay(100);
      }
      if(minutes < 0)
      {
        posChangeMinutes = 1;
        hours--;
        minutes = 59;   
        delay(100);
      }
      if(hours < 0)
      {
        posChangeHours = 1;
        hours = 24;
        delay(100);
      }
      if (posChangeHours)
      {
        lcd.setCursor(0,1);
        lcd.print("00");
        posChangeHours = 0;
      }
      if (posChangeMinutes)
      {
        lcd.setCursor(3,1);
        lcd.print("00");
        posChangeMinutes = 0;
      }
      if (posChangeSeconds)
      {
        lcd.setCursor(6,1);
        lcd.print("00");
        posChangeSeconds = 0;
      }
      if(!hours && !minutes && !seconds && Alarm)
       {
          Alert = 1;
          Alarm = 0;
       }
        if(hours < 10)
        {
          lcd.setCursor(0,1);
          lcd.print("00");
          lcd.setCursor(1,1);
          lcd.print(hours);
        }
        if (hours > 9)
        {
          lcd.setCursor(0,1);
          lcd.print(hours);
        }
        if(minutes < 10)
        {
          lcd.setCursor(3,1);
          lcd.print("00");
          lcd.setCursor(4,1);
          lcd.print(minutes);
        }
        if (minutes > 9)
        {
          lcd.setCursor(3,1);
          lcd.print(minutes);
        }
        
        if(seconds < 10)
        {
          lcd.setCursor(6,1);
          lcd.print("00");
          lcd.setCursor(7,1);
          lcd.print(seconds);
        }
        if (seconds > 9)
        {
          lcd.setCursor(6,1);
          lcd.print(seconds);
        }
        delay(1000);
        seconds--;
      }
      if(Alert)
      {
        lcd.setCursor(0,0);
        lcd.print("Wake up!       ");
        while(Alert)
        {
          int stopButtonValue = digitalRead(stopButtonPin);
          if(stopButtonValue == LOW)
          {
            Alert = 0;
          }
          tone(buzzer, 1000);
          delay(500);
          noTone(buzzer);
          delay(500);
        }
        hours = 0;
        minutes = 0;
        seconds = 0;
      }
      hours = 0;
      minutes = 0;
      seconds = 0;
      setAlarm = 0;
}
