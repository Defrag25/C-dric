/////////////////////////////////////////
// librairie de gestion de l'affichage //
/////////////////////////////////////////
/// LCD 4x20 I2c 0x27

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // Câblage sur A4/A5

void Affichage_Init(){
// Init AFFICHEUR LCD ------------------------------------------------------------------------------------------------------
 lcd.init();                         
 lcd.backlight();                  
}

void Affichage_Presentation(){
 lcd.setCursor(0, 0);                
 lcd.print(F("**                **"));
 lcd.setCursor(7,1);                 
 lcd.print(F("Bonjour"));
 lcd.setCursor(8, 2);               
 lcd.print(F("CATZ"));
 lcd.setCursor(0, 3);               
 lcd.print(F("**                **"));
}

void Affichage(){
  
 switch (ValeurBp)
  {
  case 0:   {                                //Affichage MENU 0 (écran éteint)
          
//lcd.noBacklight();
lcd.clear();
lcd.setCursor(1,0);
lcd.print (F("Menu 0 noBacklight"));
break;
}
  case 1:   {                                //Affichage MENU 1
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
  case 2:   {                                // affichage écran 2


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

break;
  }
  case 3:   {                                // affichage écran 3

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

break;
  }
  default : {
lcd.init();                         
lcd.backlight(); 
lcd.clear();

lcd.setCursor(0,0);
lcd.print ("Defaut");
    break;
    }
 
  }
}
