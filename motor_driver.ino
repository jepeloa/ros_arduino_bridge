/***************************************************************
   Motor driver definitions
   
   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   *************************************************************/

#ifdef USE_BASE
   
#ifdef POLOLU_VNH5019
  /* Include the Pololu library */
  #include "DualVNH5019MotorShield.h"

  /* Create the motor driver object */
  DualVNH5019MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined POLOLU_MC33926
  /* Include the Pololu library */
  #include "DualMC33926MotorShield.h"

  /* Create the motor driver object */
  DualMC33926MotorShield drive;
  
  /* Wrap the motor driver initialization */
  void initMotorController() {
    drive.init();
  }

  /* Wrap the drive motor set speed function */
  void setMotorSpeed(int i, int spd) {
    if (i == LEFT) drive.setM1Speed(spd);
    else drive.setM2Speed(spd);
  }

  // A convenience function for setting both motor speeds
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined L298_MOTOR_DRIVER
  void initMotorController() {
    digitalWrite(RIGHT_MOTOR_ENABLE, HIGH);
    digitalWrite(LEFT_MOTOR_ENABLE, HIGH);
  }
  
  void setMotorSpeed(int i, int spd) {
    unsigned char reverse = 0;
  
    if (spd < 0)
    {
      spd = -spd;
      reverse = 1;
    }
    if (spd > 255)
      spd = 255;
    
    if (i == LEFT) { 
      if      (reverse == 0) { analogWrite(RIGHT_MOTOR_FORWARD, spd); analogWrite(RIGHT_MOTOR_BACKWARD, 0); }
      else if (reverse == 1) { analogWrite(RIGHT_MOTOR_BACKWARD, spd); analogWrite(RIGHT_MOTOR_FORWARD, 0); }
    }
    else /*if (i == RIGHT) //no need for condition*/ {
      if      (reverse == 0) { analogWrite(LEFT_MOTOR_FORWARD, spd); analogWrite(LEFT_MOTOR_BACKWARD, 0); }
      else if (reverse == 1) { analogWrite(LEFT_MOTOR_BACKWARD, spd); analogWrite(LEFT_MOTOR_FORWARD, 0); }
    }
  }
  
  void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }
#elif defined ebike_motor  //
void initMotorController() {
  //aca podria poner algo para que el robot tenga una rutina de inicio, sobre todo que quede seteado en que vaya para adelante
  }
    void setMotorSpeeds(int leftSpeed, int rightSpeed) {
    setMotorSpeed(LEFT, leftSpeed);
    setMotorSpeed(RIGHT, rightSpeed);
  }

void setMotorSpeed(int i, int spd) {
unsigned char reverse_flag_left=0;
unsigned char reverse_flag_rigth=0;

 if (spd < 0 && i==LEFT) //estas lineas de codigo permiten detectar un cambio de direccion en la velocidad, si en algun momento tiene que girar en otro sentido la rueda debo enviar un flag de medio segundo al pin del controlador
    {
      spd = -spd;
      reverse_flag_left = 1;  //los flags son para las ruedas izquierda y derecha
    }
  
  if (spd < 0 && i != LEFT)
    {
      spd = -spd;
      reverse_flag_rigth = 1;  
    }   
   
    if (spd > 2000){  //maximo valor de velocidad
      spd = 2000;
      }
    
    
  if (i == LEFT) { 

  if ((reverse_left != reverse_flag_left) && spd!=0) {
    reverse_left=reverse_flag_left;    //aca deberia enviar un pulso corto al controlador de las ruedas para que se invierta el sentido de giro
   // Serial.println("cambio izquierda: "); //sacar estas dos lineas despues solo para debug  
    //Serial.println(reverse_left);  //idem
    }
   if (!i2c_start_wait((I2C_7BITADDR_0<<1)|I2C_WRITE)) {
 //no hago nada, pero puedo poner codigo aca si no detecta los micros
   }

  if (0)   //si quiero grabar en eeprom del DAC pongo 1
  {
    i2c_write(MCP4726_CMD_WRITEDACEEPROM);
  }
  else
  {
   i2c_write(MCP4726_CMD_WRITEDAC);
  }
  i2c_write(spd / 16);                   // Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
  i2c_write((spd % 16) << 4);            // Lower data bits          (D3.D2.D1.D0.x.x.x.x)
  i2c_stop();
        
   
    }
    else  {   //derecha

 if ((reverse_rigth != reverse_flag_rigth) && spd!=0) {
  reverse_rigth=reverse_flag_rigth;    //aca deberia enviar un pulso corto al controlador de las ruedas para que se invierta el sentido de giro
     // Serial.println("cambio derecha: ");  //sacar estas dos lineas despues es solo para debug
    //Serial.println(reverse_rigth); // idem
    }
     
        if (!i2c_start_wait((I2C_7BITADDR_1<<1)|I2C_WRITE)) {   //direccion i2c del acelerador derecho
   //nada, no hago nada aca podria de ver de poner algun codigo
  }
  

  if (0)    //si quiero grabar en la eeprom del DAC pongo 1
  {
    i2c_write(MCP4726_CMD_WRITEDACEEPROM);
  }
  else
  {
   i2c_write(MCP4726_CMD_WRITEDAC);
  }
  i2c_write(spd / 16);                   // Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)  //esto sale directamente de la libreria de codigo de adafruit
  i2c_write((spd % 16) << 4);            // Lower data bits          (D3.D2.D1.D0.x.x.x.x)
  i2c_stop();
        
  
   }
  }
  
  

#else
  #error A motor driver must be selected!
#endif

#endif
