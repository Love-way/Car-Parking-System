#include <LiquidCrystal.h>// initialize the library with the numbers of the interface pins
#include <LiquidCrystal_I2C.h>
//LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
#include <Servo.h> //includes the servo library
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // set lcd pins

Servo myservo1;

int ir_s1 = 2;
int ir_s2 = 4;

int Total = 5;
int Space;

int flag1 = 0;
int flag2 = 0;



void setup() {
  Serial.begin(9600);
pinMode(ir_s1, INPUT);
pinMode(ir_s2, INPUT);
  
myservo1.attach(5);
myservo1.write(100);

lcd.begin();
    lcd.backlight();
      
lcd.setCursor (0,0);
lcd.print("  Car  Parking  ");
lcd.setCursor (0,1);
lcd.print("     System     ");
delay (2000);
lcd.clear();  

Space = Total;
}

void loop(){ 

if(digitalRead (ir_s1) == LOW && flag1==0){
if(Space>0){flag1=1;
if(flag2==0){myservo1.write(0); Space = Space-1;}
}else{

  Serial.println("    SORRY :(    ");
Serial.println("  Parking Full  "); 
delay (3000);

//LCD

lcd.setCursor (0,0);
lcd.print(" Sorry not Space ");  
lcd.setCursor (0,1);
lcd.print("    Available    "); 
delay (1000);
lcd.clear(); 
}
}

if(digitalRead (ir_s2) == LOW && flag2==0){flag2=1;
if(flag1==0){myservo1.write(0); Space = Space+1;}
}

if(flag1==1 && flag2==1){
delay (500);
myservo1.write(100);
flag1=0, flag2=0;
}

Serial.println("    WELCOME!    ");
Serial.println("Slot Left: ");
delay (3000);
Serial.print(Space);

//LCD
lcd.setCursor (0,0);
lcd.print("Total Space: ");
lcd.print(Total);

lcd.setCursor (0,1);
lcd.print("Have  Space: ");
lcd.print(Space);
}
