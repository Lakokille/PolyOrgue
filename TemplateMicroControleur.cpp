#include <Arduino.h>

//Définitions des pins
#define INPUT_1 34
#define INPUT_2 35
#define INPUT_3 32
#define INPUT_4 25
#define INPUT_5 26
#define INPUT_6 27

//Le processeur ne va pas tenter d'optimisation sur ces variables en les fixant avant chaque loop
//permet de modifier la valeur même dans la loop (lisible à tout moment)
volatile int s1 = 0;
volatile int s2 = 0;
volatile int s3 = 0;

// ISR = service des interruptions
//IRAM_ATTR permet de stocker dans la RAM et non dans la flash
void IRAM_ATTR handleInput1() { s1 = digitalRead(INPUT_1); }
void IRAM_ATTR handleInput2() { s2 = digitalRead(INPUT_2); }
void IRAM_ATTR handleInput3() { s3 = digitalRead(INPUT_3); }

void setup() {
  //Vitesse du port serie en bit/s (default = 115200), 1 octet = 1 start bit + 8 bits de data + 1 stop bit
  Serial.begin(115200);

  //Ici on ne met pas de pull-up car on a déjà une résistance externe avec une led.
  pinMode(INPUT_1, INPUT);
  pinMode(INPUT_2, INPUT);
  pinMode(INPUT_3, INPUT);

  pinMode(INPUT_4, INPUT);
  pinMode(INPUT_5, INPUT);
  pinMode(INPUT_6, INPUT);

  // Attache des interruptions
  //digitalPinToInterrupt permet de convertir le pin logique en numéro d'interruption interne
  //Le troisième paramètre est le mode de déclenchement : RISING, FALLING, CHANGE, LOW, HIGH.
  attachInterrupt(digitalPinToInterrupt(INPUT_1), handleInput1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INPUT_2), handleInput2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INPUT_3), handleInput3, CHANGE);
}

//millis attend un unsigned long (ce qui signifie entier positif sur 4 octet, rq : le int classique est aussi sur 4 octet sur ESP32 (32 bits))
unsigned long lastRead = 0;
int s4, s5, s6;

void loop() {
  // Lecture secondaire toutes les 50ms (volume / bouton), millis() renvoie le temps depuis la mise sous tension de l'ESP
  if (millis() - lastRead > 50) {
    lastRead = millis();
    s4 = digitalRead(INPUT_4);
    s5 = digitalRead(INPUT_5);
    s6 = digitalRead(INPUT_6);
  }

  // Affichage ou traitement
  Serial.print(s1);
  Serial.print(s2); 
  Serial.print(s3);
  Serial.print(s4); 
  Serial.print(s5); 
  Serial.println(s6);

  delay(5); // boucle rapide pour les touches
}
