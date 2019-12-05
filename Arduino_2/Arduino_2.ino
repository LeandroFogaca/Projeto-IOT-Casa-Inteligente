//#include <LiquidCrystal.h>

#include <Servo.h>

//Pinos dos Leds
#define pinled1 A0
#define pinled2 A1
#define pinled3 A2
#define pinled4 A3
#define pinled5 A4
#define pinled6 A5 //Led Vermelho

#define Buzzer 9

/*pinos do //lcd16x2
  #define RS 13
  #define E 12
  #define db4 8
  #define db5 7
  #define db6 4
  #define db7 2
*/
//LiquidCrystal //lcd(RS, E, db4, db5, db6, db7); //Configuração do //lcd

int Rx, RxF = 0; //auxiliar e Flag do RX
char RxBuff[8]; // Menssagem que será recebida


Servo servoTdo;
Servo servoJnl;
Servo servoPt1;
Servo servoPt2;

bool Led1;
bool Led2;
bool Led3;
bool Led4;
bool Led5;
bool Led6;
bool Chv1;
bool Chv2;
bool Chv3;
bool Tag1;
bool Tag2;
bool telhado, TelhadoAuto;
bool AlarmeAcionado, AlarmeDisp;
bool Portao;
bool Janela, JanelaAuto;
bool Ldr1; //Função automática
bool LareiraAuto;

int Ldr2; //valor do LDR
int Sli1;
int TelhadoPosition;
int posJanela;

float umidade;    //usar comando dht.readHumidity();
float temperatura; // usar comando dht.readTemperature();

String myString;
int cmd;

int tempo = 100; // Tempo que pisca o Led Vermelho
void blink(int var, int time);

void setup()
{

  Serial.begin(9600);
  pinMode(pinled1 , OUTPUT);
  pinMode(pinled2 , OUTPUT);
  pinMode(pinled3 , OUTPUT);
  pinMode(pinled4 , OUTPUT);
  pinMode(pinled5 , OUTPUT);
  pinMode(pinled6 , OUTPUT);

  pinMode(Buzzer, OUTPUT);

  servoTdo.attach(5);  //anexa portão do telhado na porta 5
  servoJnl.attach(10);  //anexa portão da Janela na porta 9
  servoPt1.attach(6); //anexa portão do Portão1 na porta 10
  servoPt2.attach(11); //anexa portão do Portão2 na porta 11

  AlarmeAcionado = LOW;

  servoJnl.write(45);
  posJanela = 45;
  servoTdo.write(180);
  TelhadoPosition = 180;
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



  //...........GRAVA A MENSSAGEM RECEBIDA NAS VARIAVEIS myString E cmd..........//
  if ((RxBuff[8] == '!') && (RxBuff[0] == '#') && (RxF == 1))
  {
    for (int i = 7; i >= 4; --i) {
      myString.concat(RxBuff[i]);
    }

    cmd = ((RxBuff[3] - 48) * 100) + ((RxBuff[2] - 48) * 10) + ((RxBuff[1] - 48) * 1);


    //.............GRAVA O VALOR RECEBIDO NA VARIAVEL CORRETA................//



    if (myString == "Chv1") {
      Chv1  = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Chv2") {
      Chv2  = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Chv3") {
      Chv3  = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Tag1") {
      Tag1  = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Tag2") {
      Tag2  = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Umid") {
      cmd  = (cmd / 10);
      umidade = cmd;
    }
    if (myString == "Temp") {
      cmd  = (cmd / 10);
      temperatura = cmd;
    }
    if (myString == "Tag1") {
      Tag1  = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Tag2") {
      Tag2  = cmd ;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Led1") {
      Led1  = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Led2") {
      Led2  = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Led3") {
      Led3  = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Led4") {
      Led4  = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Led5") {
      Led5  = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Port") {
      Portao = cmd;
      //Serial.print(myString);
      //Serial.print(" = ");
      //Serial.println(cmd);
    }
    if (myString == "Sli1") {
      Sli1 = (cmd - 100);

      TelhadoPosition = map(Sli1, 0, 100, 90, 180); // Definir aqui o limite de movimento

      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Jan2") {
      Janela = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Jan1") {
      JanelaAuto = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Telh") {
      TelhadoAuto = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Ldr1") {
      Ldr1 = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    if (myString == "Ldr2") {
      cmd = cmd - 100;
      Ldr2 = cmd;
    }
    if (myString == "Lar1") {
      LareiraAuto = cmd;
      Serial.print(myString);
      Serial.print(" = ");
      Serial.println(cmd);
    }
    //if (myString == "") {    = cmd; }


    myString = "";
    cmd = 0;


    Serial.print("Umidade");
    Serial.print(" = ");
    Serial.print(umidade);
    Serial.print(" --- ");
    Serial.print("Temperatura");
    Serial.print(" = ");
    Serial.print(temperatura);
    Serial.print(" --- ");
    Serial.print("LDR");
    Serial.print(" = ");
    Serial.println(Ldr2);


    RxF = 0;
  }





  //..................SISTEMA DE ALARME..............................//
  //.................................................................//


  if ( (AlarmeAcionado == LOW) && (Tag1 == LOW) && (Tag2 == LOW)) {

    delay(2000);
    tone(Buzzer, 1200);
    delay(200);
    noTone(Buzzer);
    delay(50);

    tone(Buzzer, 1200);
    delay(200);
    noTone(Buzzer);
    delay(50);

  }
  if ( (Tag1 == LOW) && (Tag2 == LOW)) {

    AlarmeAcionado = HIGH;
  }
  if ( (AlarmeAcionado == HIGH) && ((Tag1 == HIGH) || (Tag2 == HIGH))) {
    tone(Buzzer, 1200);
    delay(400);
    noTone(Buzzer);
  }
  if ( (Tag1 == HIGH) || (Tag2 == HIGH)) {    // Tag = HIGH morador está na casa

    AlarmeAcionado = LOW;
  }
  if (((Chv1 == HIGH) || (Chv2 == HIGH) || (Chv3 == HIGH)) && (AlarmeAcionado == HIGH))
  {
    AlarmeDisp = HIGH;
  }

  if (AlarmeAcionado == LOW) {

    AlarmeDisp = LOW;
  }

  if ( AlarmeDisp == HIGH ) {

    tone(Buzzer, 1500, 500);
    blink(pinled6, tempo);
  }

  if (AlarmeDisp == LOW) {

    noTone(Buzzer);
    digitalWrite(pinled6, LOW);

  }



  //.........ACIONAMENTO DAS LUZES by APLICATIVO...................//

  digitalWrite(pinled1, Led1);
  digitalWrite(pinled2, Led2);
  digitalWrite(pinled3, Led3);
  //digitalWrite(pinled6, Led6);




  //.............ABRE E FECHA OS PORTOES by APLICATIVO.........//

  if (Portao == HIGH) {
    servoPt1.write(0);
    servoPt2.write(180);
  }

  if (Portao == LOW) {
    servoPt1.write(90);
    servoPt2.write(90);
  }


  //..............ACIONAMENTO DO TELHADO...............//


  if ( TelhadoAuto == LOW) {
    servoTdo.write(TelhadoPosition);
  }
  if ( TelhadoAuto == HIGH) {
    if ( (umidade > 70) && (TelhadoPosition > 0) ) {
      for ( TelhadoPosition; TelhadoPosition >= 90; TelhadoPosition-- ) {
        servoTdo.write(TelhadoPosition);
        delay(20);
      }
    }
    if ( umidade < 60 ) {
      for ( TelhadoPosition; TelhadoPosition <= 180; TelhadoPosition++ ) {
        servoTdo.write(TelhadoPosition);
        delay(20);
      }
    }
  }


  
  //..............ACIONAMENTO DA LAREIRA..............//


  if ( LareiraAuto == HIGH) {

    //Código de acionamento da lareira de acordo com a temperatura

    if (temperatura <= 33) {
      digitalWrite(pinled4, HIGH);
    }

    if (temperatura > 33) {
      digitalWrite(pinled4, LOW);
    }

  }
  if ( LareiraAuto == LOW) {
    digitalWrite(pinled4, Led4);
  }



  //................ACIONAMENTO AUTOMÁTICO LUZES EXTERNAS..............//


  if (( Ldr1 == HIGH ) && ( Ldr2 < 50)) {

    digitalWrite(pinled5, HIGH);
  }
  if (( Ldr1 == HIGH ) && ( Ldr2 > 50)) {
    digitalWrite(pinled5, LOW);

  }
  if ( Ldr1 == LOW ) {

    digitalWrite(pinled5, Led5);
  }

  //...........JANELA...........//

  if (JanelaAuto == HIGH){
     if (umidade > 70){
      servoJnl.write(45);
    }
    if ( umidade < 60){
      servoJnl.write(0);
    }
  }
  if ( JanelaAuto == LOW) {
    if (Janela == LOW) {
      servoJnl.write(45);
    }
    if (Janela == HIGH) {
      servoJnl.write(0);
    }
  }
}// Fim do Loop


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
