
#define DATAPIN      A0
int value = 0;

int get_mainvalue();

void setup()
{
  Serial.begin(9600);
  Serial.println("sensor test");
}

void loop()
{
  Serial.println(get_mainvalue());
  
  delay(1000);

  
}

int get_mainvalue()
{
  value = analogRead(DATAPIN);

  return value;
}
