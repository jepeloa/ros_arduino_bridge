/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
 #define RIGHT_MOTOR_BACKWARD 5
#define LEFT_MOTOR_BACKWARD  6
#define RIGHT_MOTOR_FORWARD  9
#define LEFT_MOTOR_FORWARD   10
#define RIGHT_MOTOR_ENABLE 12
#define LEFT_MOTOR_ENABLE 13
#endif

#ifdef ebike_motor
//#define RIGHT_MOTOR_ENABLE 12 //pines que van a activar los brainpowers
//#define LEFT_MOTOR_ENABLE 13  //pines que van a activar los brainpowers

#endif

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
