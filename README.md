# Niomatic NIOKit package arduino library


### Arduino needed libraries
Instructions on how to install them use this link https://www.arduino.cc/en/Guide/Libraries.

| Library | Download Link |
| ------ | ------ |
| ESP8266 | https://github.com/esp8266/Arduino |
| JSON library | https://github.com/bblanchon/ArduinoJson |

### Example Code
```C
#include "NioKit.h"

//NioKit Dataset( ssid , password ,IP Address ,UDP Port , WifiMode "STA" or "AP")
NioKit Dataset( "Nio-AP","password",IPAddress(192,168,1,36),48000,"AP");  

void setup()
{  
  //in order to use pubnub servers connect to internet(WifiMode-->STA) and enter your pubnub publishkey and subscribekey below. 
  //Dataset.pubnub("pubsub.pubnub.com", "publishkey", "subscribekey", "channel name");      //uncomment for pubnub service
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
  //Dataset.SetupLiqlevel(A0);      //uncomment for LiquidLevel Sensor and connect it to A0
  //Dataset.SetupMoisture(A0);      //uncomment for Moisture Sensor and connect it to A0
  //Dataset.SetupMq5(A0);           //uncomment for Gas sensor connect it to A0
}

void loop()
{
   Dataset.ReadSensor();    
}
```
## Niomatic Data request

### Relay Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "RELAY" | |
| Set | "pwr" | ( 0 or 1 ) |

### Buzzer Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "Buzzer" | |
| Set | "freq" | ( 20 or 20K ) |

### Servo Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "Servo" | |
| Set | "angle" | ( 0 or 180 ) |

### DHT11 humidity sensor Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "DHT" | |
| Read | "temp" |  |
| Read | "hum" |  |

### WS2812 RGB LED Module Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "RGB" | |
| Set | "color" | Niomatic HEX Format |

| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "RGB_HSL" | |
| Set | "hue" | 0 to 359 |

### MQ5 Gas Sensor Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "MQ5" | |
| Read | "hyd" |  |
| Read | "lpg" |  |
| Read | "met" |  |
| Read | "co" |  |
| Read | "alc" |  |

### Reed Switch Magent Sensor Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "Rswitch" | |
| Read | "Value-on" |  |

### Raw ADC Read
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "A_sensor" | |
| Read | "Value-data" |  |

### LDR Photo Resistor Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "LDR" | |
| Read | "Value-lux" |  |
| Read | "Value-fc" |  |

### Voltage Measurment Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "Voltmeter" | |
| Read | "Value-volt" |  |

### Soil Moisture Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "Moisture" | |
| Read | "Moisture" |  |

### Liquid Level Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "Lqlevel" | |
| Read | "Lqlevel" |  |

### Touch Button Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "Touch" | |
| Read | "Value-tch" |  |

