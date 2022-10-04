//WattmeterINA219Driver.cpp
#include <Arduino.h>
#include <Wire.h>
#include "DFRobot_INA219.h"
#include "WattmeterINA219Driver.h" 

/**
 * @fn DFRobot_INA219_IIC
 * @brief pWire I2C controller pointer
 * @param i2caddr  I2C address
 * @n INA219_I2C_ADDRESS1  0x40   A0 = 0  A1 = 0
 * @n INA219_I2C_ADDRESS2  0x41   A0 = 1  A1 = 0
 * @n INA219_I2C_ADDRESS3  0x44   A0 = 0  A1 = 1
 * @n INA219_I2C_ADDRESS4  0x45   A0 = 1  A1 = 1	 
  */
DFRobot_INA219_IIC* ina219;

// Revise the following two paramters according to actual reading of the INA219 and the multimeter
// for linearly calibration
float ina219Reading_mA = 1000;
float extMeterReading_mA = 1000;

uint8_t init_f = 0;
extern "C" void wINA219Driver_Init(int8_t wire_number, int8_t slave_address)
{ 
    /* Initialize the sensor and store the status in init_f */
    if(wire_number == 0){
        if(slave_address == 40) ina219 = new DFRobot_INA219_IIC(&Wire, INA219_I2C_ADDRESS1);
        if(slave_address == 41) ina219 = new DFRobot_INA219_IIC(&Wire, INA219_I2C_ADDRESS2);
        if(slave_address == 44) ina219 = new DFRobot_INA219_IIC(&Wire, INA219_I2C_ADDRESS3);
        if(slave_address == 45) ina219 = new DFRobot_INA219_IIC(&Wire, INA219_I2C_ADDRESS4);
    }
    if(wire_number == 1){
        if(slave_address == 40) ina219 = new DFRobot_INA219_IIC(&Wire, INA219_I2C_ADDRESS1);
        if(slave_address == 41) ina219 = new DFRobot_INA219_IIC(&Wire, INA219_I2C_ADDRESS2);
        if(slave_address == 44) ina219 = new DFRobot_INA219_IIC(&Wire, INA219_I2C_ADDRESS3);
        if(slave_address == 45) ina219 = new DFRobot_INA219_IIC(&Wire, INA219_I2C_ADDRESS4);
    }

    if (!ina219->begin()) init_f = 0; // Error, device not found
    else init_f = 1; // Device found

	//Set BRNG (Bus Voltage Range)
    //ina219->setBRNG(ina219->eIna219BusVolRange_32V);
	
    //Set PGA parameter(Shunt Voltage Only)
    //ina219->setPGA(ina219->eIna219PGABits_1);
    
    //Set BADC parameter (Bus ADC Resolution/Averaging)
	//ina219->setBADC(ina219->eIna219AdcBits_12, ina219->eIna219AdcSample_8);
    
    //Set SADC parameter (Shunt ADC Resolution/Averaging)
	//ina219->setSADC(ina219->eIna219AdcBits_12, ina219->eIna219AdcSample_8);
	
    //Set operation Mode(Bus Voltage Range)
    //ina219->setMode(ina219->eIna219SAndBVolCon);
    
    //Linear calibration
    //ina219->linearCalibrate(/*The measured current before calibration*/ina219Reading_mA, /*The current measured by other current testers*/extMeterReading_mA);
} 
extern "C" void wINA219Driver_Step(float* power)
{ 
    /* If sensor is initialized properly, then read the sensor else return 0 */
    if(init_f)              
    { 
        // Obtain sensor power data
        *power = ina219->getPower_mW();
    } 
    else
    { 
        *power = 0; 
    } 
} 
extern "C" void wINA219Driver_Terminate() 
{ 
} 