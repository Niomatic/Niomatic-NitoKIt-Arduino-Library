#ifndef NioKit_h
#define NioKit_h
#include "FS.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <NIO_LightDependentResistor.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include <NIO_DHT.h>
#include <Servo.h>
#include <NIO_Adafruit_NeoPixel.h>
#include <NIO_VoltMeter.h>
/*****************Voltmeter********************/
#define R1 100000
#define R2 10000
#define REFERENCE 3.125
/*****************DHT***********************/
//#define DHTTYPE DHT11
/****************LDR************************/
#define OTHER_RESISTOR 3300 //ohms
#define USED_PIN A0
#define USED_PHOTOCELL LightDependentResistor::GL5528
/****************RGB***********************/
#define NUMPIXELS      5 // How many NeoPixels are attached to the ESP8266
/*******************MQ5***********************/
//#define         MQ5                           1
//#define         MQ5PIN                       (0)      //define which analog input channel you are going to use
#define         RL_VALUE_MQ5                 (1)      //define the load resistance on the board, in kilo ohms
#define         RO_CLEAN_AIR_FACTOR_MQ5      (6.455)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,

#define         CALIBARAION_SAMPLE_TIMES     (50)    //define how many samples you are going to take in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //define the time interal(in milisecond) between each samples in the
//cablibration phase
#define         READ_SAMPLE_INTERVAL         (50)    //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 

#define         GAS_HYDROGEN                 (0)
#define         GAS_LPG                      (1)
#define         GAS_METHANE                  (2)
#define         GAS_CARBON_MONOXIDE          (3)
#define         GAS_ALCOHOL                  (4)
#define         accuracy                     (0)    //for linearcurves
//#define         accuracy                   (1)    //for nonlinearcurves, un comment this line and comment the above line if calculations
/**********************************************/

class NioKit
{
  public:
    NioKit(  char*  ssid, char*  pass,IPAddress ip,int port,String wifi_mode);
    void setupnio();
    static void configModeCallback (WiFiManager *myWiFiManager);

    void setup_DHT(int pin);
    void setup_RGB(int pin);
    void setup_BUZZER(int pin);
    void setup_RELAY(int pin);
    void setup_Rswitch(int pin);
    void setup_voltmeter(int pin);   
    void setup_LDR(int pin);
    void setup_liqlevel(int pin);
    void setup_moisture(int pin);
    void setup_touch(int pin);
    void setup_MQ5(int pin);

    void read_Sensor_result();
    
    int RSPIN;
    int swtPIN;
    int bzrPIN;
    int voltagePIN;
    int LDRpin;
    int MQ5PIN;
    int MoiPIN;
    int liqPIN;
    int tchpin;

    String j_ask_s;
    const char* j_ask;
    int j_port;
    int j_index;

    char* switchstate;
    char* tchstate;
    /*******************Buzzer************************/
    int j_freq;
    String JsonPrint;
    /**********************MQ5**********************/
    float  Ro;
    /**********************RGB*********************/
    String j_color_s;
    const char* j_color;
    int red, green, blue;

    

    
    void AP_SSID(const char* ssid,const char* pass);
    void ip(IPAddress ip);
    void wifi_mode(String wifi_mode);
    void port(int port);
    void Wifi_mode(String mod);



    /******************MQ5*************************/
    float MQResistanceCalculation(int raw_adc);
    float MQCalibration(int mq_pin);
    float MQRead(int mq_pin);
    int MQGetGasPercentage(float rs_ro_ratio, int gas_id);
    /*******************OLED***********************/
    void drawtext(String text, int x, int y, String font_size);
    void draw_line(int x, int y, int l, String s);
    void draw_rect(int x, int y, int w, int h, bool fill);
    void drawcircle(int x, int y, int r, bool fill);
    /*********************Servo********************/
    uint8_t servoPos();
    void servoMove(uint8_t pos);
    /***********************RGB********************/
    int stoi(char ss);





  private:
    uint16_t UDP_port;
    char UDP_packetBuffer[UDP_TX_PACKET_MAX_SIZE];
    IPAddress nio_ip;
    IPAddress nio_gw = IPAddress(192, 168, 1, 1);
    IPAddress nio_sn = IPAddress(255, 255, 255, 0);
    const char* Wifi_config_name;
    const char* Wifi_config_pass;
    WiFiUDP Udp;
    /******************RGB**********************/
    Adafruit_NeoPixel pixels;
    /*****************LDR***********************/
    LightDependentResistor photocell;
    /****************Voltmeter******************/
    VoltMeter vm;
    /********************DHT********************/
    DHT DHT_sensor;



    
    JsonObject& parse_json_object(String json_string);
    void Json_Parse(String json_string);

};


#endif
