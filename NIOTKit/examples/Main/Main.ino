#include "NioKit.h"


//NioKit Dataset( ssid , password ,IP Address ,UDP Port , WifiMode "STA" or "AP")
NioKit Dataset( "Nio-AP","password",IPAddress(192,168,1,36),48000,"AP");  

void setup()
{  
  Dataset.setup_DHT(16);          //uncomment for DHT Sensor and set the pin
  //Dataset.setup_RGB(pin);          //uncomment for RGB and set the pin
  //Dataset.setup_BUZZER(pin);       //uncomment for Buzzer and set the pin
  Dataset.setup_RELAY(13);        //uncomment for Relay and set the pin
  //Dataset.setup_Rswitch(pin);      //uncomment for Reed Switch and set the pin
  //Dataset.setup_touch(pin);        //uncomment for Touch Sensor and set the pin
  //Dataset.setup_voltmeter(A0);     //uncomment for Voltage Sensor and connect it to A0
  //Dataset.setup_LDR(A0);           //uncomment for LDR Sensor and connect it to A0
  //Dataset.setup_liqlevel(A0);      //uncomment for LIquidLevel Sensor and connect it to A0
  //Dataset.setup_moisture(A0);      //uncomment for Moisture Sensor and connect it to A0
  //Dataset.setup_MQ5(A0);           //uncomment for Gas sensor connect it to A0
}

void loop()
{
   Dataset.read_Sensor_result();    
}
