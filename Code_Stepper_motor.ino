
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define potentiometer  A0  //10k Variable Resistor
#define bt_CW A1 // Clockwise Button
#define bt_S A2 // Stop Button
#define bt_ACW A3 // Anticlockwise Button
#define bt_C A4 //Counter button

#define in1 11 
#define in2 10  
#define in3 9 
#define in4 8  

long tongvong = 10;
long xungtrenvong = 4; // so xung/vong
float speedX = 60  ; // vong/phut
int Step=0;
int Speed;
int Mode=0;
int read_ADC;
int amount=0;
int dem=0;
int en=0;
void setup()
{
  Serial.begin(9600);
 
pinMode(potentiometer, INPUT); // 
pinMode(bt_CW, INPUT_PULLUP); 
pinMode(bt_S, INPUT_PULLUP); 
pinMode(bt_ACW, INPUT_PULLUP); 
pinMode(bt_C, INPUT_PULLUP); 
pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);    
pinMode(in4, OUTPUT); 

 lcd.begin(20,4);  
 lcd.setCursor(0,0);
 lcd.print("  Sp cua Nhom 17  ");
   // Turn off the display:
  lcd.noDisplay();
  delay(500);
  // Turn on the display:
  lcd.display();
  delay(500);
 lcd.setCursor(0,1);
 lcd.print("___Stepper.Motor__");
 delay(1000);
 lcd.clear();
}

void loop() {
  read_ADC=analogRead(potentiometer);
  speedX = map(read_ADC, 0, 1023, 20, 100); //vong/phut
  Speed = map(read_ADC, 0, 1023, 100, 0);
 
//lcd.clear();

if (digitalRead (bt_C) == 0) {
    amount = amount + 5;
    lcd.setCursor(12, 3);
    lcd.print(amount);
  }
    delay(500);
if(digitalRead (bt_CW) == 0){Mode = 1;} //For Clockwise
if(digitalRead (bt_S) == 0){
  if(en==0){en=1; }
  else{en=0;amount=0;}
 
  } //For Stop
if(digitalRead (bt_ACW) == 0){Mode = 2;} //For Anticlockwise

 

//Set Lcd
lcd.setCursor(0,0);
lcd.print("RPM:");
if(Mode==0){lcd.setCursor(10, 0);
lcd.print("0.00");}
else{lcd.setCursor(10, 0);
  lcd.print(speedX);}

lcd.setCursor(0,1);{

if(Mode==1){ lcd.print("    Clockwise   ");}
if(Mode==2){ lcd.print("  Anticlockwise ");}
}
lcd.setCursor(0,2);{
  if(en==1){ lcd.print("      ON      ");}
if(en==0){ lcd.print("      OFF      ");}
}
  lcd.setCursor(0, 3);
  lcd.print("Count:"); lcd.setCursor(12, 3);
  lcd.print(amount);

  
 if((en==1)&&(amount>0)){
  moveX(amount, speedX);
 // delay(2000);
  }

}

void moveX(int tongvong, float speed_) {

  long stepsCount = 0;
float period =   1000 / (speed_ / 60 ); //don vi mili giay
  long tongxung = tongvong * xungtrenvong;
int dem=0;
delay(1000);
while (stepsCount < tongxung) {
 
stepsCount++;
dem++;
lcd.setCursor(8, 3);
lcd.print(dem/4);

if(digitalRead (bt_S) ==0) {en=0; amount=0; break;} // For Stop

if(Mode==1){  
Step = Step+1;
if(Step>3){Step=0;}    
call_Step(Step);// Quay cung chieu
}
if(Mode==2){
Step = Step-1;
if(Step<0){Step=3;}  
call_Step(Step);// Quay nguoc chieu
}
  delay(0.25 * period);
  
 //  delay(2000);
}
delay(1000);
lcd.clear();

}


//Step C0 C1 C2 C3
//  1  1  0  1  0
//  2  0  1  1  0
//  3  0  1  0  1
//  4  1  0  0  1


void call_Step(int i){  //ham tao xung
    switch (i) {
      case 0:  // 1010
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      break;
      case 1:  // 0110
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      break;
      case 2:  //0101
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      break;
      case 3:  //1001
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      break;
    }
    
  }
