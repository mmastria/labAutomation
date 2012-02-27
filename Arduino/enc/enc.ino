#define ENCODER 2
unsigned long encoder = 0;

void encoderPinChange() {
  encoder++;
}

void setup() {
  attachInterrupt(0, encoderPinChange, CHANGE);
  Serial.begin(57600);
  Serial.println("encoder test");
}

void loop() {
  Serial.print("Encoder: ");
  Serial.println(encoder);
  delay(1000);
}

