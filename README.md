# Overview

A modification of the original ros_arduino_bridge library https://github.com/hbrobotics/ros_arduino_bridge to control e-bike wheels with ROS. This modification also works for measure the odometry (using the rotation of the wheel) with the hall sensors that the e-bike motor have.
https://jepeloa.medium.com/controlling-e-bike-wheels-with-ros-1e58bc4d688f



# Integrate the MCP4725 to the ros_arduino_bridge 

To control the velocity of the wheels, the controller have a line in where it's possible send a voltage to control the speed of rotation. This voltage can generated using an external signal, that in my case is a DAC MCP4725.
For use the DAC MCP4725 it's necessary use an I2C port, that in the Arduino UNO board it's located in the pins A4 and A5. The problem with this pins is that cannot use them because in the arduino_ros_bridge library are used to measured the odometry.

![alt text](https://github.com/jepeloa/ros_arduino_bridge/blob/master/mcp4725.jpeg)

To resolve the pinout issue, there is a Softi2C library (https://github.com/felias-fogg/SoftI2CMaster) that can used to emulate by software the I2C comunication over another pins. In my case i'm used the A2 to SDA and A3 to SCL. This pinout works for me.
In the code i'm add a new definition named ebike_motor using #ifdef ebike_motor sentence. When the program compiles, if define ebike_motor isn't commented the code executes, bellow there is a part of the code:  


#ifdef ebike_motor   

#define I2C_TIMEOUT 1000

#define I2C_PULLUP 1

#define SDA_PORT PORTC

#define SDA_PIN 2 // = A3

#define SCL_PORT PORTC

#define SCL_PIN 3 // = A

#include <SoftI2CMaster.h>

#define I2C_7BITADDR_0 0x62 // rigth accelerator

#define I2C_7BITADDR_1 0x63 // Left accelerator

#define ADDRLEN 1 // address length, usually 1 or 2 bytes

#define MCP4726_CMD_WRITEDAC            (0x40)  // Writes data to the DAC

#define MCP4726_CMD_WRITEDACEEPROM      (0x60)  // Writes data to the DAC and the EEPROM 

#endif

In my harware configuration i'm used A2 and A3 to control de I2C port to connect two the MCP4725, the A4 and A5 lines cannot be used because the ros_arduino_bridge library measure the odometry of one of the wheels with a quadrature encoder using this pins.

The I2C address of the of the DAC are defined in this lines:

#define I2C_7BITADDR_0 0x62 // 

#define I2C_7BITADDR_1 0x63 // 

You need soldier the pcb pads (ADDR) of the MCP4725 to correct the address if you want to control the two wheels (using two MCP4725).

In the motor_driver.h I defined the function to set the motor speed (this function sent the values of the PID to the wheels) 

The funcion sent the values of each DAC for move the wheels independently. There is the posibility of record the last value of voltage in the eeprom of the DAC, in my case i didn't use this option.

# Connect to e-bike wheel

The way to connect the e-bike wheel to the DAC is using the accelerator line of the brain power controller. The accelerator line have three cables, red (+5V), black(GND) and white (voltage signal). If you connect the white cable to the VOUT of the DAC and the GND(black) to the GND of the Arduino, every voltage in a range of 0-2V (generally this is a common value but depend of the controller) must move the wheel.
![alt text](https://github.com/jepeloa/ros_arduino_bridge/blob/master/brainpower_controller.png)


The pins A2 and A3 of the arduino must connected to the SDA and SCL of both MCP4725, and each VOUT to the withe cable of the accelerator line of the e-bikes controllers.

# Measure the odometry

To obtain the odometry using the rotation of the wheels it's necesary connect two of the three outs of the hall sensor of the e-bike motors to the pins A4, A5 of the arduino for one wheel and D2, D3 for the other.

I'm my case one round of the wheel is about to 78 pulses. Depends of the type of wheel this value can change. It's possible measure using he command e in the serial terminal of the arduino to obtain the amount of pulser per round. The ros_arduino_bridge library have a set of commands that you can execute in the serial terminal, the "e" commands get the total amount of pulses, it's possible that you need reset the encoders usinf before the command "r"


# Complete schematic circuit

![alt text](https://github.com/jepeloa/ros_arduino_bridge/blob/master/esquematico.png)

