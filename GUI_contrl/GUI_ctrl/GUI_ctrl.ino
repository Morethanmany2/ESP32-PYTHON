int laserPin = 25;

void setup() {
  Serial.begin(9600);
  pinMode(laserPin, OUTPUT);

  digitalWrite(laserPin, HIGH); // OFF initially (ACTIVE LOW)
}

void loop() {

  if (Serial.available()) {

    String cmd = Serial.readStringUntil('\n');
    cmd.trim();  // remove spaces/newline

    if (cmd == "ON") {
      digitalWrite(laserPin, HIGH);   // Laser ON
    }

    else if (cmd == "OFF") {
      digitalWrite(laserPin, LOW);  // Laser OFF
    }

    else if (cmd == "BLINK") {
      for (int i = 0; i < 5; i++) {
        digitalWrite(laserPin, LOW);   // ON
        delay(300);
        digitalWrite(laserPin, HIGH);  // OFF
        delay(300);
      }
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
