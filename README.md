# Niomatic NIOT Kit package arduino library


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
| Read | "hydrogen" |  |
| Read | "lpg" |  |
| Read | "methane" |  |
| Read | "co" |  |
| Read | "alcohol" |  |

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

### Touch Button Module
| Parameters | Value | Range |
| ------ | ------ | ------ |
| Request Data | "Touch" | |
| Read | "Value-tch" |  |

