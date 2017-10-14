//**************************************************//
//   	  Team BAH : Morse Code Alphabet    	    //
//**************************************************//

int led13 = 13;      		// blink an led on baord 
int dotLen = 100;     		// length of the morse code 'dot'
int dashLen = dotLen * 3;    	// length of the morse code 'dash'
int Spaces = dotLen * 3;     	// length of the spaces between characters
int Pause = dotLen * 7;  	// length of the pause between words
char input;
String inputString = "";
bool stringComplete = false;


// the setup routine runs once when you press reset:
void setup() {
	pinMode(led13, OUTPUT);
	Serial.begin(9600); // open serial port baud rate 9600
	while (!Serial) {
    		; // wait for serial port to connect. Needed for native USB port only
  	}
}

void loop() 
{
	// alternative: while(Serial.available())
	if (stringComplete)
	{
		Serial.print("received: %c/n", input);
		for(int i; i<inputString.length(); i++)
		{
			inputString.toUpperCase();
			toMorse(inputString.charAt(i));
		}
	}
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char input = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

// DOT
void MorseDot()
{
  digitalWrite(led13, HIGH);  	// turn the LED on
  delay(dotLen);             	// hold in this positioni
  digitalWrite(led13, LOW);
}

// DASH
void MorseDash()
{
  digitalWrite(led13, HIGH);  	// turn the LED on
  delay(dashLen);               // hold in this position
  digitalWrite(led13, LOW);
}

// SPACE
void Space()
{
	delay(Pause);
}

// *** Characters to Morse Code Conversion *** //
void toMorse(char tmpChar)
{
	tmpChar.toUpperCase();
	switch (tmpChar) {
	  case 'A':
		MorseDot();
		Space();
		MorseDash();
		Space();
		break;
	  case 'B':
		MorseDash();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		break;
	  case 'C':
	    	MorseDash();
		Space();
		MorseDot();
		Space();
	    	MorseDash();
		Space();
		MorseDot();
		Space();
		break;
	  case 'D':
		MorseDash();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		break;
	  case 'E':
		MorseDot();
		Space();
		break;
	  case 'F':
	    	MorseDot();
		Space();
	    	MorseDot();
		Space();
		MorseDash();
		Space();
		MorseDot();
		Space();
		break;
	  case 'G':
		MorseDash();
		Space();
		MorseDash();
		Space();
		MorseDot();
		Space();
		break;
	  case 'H':
	    	MorseDot();
		Space();
	    	MorseDot();
		Space();
	    	MorseDot();
		Space();
		break;
	  case 'I':
	    	MorseDot();
		Space();
	    	MorseDot();
		Space();
		break;
	  case 'J':
	    	MorseDot();
		Space();
		MorseDash();
		Space();
		MorseDash();
		Space();
		MorseDash();
		Space();
		break;
          case 'K':
	    	MorseDash();
		Space();
		MorseDot();
		Space();
		MorseDash();
		Space();
		break;
	  case 'L':
	    	MorseDot();
		Space();
		MorseDash();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		break;
	  case 'm':
	    	MorseDash();
		Space();
		MorseDash();
		Space();
		break;
	  case 'N':
	    	MorseDash();
		Space();
		MorseDot();
		Space();
		break;
	  case 'O':
	    	MorseDash();
		Space();
		MorseDash();
		Space();
		MorseDash();
		Space();
		break;
	  case 'P':
	    	MorseDot();
		Space();
		MorseDash();
		Space();
		MorseDash();
		Space();
		MorseDot();
		Space();
		break;
	  case 'Q':
	    	MorseDash();
		Space();
		MorseDash();
		Space();
		MorseDot();
		Space();
		MorseDash();
		Space();
		break;
	  case 'R':
	    	MorseDot();
		Space();
		MorseDash();
		Space();
		MorseDot();
		Space();
		break;
	  case 'S':
	    	MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		break;
	  case 'T':
	    	MorseDash();
		Space();
		break;
	  case 'U':
	    	MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDash();
		Space();
		break;
	  case 'V':
	    	MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDash();
		Space();
		break;
	  case 'W':
	    	MorseDot();
		Space();
		MorseDash();
		Space();
		MorseDash();
		Space();
		break;
	  case 'X':
	    	MorseDash();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
	    	MorseDash();
		Space();
		break;
	  case 'Y':
	    	MorseDash();
		Space();
		MorseDot();
		Space();
	    	MorseDash();
		Space();
		MorseDash();
		Space();
		break;
	  case 'Z':
	    	MorseDash();
		Space();
		MorseDash();
		Space();
		MorseDot();
		Space();
		MorseDot();
		break;
	case '0';
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
		break;
	case '1';
		MorseDot();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
		
		break;
	case '2';
		MorseDot();
		Space();
		MorseDot();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
		
		break;
	case '3';
		MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
		
		break;
	case '4';
		MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
	    	MorseDash();
		Space();
		
		break;
	case '5';
		MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		
		break;
	case '6';
	    	MorseDash();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		
		break;
	case '7';
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		
		break;
	case '8';
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
		MorseDot();
		Space();
		MorseDot();
		Space();
		
		break;
	case '9';
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
	    	MorseDash();
		Space();
		MorseDot();
		Space();
		
		break;
	
	
	
	
	
	
	
	
	
	
	  default:
		// If a matching character was not found it will default to a blank space
		Space();
	}
}
