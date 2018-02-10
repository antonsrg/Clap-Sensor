const int micpin = 7, ledpin=3;
const int clapdelay = 500;
int eventstatus=0;
bool sensorstatus=0, startMeasured = false, lastDebounceSet = false;

unsigned long firstClapStart, firstClapEnd;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 20;

void setup() {
  Serial.begin(9600);
  
  pinMode(micpin, INPUT);
  pinMode(ledpin, OUTPUT);
}

void loop() {
  eventstatus = 0;
  sensorstatus = digitalRead(micpin);
  
  //delay(1);

  if(eventstatus == 0)
  {
    if(sensorstatus == 1 && startMeasured == false)
    {
      firstClapStart = millis();
      startMeasured = true;
      Serial.println("Start now!");
    }
    
      bool bouncing = false;
      sensorstatus = digitalRead(micpin);
      if(startMeasured)
      {
        //Serial.println("Debouncer!");
        if(sensorstatus == 0)
        { 
          //Serial.println("sensorstatus = 0");
          lastDebounceTime = millis();
          lastDebounceSet = true;
        }
        while( (millis() - lastDebounceTime) < 50 )
        {
          //Serial.println("In while loop");
          if(digitalRead(micpin) == 1)
          {
            bouncing = true;
            lastDebounceSet = false;
            //Serial.println("bouncing true");
          }
        }
      }
        
        //Serial.println("Gebounced!!!!!");
  
      if(!bouncing && startMeasured && lastDebounceSet)
      {
        //Serial.println("test!");
            
        //Serial.println("checking lenght of clap");
        firstClapEnd = millis();
        //Serial.print("Start Clap: ");
        //Serial.println(firstClapStart);
        //Serial.print("End Clap: ");
        //Serial.println(firstClapEnd);
        //Serial.print("Time difference: ");
        //Serial.println(firstClapEnd - firstClapStart);

        lastDebounceSet = false;
        startMeasured = false; 

        int timeDifference = firstClapEnd - firstClapStart;
        Serial.println(timeDifference);
        
        if( (timeDifference > 290) && (timeDifference < 310) )
        {
          //Serial.println("signal long and short enough");
          eventstatus = 1;  
        } 
      }
    }
  

  if(eventstatus == 1)
  {
    Serial.println("eventstatus 2 hurrayy");
    /*
    for(int n=0; n<250; n++)
    {
      delay(1);
      sensorstatus = digitalRead(micpin);
      if(sensorstatus == 1)
      {
        Serial.println("high again");
        eventstatus = 3;
        break;
      }
    }*/
  }
  
/*
  if(eventstatus == 3)
  {
    Serial.println("shouting led");
    digitalWrite(ledpin, !digitalRead(ledpin));
  }



/*
  if(eventstatus == 1)
  {
    do
    {
      sensorstatus = digitalRead(micpin);
      if(sensorstatus != lastsensorstatus)
      {
        lastDebounceTime = millis();
      }
      
      if((millis() - lastDebounceTime) > debounceDelay)
      {
        eventstatus = 2;
        Serial.println("Signal wurde gedebounced");
      }
    }while(eventstatus == 1);
  }


  if(eventstatus == 2)
  {
    for(int n=500; n>0; n--)
    {
      delay(1);
      sensorstatus = digitalRead(micpin);
      if(sensorstatus == HIGH)
      {
        eventstatus = 3;
        break;
      }
    }
  }

  if(eventstatus == 3)
  {
    digitalWrite(ledpin, !digitalRead(ledpin));
  }
  */
}
