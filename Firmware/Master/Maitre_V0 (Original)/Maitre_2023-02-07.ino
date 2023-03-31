// BIBLIOTHEQUES
// ARDUINO Nano
// ATmega328P
// sur COM3

#include <PZEM004Tv30.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

PZEM004Tv30 pzem1(14,15); // Câblage sur A0/A1
PZEM004Tv30 pzem2(16,17); // Câblage sur A2/A3
LiquidCrystal_I2C lcd(0x27,20,4);  // Câblage sur A4/A5

// Définition des adresses logiques des esclaves I2C.
#define I2C_SLAVE_SCR 9

// DECLARATION ET INITIALISATION DES VARIABLES-------------------------------------------------------------------------
float U1 = 0;             //exprimé en V
float I1 = 0;             //exprimé en A
float P1 = 0;             //exprimé en W
float W1 = 0;             //exprimé en Wh

float U2 = 0;             //exprimé en V
float I2 = 0;             //exprimé en A
float P2 = 0;             //exprimé en W
float W2 = 0;             //exprimé en Wh

float P3_Delta = 0;            // Puissance Photovoltaïque - Puissance Maison (si >0 : surplus solaire)
float ConsVarECS_Calculee = 0; // Consigne variateur ECS calculée
int ConsVarECS = 0;            // Consigne Variateur ECS à envoyer
int ValeurBp = 1;              // Pour menu déroulant LCD
float CptEnergieEcsEDF =0;     // Comptage energie ECS sur EDF
float CptEnergieEcsSolaire =0; // Comptage energie ECS solaire
float CptEnergieECS = 0;       // Comptage energie Total pour le forcage ECS
int CptCycles = 0;             // Comptage nombre de cycle 
int CptDemandeForcageECS =0 ;  // Comptage forçage manuel ECS
int TpsCycle = 1.4610 + 2 ;    // Tps de cycle + Delay final
void setup()
{
Serial.begin(115200);
  
// DECLARATION ENTRÉES / SORTIES --------------------------------------------------------------------------------------
pinMode (2, INPUT_PULLUP); // Digital Input Forcage ECS (Câblage sur D2)
pinMode (3, INPUT_PULLUP); // Digital Input Bouton sélection écran LCD (Câblage sur D3)
pinMode (4, INPUT_PULLUP); // Digital Input Bouton sélection écran LCD (Câblage sur D4) 
pinMode (5, INPUT_PULLUP); // Digital Input Bouton poussoir forçage ECS(Câblage sur D5)
pinMode (LED_BUILTIN, OUTPUT);

// AFFICHEUR LCD ------------------------------------------------------------------------------------------------------
lcd.init();                         
lcd.backlight();                    
lcd.setCursor(0, 0);                
lcd.print("**                **");
lcd.setCursor(7,1);                 
lcd.print("Bonjour");
lcd.setCursor(8, 2);               
lcd.print("CATZ");
lcd.setCursor(0, 3);               
lcd.print("**                **");
delay(2000);

// Initialise la library Wire et se connecte au bus I2C en tant que maître 
Wire.begin();
  
   // débute de la communication avec un esclave (ouvre le stockage données à envoyer avec write)
    Wire.beginTransmission(I2C_SLAVE_SCR);
    // charge des octets pour une transmission du composant maître vers un composant esclave 
    Wire.write(0);
    // Termine la transmission avec un composant esclave sur le bus I2C qui a été débutée avec 
    // la fonction beginTransmission() 
    Wire.endTransmission();

}

void loop()
{
  
// Multimètre PZEM 1 Maison
float U1 = pzem1.voltage();               //exprimé en V
float I1 = pzem1.current();               //exprimé en A
float P1 = pzem1.power();                 //exprimé en W
float W1 = pzem1.energy();                //exprimé en Wh

if (isnan(U1) || isnan(I1) || isnan(P1)|| isnan(W1)) 
    {
    Serial.println("Erreur Lecture PZEM1");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print ("Erreur Lecture PZEM1");   
    return;
    }

// Multimètre PZEM 2 Photovoltaique
float U2 = pzem2.voltage();               //exprimé en V
float I2 = pzem2.current();               //exprimé en A
float P2 = pzem2.power();                 //exprimé en W 
float W2 = pzem2.energy();                //exprimé en Wh

if (isnan(U2) || isnan(I2) || isnan(P2)|| isnan(W2)) 
    {
    Serial.println("Erreur Lecture PZEM2");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print ("Erreur Lecture PZEM2");
    return;
    }

//CALCUL SURPLUS SOLAIRE DISPONIBLE------------------------------------------------------------------------------------

P3_Delta = P2-P1;

// REGULATION SIMPLE -------------------------------------------------------------------------------------------------

if (P3_Delta > 300 && ConsVarECS_Calculee < 100)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 15;           //+221.25W
    lcd.setCursor(9,3);
    lcd.print("+++"); // Affichage de l'étape de régulation
  }

if (P3_Delta > 175 && P3_Delta < 300 && ConsVarECS_Calculee < 100)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 10;          //+147.5W
    lcd.setCursor(9,3);
    lcd.print("+10"); // Affichage de l'étape de régulation
  }
  
if (P3_Delta > 80 && P3_Delta < 175 && ConsVarECS_Calculee < 100)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 5;          //+74.75W
    lcd.setCursor(9,3);
    lcd.print(" +5"); // Affichage de l'étape de régulation
  }

if (P3_Delta > 67 && P3_Delta < 80 && ConsVarECS_Calculee < 100)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 4;          //+59W
    lcd.setCursor(9,3);
    lcd.print(" +4"); // Affichage de l'étape de régulation
  }

if (P3_Delta > 55 && P3_Delta < 67 && ConsVarECS_Calculee < 100)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 3;          //+44.25W
    lcd.setCursor(9,3);
    lcd.print(" +3"); // Affichage de l'étape de régulation
  }

if (P3_Delta > 40 && P3_Delta < 55 && ConsVarECS_Calculee < 100)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 2;          //+29.5W
    lcd.setCursor(9,3);
    lcd.print(" +2"); // Affichage de l'étape de régulation
  }

if (P3_Delta > 20 && P3_Delta < 40 && ConsVarECS_Calculee < 100)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 1;          //+14.75W
    lcd.setCursor(9,3);
    lcd.print(" +1"); // Affichage de l'étape de régulation
  }

// -----------------------------------------------------------------

if (P3_Delta < -145 && ConsVarECS_Calculee > 0)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 15;
    lcd.setCursor(9,3);
    lcd.print("---"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -145 && P3_Delta < -130 && ConsVarECS_Calculee > 0)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 10;             //-147.5W
    lcd.setCursor(9,3);
    lcd.print("-10"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -130 && P3_Delta < -115 && ConsVarECS_Calculee > 0)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 9;             //-132.75W
    lcd.setCursor(9,3);
    lcd.print(" -9"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -115 && P3_Delta < -100 && ConsVarECS_Calculee > 0)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 8;             //-118W
    lcd.setCursor(9,3);
    lcd.print(" -8"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -100 && P3_Delta < -86 && ConsVarECS_Calculee > 0)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 7;             //-103.25W
    lcd.setCursor(9,3);
    lcd.print(" -7"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -86 && P3_Delta < -70 && ConsVarECS_Calculee > 0)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 6;             //-88.50W
    lcd.setCursor(9,3);
    lcd.print(" -6"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -70 && P3_Delta < -57 && ConsVarECS_Calculee > 0)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 5;             //-73.5W
    lcd.setCursor(9,3);
    lcd.print(" -5"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -57 && P3_Delta < -42 && ConsVarECS_Calculee > 0)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 4;             //-59W
    lcd.setCursor(9,3);
    lcd.print(" -4"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -42 && P3_Delta < -25 && ConsVarECS_Calculee > 0)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 3;             //-44.25W
    lcd.setCursor(9,3);
    lcd.print(" -3"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -25 && P3_Delta < -10 && ConsVarECS_Calculee > 0)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 2;             //-29.5W
    lcd.setCursor(9,3);
    lcd.print(" -2"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -10 && P3_Delta < -4 && ConsVarECS_Calculee > 0)
  {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 1;             //-14.75W
    lcd.setCursor(9,3);
    lcd.print(" -1"); // Affichage de l'étape de régulation
  }

if (ConsVarECS_Calculee >95)
  {
    ConsVarECS_Calculee = 100;
    lcd.setCursor(9,3);
    lcd.print(" > "); // Affichage de l'étape de régulation
  }

if (ConsVarECS_Calculee < 5)
  {
    ConsVarECS_Calculee = 0;
    lcd.setCursor(9,3);
    lcd.print(" < "); // Affichage de l'étape de régulation
  }

// COMPTAGE ENERGIE ECS -----------------------------------------------------------------------------------------------
if (P3_Delta > 15)
  {
  CptEnergieEcsSolaire = CptEnergieEcsSolaire + (ConsVarECS_Calculee*16*U1/230*TpsCycle/3600); // ConsVarECS_Calculee * 16 (pour 1600W à 100%)* temps de cycle / 3600 (conversion en heure)
  }
if ((digitalRead(2)==LOW) &&  CptEnergieECS < 6000)
  {
  CptEnergieEcsEDF = CptEnergieEcsEDF + (1600*U1/230*TpsCycle/3600);         // Ajout 1600W (Pmaxi chauffe eau) * U1 (tension réelle) / 230 (tension théorique) * temps de cycle / 3600 (conversion en heure)
  }

CptEnergieECS = CptEnergieEcsSolaire + CptEnergieEcsEDF; 

CptCycles = CptCycles +1;


// FORCAGE ECS A 100% -------------------------------------------------------------------------------------------------

if (digitalRead(5)==LOW)                 // appui sur BP forçage ECS
  { 
  CptDemandeForcageECS = 5400;           // consigne temps forçage manuel ECS 3600*3/tps de cycle (environs 3h)
  }

 if (CptDemandeForcageECS > 0 || (((digitalRead(2)==LOW) &&  CptEnergieECS < 6000))) 
   {
  ConsVarECS = 100;
  CptDemandeForcageECS = CptDemandeForcageECS -1;  // décomptage temps forçage manuel ECS
  }
  
else 
  {
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

switch (ValeurBp)
{
case 0:                                         //Affichage MENU 0 (écran éteint)
{
//lcd.noBacklight();
lcd.clear();
lcd.setCursor(1,0);
lcd.print ("Menu 0 noBacklight");
break;
}

case 1:                                         //Affichage MENU 1
{
int align1 = 16;
        if (P1 >9) 
            { 
             align1 = 15;
             }
        if (P1 >99) 
            { 
             align1 = 14;
            }
        if (P1 >999) 
             { 
             align1 = 13;
             }

int align2 = 16;
        if (P2 >9) 
            { 
             align2 = 15;
             }
        if (P2 >99) 
            { 
             align2 = 14;
            }
        if (P2 >999) 
             { 
             align2 = 13;
             }
             
int align3 = 16;
        if (P3_Delta >9) 
            { 
             align3 = 15;
             }
        if (P3_Delta >99) 
            { 
             align3 = 14;
            }
        if (P3_Delta >999) 
             { 
             align3 = 13;
             }
        if (P3_Delta < 0) 
            { 
             align3 = 15;
             }
        if (P3_Delta < -9) 
            { 
             align3 = 14;
             }
        if (P3_Delta < -99) 
            { 
             align3 = 13;
            }
        if (P3_Delta < -999) 
             { 
             align3 = 12;
             }

int align4 = 16;
        if (ConsVarECS >9) 
            { 
             align4 = 15;
             }
        if (ConsVarECS >99) 
            { 
             align4 = 14;
            }
lcd.init();                         
lcd.backlight(); 
lcd.clear();
lcd.setCursor(0,0);
lcd.print ("Maison");
lcd.setCursor(align1,0);
lcd.print(P1,0);
lcd.setCursor(18,0);
lcd.print ("W1");

lcd.setCursor(0,1);     
lcd.print ("Solaire");
lcd.setCursor(align2, 1);
lcd.print(P2,0);
lcd.setCursor(18,1);
lcd.print ("W");

lcd.setCursor(0,2);
lcd.print ("DELTA");
lcd.setCursor(align3, 2);
lcd.print(P3_Delta,0);
lcd.setCursor(18,2);
lcd.print ("W");

lcd.setCursor(0,3);     
lcd.print ("ECS");
lcd.setCursor(align4, 3);
lcd.print(ConsVarECS);
lcd.setCursor(18,3);
lcd.print ("%");

// Affichage Chauffe Forcée par DI
if (digitalRead(2)==LOW) 
{
 lcd.setCursor(4,3);     
 lcd.print ("FORCE");
}
if (CptDemandeForcageECS > 0) 
{
 lcd.setCursor(4,3);     
 lcd.print ("ForceM");
}
break;
}

case 2:                                  // affichage écran 2
{

int align21 = 13;
        if (CptEnergieEcsEDF >9) 
            { 
             align21 = 12;
             }
        if (CptEnergieEcsEDF >99) 
            { 
             align21 = 11;
             }
        if (CptEnergieEcsEDF >999) 
            { 
             align21 = 10;
             }
        if (CptEnergieEcsEDF >9999) 
            { 
             align21 = 9;
             }
             
int align22 = 13;
        if (CptEnergieEcsSolaire >9) 
            { 
             align22 = 12;
             }
        if (CptEnergieEcsSolaire >99) 
            { 
             align22 = 11;
             }
        if (CptEnergieEcsSolaire >999) 
            { 
             align22 = 10;
             }
        if (CptEnergieEcsSolaire >9999) 
            { 
             align22 = 9;
             }

int align23 = 13;
        if (CptEnergieECS >9) 
            { 
             align23 = 12;
             }
        if (CptEnergieECS >99) 
            { 
             align23 = 11;
            }
        if (CptEnergieECS >999) 
             { 
             align23 = 10;
             }
        if (CptEnergieECS >9999) 
             { 
             align23 = 9;
             }

int align24 = 16;
        if (ConsVarECS >9) 
            { 
             align24 = 15;
             }
        if (ConsVarECS >99) 
            { 
             align24 = 14;
            }
  
lcd.init();                         
lcd.backlight(); 
lcd.clear();

lcd.setCursor(0,0);
lcd.print ("Ecs EDF");
lcd.setCursor(align21,0);
lcd.print(CptEnergieEcsEDF,1);
lcd.setCursor(17,0);
lcd.print ("Wh2");

lcd.setCursor(0,1);     
lcd.print ("Ecs Sol.");
lcd.setCursor(align22, 1);
lcd.print(CptEnergieEcsSolaire,1);
lcd.setCursor(17,1);
lcd.print ("Wh");

lcd.setCursor(0,2);     
lcd.print ("Ecs Tot.");
lcd.setCursor(align23, 2);
lcd.print(CptEnergieECS,1);
lcd.setCursor(17,2);
lcd.print ("Wh"); 

lcd.setCursor(0,3);     
lcd.print ("ECS");
lcd.setCursor(align24, 3);
lcd.print(ConsVarECS);
lcd.setCursor(18,3);
lcd.print ("%");

// Affichage Chauffe Forcée par DI
if (digitalRead(2)==LOW) 
{
 lcd.setCursor(4,3);     
 lcd.print ("FORCE");
}
if (CptDemandeForcageECS > 0) 
{
 lcd.setCursor(4,3);     
 lcd.print ("ForceM");
}
}
break;

case 3:                                  // affichage écran 3
{
int align32 = 15;
        if (ConsVarECS >9) 
            { 
             align32 = 14;
             }

int align33 = 15;
        if (ConsVarECS >9) 
            { 
             align33 = 14;
             }

int align34 = 16;
        if (CptEnergieECS >9) 
            { 
             align34 = 15;
             }
        if (CptEnergieECS >99) 
            { 
             align34 = 14;
            }
  
lcd.init();                         
lcd.backlight(); 
lcd.clear();

lcd.setCursor(0,0);
lcd.print ("U1");
lcd.setCursor(13,0);
lcd.print(U1,1);
lcd.setCursor(18,0);
lcd.print ("V3");

lcd.setCursor(3,0); // Cpt cycles
lcd.print(CptCycles);

lcd.setCursor(0,1);     
lcd.print ("I1");
lcd.setCursor(align32, 1);
lcd.print(I1,1);
lcd.setCursor(18,1);
lcd.print ("A");

lcd.setCursor(0,2);     
lcd.print ("I2");
lcd.setCursor(align33, 2);
lcd.print(I2,1);
lcd.setCursor(18,2);
lcd.print ("A"); 

lcd.setCursor(0,3);     
lcd.print ("ECS");
lcd.setCursor(align34, 3);
lcd.print(ConsVarECS);
lcd.setCursor(18,3);
lcd.print ("%");

// Affichage Chauffe Forcée par DI
if (digitalRead(2)==LOW)
{
 lcd.setCursor(4,3);     
 lcd.print ("FORCE");
}
if (CptDemandeForcageECS > 0) 
{
 lcd.setCursor(4,3);     
 lcd.print ("ForceM");
}
}
break;

default :
lcd.init();                         
lcd.backlight(); 
lcd.clear();

lcd.setCursor(0,0);
lcd.print ("Defaut");
break;
}


// débute de la communication avec un esclave (ouvre le stockage données à envoyer avec write)
    Wire.beginTransmission(I2C_SLAVE_SCR);
    // charge des octets pour une transmission du composant maître vers un composant esclave 
    Wire.write(ConsVarECS);
    // Termine la transmission avec un composant esclave sur le bus I2C qui a été débutée avec 
    // la fonction beginTransmission() 
    Wire.endTransmission();

Serial.println();

delay(2000);           // Si modification voir CptEnergieECS

}
