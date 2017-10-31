#define BLAL 0 // 00
#define BLAH 1 // 01
#define BHAH 2 // 11
#define BHAL 3 // 10

/**
GrayCode
  |B | A | State
  |--|---|------
0 |0 | 0 |  1
1 |0 | 1 |  2
2 |1 | 1 |  3
3 |1 | 0 |  4
**/

const int pinA = 2; //DigitalPin2 intterupt pin, setze interrupt A
const int pinB = 3; // DigitalPin3 interrupt pin, setze interrupt B
int state, A, B;
int stateCounter=0;
int clockwiseCount = 0;
int anticlockwiseCount = 0;
int lastCount = 50;
int updateCount = 0;
int drehzahl;
static unsigned long LastInterruptTime;


// INTERRUPT SERVICE ROUTINE 
void isr()
{    
    unsigned long interruptTime = millis();

  // wenn interrupt schneller kommt als erwartet nehmen wir an, der drehgeber prellt und ignorieren ihn 
  	if (interruptTime - LastInterruptTime > 1) 
  	{
        Serial.println("Entering ISR");
        stateMachine();
        // Übersicht behalten wann wir zuletzt hier waren
        LastInterruptTime = interruptTime;
      } 
}

// STATE MACHINE 
void stateMachine()
{
    Serial.println("Entering SM");

    A=digitalRead(pinA);
    B=digitalRead(pinB);    

    Serial.print("State :");
    Serial.print(A);
    Serial.println(B);
    
    if(anticlockwiseCount == 4) 
    {
        drehzahl--;
        anticlockwiseCount = 0;
        Serial.print("DEBUG einmal rum counter clock !!\n");
    }
    if(clockwiseCount == 4)
    {
        drehzahl++;
        clockwiseCount = 0;
        Serial.println("DEBUG einmal rum clockwise !!\n");
    }

    switch( (state) )
    {
    //00
    case BLAL:
        if (B==0 && A==1)
        {
            stateCounter++;
            state = BLAH;

            clockwiseCount++;
            anticlockwiseCount = 0;
        }
        else if (B==1 && A==0)
        {
            stateCounter--;
            state = BHAL;

            clockwiseCount = 0;
            anticlockwiseCount++;
        }
        break;
    //01
    case BLAH:
        if (B==1 && A==1)
        {
            stateCounter++;
            state = BHAH;
            
            clockwiseCount++;
            anticlockwiseCount = 0;
        }
        else if (B==0 && A==0)
        {
            stateCounter--;
            state = BLAL;
            clockwiseCount = 0;
            anticlockwiseCount++;
        }
        break;
    //11
    case BHAH:
        if (B==1 && A==0)
        {
            stateCounter++;
            state = BHAL;
            clockwiseCount++;
            anticlockwiseCount = 0;
        }
        else if (B==0 && A==1)
        {
            stateCounter--;
            state = BLAH;
            clockwiseCount = 0;
            anticlockwiseCount++;
        }
        break;
    //10
    case BHAL:
        if (B==0 && A==0)
        {
            stateCounter++;
            state = BLAL;
            clockwiseCount++;
            anticlockwiseCount = 0;
        }
        else if (B==1 && A==1)
        {
            stateCounter--;
            state = BHAH;
            clockwiseCount = 0;
            anticlockwiseCount++;
        }
        break;
    }

    // wenn die aktuelle position nicht der letztes entspricht updaten wir alles
     Serial.print(drehzahl > lastCount ? "Uhrezigersinn: " : "Gegenuhrzeigers.: ");
     Serial.println(drehzahl);
    
    //wert verfolgen
    lastCount = drehzahl;
}

    
void setup() {
    Serial.begin(9600); 
    // Drehpulse sind inputs
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pinA), isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pinB), isr, CHANGE);
    //Ready
    Serial.println("Start");
    state = 0;//welchen State ist eigendlich egal
    stateCounter =0; // Das ist der zähler
    drehzahl = 0;
  
}

void loop() { }
