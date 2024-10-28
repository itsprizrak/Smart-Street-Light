#include <SoftwareSerial.h>
SoftwareSerial SwSerial(2, 3); // RX, TX
#include <BlynkSimpleStream.h>

char auth[] = "ac376837ffbb429595877bde9133fbfa";

//Pin Setup
int ir1 = 6;
int ir2 = 7;
int ir3 = 8;

int led1 = 9;
int led2 = 10;
int led3 = 11;

int com = 4;

int c_class = 5;

int s = 0;

void setup()
{
  Serial.begin(9600);

  SwSerial.begin(9600);
  Blynk.begin(Serial, auth);

  //Pin configaratioons
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(c_class, OUTPUT);
}

void street()
{
  int irval1 = digitalRead(ir1);
  int irval2 = digitalRead(ir2);
  int irval3 = digitalRead(ir3);

  if (irval1 == HIGH)
  {
    analogWrite(led1, 255);
  }
  else
  {
    analogWrite(led1, 20);
  }
  if (irval2 == HIGH)
  {
    analogWrite(led2, 255);
  }
  else
  {
    analogWrite(led2, 20);
  }
  if (irval3 == HIGH)
  {
    analogWrite(led3, 255);
  }
  else
  {
    analogWrite(led3, 20);
  }
}

WidgetTerminal terminal(V1); // It is the widget to send the data on or off through blynk app

BLYNK_WRITE(V1)
{
  if (String("on") == param.asStr()) // Getting data from blynk app, if the data received is on then the entire system turns on
  {
    s = 1;
    Blynk.virtualWrite(V0, "SYSTEM ON"); // Printing on LCD display on Blynk app
  }
  else if (String("off") == param.asStr())// Getting data from blynk app, if the data received is on then the entire system turns off
  {
    s = 2;
    Blynk.virtualWrite(V0, "SYSTEM OFF");// Printing on LCD display on Blynk app
  }
  else if (String("break") == param.asStr())// Getting data from blynk app, if the data received is on then the entire system turns off
  {
    s = 3;
  }
}

void loop()
{
  Blynk.run();

  if (s == 1)
  {
    street();
  }
  else if (s == 2)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }

  else if (s == 3)
  {
    delay(2000);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay(1000);
    Blynk.virtualWrite(V0, "Circuit Break");
  }

  int command = digitalRead(com);
  if(command == HIGH)
  {
    digitalWrite(c_class, HIGH);
  }
  else
  {
    digitalWrite(c_class, LOW);
  }
}
