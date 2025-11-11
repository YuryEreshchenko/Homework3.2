const int RedLEDPin   = 9;
const int GreenLEDPin = 10;
const int BlueLEDPin  = 11;

const int pushButton  = 2;

int  buttonState    = 0;
bool buttonPressed  = false;

unsigned long pressingTime           = 0;
const long     longPressInterval     = 1000;  // ms

int currentMode = 1;  // 1 = ON, 2/3/4 = blinking speeds

unsigned long blinkTimer = 0;
bool          blinkOn    = true;

void setup() {
  Serial.begin(9600);

  pinMode(RedLEDPin,   OUTPUT);
  pinMode(GreenLEDPin, OUTPUT);
  pinMode(BlueLEDPin,  OUTPUT);
  pinMode(pushButton,  INPUT);
}

void loop() {
  int clickType = checkButton();

  // Change mode on any valid click
  if (clickType == 1) {
    currentMode++;
    if (currentMode > 4) {
      currentMode = 1;
    }
  }

  // Run current mode
  if (currentMode == 1) {
    // Constant ON (inverted LED: 0 = ON)
    PowerLEDControl(0, 0, 0);
  }
  else if (currentMode == 2) {
    Blinking(1000);  // slow
  }
  else if (currentMode == 3) {
    Blinking(500);   // medium
  }
  else if (currentMode == 4) {
    Blinking(50);    // fast
  }
}

// Returns 1 on short *or* long press release, 0 otherwise
int checkButton() {
  int clickType = 0;

  // Inverted logic: button wired so !digitalRead() is pressed
  buttonState = !digitalRead(pushButton);
  delay(5);  // simple debounce

  if (buttonState == HIGH && !buttonPressed) {
    pressingTime  = millis();
    buttonPressed = true;
  }

  if (buttonState == LOW && buttonPressed) {
    unsigned long currentTime = millis();

    if (currentTime - pressingTime < longPressInterval) {
      Serial.println("Short click");
      clickType = 1;
    } else {
      Serial.println("Long Press");
      clickType = 1;
    }

    buttonPressed = false;
  }

  return clickType;
}

void PowerLEDControl(int red, int green, int blue) {
  analogWrite(RedLEDPin,   red);
  analogWrite(GreenLEDPin, green);
  analogWrite(BlueLEDPin,  blue);
}

void Blinking(int interval) {
  unsigned long currentTime = millis();

  if (currentTime - blinkTimer > (unsigned long)interval) {
    if (blinkOn) {
      // Inverted LED: 0 = ON
      PowerLEDControl(0, 0, 0);
    } else {
      // Inverted LED: 255 = OFF
      PowerLEDControl(255, 255, 255);
    }

    blinkOn    = !blinkOn;
    blinkTimer = currentTime;
  }
}
