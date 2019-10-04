//#include <DHT.h>
//#include <DHT_U.h>

#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>


//Pinos da comunicação com o HC-05
#define BTX 5
#define BRX 4

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define pinDHT A4 // pino de dados do DHT11

#define pinChave1 6
#define pinChave2 7
#define pinChave3 8


SoftwareSerial Bluetooth(BRX, BTX); //Configura a comunicação serial com para o HC-05
//DHT dht(pinDHT, DHTTYPE);  //Configura o DHT11


int Rx, RxF = 0; //auxiliar e Flag do RX
char RxBuff[9]; // Menssagem que será recebida

float umidade;    //usar coando dht.readHumidity();
float temperatura; // usar comando dht.readTemperature();

bool Chv1;
bool Chv2;
bool Chv3;
bool Tag1;
bool Tag2;

String myString;
int cmd;
int es = 0;

void setup()
{
  Bluetooth.begin(9600); //Inicia comunicação serial para a placa HC-05
  Serial.begin(9600);   //Inicia comunicação serial para o outro arduino
  SPI.begin();          //Não sei para oque serve
  mfrc522.PCD_Init(); //Inicia a comunicação com o sensor RFID
  //dht.begin();  //inicia a comunicação com o DHT11


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
  }


  if ((RxBuff[8] == '!') && (RxBuff[0] == '#') && (RxF == 1))
  {

    for (int i = 7; i >= 4; --i) {
      myString.concat(RxBuff[i]);
    }

    cmd = ((RxBuff[3] - 48) * 100) + ((RxBuff[2] - 48) * 10) + ((RxBuff[1] - 48) * 1);

    //Enviar os dados do App direto para o arduino02?

    for (int i = 0; i >= 9; i++) {
  Serial.println(RxBuff[i]);
}

    RxF = 0;
  }


  Chv1 = digitalRead(pinChave1);
  Chv2 = digitalRead(pinChave2);
  Chv3 = digitalRead(pinChave3);









  /*
     Inicio da programação do RFID
  */

  if ( ! mfrc522.PICC_IsNewCardPresent()) { // Busca novos cartões
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {   // Seleciona um catão a ser lido
    return;
  }

  String Tag = "";

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : " "));
    Tag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }


  Serial.println(Tag);

  if ((Tag == " e7 13 6c 34") && (es == 0)) {
   
    es = 1;
    Tag = "";
    delay (1000);
  }

  if ((Tag == " e7 13 6c 34") && (es == 1)) {
  
    es = 0;
    Tag = "";
    delay (1000);
  }










}



/*
  testa se retorno do dht é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }

*/
