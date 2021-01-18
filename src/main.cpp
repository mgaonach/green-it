// Definition de la taille max du payload
#define T2_MESSAGE_MAX_DATA_LEN 15
#include <Arduino.h>
#include <RH_RF95.h>
#include <T2WhisperNode.h>
#include <LoRa.h>
#include <bouton.cpp>

////////////////////////////////////////////
/// Configuration WhisperNode
int myNetID = 1; // Definition du réseau
int myID = 0; // ID du WhisperNode
int mySerialNumber = 16; // Numero de série A CHANGER !!!
////////////////////////////////////////////
////////////////////////////////////////////

// Radio
uint8_t radioBuf[(T2_MESSAGE_HEADERS_LEN + T2_MESSAGE_MAX_DATA_LEN)];
T2Message myMsg;

// Mes 2 boutons
Bouton myButtonD(T2_WPN_BTN_2);
Bouton myButtonG(T2_WPN_BTN_1);

// Tableau stockant les valeurs du payload
char *array[10];
int arrayint[10];

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

int sendLORA(int idx,int src, int dst, int sdx, int cmd, const char *data,int len) {
	uint8_t radioBufLen = 0;

  // Q4 A completer
  // ...

  LoRa.beginPacket();
  LoRa.write(radioBuf,radioBufLen);
  LoRa.endPacket();
  return 1;
}

char buf[10]; // Buffeur utilisé pour l'envois de la trame
int len;      // longueur de la trame

int sendGiveMeANodeID(){
  // Q5 A completer
  // ...
}

int sendGiveMeAChannelAndField(){
  // Q9 a completer
}

int sendMyValue(int value){
  // Q11 a completer

}

void setup() {
    Serial.begin(9600);
    Serial.println("Radio Init");
    // Q2 Initialisation Puce LoRa
    // ...
}

char message[255]; //buffeur de reception d'un message
uint8_t lmes; //longeur du message recu

int receivLoRa(){
  // Q6 Reception d'une trame et construction de l'objet myMsg.
  // ...
}


void loop() {
  /// RECEPTION
  if (receivLoRa()==1) {
      // Recoit on un ID ???
      // Q7 Reception d'un ID
      // tester les champs avec la bonne valeur.
      if ((myMsg.idx == 0x00)&&(myMsg.dst==0x00)&&(myMsg.src==0x00)&&(myMsg.sdx==0x00)) {
          parseString((char *) myMsg.data);
          Serial.print("Reception d'un ID : ");
          Serial.print(arrayint[0]);
          Serial.print(" NETID : ");
          Serial.print(arrayint[1]);
          Serial.print(" au numero de serie : ");
          Serial.println(arrayint[2]);

      // Q7 puis si le numéro de série est le bon affecter myID
      }

      // Recoit on un Channel ???
      // Q10 tester les champs avec la bonne valeur.
      // puis afficher les valeurs
      if ((myMsg.idx == 0x00)&&(myMsg.dst==0x00)&&(myMsg.src==0x00)&&(myMsg.sdx==0x00)) {
      // Q10 a completer
      }

    }
    /// FIN PARTIE RECEPTION

  /// DEMANDE ID si Bouton droit appuyé
  if (myButtonD.getNumber() >= 1) {
      myID=0;myNetID=1;
      Serial.println("J'ai besoin d'un ID");
      sendGiveMeANodeID();
  }
}
