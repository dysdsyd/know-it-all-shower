
const int echo = 8, Trig = 9;
float tempC;
int reading,del=460,del2=0;
int tempPin = 0;
int i=0;
void setup() 
{
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);//for motors
  analogReference(INTERNAL);
// initialize serial communication:
Serial.begin(9600);
pinMode(Trig, OUTPUT);
pinMode(echo, INPUT);
}


void loop()
{
// establish variables for duration of the ping,
// and the distance result in inches and centimeters:
long duration, inches, cm,x;
// The PING))) is triggered by a HIGH pulse of 10 microseconds.
// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
digitalWrite(Trig, LOW);
delayMicroseconds(2);
digitalWrite(Trig, HIGH);
delayMicroseconds(10);
digitalWrite(Trig, LOW);
// The echo pin is used to read the signal from the PING))): a HIGH
// pulse whose duration is the time (in microseconds) from the sending
// of the ping to the reception of its echo off of an object.
duration = pulseIn(echo, HIGH);
// convert the time into a distance
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);
reading = analogRead(tempPin);
tempC = reading / 9.31;
Serial.print(tempC);
Serial.print(cm);
Serial.print("cm");
Serial.println();
Serial.print(i);
Serial.println();
Serial.print(del);
Serial.println();
Serial.print(del2);
Serial.println();

if(tempC>=15)// for setting angles according to temperature 

{
  del=480;//for around 460 degree
  del2=0;
}
if(tempC<15&&tempC>8)
{
  del=480;
  del2=59;//around 45 degree
}
if(tempC<=8)
{
  del=480;
  del2=130;//around 90 degree
  
}

x=cm;

if(i==0)
{
if(x>=60)
{
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(11,LOW);
 digitalWrite(10,LOW); 

}
if(x<60)
{
  
 digitalWrite(13,HIGH);
 digitalWrite(12,LOW);
 delay(del);
 digitalWrite(10,HIGH);
 digitalWrite(11,LOW); 
 delay(del2);
 i=1;
}
}

if(i==1)
{
if(x>=60)
{
 digitalWrite(12,HIGH);
 digitalWrite(13,LOW);
 delay(del);
 if(del2==0)
 {
 digitalWrite(11,LOW);
 digitalWrite(10,LOW);
 } 
 else
{
 digitalWrite(11,HIGH);
 digitalWrite(10,LOW);
 delay(del2);
}
 i=0;
}
if(x<60)
{
 digitalWrite(12,LOW);
 digitalWrite(13,LOW);
 digitalWrite(11,LOW);
 digitalWrite(10,LOW);   
 
}
}

delay(50);

}






long microsecondsToInches(long microseconds)
{
// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second). This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
return microseconds / 74 / 2;
}




long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}
