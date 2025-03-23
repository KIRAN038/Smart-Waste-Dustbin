#include<Servo.h>
Servo servo;

#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define trig 9  
#define echo 10
long distance,duration; 

const int IRSensor = 2;
int ir_sense;

const int buzzer = 6;

void setup() 
{
  Serial.begin(115200);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(IRSensor, INPUT);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer,LOW);

  servo.attach(5);delay(1000);
  servo.write(0);delay(1000);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.print("Smart Bin Ready");
  delay(1500); 
}

void loop() 
{
  dist_loop();

  ir_sense=digitalRead(IRSensor);
  ir_sense=1-ir_sense;
  Serial.print("IR : ");Serial.println(ir_sense);

  if(ir_sense==1 && distance >=5)
  {
    beep1();
    lcd.clear();
    lcd.print("  OPENING DOOR  ");

    for(int i=0;i<=90;i=i+10)
    {
      servo.write(i);
      delay(500);
    }
    delay(2000);
    lcd.clear();
    lcd.print("  CLOSING DOOR  ");
    for(int i=90;i>=0;i=i-10)
    {
      servo.write(i);
      delay(500);
    }
    lcd.clear();
  }
  lcd.clear();
  lcd.print("AVAILABLE LEVEL");
  lcd.setCursor(0,1);
  lcd.print(distance);
  delay(500);
}
void dist_loop()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  Serial.print("DIST : ");Serial.println(distance);

  if(distance <= 5)
  {
    beep();
  }
  else
  {
    digitalWrite(buzzer,LOW);
  }
}
void beep()
{
 digitalWrite(buzzer,HIGH);delay(500);digitalWrite(buzzer,LOW);delay(500); 
}
void beep1()
{
 digitalWrite(buzzer,HIGH);delay(300);digitalWrite(buzzer,LOW);delay(200); 
}
