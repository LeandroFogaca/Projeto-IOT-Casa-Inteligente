#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>


//Pinos da comunicação com o HC-05
#define BTX 4
#define BRX 3

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define DHTTYPE DHT11
#define pinDHT 5 // pino de dados do DHT11

#define pinChave1 A5
#define pinChave2 A4
#define pinChave3 A3
#define pinLDR A2


SoftwareSerial Bluetooth(BRX, BTX); //Configura a comunicação serial com para o HC-05
DHT dht(pinDHT, DHTTYPE);  //Configura o DHT11


char Rx;
int RxF = 0; //auxiliar e Flag do RX
char RxBuff[9]; // Menssagem que será recebida

float umidade;    //usar comando dht.readHumidity();
float temperatura; // usar comando dht.readTemperature();

bool Chv1, lastChv1;
bool Chv2, lastChv2;
bool Chv3, lastChv3;
bool Tag1, lastTag1;
bool Tag2, lastTag2;


String myString;
int cmd;
int es = 0;
int tempo;
bool temporizador();


void setup()
{
  Bluetooth.begin(9600); //Inicia comunicação serial para a placa HC-05
  Serial.begin(9600);   //Inicia comunicação serial para o outro arduino
  SPI.begin();          //Não sei para oque serve
  mfrc522.PCD_Init(); //Inicia a comunicação com o sensor RFID
  dht.begin();  //inicia a comunicação com o DHT11

  tempo = 0;

}
void loop()
{


  if (Bluetooth.available() > 0)
  {
    Rx = Bluetooth.read();
    RxBuff[8] = RxBuff[7];
    RxBuff[7] = RxBuff[6];
    RxBuff[6] = RxBuff[5];
    RxBuff[5] = RxBuff[4];
    RxBuff[4] = RxBuff[3];
    RxBuff[3] = RxBuff[2];
    RxBuff[2] = RxBuff[1];
    RxBuff[1] = RxBuff[0];
    RxBuff[0] = Rx;

    RxF = 1; //Flag para sinalizar que a informação é nova
    //Serial.println(Rx);
  }


  if ((RxBuff[8] == '!') && (RxBuff[0] == '#') && (RxF == 1))
  {

    for (int i = 8; i >= 0; i--) {
      myString.concat(RxBuff[i]);
    }
    Serial.println(myString);
    myString = "";
    RxF = 0;
  }


  Chv1 = digitalRead(pinChave1);
  Chv2 = digitalRead(pinChave2);
  Chv3 = digitalRead(pinChave3);

  if (Chv1 != lastChv1)
  {
    myString = "!Chv100";
    myString.concat(Chv1);
    myString.concat("#");
    Serial.println(myString);
    lastChv1 = Chv1;
  }

  if (Chv2 != lastChv2)
  {
    myString = "!Chv200";
    myString.concat(Chv2);
    myString.concat("#");
    Serial.println(myString);
    lastChv2 = Chv2;
    myString = "";
  }

  if (Chv3 != lastChv3)
  {
    myString = "!Chv300";
    myString.concat(Chv3);
    myString.concat("#");

    Serial.println(myString);
    lastChv3 = Chv3;
    myString = "";
  }
  if (Tag1 != lastTag1)
  {
    myString = "!Tag100";
    myString.concat(Tag1);
    myString.concat("#");
    Serial.println(myString);
    lastTag1 = Tag1;
    myString = "";
  }
  if (Tag2 != lastTag2)
  {
    myString = "!Tag200";
    myString.concat(Tag2);
    myString.concat("#");
    Serial.println(myString);
    lastTag2 = Tag2;
    myString = "";
  }


  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();


  if ( temporizador(1000) == HIGH) {

    int valor = umidade * 10;

    myString = "!Umid";
    myString.concat(valor);
    myString.concat("#");
    Serial.println(myString);
    myString = "";  
    valor = temperatura * 10;

    myString = "!Temp";
    myString.concat(valor);
    myString.concat("#");
    Serial.println(myString);
    myString = "";

    

  }

  


  /*
     Inicio da programação do RFID
  */

  if ( ! mfrc522.PICC_IsNewCardPresent()) { // Busca novos cartões  
    return;
  }
    
    
  if ( ! mfrc522.PICC_ReadCardSerial()) {   // Seleciona um cartão a ser lido
    return;
  }

  String Tag = "";
  
  
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : " "));
    Tag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }



  if ((Tag == " e7 13 6c 34") && (Tag1 == 0)) {
    Tag1 = 1;
    Tag = "";
    delay (2000);
  }

  if ((Tag == " e7 13 6c 34") && (Tag1 == 1)) {
    Tag1 = 0;
    Tag = "";
    delay (2000);
  }
  if ((Tag == " ca 64 99 1a") && (Tag2 == 0)) {
    Tag2 = 1;
    Tag = "";
    delay (2000);
  }

  if ((Tag == " ca 64 99 1a") && (Tag2 == 1)) {
    Tag2 = 0;
    Tag = "";
    delay (2000);
  }


}

/////// FUNÇÕES //////

bool temporizador(int time) {

  if (millis() - tempo > time) {

    tempo = millis();
    return HIGH;
  }
  return LOW;
}


/*
  testa se retorno do dht é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }

*/
