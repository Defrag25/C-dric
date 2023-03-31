// BIBLIOTHEQUES
// ARDUINO Nano
// ATmega328P
// sur COM3


///////////////////
// Modifications //
///////////////////
// Version 0: Initial
// Version 1: décomposaition boucle principale en sous programme + (Lib_x.h)
//            aucune autre modif


#include <Wire.h>
#include "Lib_Variables.h"
#include "Lib_LCD.h"
#include "Lib_ECS.h"
#include "Lib_Calcul.h"
#include "Lib_Mesures.h"


void setup()
{
Serial.begin(115200);
  
// DECLARATION ENTRÉES / SORTIES --------------------------------------------------------------------------------------
pinMode (2, INPUT_PULLUP); // Digital Input Forcage ECS (Câblage sur D2)
pinMode (3, INPUT_PULLUP); // Digital Input Bouton sélection écran LCD (Câblage sur D3)
pinMode (4, INPUT_PULLUP); // Digital Input Bouton sélection écran LCD (Câblage sur D4) 
pinMode (5, INPUT_PULLUP); // Digital Input Bouton poussoir forçage ECS(Câblage sur D5)
pinMode (LED_BUILTIN, OUTPUT);

 Affichage_Init();
 Affichage_Presentation();
 ECS_Start();
 
}

void loop()
{


// Mesures ( PZEM 1 Maison ) et (PZEM 2 Photovoltaique)
  PZEM_MesureMaison();
  PZEM_MesurePhotovoltaique();

//CALCUL SURPLUS SOLAIRE DISPONIBLE------------------------------------------------------------------------------------
  P3_Delta = P2-P1;

// REGULATION SIMPLE -------------------------------------------------------------------------------------------------
  process_calcul();

  CptEnergieECS = CptEnergieEcsSolaire + CptEnergieEcsEDF; 

  CptCycles = CptCycles +1;


// FORCAGE ECS A 100% -------------------------------------------------------------------------------------------------
if (digitalRead(5)==LOW)    {             // appui sur BP forçage ECS
   
  CptDemandeForcageECS = 5400;           // consigne temps forçage manuel ECS 3600*3/tps de cycle (environs 3h)
  }

 if (CptDemandeForcageECS > 0 || (((digitalRead(2)==LOW) &&  CptEnergieECS < 6000)))    {
  ConsVarECS = 100;
  CptDemandeForcageECS = CptDemandeForcageECS -1;  // décomptage temps forçage manuel ECS
  }
  
else   {
  ConsVarECS = ConsVarECS_Calculee;
  }

Serial.print (ConsVarECS);


// BOUTON SELECTION ECRAN AFFICHAGE LCD -------------------------------------------------------------------------------

if ((digitalRead(3)==LOW) && (digitalRead(4)==HIGH))
  {
  ValeurBp =1; // Affichage écran 1
  }
if ((digitalRead(3)==LOW) && (digitalRead(4)==LOW))
  {
  ValeurBp =2; // Affichage écran 2
  }
if ((digitalRead(3)==HIGH) && (digitalRead(4)==LOW))
  {
  ValeurBp =3; // Affichage écran 3
  }  


//AFFICHAGE LCD -------------------------------------------------------------------------------------------------------
  Affichage();

//Transmission valeur ECS-----------------------------------------------------------------------------------------------
  ECS_Send(ConsVarECS);




Serial.println();

delay(2000);           // Si modification voir CptEnergieECS

}
