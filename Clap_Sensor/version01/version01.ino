const int micpin = 7, ledpin=3;
const int clapdelay = 500;
int eventstatus=0;
bool sensorstatus=0, lastsensorstatus=HIGH;

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
    if(sensorstatus == 1)
    {
      eventstatus = 1;
      //Serial.println("eventstatus: 1");
    }
  }


  if(eventstatus == 1)
  {
      bool bouncing = false;
      sensorstatus = digitalRead(micpin);
      if(sensorstatus == 0)
      {
        lastDebounceTime = millis();
      }
      while((millis() - lastDebounceTime) < 250)
      {
        if(digitalRead(micpin) == 1)
        {
          bouncing = true;
          //Serial.println("bouncing true");
        }
      }

      if(bouncing)  //von der logik her müsste hier !bouncing stehen
      {
        //Serial.println("signal gedebounced");
        eventstatus = 2;
      }
  }

  if(eventstatus == 2)
  {
    for(int n=0; n<250; n++)
    {
      delay(1);
      sensorstatus = digitalRead(micpin);
      if(sensorstatus == 1)
      {
        //Serial.println("high again");
        eventstatus = 3;
        break;
      }
    }
  }

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
