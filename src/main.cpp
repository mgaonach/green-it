// Definition de la taille max du payload
#define T2_MESSAGE_MAX_DATA_LEN 15
#include <Arduino.h>
#include <RH_RF95.h>
#include <T2WhisperNode.h>
#include <LoRa.h>
#include <bouton.cpp>
#include <Wire.h>
#include <string.h>

////////////////////////////////////////////
/// Configuration WhisperNode
int myNetID = 1; // Definition du réseau
int myID = 0; // ID du WhisperNode
int mySerialNumber = 10; // Numero de série A CHANGER !!!
long myChannel = 0;
int myField  = 0;
////////////////////////////////////////////
////////////////////////////////////////////

// Radio
uint8_t radioBuf[(T2_MESSAGE_HEADERS_LEN + T2_MESSAGE_MAX_DATA_LEN)];
T2Message myMsg;

// Mes 2 boutons
Bouton myButtonD(T2_WPN_BTN_2);
Bouton myButtonG(T2_WPN_BTN_1);

// LEDS
T2Led led1;
T2Led led2;

// Tableau stockant les valeurs du payload
char *array[10];
int arrayint[10];
int arraylong[10];

// fonction permettant d'analyser le payload d'une trame
// stocke les valeurs dans le tableau arrayint
// premier parametre dans arrayint[0], deuxième dans arrayint[1] etc...
int parseString (char *s) {
    int i = 0;
    char *p = strtok (s, ";");
    while ((p != NULL) & (i<9)) {
        array[i++] = p;
        p = strtok (NULL, ";");
    }
    while (i<10) array[i++] = NULL;
    for (i = 0; i < 10; ++i) {
      if (array[i]!=NULL) {
        arrayint[i]=atoi(array[i]);
        }
    }
    return 0;
}

// fonction permettant d'analyser le payload d'une trame
// stocke les valeurs dans le tableau arrayint
// premier parametre dans arrayint[0], deuxième dans arrayint[1] etc...
int parseStringToLong (char *s) {
    int i = 0;
    char *p = strtok (s, ";");
    while ((p != NULL) & (i<9)) {
        array[i++] = p;
        p = strtok (NULL, ";");
    }
    while (i<10) array[i++] = NULL;
    for (i = 0; i < 10; ++i) {
      if (array[i]!=NULL) {
        arraylong[i]=atol(array[i]);
        }
    }
    return 0;
}

int sendLORA(int idx,int src, int dst, int sdx, int cmd, const char *data,int len) {
	
  uint8_t radioBufLen = 0;

  // Q4 A completer

  memset(myMsg.data, 0, sizeof(myMsg.data));

  myMsg.idx = idx;
  myMsg.src = src;
  myMsg.dst = dst;
  myMsg.sdx = sdx;
  myMsg.cmd = cmd;
  myMsg.len = len;

  for (size_t i = 0; i < sizeof(&data); i++)
  {
    myMsg.data[i] = data[i];
  }
  // memcpy(myMsg.data, &data, len);
  myMsg.getSerializedMessage(radioBuf, &radioBufLen);

  LoRa.beginPacket();
  LoRa.write(radioBuf,radioBufLen);
  LoRa.endPacket();
  return 1;
}

char buf[10]; // Buffeur utilisé pour l'envois de la trame
int len;      // longueur de la trame

int sendGiveMeANodeID(){
  // Q5 A completer
  itoa(mySerialNumber,buf,10);
  len = strlen(buf);
  buf[len ] = ';';
  len = len +1;
  return sendLORA(1, 0, 1, 1, 0, buf, len);
}

int sendGiveMeAChannelAndField(){
  // Q9 a completer
  buf[0] = 0;
  return sendLORA(myNetID, myID, 1, 2, 0, buf, 1);
}

int sendMyValue(int value){
  // Q11 a completer
  itoa(value,buf,10);
  len = strlen(buf);
  buf[len ] = ';';
  len = len +1;
  return sendLORA(myNetID, myID, 1, 3, 1, buf, len);
}

int sendBlink(){
  // Q11 a completer
  buf[0] = 0;
  return sendLORA(0, 0, 0, 0, 0, buf, 0);
}

void setup() {
    Serial.begin(9600);
    Serial.println("Radio Init");

    led1 = T2Led(6);
    led2 = T2Led(9);

    // Q2 Initialisation Puce LoRa
    LoRa.setPins(10,7,2);
    if (!LoRa.begin(868E6)) {
      Serial.println("Starting LoRa failed!");
      while (1);
    }
}

char message[255]; //buffeur de reception d'un message
uint8_t lmes; //longeur du message recu

int receivLoRa(){
  // Q6 Reception d'une trame et construction de l'objet myMsg.

  uint8_t radioBufLen = 0;

  int i = 0;
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      radioBuf[i++] = (char) LoRa.read();
    };
    radioBufLen = i ;
    myMsg.setSerializedMessage(radioBuf, radioBufLen);
    return 1;
  }
  else {
    return 0;
  }
}


void loop() {

  myButtonD.check();
  myButtonG.check();

  /// RECEPTION
  if (receivLoRa()==1) {

      // Recoit on un ID ???
      // Q7 Reception d'un ID
      // tester les champs avec la bonne valeur.
      if ((myMsg.idx == 0x01)&&(myMsg.dst==0x00)&&(myMsg.src==0x01)&&(myMsg.sdx==0x01)) {
        parseString((char *) myMsg.data);
        
        // Q7 puis si le numéro de série est le bon affecter myID
        if (arrayint[2] == mySerialNumber) {
          myID = arrayint[0];
          myNetID = arrayint[1];
          Serial.print("Reception d'un ID : ");
          Serial.print(arrayint[0]);
          Serial.print(" NETID : ");
          Serial.print(arrayint[1]);
          Serial.print(" au numero de serie : ");
          Serial.println(arrayint[2]);
        }
      }
      
      // Recoit on un Channel ???
      // Q10 tester les champs avec la bonne valeur.
      // puis afficher les valeurs
      if ((myMsg.idx == 0x01)&&(myMsg.dst==myID)&&(myMsg.src==0x01)&&(myMsg.sdx==0x02)&&(myMsg.cmd==0x01)) {
        // Q10 a completer
        parseString((char *) myMsg.data);
        myChannel = atol(array[0]);
        myField = arrayint[1];
        Serial.print("Reception d'un channel : ");
        Serial.print(myChannel);
        Serial.print(" Field : ");
        Serial.print(arrayint[1]);
      }

      if ((myMsg.idx == 0x00)&&(myMsg.dst==0x00)&&(myMsg.src==0x00)&&(myMsg.sdx==0x00)) {
        for (int i = 0; i < 1; i++)
        {
            led1.turnOn();
            led2.turnOn();
            delay(500);
            led1.turnOff();
            led2.turnOff();
            delay(500);
        }
      }

    }
    /// FIN PARTIE RECEPTION

    int nbPressed = myButtonD.getNumber();

  /// DEMANDE ID si Bouton droit appuyé
  if (nbPressed == 1) {
      myID=0;myNetID=1;
      Serial.println("J'ai besoin d'un ID");
      sendGiveMeANodeID();
  }

  if (nbPressed == 2) {
      Serial.println("J'ai besoin d'un channel");  
      sendGiveMeAChannelAndField();
  }

  if (nbPressed == 3) {
      Serial.println("J'envoie ma temp");
      sendMyValue(19);
  }

  if (nbPressed == 4) {
      Serial.println("Envoie msg blink");
      sendBlink();
  }
}
