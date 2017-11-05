#define BLAL 0 // 00
#define BLAH 1 // 01
#define BHAH 2 // 11
#define BHAL 3 // 10

#define rising 1
#define falling -1

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
int state = BLAL;
int A, B;
int cnt = 0;
int stateCounter=0;
int clockwiseCount = 0;
int anticlockwiseCount = 0;
int updateCount = 0;
int drehzahl;
int oldA, oldB; 
static unsigned long LastInterruptTime;

// INTERRUPT SERVICE ROUTINE 
void isrA()
{    
    if (digitalRead(pinA) > oldA){
      A = rising;
    }
    if (digitalRead(pinA) < oldA){
      A = falling;
    } 
    oldA = digitalRead(pinA);
}

void isrB()
{    
    if (digitalRead(pinB) > oldB){
      B = rising;
    }
    if (digitalRead(pinB) < oldB){
      B = falling;
    } 
    oldB = digitalRead(pinB);
}

// STATE MACHINE 
void stateMachine()
{
  if (cnt == -4)
  {
    drehzahl--;
    Serial.print("Drehzahl: ");
    Serial.println(drehzahl);
    cnt = 0;
  }
  if (cnt == 4)
  {
    drehzahl++;
    Serial.print("Drehzahl: ");
    Serial.println(drehzahl);
    cnt = 0;
  }

    switch( (state) )
    {
    //00
    case BLAL:
        if ((A == rising) && (oldB == 0))
        {          
            state = BLAH;
            cnt++;
        }
        else if ((B==rising) && (oldA==0))
        {
            state = BHAL;
            cnt--;
        }
        break;
    //01
    case BLAH:
        if ((B==rising) && (oldA == 1))
        {
            state = BHAH;
            cnt++;
        }
        else if ((oldB== 0) && (A==falling))
        {
            state = BLAL;
            cnt--;
        }
        break;
    //11
    case BHAH:
        if ((oldB==1) && (A==falling))
        {
            state = BHAL;
            cnt++;
        }
        else if ((B==falling) && (oldA==1))
        {
            state = BLAH;
            cnt--;;
        }
        break;
    //10
    case BHAL:
        if ((B==falling) && (oldA==0))
        {
            state = BLAL;
            cnt++;
        }
        else if ((oldB==1) && (A==rising))
        {
            state = BHAH;
            cnt--;
        }
        break;
    }
}

void setup() {
    Serial.begin(57600); 
    // Drehpulse sind inputs
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pinA), isrA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pinB), isrB, CHANGE);
    //Ready
    Serial.println("Start");
    drehzahl = 0;
}

void loop() { 
  stateMachine(); 
  }
