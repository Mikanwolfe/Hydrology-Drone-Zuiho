

int sensorLED = A0;
int ledLight = 7;
int ledDiffuse = 8;

int sensorValue=0; // Direct

int diffuseValue = 0;
int directValue = 0;

int sensorOffset = 0;
int diffuseOffset = 0;

int ambientOffset = 0;

int constLightLevel = 0;

float sensorPercentageL; // light
float sensorPercentageA; // ambience
float sensorPercentageD; // diffuse

float difference;

int controlDirect = 35; // this is the amount of light received by the sensor as it passed through water; after you subtract the ambient.
int controlDiffuse = 62;


void setup() {
  //i should start by measuring water

  //this program will assume the system is in a constant dark environment. Thusly, I will need to hard-code tap water turbidity.
  //thusly, there is no real need for offset.
  Serial.begin(9600);
  pinMode(ledLight, OUTPUT);
  pinMode(ledDiffuse, OUTPUT);
  
  /*
  sensorValue = analogRead(sensorLED);
  sensorValue = 1023 - sensorValue;
  sensorOffset = sensorValue;
  
  
  digitalWrite(ledDiffuse, HIGH);
  delay(50);
  sensorValue = analogRead(sensorLED);
  sensorValue = 1023 - sensorValue;
  diffuseOffset = sensorValue;
  diffuseOffset = sensorValue + 30;
  digitalWrite(ledDiffuse, LOW);
  
  digitalWrite(ledLight, HIGH);
  delay(50);
  sensorValue = analogRead(sensorLED);
  sensorValue = 1023 - sensorValue;
  constLightLevel = sensorValue;
  digitalWrite(ledLight, LOW);
  */
}

void loop() {
  
  
  //read ambient
  sensorValue = analogRead(sensorLED);
  sensorValue = 1023 - sensorValue - sensorOffset;
  
  //since we're in darkness, subtract the ambience from the light received. Thusly, int ambient offset
  
  ambientOffset = sensorValue;
  
  Serial.print("Ambient Offset: ");
  Serial.println(ambientOffset);
  
  /*
  sensorPercentageA = ((float)sensorValue / (float)(1023-sensorOffset)) * 100.0;
  
  if (sensorPercentageA < 0) {
    sensorPercentageA = 0;
  }
  
  Serial.print("Offset:");
  Serial.println(sensorOffset);
  
  Serial.print("Diffuse Offset:");
  Serial.println(diffuseOffset);
  //Serial.print("A: ");
  //Serial.println(sensorValue);
  */
  
  
  //read the light BLOCKED. Thusly, I will have to find the value of Light through NORMAL water.
  
  digitalWrite(ledLight, HIGH);
  delay(100); // make sure the LED is on.
  sensorValue = analogRead(sensorLED);
  sensorValue = 1023 - sensorValue - sensorOffset;
  
  sensorValue = sensorValue - ambientOffset;
 
  
  sensorPercentageL = ((float)sensorValue / (float)(constLightLevel)) * 100.0;
  if (sensorPercentageL < 0) {
    sensorPercentageL = 0;
  }
  delay(50);
  digitalWrite(ledLight, LOW);
  Serial.print("L: ");
  Serial.println(sensorValue);
  directValue = sensorValue;
  
  //read the diffuse
  digitalWrite(ledDiffuse, HIGH);
  delay(100); // make sure the LED is on.
  sensorValue = analogRead(sensorLED);
  sensorValue = 1023 - sensorValue - diffuseOffset;
  sensorValue = sensorValue - ambientOffset; // as ambient is complete darkness, just remove the excess light.
  // sensorvalue = amount of diffuse light received by the LED. Increase = more Diffuse.
  
  
  /*
  sensorPercentageD = ((float)sensorValue / (float)(1023-diffuseOffset)) * 100.0;
  if (sensorPercentageD < 0) {
    sensorPercentageD = 0;
  }
  */
  
  delay(50);
  digitalWrite(ledDiffuse, LOW);
  Serial.print("D: ");
  Serial.println(sensorValue);
  diffuseValue = sensorValue;
  
  //time for maths!
  
  //assuming the thing is more turbid than normal water...
  //Let's work with direct:
  
  /*
  
  Therefore the system should measure the direct light less than the current set value. Thusly,
  relativelevel = control - current
  relativepercentage = control/current*100 (this shall be done later)
  
  Diffuse should be the amount increased;
  thusly,
  relativelevel = current - control.
 
  
  */
  
  int relativeDirect = controlDirect - directValue;
  int relativeDiffuse = diffuseValue - controlDiffuse;
  
    
   Serial.println(" ");
   
  Serial.print("R.L: ");
  Serial.println(relativeDirect);
    
  Serial.print("R.D: ");
  Serial.println(relativeDiffuse);
  
     Serial.println(" ");
  
      if (relativeDiffuse < 0) {
      Serial.println("Relative diffuse is measuring an opaque object.");
    };
    
    if (relativeDirect < 0) {
      Serial.println("Relative direct is measuring clear water");
    };
  
  /*
  difference = (float)sensorPercentageA - (float)sensorPercentage;
  if (difference < 0) {
    difference = 0;
  }
  
  Serial.println(sensorPercentage);
  Serial.println(sensorPercentageA);
  
  //Serial.println(" ");
  //Serial.print("Ambient (current light): ");
  //Serial.println(sensorPercentageA);
  Serial.print("Diffuse (light received): ");
  Serial.println(sensorPercentageD);
  Serial.print("Direct (light blocked): ");
  Serial.println(sensorPercentageL);
  Serial.println(" ");
  
  Serial.println(" ");
  Serial.print("% Difference = (Direct light blocked): ");
  Serial.println(difference);
  Serial.print("% of Diffuse light dect.: ");
  Serial.println(sensorPercentageD);
  Serial.println(" ");
  */
  
  /*
  if (sensorPercentage > 0) {
    Serial.print("Current Ambient Level: ");
    Serial.println(sensorPercentageA);
    Serial.print("Current Light Level: ");
    Serial.println(sensorPercentage);
  } else {
    Serial.print("Current Light Level: 0.00% with a value of ");
    Serial.println(sensorValue);
  }
  */
  delay(2000);
}

