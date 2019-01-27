#include "NioKit.h"


//NioKit Dataset( ssid , password ,IP Address ,UDP Port , WifiMode "STA" or "AP")
NioKit Dataset( "Niomatic_AP","12345678",IPAddress(192,168,1,36),48000,"AP");  



void setup()
{  
  //Dataset.pubnub("pubsub.pubnub.com", "pub-c-c5e5a0e5-37e3-4e64-8930-a1b75e81941f", "sub-c-db676276-f860-11e8-9488-9e80330262eb", "demo");
  //Dataset.SetupDht(pin);          //uncomment for DHT Sensor and set the pin
  //Dataset.SetupRgb(pin);          //uncomment for RGB and set the pin
  //Dataset.SetupBuzzer(pin);       //uncomment for Buzzer and set the pin
  //Dataset.SetupRelay(pin);        //uncomment for Relay and set the pin
  //Dataset.SetupReed(pin);         //uncomment for Reed Switch and set the pin
  //Dataset.SetupServo(pin);        //uncomment for Servo and set the pin
  //Dataset.SetupTouch(pin);        //uncomment for Touch Sensor and set the pin
  //Dataset.SetupAnalog(A0);        //uncomment for analog Sensor and connect it to A0
  //Dataset.SetupVoltmeter(A0);     //uncomment for Voltage Sensor and connect it to A0
  //Dataset.SetupLdr(A0);           //uncomment for LDR Sensor and connect it to A0
  //Dataset.SetupLiqlevel(A0);      //uncomment for LIquidLevel Sensor and connect it to A0
  //Dataset.SetupMoisture(A0);      //uncomment for Moisture Sensor and connect it to A0
  //Dataset.SetupMq5(A0);           //uncomment for Gas sensor connect it to A0

}

void loop()
{
   Dataset.ReadSensor();    
}
