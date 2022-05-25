const int NUM_SLIDERS = 4;
const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3};

int analogSliderValues[NUM_SLIDERS];
int buttonState = 1;
int prevButtonState = 1;
bool off = false;

void setup() { 
  for (int i = 0; i < NUM_SLIDERS; i++) {
    pinMode(analogInputs[i], INPUT);
  }

  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
}

void loop() {
  delay(10);
  buttonState = digitalRead(2);
  if(buttonState == LOW && buttonState != prevButtonState){//not the bestsolution, but works
    if(off)off = false;
    else off = true;
  }
  prevButtonState = buttonState;
  
  if(off){
    updateSliderValuesToOff();
    sendSliderValues();
    digitalWrite(3,1);
  }else{
    updateSliderValues();
    sendSliderValues(); // Actually send data (all the time)
    digitalWrite(3,0);
  }
}


void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = analogRead(analogInputs[i]);
  }
}
void updateSliderValuesToOff() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
     analogSliderValues[i] = 0;
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    builtString += String((int)analogSliderValues[i]);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}
