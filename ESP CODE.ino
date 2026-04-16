#define TRIG_PIN 5
#define ECHO_PIN 18
#define RELAY_PIN 23

long duration;
float distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH); // Relay OFF (active LOW)
  Serial.begin(115200);
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo time
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance (cm)
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  // If hand detected within 10 cm
  if (distance > 0 && distance < 10) {
    Serial.println("Hand Detected → Pump ON");

    digitalWrite(RELAY_PIN, LOW); // Pump ON
    delay(1000);                  // Dispense time

    digitalWrite(RELAY_PIN, HIGH); // Pump OFF
    delay(2000);                  // Avoid repeated triggering
  }

  delay(200);
}
