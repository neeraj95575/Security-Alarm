//security alarm.


const int pingPin = 5;   //trig pin of arduino

int inPin = 6;    //echo pin of arduino.
 
//range in cm which is considered safe to enter, anything
//coming within less than 5 cm triggers red LED
int safeZone = 95;
int tonepin=8;
//LED pin numbers
int greenLed = 3;
int redLed = 2;
 
void setup() {
  // initialize serial communication
  Serial.begin(9600);
}
 
void loop()
{
  //raw duration in milliseconds, cm is the
  //converted amount into a distance
  long duration, cm;
 
  //initializing the pin states
  pinMode(pingPin, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);  
  pinMode(tonepin, OUTPUT);
  //sending the signal, starting with LOW for a clean signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
 
  //setting up the input pin, and receiving the duration in
  //microseconds for the sound to bounce off the object infront
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
 
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
 
  //printing the current readings to ther serial display
  //Serial.print(cm);
  //Serial.print("cm");
  //Serial.println();
 
  //checking if anything is within the safezone, if not, keep
  //green LED on if safezone violated, activate red LED instead
  if (cm > safeZone)
  {
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
  }
  else
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    for(int i=0;i<20;i++)
    {tone(tonepin, 500);   //you can change the sound by changing numbers.
    delay(50);
    tone(tonepin, 400);    //you can change the sound by changing numbers.
    delay(50);
    }

    noTone(tonepin);
  }
 
  delay(100);
}
 
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
