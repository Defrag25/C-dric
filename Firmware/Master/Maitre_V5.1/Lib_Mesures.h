//Librairie de gestion des mesures


#include <PZEM004Tv30.h>
PZEM004Tv30 pzem1(14,15); // Câblage sur A0/A1
PZEM004Tv30 pzem2(16,17); // Câblage sur A2/A3


void PZEM_MesureMaison(){

// Multimètre PZEM 1 Maison
 U1 = pzem1.voltage();               //exprimé en V
 I1 = pzem1.current();               //exprimé en A
 P1 = pzem1.power();                 //exprimé en W
 W1 = pzem1.energy();                //exprimé en Wh

if (isnan(U1) || isnan(I1) || isnan(P1)|| isnan(W1)) 
    {
    Serial.println("Erreur Lecture PZEM1");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print ("Erreur Lecture PZEM1");   
    return;
    }

}
void PZEM_MesurePhotovoltaique(){

// Multimètre PZEM 2 Photovoltaique
 U2 = pzem2.voltage();               //exprimé en V
 I2 = pzem2.current();               //exprimé en A
 P2 = pzem2.power();                 //exprimé en W 
 W2 = pzem2.energy();                //exprimé en Wh

if (isnan(U2) || isnan(I2) || isnan(P2)|| isnan(W2)) 
    {
    Serial.println("Erreur Lecture PZEM2");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print ("Erreur Lecture PZEM2");
    return;
    }
}
