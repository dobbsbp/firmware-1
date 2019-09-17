void setup() {
  // put your setup code here, to run once:
  // pinMode(A4, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(13, LOW);
  // digitalWrite(12, LOW);
  // analogWrite(A5, 0);
  Serial.println(digitalRead(3));
  delay(200);
}
