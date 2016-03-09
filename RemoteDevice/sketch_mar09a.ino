enum ErrorCode
{
  OK,
  NO_ARG
};

//#define DBG_LOG

#ifdef DBG_LOG
#define LOG(x) Serial.print(x)
#define LOGln(x) Serial.println(x)
#else
#define LOG(x)
#define LOGln(x)
#endif

const int ledPin = 13;

const int idPin0 = 5;
const int idPin1 = 6;
const int idPin2 = 7;

const int max_message_len = 128;

char message_raw[max_message_len];
char message[max_message_len];
int message_len = 0;


void setup(){
  message_raw[0]='\0';
  pinMode(ledPin, OUTPUT);
  pinMode(idPin0, INPUT);
  pinMode(idPin1, INPUT);
  pinMode(idPin2, INPUT);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
  Serial.begin(9600);
}

void loop(){
  if (Serial.available())  {
    if (message_len > max_message_len - 2)
    { //reset
      message_len = 0;
    }
    message_raw[message_len] = Serial.read();
    message_raw[message_len+1] = '\0';
    message_len++;

    if (message_raw[message_len-1] == ';')
    {
      LOG("Received message: "); LOGln(message_raw);
      int args_no = prepareArgs();
      LOG("args_no:"); LOGln(args_no);

      
      char* arg0 = getArg(0);
      LOG("arg0:"); LOGln(arg0);
            
      if (strcmp(arg0, "getId") == 0)
      {
        getId();
      }
      else if (strcmp(arg0, "setPin") == 0)
      {
        setPin();        
      }
      else if (strcmp(arg0, "setPinMode") == 0)
      {
        setPinMode();        
      }
      else if (strcmp(message, "dupa") == 0)
      {
        Serial.print("dupa");
      }

      Serial.print(";");
      message_len = 0;
      message_raw[message_len]='\0';
    }
  }
  delay(20);
}

int prepareArgs()
{
  int args_no = 0;
  int pos = 0;
  strcpy(message, message_raw);
  
  while(pos < message_len)
  {
    if (message[pos] == '-' || message[pos] == ';' )
    {
      args_no++;
      message[pos] = '\0';
    }

    pos++;
  }

  return args_no;
}

char* getArg(int arg)
{
  int count = 0;
  int pos = 0;
  int arg_start = 0;
  while (count < arg && pos < message_len)
  {
    if (message_raw[pos++] == '-')
    {
      count++;
      arg_start = pos;
    }
  }

  return message + arg_start;
}

ErrorCode getId()
{
  int id = (digitalRead(idPin2) << 2 | digitalRead(idPin1) << 1 | digitalRead(idPin0));
  Serial.print(id);
}

ErrorCode setPinMode()
{
  LOG("setPinMode");
  char* arg1 = getArg(1);
  if (!(*arg1))
  {
    LOG("No arg1");
    return NO_ARG;
  }
  LOG("arg1:"); LOG(arg1);
  
  int pin = atoi(arg1);
  LOG("Pin:"); LOGln(pin);
  
  char* arg2 = getArg(2);
  if (!(*arg2))
  {
    LOG("No arg2");
    return NO_ARG;
  }
  LOG("arg2:"); LOGln(arg2);
  int mode = atoi(arg2);
  LOG("state:"); LOGln(mode);

  if (mode == 0)
    pinMode(pin, INPUT);
  else if (mode == 1)
    pinMode(pin, OUTPUT);
  else if (mode == 2)
    pinMode(pin, INPUT_PULLUP);

  return OK;
}

ErrorCode setPin()
{
  char* arg1 = getArg(1);
  if (!(*arg1))
  {
    LOG("No arg1");
    return NO_ARG;
  }
  LOG("arg1:"); LOGln(arg1);
  
  int pin = atoi(arg1);
  LOG("Pin:"); LOGln(pin);
  
  char* arg2 = getArg(2);
  if (!(*arg2))
  {
    Serial.print("No arg2");
    return NO_ARG;
  }
  LOG("arg2:"); LOGln(arg2);
  int state = atoi(arg2);
  LOG("state:"); LOGln(state);
  if (state == 0)
  {
    digitalWrite(pin, LOW);
  }
  else if (state == 1)
  {
    digitalWrite(pin, HIGH);
  }
  
  
  return OK;
}
