void setup() {
  // put your setup code here, to run once:
 pinMode(13, OUTPUT);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(13, 0);
  delay(1000);
}
