// Librairie de gestion de l'ECS
// L'ECS est piloté par le module esclave (Arduino Slave d'adresse 2C_SLAVE_SCR=0x09)


// Définition des adresses logiques des esclaves I2C.
#define I2C_SLAVE_SCR 9


void ECS_Start(){
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

void ECS_Send(int val){
  // débute de la communication avec un esclave (ouvre le stockage données à envoyer avec write)
    Wire.beginTransmission(I2C_SLAVE_SCR);
    // charge des octets pour une transmission du composant maître vers un composant esclave 
    Wire.write(val); //ConsVarECS);
    // Termine la transmission avec un composant esclave sur le bus I2C qui a été débutée avec 
    // la fonction beginTransmission() 
    Wire.endTransmission();  
}
