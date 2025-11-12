/*
  Basic RGB LED Button Control
  ----------------------------
  This program turns an RGB LED ON or OFF using a single push button.

  - When the button is pressed, the LED turns ON.
  - When released, the LED turns OFF.
  - Button state is printed to the Serial Monitor for debugging.

  Author: Yury Ereshchenko
  Date: 12/11/2025
*/
const int RedLEDPin = 9;
const int GreenLEDPin = 10;
const int BlueLEDPin = 11;

const int pushButton = 2;

int buttonState = 0;

void setup() {

  Serial.begin(9600);
  pinMode(RedLEDPin, OUTPUT);
  pinMode(GreenLEDPin, OUTPUT);
  pinMode(BlueLEDPin, OUTPUT);
  pinMode(pushButton, INPUT);

}

void loop() {

  buttonState = !digitalRead(pushButton);

  Serial.println(buttonState);
  delay(1);

  if (buttonState == HIGH){
    PowerLEDControl(0,0,0);
  }
  else {
    PowerLEDControl(255,255,255);
  }

}

void PowerLEDControl(int red, int green, int blue) {
  analogWrite(RedLEDPin, red);
  analogWrite(GreenLEDPin, green);
  analogWrite(BlueLEDPin, blue);
}