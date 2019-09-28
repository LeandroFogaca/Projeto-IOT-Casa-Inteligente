#include <SoftwareSerial.h>

#define pinLed 13
#define TX 5
#define RX 4

SoftwareSerial Bluetooth(RX, TX);

int Rx, RxF=0;  ////auxiliar e Flag do RX
char RxBuff[8];

String myString;
char cmd;


void setup()
{
  Bluetooth.begin(9600);
  Serial.begin(9600);

  pinMode(pinLed, OUTPUT);
  
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
        
}
