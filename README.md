# ros_arduino_bridge
ROS_ARDUINO_BRIDGE modified to use e-bike wheels with ROS. 
This library is a modification of https://github.com/hbrobotics/ros_arduino_bridge to connect an e-bike wheels to ROS. I defined a new type of driver motor named ebike_motor.  With that i'm defined an I2C port by software with the library https://github.com/felias-fogg/SoftI2CMaster to control two DAC MCP4726.
I'm defined the I2C port in this lines:

#define SDA_PIN 2 // = A2

#define SCL_PORT PORTC

#define SCL_PIN 3 // = A3

In my harware configuration i'm used A2 and A3 to control de I2C port to connect two the MCP4726, the A4 and A5 lines cannot be used because the ros_arduino_bridge library measure the odometry of one of the wheels with a quadrature encoder using this pins.

The I2C address of the of the DAC are defined in this lines:

#define I2C_7BITADDR_0 0x62 // 

#define I2C_7BITADDR_1 0x63 // 

You need soldier the pcb pads of the MCP4726 to correct the address if you want to control the two wheels (using two MCP4726).

In the motor_driver.h I defined the function to set the motor speed (this function sent the values of the PID to the wheels) 

The funcion sent the values of each DAC for move the wheels independently. There is the posibility of record the last value of voltage in the eeprom of the DAC, in my case i didn't use this option.










