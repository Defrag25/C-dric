// Librairie de définition des variables Globales 


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
