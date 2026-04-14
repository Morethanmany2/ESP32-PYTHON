int laserPin = 25;

void setup() {
  Serial.begin(9600);
  pinMode(25, OUTPUT); // built-in LED
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();

    if (cmd == '1') {
      digitalWrite(laserPin, LOW);
    }
    else if (cmd == '0') {
      digitalWrite(laserPin, HIGH);
    }
  }
}

// int laserPin = 25;

// void setup() {
//   pinMode(laserPin, OUTPUT);
// }

// void loop() {
//   digitalWrite(laserPin, LOW);   // ON (reverse logic)
//   delay(1000);

//   digitalWrite(laserPin, HIGH);  // OFF
//   delay(1000);
// }
