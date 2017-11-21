#define CLKW true
#define CCLKW false

int inA1 = 9; // input 1 of the stepper
int inA2 = 12; // input 2 of the stepper
int inB1 = 11; // input 3 of the stepper
int inB2 = 10; // input 4 of the stepper

typedef enum State{ s1, s2, s3, s4 };
State state; 

int i = 0; 
int stepDelay = 25; // Delay between steps in milliseconds
int soll, ist = 0;

void setup() {    
  Serial.begin(9600);
              
  pinMode(inA1, OUTPUT);     
  pinMode(inA2, OUTPUT);     
  pinMode(inB1, OUTPUT);     
  pinMode(inB2, OUTPUT);    
  state = s1;
//  Serial.print("start");

}

// the loop routine runs over and over again forever:
void loop() {
    moveClkw();
/**
  while (soll != ist)
  {
    switch (state){
      case 0:    
        step1(); state = 1;  break;
      case 1:    
        step2(); state = 2;  break;
      case 2:    
        step3(); state = 3; break;
      case 3:    
        step4(); state = 0; break;
      default:  stopMotor();
    }*/
    //  soll ++;

}

void moveClkw(){
  step1();
  step2();
  step3();
  step4();
  stopMotor();
}

void step1() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, HIGH);   
  digitalWrite(inB1, HIGH);   
  digitalWrite(inB2, LOW);   
  delay(stepDelay);
}
void step2() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, HIGH);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, HIGH);   
  delay(stepDelay);
}
void step3() {
  digitalWrite(inA1, HIGH);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, HIGH);   
  delay(stepDelay);
}
void step4() {
  digitalWrite(inA1, HIGH);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, HIGH);   
  digitalWrite(inB2, LOW);   
  delay(stepDelay);
}
void stopMotor() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, LOW);   
}

