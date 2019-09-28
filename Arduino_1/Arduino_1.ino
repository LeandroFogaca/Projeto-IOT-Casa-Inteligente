#include <DHT.h>
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>

/*
 * #Define para todos os pinos utilizados
 */
 
//Pinos da comunicação com o HC-05
#define BTX 5
#define BRX 4

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN)

#define pinDHT A4 // pino de dados do DHT11

SoftwareSerial Bluetooth(BRX, BTX); //Configura a comunicação serial com para o HC-05
DHT dht(pinDHT, DHTTYPE);  //Configura o DHT11


int Rx, RxF=0;  //auxiliar e Flag do RX
char RxBuff[8]; // Menssagem que será recebida

String myString;
char cmd;

float umidade;    //usar coando dht.readHumidity();
float temperatura; // usar comando dht.readTemperature();

void setup()
{
  Bluetooth.begin(9600); //Inicia comunicação serial para a placa HC-05
  Serial.begin(9600);   //Inicia comunicação serial para o outro arduino
  SPI.begin();          //Não sei para oque serve
  mfrc522.PCD_Init(); //Inicia a comunicação com o sensor RFID
  dht.begin();  //inicia a comunicação com o DHT11

 
}

void loop()
{
 
      if (Bluetooth.available() > 0)
         {
            Rx = Bluetooth.read();
            RxBuff[7]=RxBuff[6];
            RxBuff[6]=RxBuff[5];
            RxBuff[5]=RxBuff[4];
            RxBuff[4]=RxBuff[3];
            RxBuff[3]=RxBuff[2];
            RxBuff[2]=RxBuff[1];
            RxBuff[1]=RxBuff[0];
            RxBuff[0]=Rx;
      
           RxF = 1; //Flag para sinalizar que a informação é nova
           //Serial.print("Byterecebido= ");
           //Serial.println(char(Rx));
         }


      if ((RxBuff[7] == '!') && (RxBuff[0]=='#') && (RxF==1))
      {              
           Serial.print("Mensagem recebida: ");
           Serial.print(char(RxBuff[7]));
           Serial.print(char(RxBuff[6]));
           Serial.print(char(RxBuff[5]));
           Serial.print(char(RxBuff[4]));
           Serial.print(char(RxBuff[3]));
           Serial.print(char(RxBuff[2]));
           Serial.print(char(RxBuff[1]));
           Serial.println(char(RxBuff[0]));

           // trasnforma o valor em uma string
           for (int i = 6; i >= 3; --i) {   
              myString.concat(RxBuff[i]);     
           }
           cmd = RxBuff[1];
        
           Serial.print(myString);
           Serial.print(" = ");
           Serial.println(cmd);      
           RxF = 0;

           cmd = ' ';
           myString = " ";
        }


/*
 * Inicio da programação do RFID
 */
          
  if ( ! mfrc522.PICC_IsNewCardPresent()){  // Busca novos cartões 
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()){    // Seleciona um catão a ser lido
    return;
  }

String Tag = "";

for (byte i = 0; i < mfrc522.uid.size; i++)
{
  Tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0":" "));
  Tag.concat(String(mfrc522.uid.uidByte[i], HEX));
}


Serial.println(Tag);
  





        
}



/*
  testa se retorno do dht é valido, caso contrário algo está errado.
if (isnan(t) || isnan(h)) 
  {
    Serial.println("Failed to read from DHT");
  }

  */
 
