/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/
#define PWM_PIN 3
#define DIR_PIN 2
#define NAV_OUTPUT A1


  /*float system_Voltage = 5;
  float neutral = 0.204;//volts
  float forward = 0.244;
  float reverse = 0.146;
  */
  /*//for PIXhawk
  float system_Voltage = 3.3;
  float neutral = 0.204;//volts
  float forward = 0.244;
  float reverse = 0.1;
  */

  //for navigator board
  float system_Voltage = 3.3;
  float neutral = 0.9;//volts
  float forward = 1;
  float reverse = 0.6;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial1.begin(9600);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);

  //status on
  digitalWrite(A3,HIGH);
  delay(1000);
  //status off
  digitalWrite(A3,LOW);
  
}

// the loop routine runs over and over again forever:
void loop() {
  float sensorValue = analogRead(NAV_OUTPUT);
  float voltage = sensorValue / 1024 * system_Voltage ;
  Serial1.println(voltage);

  if(voltage > forward){
    digitalWrite(PWM_PIN,HIGH);//if forward
    digitalWrite(DIR_PIN,HIGH);
    digitalWrite(A3,HIGH);//if forward
    digitalWrite(A2,HIGH);
    Serial1.println("FORWARD");
  } else if(voltage < 0.04){
    digitalWrite(PWM_PIN,LOW);//if no power
    digitalWrite(DIR_PIN,LOW);
    digitalWrite(A3,LOW);//if forward
    digitalWrite(A2,LOW);
    Serial1.println("NO SIGNAL");
  } else if(voltage < reverse){
    digitalWrite(PWM_PIN,HIGH);//if reverse
    digitalWrite(DIR_PIN,LOW);//if reverse
    digitalWrite(A3,HIGH);//if forward
    digitalWrite(A2,LOW);
    Serial1.println("REVERSE");
  } else {
    digitalWrite(PWM_PIN,LOW);//if neutral
    digitalWrite(DIR_PIN,LOW);
    digitalWrite(A3,LOW);//if forward
    digitalWrite(A2,LOW);
    Serial1.println("NEUTRAL");
  }
  //wait
  //digitalWrite(A3,HIGH);
  delay(100);
  //digitalWrite(A3,LOW);
  //delay(100);
  
}
