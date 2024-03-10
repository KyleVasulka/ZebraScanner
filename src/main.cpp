#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);
void rotateStepper(int);
void home();

int dir_pin = 4;
int step_pin = 12;
int limit_pin = 16;
int pi_pin = 36;

int forward = LOW;
int backward = HIGH;

void setup()
{
  // put your setup code here, to run once:
  int result = myFunction(2, 3);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  pinMode(limit_pin, INPUT_PULLDOWN);
  pinMode(pi_pin, INPUT_PULLDOWN);
  Serial.begin(9600);
}

void loop()
{

  // Serial.println("Hello World");
  // put your main code here, to run repeatedly:
  while (true)
  {
    if (digitalRead(pi_pin) == HIGH)
    {
      // Pi just told us to do the thing
      home();
      digitalWrite(dir_pin, forward);
      rotateStepper(195);
      delay(1000);
      home();
    }
  }

  // Serial.println("going forward");
  // digitalWrite(dir_pin, HIGH);
  // rotateStepper(200);
  // delay(2000);

  // digitalWrite(dir_pin, LOW);
  // // Serial.println("going backward");
  // rotateStepper(200);
  // delay(2000);
}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}

// put function definitions here:
void rotateStepper(int steps)
{

  for (int i = 0; i < steps; i++)
  {
    digitalWrite(step_pin, HIGH);
    delay(1);
    digitalWrite(step_pin, LOW);
    delay(1);
  }
}

void home()
{

  if (digitalRead(limit_pin) == HIGH)
  {
    Serial.println("limit hit, unclick and reclick");
    // Serial.println("going forward");
    digitalWrite(dir_pin, forward);
    rotateStepper(100);
  }
  Serial.println("limit depressed, going back");
  // go back in until we hit the limit switch
  while (digitalRead(limit_pin) == LOW)
  {
    digitalWrite(dir_pin, backward);
    rotateStepper(1);
  }
}