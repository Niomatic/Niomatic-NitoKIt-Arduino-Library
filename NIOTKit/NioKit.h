/*--------------------------------------------------------------------

  NioKit.h is part of the Niomatic NioKit library.
  NioKit is a library for NioKit educational sensor pack, easing the 
  use of sensors provided in our pack while maintaining an understandable
  code structure.

  Niomatic is a free software: It is distributed in the hope that it will be useful,
  time saving and efficient for user interface. NioKit library is also free and you 
  can redistribute it and/or modify it under the terms of ... .
  
  
  Written by : Ehsan Moradi, Narmin Samimian, ...
  Date : ...
  

  --------------------------------------------------------------------*/


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <NIO_LightDependentResistor.h>
#include <Wire.h>  			// Only needed for Arduino 1.6.5 and earlier
#include <NIO_DHT.h>
#include <Servo.h>
#include <NIO_Adafruit_NeoPixel.h>
#include <NIO_VoltMeter.h>

//Voltage sensor parameters
#define R1 100000			//module R1 resistor(ohms)
#define R2 10000			//module R2 resistor(ohms)
#define REFERENCE 3.125		//refrence voltage(v)

//Photoresistor sensor parameters
#define OTHER_RESISTOR 3300 //module resistor(ohms)
#define USED_PHOTOCELL LightDependentResistor::GL5528

//RGB parameters
#define NUMPIXELS      18  // How many NeoPixels are attached to the ESP8266

//MQ5 sensor parameters and calibration phase parameters
#define         RL_VALUE_MQ5                 (4.7)      //module load resistance on the board (Kohms)
#define         RO_CLEAN_AIR_FACTOR_MQ5      (6.455)    //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
#define         CALIBARAION_SAMPLE_TIMES     (10)       //how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)      //the time interval(milisecond) between each samples in the calibration phase
#define         READ_SAMPLE_INTERVAL         (10)       //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (2)        //define the time interval(in milisecond) between each samples in calibration phase
#define         GAS_HYDROGEN                 (0)		//Hydrogen gas id
#define         GAS_LPG                      (1)		//LPG gas id
#define         GAS_METHANE                  (2)		//Methane gas id
#define         GAS_CARBON_MONOXIDE          (3)		//Carbon-monoxide gas id
#define         GAS_ALCOHOL                  (4)		//Alcohol gas id
#define         MQ5_accuracy                 (0)        //for linearcurves
//#define         accuracy                   (1)          //for nonlinearcurves, uncomment this line and comment the above line
/**********************************************/


class NioKit
{
  public:
	//Constructor: Wifi ssid, wifi password, specified IP address, UDP port, wifi mode station/access poin
    NioKit(const char*  m_pchSSID,const char*  m_pchPASS, IPAddress m_IP, int m_nPort,String m_strWifiMode);

	//Setup functions which activate a specific module
  void
    SetupDht(int pin),
    SetupRgb(int pin),
    SetupBuzzer(int pin),
    SetupRelay(int pin),
    SetupReed(int pin),
    SetupVoltmeter(int pin),   
    SetupLdr(int pin),
    SetupLiqlevel(int pin),
    SetupMoisture(int pin),
    SetupTouch(int pin),
    SetupMq5(int pin),
	SetupServo(int pin),
    ReadSensor();

	//Sets the pin for the specific module
	int g_nMoisturepin;
	int g_nTouchpin;
	int g_nRelaypin;
	int g_nBuzzerpin;
	int g_nMq5pin;
	int g_nReedpin;
	
    String g_strJsonPrint;			//Holds json information

    float  g_fMq5Res;				//Holds MQ5 calibration result

	
	//MQ5 sensor functions
    float Mq5ResistanceCalculation(int m_nADCin);
    float Mq5Calibration(int m_nMqPin);
    float Mq5Read(int m_nMqPin);
    int Mq5GetGasPercentage(float m_fRsRoRatio, int m_nGasid);

    //ServoMotor functions
    uint8_t servoPos();
    void servoMove(uint8_t pos);
	
    //RGB HSL functions
    int Strtoint(char m_chStr);		//converts RGB color numbers into HEX char 
    uint32_t HSL(uint16_t ih, uint8_t is, uint8_t il);
	uint8_t HSLConvert(float m_fC, float m_fT1, float m_fT2);
	
	
	
	
  private:
    
    
	char UDP_packetBuffer[UDP_TX_PACKET_MAX_SIZE];	
    void JsonParse(String json_string);			//Sends and receives data to and from modules

	//Enable data transmission for the specified module
   bool	
	g_bEnablevoltmeter=false,
	g_bEnableldr=false,
	g_bEnablemoisture=false,
	g_bEnableliqlevel=false,
	g_bEnabletouch=false,
	g_bEnablereed=false,
	g_bEnablerelay=false,
	g_bEnablebuzzer=false,
	g_bEnabledht=false,
	g_bEnablergb=false,
	g_bEnablemq5=false;
	g_bEnableservo=false;

	//class objects
    WiFiUDP Udp;
    Adafruit_NeoPixel pixels;
    LightDependentResistor photocell;
    VoltMeter vm;
    DHT DHT_sensor;			

};


