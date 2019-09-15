void setup() {
  // put your setup code here, to run once:
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(13, LOW);
  // digitalWrite(12, LOW);
  // analogWrite(A5, 0);
  analogWrite(A3, 255);
  delay(200);
}
