//*Mike hat spaß an c*/
//TODO: Counter soll erst bei einem Druchlauf durch 4 States zählen 
//TODO: bita und bitb über interruptroutinen lesen
//TODO: Debouncer
#include <stdio.h>
#include <stdlib.h>

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
/**
Wichtig für die Aufgabe Sind nur die Statemachine und der Rumpf der do while Schleife
**/
const int PinA = 2; //DigitalPin2 ist intterupt pin, setze interrupt A
const int PinB = 3; // DigitalPin3 ist interrupt pin, setze intterupt B
int state;
int bita=0;
int bitb=0;
int stateCounter=0;
int clockwiseCount = 0;
int anticlockwiseCount = 0;
int lastCount = 50;
int updateCount = 0;
int drehzahl = 0;
//update isr
volatile int virtualPosition = 50;

/* NON C FUNKTION........................
// INTERRUPT
void isr()
{
	static unsigned long lastInterruptTime = 0;
	unsigned long interrupTTime = millis();

// wenn interrupt schneller kommt als erwartet nehmen wir an, der drehgeber prellt und ignorieren ihn 
	if (interrupTTime - lastInterruptTime > 5) 
	{
		if(digitalRead(PinB == LOW))
		{
			virtualPosition--;
		} else {
			virtualPosition++;
		}
        // Wert auf 0 bis 100 begrenzen
        //virtualPosition = min(100, max(0, virtualPosition));
		
        // Übersicht behalten wann wir zuletzt hier waren
        lastInterruptTime = interrupTTime;
    }
}
..............*/
void stateMachine()
{
    if(anticlockwiseCount == 4) 
    {
        drehzahl--;
        anticlockwiseCount = 0;
        printf("DEBUG einmal rum counter clock !!\n");
    }
    if(clockwiseCount == 4)
    {
        drehzahl++;
        clockwiseCount = 0;
        printf("DEBUG einmal rum clockwise !!\n");
    }

    switch( (state) )
    {
    //00
    case BLAL:
        if (bitb==0 && bita==1)
        {
            stateCounter++;
            state = BLAH;

            clockwiseCount++;
            anticlockwiseCount = 0;
        }
        else if (bitb==1 && bita==0)
        {
            stateCounter--;
            state = BHAL;

            clockwiseCount = 0;
            anticlockwiseCount++;
        }
        break;
    //01
    case BLAH:
        if (bitb==1 && bita==1)
        {
            stateCounter++;
            state = BHAH;
            
            clockwiseCount++;
            anticlockwiseCount = 0;
        }
        else if (bitb==0 && bita==0)
        {
            stateCounter--;
            state = BLAL;
            clockwiseCount = 0;
            anticlockwiseCount++;
        }
        break;
    //11
    case BHAH:
        if (bitb==1 && bita==0)
        {
            stateCounter++;
            state = BHAL;
            clockwiseCount++;
            anticlockwiseCount = 0;
        }
        else if (bitb==0 && bita==1)
        {
            stateCounter--;
            state = BLAH;
            clockwiseCount = 0;
            anticlockwiseCount++;
        }
        break;
    //10
    case BHAL:
        if (bitb==0 && bita==0)
        {
            stateCounter++;
            state = BLAL;
            clockwiseCount++;
            anticlockwiseCount = 0;
        }
        else if (bitb==1 && bita==1)
        {
            stateCounter--;
            state = BHAH;
            clockwiseCount = 0;
            anticlockwiseCount++;
        }
        break;
    }
   // printf(" State: %i ,Count: %i\n",state,stateCounter);

}

void printMenue()
{
    printf("Der Statemaschiene Drehgebe Simulator 2017 v.1\n");
    printf("Menue\n");
    printf("Bits: BA\n");
    printf("\n'a'=00");
    printf("\n's'=01");
    printf("\n'd'=11");
    printf("\n'f'=10\n");
    printf("\n'm'=Print Menue");
    printf("'e'= exit: \n");
    printf("--------------\n");
    return ;
}
int main()
{
    /*
     * void setup() {
     *      Serial.begin(9600); //höfig meinte irgendwas mit 7?
     *
     *      // Drehpulse sind inputs
     *      pinMode(pinA, INPUT_PULLUP);
     *      pinMode(pinB, INPUT_PULLUP);
     *
     *      attachInterrupt(digitalPinToInterrupt(PinA), isr, LOW);
     *
     *      //Ready
     *      Serial.println("Start");
     */
    state = 3;//welchen State ist eigendlich egal
    stateCounter =0; // Das ist der zähler
    int A=0;


    /*
     * loop() {
     *
     * // wenn die aktuelle position nicht der letztes entspricht updaten wir alles
     * Serial.print(virtualPosition > lastCount ? "Uhrezigersinn: " : "Gegenuhrzeigers.: ");
     * Serial.println(virtualPosition);
     *
     *  //wert verfolgen
     *  lastCount = virtualPosition;
     */

    printMenue();
    do
    {
        A = getchar();

        //nur für Die Benutzerfreundlichkeit
        if(A=='m')
            printMenue();
        //Nach dem getchar bleibt immer noch nen \n deswegen hatte der das immer
        //doppelt geprintet
        if (A!= '\n') {
            printf(" State: %i ,Count: %i\n LastCommand: '%c'\n",state,stateCounter,A);
            printf("\nUhrzeigersinn: %i\nGegegn Uhrezigersinn: %i\n", clockwiseCount, anticlockwiseCount); 
            printf("Drehzahl: %i\n", drehzahl);
        }
            //'a'=00 | 's'=01 | 'd'=11 | 'f'=10
        if (A=='a')
        {
            bita=bitb=0;
        }
        else if (A=='s')
        {
            bitb=0;
            bita=1;
        }
        else if (A=='d')
        {
            bitb=1;
            bita=1;
        }
        else if (A=='f')
        {
            bitb=1;
            bita=0;
        }
        stateMachine();

    }while((A !='e'));
    printf("Danke und Aufwiedersehen\n");
    getchar();
    return 0;
}
