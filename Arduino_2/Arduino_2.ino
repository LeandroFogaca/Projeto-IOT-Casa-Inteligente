//Bibliotecas

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Servo.h>


/*

#Define para definir todos os pinos utilizados

*/

//Pinos dos Leds
#define pinled1 A0
#define pinled2 A1
#define pinled3 A2
#define pinled4 A3
#define pinled5 A4
#define pinled6 A5

#define Buzzer 6

//pinos do LCD16x2
#define RS 13
#define E 12
#define db4 8
#define db5 7
#define db6 4
#define db7 2

LiquidCrystal lcd(RS, E, db4, db5, db6, db7); //Configuração do LCD


//SoftwareSerial Arduino02(0,1);


Servo servoTdo;
Servo servoJnl;
Servo servoPt1;
Servo servoPt2;




void setup()
{
  
  lcd.begin(16, 2);
  Serial.begin(9600);
  //Arduino02.begin(9600);
  pinMode(pinled1 , OUTPUT);
  pinMode(pinled2 , OUTPUT);
  pinMode(pinled3 , OUTPUT);
  pinMode(pinled4 , OUTPUT);
  pinMode(pinled5 , OUTPUT);
  pinMode(pinled6 , OUTPUT);
  
  pinMode(Buzzer, OUTPUT);
 
  
  servoTdo.attach(5);  //anexa portão do telhado na porta 5
  servoJnl.attach(9);  //anexa portão da Janela na porta 9
  servoPt1.attach(10); //anexa portão do Portão1 na porta 10
  servoPt2.attach(11); //anexa portão do Portão2 na porta 11
  
  
  
  lcd.clear();
  delay(200);
  lcd.setCursor(3, 0);
  lcd.print("Iniciando");
  delay(200);
}

void loop()
{
 


  
  
  
  
  
  
  
}

