// Calcul de régulation
//
void process_calcul(){

  
if (P3_Delta > 300 && ConsVarECS_Calculee < 100)  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 15;           //+221.25W
    lcd.setCursor(9,3);
    lcd.print("+++"); // Affichage de l'étape de régulation
  }

if (P3_Delta > 175 && P3_Delta < 300 && ConsVarECS_Calculee < 100)  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 10;          //+147.5W
    lcd.setCursor(9,3);
    lcd.print("+10"); // Affichage de l'étape de régulation
  }
  
if (P3_Delta > 80 && P3_Delta < 175 && ConsVarECS_Calculee < 100)  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 5;          //+74.75W
    lcd.setCursor(9,3);
    lcd.print(" +5"); // Affichage de l'étape de régulation
  }

if (P3_Delta > 67 && P3_Delta < 80 && ConsVarECS_Calculee < 100)  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 4;          //+59W
    lcd.setCursor(9,3);
    lcd.print(" +4"); // Affichage de l'étape de régulation
  }

if (P3_Delta > 55 && P3_Delta < 67 && ConsVarECS_Calculee < 100)  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 3;          //+44.25W
    lcd.setCursor(9,3);
    lcd.print(" +3"); // Affichage de l'étape de régulation
  }

if (P3_Delta > 40 && P3_Delta < 55 && ConsVarECS_Calculee < 100)  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 2;          //+29.5W
    lcd.setCursor(9,3);
    lcd.print(" +2"); // Affichage de l'étape de régulation
  }

if (P3_Delta > 20 && P3_Delta < 40 && ConsVarECS_Calculee < 100)  {
    ConsVarECS_Calculee = ConsVarECS_Calculee + 1;          //+14.75W
    lcd.setCursor(9,3);
    lcd.print(" +1"); // Affichage de l'étape de régulation
  }

// -----------------------------------------------------------------

if (P3_Delta < -145 && ConsVarECS_Calculee > 0)   {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 15;
    lcd.setCursor(9,3);
    lcd.print("---"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -145 && P3_Delta < -130 && ConsVarECS_Calculee > 0)   {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 10;             //-147.5W
    lcd.setCursor(9,3);
    lcd.print("-10"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -130 && P3_Delta < -115 && ConsVarECS_Calculee > 0)   {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 9;             //-132.75W
    lcd.setCursor(9,3);
    lcd.print(" -9"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -115 && P3_Delta < -100 && ConsVarECS_Calculee > 0)   {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 8;             //-118W
    lcd.setCursor(9,3);
    lcd.print(" -8"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -100 && P3_Delta < -86 && ConsVarECS_Calculee > 0)   {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 7;             //-103.25W
    lcd.setCursor(9,3);
    lcd.print(" -7"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -86 && P3_Delta < -70 && ConsVarECS_Calculee > 0)   {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 6;             //-88.50W
    lcd.setCursor(9,3);
    lcd.print(" -6"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -70 && P3_Delta < -57 && ConsVarECS_Calculee > 0)   {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 5;             //-73.5W
    lcd.setCursor(9,3);
    lcd.print(" -5"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -57 && P3_Delta < -42 && ConsVarECS_Calculee > 0)    {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 4;             //-59W
    lcd.setCursor(9,3);
    lcd.print(" -4"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -42 && P3_Delta < -25 && ConsVarECS_Calculee > 0)   {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 3;             //-44.25W
    lcd.setCursor(9,3);
    lcd.print(" -3"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -25 && P3_Delta < -10 && ConsVarECS_Calculee > 0)   {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 2;             //-29.5W
    lcd.setCursor(9,3);
    lcd.print(" -2"); // Affichage de l'étape de régulation
  }

if (P3_Delta > -10 && P3_Delta < -4 && ConsVarECS_Calculee > 0)   {
    ConsVarECS_Calculee = ConsVarECS_Calculee - 1;             //-14.75W
    lcd.setCursor(9,3);
    lcd.print(" -1"); // Affichage de l'étape de régulation
  }

if (ConsVarECS_Calculee >95)   {
    ConsVarECS_Calculee = 100;
    lcd.setCursor(9,3);
    lcd.print(" > "); // Affichage de l'étape de régulation
  }

if (ConsVarECS_Calculee < 5)   {
    ConsVarECS_Calculee = 0;
    lcd.setCursor(9,3);
    lcd.print(" < "); // Affichage de l'étape de régulation
  }

// COMPTAGE ENERGIE ECS -----------------------------------------------------------------------------------------------
if (P3_Delta > 15)   {
  CptEnergieEcsSolaire = CptEnergieEcsSolaire + (ConsVarECS_Calculee*16*U1/230*TpsCycle/3600); // ConsVarECS_Calculee * 16 (pour 1600W à 100%)* temps de cycle / 3600 (conversion en heure)
  }
if ((digitalRead(2)==LOW) &&  CptEnergieECS < 6000)   {
  CptEnergieEcsEDF = CptEnergieEcsEDF + (1600*U1/230*TpsCycle/3600);         // Ajout 1600W (Pmaxi chauffe eau) * U1 (tension réelle) / 230 (tension théorique) * temps de cycle / 3600 (conversion en heure)
  }



}
