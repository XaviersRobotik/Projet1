#include <IRremote.h>
//#include <Wire.h>
#include "IR_VTECH_CODES.h"
#include "UsbKeyboard.h"

const int RECV_PIN = 4; // Recepteur TSP1708 sur broche 4

IRrecv irrecv(RECV_PIN); // declaration de l'objet de reception IR
decode_results results; // varieble pour le decodage

int Code_USB;// Bonjour

int ConversionIRVersUSB(int Valeur)
{
	char Caractere_decode = ""; //bonne chance pour telecharger GitHub les gars 
	
	switch(Valeur) {
       case TOUCHE_A:
         Caractere_decode = "A";
         Caractere_USB = KEY_A;
          break;
      case TOUCHE_B:
         Caractere_decode = "B";
         Caractere_USB = KEY_B;
          break;
      case TOUCHE_C:
         Caractere_decode = "C";
         Caractere_USB = KEY_C;
          break;
      case TOUCHE_D:
         Caractere_decode = "D";
         Caractere_USB = KEY_D;
          break;
      case TOUCHE_E:
         Caractere_decode = "E";
         Caractere_USB = KEY_E;
          break;
      case TOUCHE_F:
         Caractere_decode = "F";
         Caractere_USB = KEY_F;
          break;
      case TOUCHE_G:
         Caractere_decode = "G";
         Caractere_USB = KEY_G;
          break;
      case TOUCHE_H:
         Caractere_decode = "H";
         Caractere_USB = KEY_H;
          break;
      case TOUCHE_I:
         Caractere_decode = "I";
         Caractere_USB = KEY_I;
          break;
      case TOUCHE_J:
         Caractere_decode = "J";
         Caractere_USB = KEY_J;
          break;
      case TOUCHE_K:
         Caractere_decode = "K";
         Caractere_USB = KEY_K;
          break;
      case TOUCHE_L:
         Caractere_decode = "L";
         Caractere_USB = KEY_L;
          break;
      case TOUCHE_M:
         Caractere_decode = "M";
         Caractere_USB = KEY_M;
          break;
      case TOUCHE_N:
         Caractere_decode = "N";
         Caractere_USB = KEY_N;
          break;
      case TOUCHE_O:
         Caractere_decode = "O";
         Caractere_USB = KEY_O;
          break;
      case TOUCHE_P:
         Caractere_decode = "P";
         Caractere_USB = KEY_P;
          break;
      case TOUCHE_Q:
         Caractere_decode = "Q";
         Caractere_USB = KEY_Q;
          break;
      case TOUCHE_R:
         Caractere_decode = "R";
         Caractere_USB = KEY_R;
          break;
      case TOUCHE_S:
         Caractere_decode = "S";
         Caractere_USB = KEY_S;
          break;
      case TOUCHE_T:
         Caractere_decode = "T";
         Caractere_USB = KEY_T;
          break;
      case TOUCHE_U:
         Caractere_decode = "U";
         Caractere_USB = KEY_U;
          break;
      case TOUCHE_V:
         Caractere_decode = "V";
         Caractere_USB = KEY_V;
          break;
      case TOUCHE_W:
         Caractere_decode = "W";
         Caractere_USB = KEY_W;
          break;
      case TOUCHE_X:
         Caractere_decode = "X";
         Caractere_USB = KEY_X;
          break;
      case TOUCHE_Y:
         Caractere_decode = "Y";
        Caractere_USB = KEY_Y;
         break;
      case TOUCHE_Z:
         Caractere_decode = "Z";
         Caractere_USB = KEY_Z;
          break;
      case TOUCHE_1:
         Caractere_decode = "1";
         Caractere_USB = KEY_1;
          break;
      case TOUCHE_2:
         Caractere_decode = "2";
         Caractere_USB = KEY_2;
          break;
      case TOUCHE_3:
         Caractere_decode = "3";
         Caractere_USB = KEY_3;
          break;
      case TOUCHE_4:
         Caractere_decode = "4";
         Caractere_USB = KEY_4;
          break;
      case TOUCHE_5:
         Caractere_decode = "5";
         Caractere_USB = KEY_5;
          break;
      case TOUCHE_6:
         Caractere_decode = "6";
         Caractere_USB = KEY_6;
          break;
      case TOUCHE_7:
         Caractere_decode = "7";
         Caractere_USB = KEY_7;
          break;
      case TOUCHE_8:
         Caractere_decode = "8";
         Caractere_USB = KEY_8;
          break;
      case TOUCHE_9:
         Caractere_decode = "9";
         Caractere_USB = KEY_9;
          break;
      case TOUCHE_0:
         Caractere_decode = "0";
         Caractere_USB = KEY_0;
         break;
      case ESPACE:
         Caractere_decode = " ";
         Caractere_USB = KEY_SPACE;
         break;
      case MAJUSCULE_MINUSCULE:
         Caractere_USB = KEY_CAPSLOCK;
         break;
      case RETOUR_ARRIERE:
         Caractere_USB = KEY_BKSPACE;
         break; 
       case VALID_HAUT: // Touche Entrée
       case VALID_BAS: // Touche Entrée
         Caractere_USB = KEY_ENTER;
		 break;
         
       default:
           irrecv.resume(); // Receive the next value
           
      }
	  
	//return Caractere_decode;
	return Caractere_USB;
	
}


void setup()
{
	irrecv.enableIRIn(); // Start the receiver
	InitUSBKeyboardEmulation();
	delay(1000);
}

void loop() {
  UsbKeyboard.update();
  if (irrecv.decode(&results)) 
  {
    Code_USB = ConversionIRVersUSB(results.value); // conversion du code IR vers code USB
	if(Code_USB <> 0)
	{
		UsbKeyboard.sendKeyStroke(Code_USB);
	}
	
	irrecv.resume(); // Receive the next value
  }
}


/*
 * Define our own delay function so that we don't have to rely on
 * operation of timer0, the interrupt used by the internal delay()
 */
void delayMs(unsigned int ms)
{
  for (int i = 0; i < ms; i++) {
    delayMicroseconds(1000);
  }
}

void InitUSBKeyboardEmulation()
{
	// Disable timer0 since it can mess with the USB timing. Note that
	// this means some functions such as delay() will no longer work.
	TIMSK0&=!(1<<TOIE0);

  // Clear interrupts while performing time-critical operations
  cli();

  // Force re-enumeration so the host will detect us
  usbDeviceDisconnect();
  delayMs(250);
  usbDeviceConnect();

  // Set interrupts again
  sei();
	
}





/*
POUBELLE

     case JOYSTICK_HAUT_MODE1:
         lcd.setCursor(0,1);
         lcd.println("JOYSTICK_HAUT_MODE1   ");
         lcd.setCursor(Colonne,Ligne);
         break;
      case JOYSTICK_BAS_MODE1:
         lcd.setCursor(0,1);
         lcd.println("JOYSTICK_BAS_MODE1    ");
         lcd.setCursor(Colonne,Ligne);
         break;
      case JOYSTICK_GAUCHE_MODE1:
         lcd.setCursor(0,1);
         lcd.println("JOYSTICK_GAUCHE_MODE1 ");
         lcd.setCursor(Colonne,Ligne);
         break;
      case JOYSTICK_DROITE_MODE1:
         lcd.setCursor(0,1);
         lcd.println("JOYSTICK_DROITE_MODE1 ");
         lcd.setCursor(Colonne,Ligne);
         break;






*/
