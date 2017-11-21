

const int out1 = 4;
const int out2 = 3;
const int out3 = 5;
const int out4 = 2;
int i=0;
int negative=0;
int positive=0;
char temp_print=0;
char temp_print1=0;

int led=13;

void setup() 
{

  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(led,OUTPUT);

  digitalWrite(out1,LOW);
  digitalWrite(out2,LOW);

  digitalWrite(out3,LOW);
  digitalWrite(out4,LOW);

  digitalWrite(led,LOW);
  Serial.begin(9600);
  
 }

void loop() 
{
  if(temp_print1==1)
  {
    Serial.println(".");
    delay(1000);
    Serial.println(".");
    delay(1000);
    Serial.println(".");
    delay(1000);
    Serial.println(".");
    delay(1000);
    Serial.println(".");
    delay(1000);
    Serial.println(".");
    delay(1000);
    Serial.println(".");
    Serial.println("calibration completed......");
    Serial.println("Stepper Motor Ready");
    temp_print1=temp_print1+1;

  }
 
  if(temp_print==0)
  {
    Serial.println("Enter the dummy DIRECTION & STEPS for calibration");
    temp_print=temp_print+1;
    temp_print1=temp_print1+1;
  }
  
  abc:
  Serial.print("Direction = ");
       while(Serial.available()==false);
  
    char temp = Serial.read();
    
    if(temp=='+')
    {
      Serial.println(temp);
      Serial.print("Steps = "); 
       while(Serial.available()==false)
       {
        digitalWrite(led,HIGH);
        delay(50);
        digitalWrite(led,LOW);
        delay(50);
       }
       
    int val = Serial.parseInt();
    Serial.println(val);
    if(val>=0 && val<=400)
      {
        for(int a=val;a>0;a--)
          {
            if(negative==1)
             {
              if(i==7)
              i=0;
              else
              a=a+1;
              i=i+1;
              negative=0;
            
             }
            positive=1;
            if(i==0)      { digitalWrite(out1,HIGH);digitalWrite(out2,LOW);digitalWrite(out3,LOW);digitalWrite(out4,LOW);delay(60);  }
            else if(i==1) { digitalWrite(out1,HIGH);digitalWrite(out2,HIGH);digitalWrite(out3,LOW);digitalWrite(out4,LOW);delay(60); }
            else if(i==2) { digitalWrite(out1,LOW);digitalWrite(out2,HIGH);digitalWrite(out3,LOW);digitalWrite(out4,LOW);delay(60);  }
            else if(i==3) { digitalWrite(out1,LOW);digitalWrite(out2,HIGH);digitalWrite(out3,HIGH);digitalWrite(out4,LOW);delay(60); }
            else if(i==4) { digitalWrite(out1,LOW);digitalWrite(out2,LOW);digitalWrite(out3,HIGH);digitalWrite(out4,LOW);delay(60);  }
            else if(i==5) { digitalWrite(out1,LOW);digitalWrite(out2,LOW);digitalWrite(out3,HIGH);digitalWrite(out4,HIGH);delay(60); }
            else if(i==6) { digitalWrite(out1,LOW);digitalWrite(out2,LOW);digitalWrite(out3,LOW);digitalWrite(out4,HIGH);delay(60);  }
            else if(i==7) { digitalWrite(out1,HIGH);digitalWrite(out2,LOW);digitalWrite(out3,LOW);digitalWrite(out4,HIGH);delay(60); }
            if(i==7)
            {i=0;continue;}
            i++;
          }
      }
      
      else 
      {
        goto abc;
      }
     digitalWrite(out1,LOW);digitalWrite(out2,LOW);digitalWrite(out3,LOW);digitalWrite(out4,LOW);delay(50);  
      val=0;
      
      }
       


   else if(temp=='-')
    {
      Serial.println(temp);
      Serial.print("Steps = "); 
     while(Serial.available()==false)
       {
        digitalWrite(led,HIGH);
        delay(50);
        digitalWrite(led,LOW);
        delay(50);
       }
    int val = Serial.parseInt();
     Serial.println(val);
    if(val>=0 && val<=400)
      {
        for(int a=val;a>0;a--)
          {

           if(positive==1)
           {
            i=i-1;
            positive=0;
            a=a+1;
           }
           negative=1;            
            if(i==0)      { digitalWrite(out1,HIGH);digitalWrite(out2,LOW);digitalWrite(out3,LOW);digitalWrite(out4,LOW);delay(60);  }
            else if(i==1) { digitalWrite(out1,HIGH);digitalWrite(out2,HIGH);digitalWrite(out3,LOW);digitalWrite(out4,LOW);delay(60); }
            else if(i==2) { digitalWrite(out1,LOW);digitalWrite(out2,HIGH);digitalWrite(out3,LOW);digitalWrite(out4,LOW);delay(60);  }
            else if(i==3) { digitalWrite(out1,LOW);digitalWrite(out2,HIGH);digitalWrite(out3,HIGH);digitalWrite(out4,LOW);delay(60); }
            else if(i==4) { digitalWrite(out1,LOW);digitalWrite(out2,LOW);digitalWrite(out3,HIGH);digitalWrite(out4,LOW);delay(60);  }
            else if(i==5) { digitalWrite(out1,LOW);digitalWrite(out2,LOW);digitalWrite(out3,HIGH);digitalWrite(out4,HIGH);delay(60); }
            else if(i==6) { digitalWrite(out1,LOW);digitalWrite(out2,LOW);digitalWrite(out3,LOW);digitalWrite(out4,HIGH);delay(60);  }
            else if(i==7) { digitalWrite(out1,HIGH);digitalWrite(out2,LOW);digitalWrite(out3,LOW);digitalWrite(out4,HIGH);delay(60); }
            if(i==0)
            {i=7;continue;}
            i--;
            }
      }
       else 
      {
        goto abc;
      }
     digitalWrite(out1,LOW);digitalWrite(out2,LOW);digitalWrite(out3,LOW);digitalWrite(out4,LOW);delay(50);  
      val=0;
     }
     else
     goto abc;

}

