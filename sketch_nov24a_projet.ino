#include <Servo.h>
#include <LiquidCrystal.h>

//afficheur LCD
const int rs=13;
const int enable=12;
const int d4=11;
const int d5=10;
const int d6=9;
const int d7=8;
LiquidCrystal lcd(rs,enable,d4,d5,d6,d7); // liaison 4 bits de données

//broches capteur de distance
const int TRIG_PIN=4;
const int ECHO_PIN=3;

//servo moteur
Servo monServo;     // on crée l'objet monServo

//variables calcul distance
long dureeEcho, distance;

//variable pin buzzer 
const int buzzerPin = A5;


void setup()
{
   //servo moteur
  monServo.attach(2);           // on définit le Pin utilisé par le servomoteur
  monServo.write(0);
  
  //potentiomètre
  pinMode(A0, INPUT);
  
  //afficheur LCD
  lcd.begin(16,2);
  lcd.write("Initialisation...");
  //Initialise les broches
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);      // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);
  
  //Port série
  Serial.begin(9600);
  Serial.println("Initialisation...");
  
  //LEDs
  pinMode(7, OUTPUT);         //led gauche
  pinMode(6, OUTPUT);         //led milieu
  pinMode(5, OUTPUT);         //led droite
  
  //Buzzer
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{ 
  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  dureeEcho=pulseIn(ECHO_PIN, HIGH);  //microsecondes
  
  // 3. Calcul la distance à partir du temps mesuré
  distance=(dureeEcho/2) / 29.1;    //calcul distance en cm
  Serial.print(distance);
  Serial.println(" cm");
  lcd.clear();
  lcd.print(distance);
  lcd.print(" cm");
  
  if (distance >=0 && distance<5){
    digitalWrite(7, HIGH);        //led gauche
    digitalWrite(6, HIGH);        //led milieu
    digitalWrite(5, HIGH);        //led droite
    monServo.write(150);
    analogWrite(buzzerPin, 255);
    delay(1000);
    analogWrite(buzzerPin, 0);
    delay(4000);
    
  }
  if (distance >=5 && distance<15){
    digitalWrite(7, HIGH);        //led gauche
    digitalWrite(6, HIGH);        //led milieu
    digitalWrite(5, LOW);         //led droite
    monServo.write(90);
    delay(5000);
    
  } 
  if (distance >=15){
    digitalWrite(7, HIGH);        //led gauche
    digitalWrite(6, LOW);         //led milieu
    digitalWrite(5, LOW);         //led droite
    monServo.write(30);
    delay(5000);
  }
}
