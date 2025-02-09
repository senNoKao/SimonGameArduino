#include "pitches.h"

int led[4] = {27,29,31,33};
int bp[4] = {11,10,9,8};

int buzzer = 25;
int melody[] = {
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_C5};
int defeatMelody[] = {
  NOTE_D2, NOTE_E3, NOTE_F4, NOTE_C5};
int duration = 300;  

int passage = 1;
int k = 0;

int stage[5] = {5,6,7,9,12};
int level = 0;


void setup() {
  
  Serial.begin(9600);
  
  for(int i=0; i<4; i++){
    pinMode(led[i],OUTPUT);
  }
  for(int i=0; i<4; i++){
    pinMode(bp[i],INPUT);
  }

  pinMode(buzzer,OUTPUT);

}

void loop() {    
    randomSeed(analogRead(0));//mélange la fonction random
    
    int sequence[stage[level]];
    //Assignation de la séquence de couleurs aléatoires :
    for(int i=0; i<stage[level]; i++){
      sequence[i] = random(0,4);
    }

    while(true){
      //Affichage de cette séquence (1, 12, 123, 1234,...)
      while(k < passage){
        digitalWrite(led[sequence[k]],HIGH);
        tone(buzzer, melody[sequence[k]], duration);
        delay(duration);
        digitalWrite(led[sequence[k]],LOW);
        delay(duration);
        k++;
      }
      k = 0;
  
  
      //Le joueur reproduit la suite avec les boutons
      while(k < passage){
        
        //Attendre l'appui d'un bouton
        while(digitalRead(bp[0])==0 and digitalRead(bp[1])==0 and digitalRead(bp[2])==0 and digitalRead(bp[3])==0){
         
        }
        
    
        //On vérifie si le bouton pressé correspond à la séquence
        if(digitalRead(bp[sequence[k]])==1){//Si le bouton correspond bien à la séquence
          digitalWrite(led[sequence[k]],HIGH);
          tone(buzzer, melody[sequence[k]], duration);
          delay(duration);
          digitalWrite(led[sequence[k]],LOW);
        }
        else{//Si le bouton ne correspond pas à la séquence
          for(int i=0; i<4; i++){
            digitalWrite(led[i],HIGH);
          }
          delay(200);
          for(int i=4; i>=0; i--){
            digitalWrite(led[i],LOW);
            tone(buzzer, defeatMelody[i], duration);
            delay(duration);
            
          }
          passage = 0;
          k = 0;
          delay(300);
          break; 
        }
        delay(200);
    
        k++;
        
      }
      k = 0;
      
      passage++;

      //Si toutes les couleurs ont été faites on sort de la boucle et on créé une nouvelle séquence
      //Célébration de la réussite du niveau
      if(passage>stage[level]){
        passage = 0;
        for(int i=0; i<4; i++){
          for(int k=0; k<4; k++){
            digitalWrite(led[k],HIGH);
            tone(buzzer, melody[k], 100);
            delay(100);
            digitalWrite(led[k],LOW);
          }
        }
        level++;
        delay(1500);
        break;
      }
      delay(800);
    }
  }
