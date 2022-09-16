//CS - Headlight System Proof-of-Concept
//Victoria Rea Vastis

//Variables:
//These constants won't change!

const int piezoSensorPin = A0; //Defines A0 as the input pin for the piezo electri sensor

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Serial.begin - opens up a connection between the computer and arduino
                     //Allows me to see the analog inputs from the sensor
                     //9600 is the speed in bits/s

  pinMode(2, OUTPUT); //Sets pin 2 as a output pin
  pinMode(3, OUTPUT); //Sets pin 3 as a output pin
  pinMode(4, OUTPUT); //Sets pin 4 as a output pin
  pinMode(6, OUTPUT); //Sets pin 6 as a output pin

}

void loop() {
  // put your main code here, to run repeatedly:
  int piezoVoltage = analogRead(piezoSensorPin); //Reads analog values from piezo sensor pin
  Serial.println(piezoVoltage); //prints analog signal to serial monitor

// ON/OFF VARIANT 
// If the piezo sensor generates a voltage --> Turn LEDs on
  // if (piezoVoltage > 200) {
  //   digitalWrite(2,HIGH);
  //   digitalWrite(3,HIGH);
  //   digitalWrite(4,HIGH);
  //   digitalWrite(6,LOW);
  // }

  // else {
  //   digitalWrite(2,LOW);
  //   digitalWrite(3,LOW);
  //   digitalWrite(4,LOW);
  //   digitalWrite(6,HIGH); //Indicates no voltage change has been detected
  // }
// MORE VOLTAGE = MORE LIGHTS VARIANTS
// The more voltage the piezo sensor generates, the more LEDs turn on
  for (int a = 1; a <= 5; a++) {
    if (piezoVoltage > a * 100) {
      digitalWrite(a + 1, HIGH);
    } else {
      digitalWrite(a + 1, LOW);
    }
  }
}