#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Servo.h>


//Pinos dos Leds
#define pinled1 A0
#define pinled2 A1
#define pinled3 A2
#define pinled4 A3
#define pinled5 A4
#define pinled6 A5 //Led Vermelho

#define Buzzer 9

//pinos do LCD16x2
#define RS 13
#define E 12
#define db4 8
#define db5 7
#define db6 4
#define db7 2

LiquidCrystal lcd(RS, E, db4, db5, db6, db7); //Configuração do LCD

int Rx, RxF = 0; //auxiliar e Flag do RX
char RxBuff[8]; // Menssagem que será recebida


Servo servoTdo;
Servo servoJnl;
Servo servoPt1;
Servo servoPt2;

bool Chv1;
bool Chv2;
bool Chv3;
bool Tag1;
bool Tag2;
bool AlarmeAcionado;
bool AcionamentoPortao;

float umidade;    //usar comando dht.readHumidity();
float temperatura; // usar comando dht.readTemperature();

String myString;
int cmd;

int tempo = 200;
void blink(int var, int time);

void setup()
{

  lcd.begin(16, 2);
  Serial.begin(9600);
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


  if (Serial.available() > 0)
  {
    Rx = Serial.read();
    RxBuff[8] = RxBuff[7];
    RxBuff[7] = RxBuff[6];
    RxBuff[6] = RxBuff[5];
    RxBuff[5] = RxBuff[4];
    RxBuff[4] = RxBuff[3];
    RxBuff[3] = RxBuff[2];
    RxBuff[2] = RxBuff[1];
    RxBuff[1] = RxBuff[0];
    RxBuff[0] = Rx;

    //Serial.println("recebeu dados");
    //Serial.println(char(Rx));
    RxF = 1; //Flag para sinalizar que a informação é nova
  }


  if ((RxBuff[8] == '!') && (RxBuff[0] == '#') && (RxF == 1))
  {
    for (int i = 7; i >= 4; --i) {
      myString.concat(RxBuff[i]);
    }

    cmd = ((RxBuff[3] - 48) * 100) + ((RxBuff[2] - 48) * 10) + ((RxBuff[1] - 48) * 1);



    if (myString == "Chv1") {
      Chv1  = cmd;
    }
    if (myString == "Chv2") {
      Chv2  = cmd;
    }
    if (myString == "Chv3") {
      Chv3  = cmd;
    }
    if (myString == "Tag1") {
      Tag1  = cmd;
    }
    if (myString == "Tag2") {
      Tag2  = cmd;
    }
    if (myString == "Umid") {
      umidade  = (cmd / 10);
    }
    if (myString == "Temp") {
      temperatura  = (cmd / 10);
    }

    if (myString == "Tag1") {  Tag1  = cmd; }
    if (myString == "Tag2") {  Tag2  = cmd ;}
    //if (myString == "") {    = cmd; }
    //if (myString == "") {    = cmd; }
    //if (myString == "") {    = cmd; }
    //if (myString == "") {    = cmd; }


    Serial.print(myString);
    Serial.print(" = ");
    Serial.println(cmd);


    myString = "";
    cmd = 0;

    RxF = 0;
  }


  if ( (Tag1 == HIGH) || (Tag2 == HIGH)) {
    AlarmeAcionado = LOW;
  }else{
    AlarmeAcionado = HIGH;
  }
  


  if (((Chv1 == HIGH) || (Chv2 == HIGH) || (Chv3 == HIGH)) && (Tag1 == LOW)
      && (Tag2 == LOW) && (AlarmeAcionado == HIGH))
  {
    tone(Buzzer, 1500, 500);
  

    blink(pinled6, tempo);
  }
  
  if(AlarmeAcionado == LOW) {
    noTone(Buzzer);
      Serial.println("Teste");

  }


  /*

    if (AcinamentoPortao == HIGH)
    {
     servopt1(90);
     servopt2(90);
    }
    if (AcionemntoPortao == LOW)
    {
     servopt1(0);
     servopt2(180);
    }





  */












}


void blink(int var, int time) {

  if (millis() - tempo < time) {
    digitalWrite(var, LOW);
  }
  if ((millis() - tempo > time) && (millis() - tempo < (2 * time))) {
    digitalWrite(var, HIGH);
  }
  if (millis() - tempo > (2 * time)) {
    digitalWrite(var, LOW);
    tempo = millis();
  }
}
