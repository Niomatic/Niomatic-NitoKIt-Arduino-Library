#include "Arduino.h"
#include "NioKit.h"

NioKit::NioKit(const char*  ssid,const char*  pass, IPAddress ip, int port,String wifi_mode)
  : pixels(NUMPIXELS, NEO_GRB + NEO_KHZ800),photocell(OTHER_RESISTOR, USED_PHOTOCELL) ,DHT_sensor(),vm(R1, R2, REFERENCE)
{
  Serial.begin(115200);
  UDP_port = port;
  nio_ip = ip;
  Wifi_config_name = ssid;
  Wifi_config_pass = pass;

 if (wifi_mode == "AP")
  {
    Serial.print("Setting soft-AP configuration ... ");
    Serial.println(WiFi.softAPConfig(nio_ip, nio_gw, nio_sn) ? "Ready" : "Failed!");
    Serial.print("Setting soft-AP ... ");
    Serial.println(WiFi.softAP(Wifi_config_name, Wifi_config_pass) ? "Ready" : "Failed!");
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
  }
  if (wifi_mode== "STA")
  {
    IPAddress _gw = IPAddress(192, 168, 1, 1);
    IPAddress _sn = IPAddress(255, 255, 255, 0);
    WiFi.config(nio_ip,_gw,_sn);
    WiFi.begin(Wifi_config_name,Wifi_config_pass);
    Serial.println(WiFi.localIP());
    Serial.println("connected.. )");
  }
    Udp.begin(UDP_port);        // start UDP server
    Serial.println(UDP_port);
//#define DEBUG_VALUE(l, v) Serial.print(l); Serial.print(":"); Serial.println(v,DEC);
//DEBUG_VALUE(3,6);
}

/*****************************SetupFunctions******************************/
void NioKit::setup_voltmeter(int pin)
{
  voltagePIN = pin;
  vm.Setup_Voltage(voltagePIN);
   Serial.println("Voltmeter Started");
   Enabled_voltmeter=true;
}
/***************/
void NioKit::setup_LDR(int pin)
{
  LDRpin = pin;
  photocell.setpin(LDRpin);
   Serial.println("LDR Started");
   Enabled_LDR=true;
}
/***************/
void NioKit::setup_moisture(int pin)
{
  MoiPIN = pin;
   Serial.println("Moisture Started");
   Enabled_moisture=true;
}
/***************/
void NioKit::setup_liqlevel(int pin)
{
  liqPIN = pin;
   Serial.println("Liquid level Started");
   Enabled_liqlevel=true;
}
/***************/
void NioKit::setup_touch(int pin)
{
  tchpin = pin;
   Serial.println("Touch Sensor Started");
   Enabled_touch=true;
}

/***************/
void NioKit::setup_Rswitch(int pin)
{
  swtPIN = pin;
  pinMode(swtPIN, INPUT_PULLUP);  
   Serial.println("Reed Switch Started");
   Enabled_Rswitch=true;
}

/***************/
void NioKit::setup_RELAY(int pin)
{
  RSPIN = pin;
  pinMode(RSPIN, OUTPUT);  
   Serial.println("Relay Started");
   Enabled_RELAY=true;
}
/***************/
void NioKit::setup_BUZZER(int pin)
{ 
      bzrPIN = pin;
      pinMode(bzrPIN, OUTPUT);  
	   Serial.println("Buzzer Started");
	   Enabled_BUZZER=true;
}
/***************/
void NioKit::setup_DHT(int pin)
{ 
    DHT_sensor.begin(pin);
    Serial.println("DHT Sensor Started");
	Enabled_DHT=true;
}
/***************/
void NioKit::setup_RGB(int pin)
{
  pixels.begin(pin);
   Serial.println("RGB LED Started");
   Enabled_RGB=true;
}
/***************/
void NioKit::setup_MQ5(int pin)
{
    MQ5PIN = pin;
    Ro = 10; 
    Ro = MQCalibration(MQ5PIN);
    Serial.println("MQ5 Sensor Started"); 
Enabled_MQ5=true;	
}  



/*************************************PublicJsonParseFunction***********************************/

void NioKit::Json_Parse(String json_string)
{
	DynamicJsonBuffer jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(json_string);
	if (!root.success()) {
		Serial.println("parseObject() failed");
		//return NULL;
	} 
	
  else {
  j_ask = root["ask"];
  j_port = root["port"];
  j_ask_s = j_ask;
   Serial.print(j_ask_s);
    Serial.print("-->> ");
  /********************/
  if (j_ask_s == "DHT")
  {
    float h = DHT_sensor.readHumidity();
    float t = DHT_sensor.readTemperature(false); //For Read temperature as Fahrenheit (isFahrenheit = true)
    if (isnan(h) || isnan(t)) {// Check if any reads failed and exit early (to try again).
	Serial.print("DHT Error");
      return; //Failed to read from DHT sensor!
    }
    Serial.print("Temp :");
    Serial.print(t);
    Serial.print("   Humidity: ");
    Serial.print(h);
    Serial.println();
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["temp"] = t;
    root["hum"] = h;
    root.prettyPrintTo(JsonPrint);
  }
  /********************/  
 else if (j_ask_s == "RGB")
  {
    j_color = root["color"];
    j_color_s = j_color; //comment this line
    red = (stoi(j_color[2]) * 16) + stoi(j_color[3]);
    green = (stoi(j_color[4]) * 16) + stoi(j_color[5]);
    blue = (stoi(j_color[6]) * 16) + stoi(j_color[7]);
    Serial.print("RED:");
    Serial.print(red);
    Serial.print("   Green:");
    Serial.print(green);
    Serial.print("   Blue:");
    Serial.print(blue);
    Serial.println("");
    for (int i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, red, green, blue); // Moderately bright green color.
	  pixels.show(); // This sends the updated pixel color to the hardware.
    }
	
   }
   /********************/  
 else if (j_ask_s == "RGB_HSL")
  {
    uint16_t hue = root["hue"];
    Serial.print("hue: ");
    Serial.println(hue);
    for (int i = 0; i < NUMPIXELS; i++)
    {
		uint8_t saturation = 100;
		uint8_t lightness = 50;
		pixels.setPixelColor(i, hsl(hue, saturation, lightness));
		pixels.show();
		//pixels.setPixelColor(i, red, green, blue); // Moderately bright green color.
	    //pixels.show(); // This sends the updated pixel color to the hardware.
    }
	
   }
   /********************/
   else if (j_ask_s == "MQ5")
  {
  int gas_value=MQRead(MQ5PIN);
    int hydrogen = MQGetGasPercentage(gas_value / Ro, GAS_HYDROGEN);
    int lpg = MQGetGasPercentage(gas_value / Ro, GAS_LPG);
    int methane = MQGetGasPercentage(gas_value / Ro, GAS_METHANE) ;
    int carbon_monoxide = MQGetGasPercentage(gas_value / Ro, GAS_CARBON_MONOXIDE);
    int alcohol = MQGetGasPercentage(gas_value / Ro, GAS_ALCOHOL);
    Serial.printf("Hydrogen: %d LPG: %d Methane: %d Carbon: %d Alcohol: %d ", hydrogen, lpg, methane, carbon_monoxide, alcohol);
    Serial.println();
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["hyd"] = hydrogen;
    root["lpg"] = lpg;
    root["met"] = methane;
    root["co"] = carbon_monoxide;
    root["alc"] = alcohol;
    root.prettyPrintTo(JsonPrint);
  }
   /********************/
  else if (j_ask_s == "Buzzer")
  {
    int j_freq = root["freq"];
    if (j_freq == 0)
    {
      noTone(bzrPIN);
    }
    else
    {
      tone(bzrPIN,  j_freq);
      Serial.print("freq: ");
      Serial.println(j_freq);
    }

  }
   /********************/  
  else if (j_ask_s == "Rswitch")
  {
    pinMode(swtPIN, INPUT_PULLUP);
    int proximity = digitalRead(swtPIN);
    if (proximity == HIGH)
    {

      Serial.println("Switch is closed");
      switchstate = "1";
    }
    if (proximity == LOW) // If the pin reads low, the switch is closed.
    {
      Serial.println("Switch is open");
      switchstate = "0";
    }

    Serial.println();
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
  
    //root["Value-switch"] = proximity;
    root["Value-on"] = switchstate;
    root.prettyPrintTo(JsonPrint);
  }

   /********************/
   else if (j_ask_s == "A_sensor")
  {
    int data = analogRead(A0);
    Serial.println(data);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    root["Value-data"] = data;
    root.prettyPrintTo(JsonPrint);
  }

   /********************/  
   else if (j_ask_s == "RELAY")

  {
    j_index = root["pwr"];
    Serial.printf("Set relay to %d \n", j_index);

    if (j_index == 1)
    {
      digitalWrite(RSPIN, HIGH);
      Serial.println(j_index);
    }
    if (j_index == 0)
    {
      digitalWrite(RSPIN, LOW);
      Serial.println(j_index);
    }
  }

   /********************/  
  else if (j_ask_s == "LDR")
  {
    float intensity_in_lux = photocell.getCurrentLux();
    float intensity_in_fc = LightDependentResistor::luxToFootCandles(intensity_in_lux);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    root["Value-lux"] = intensity_in_lux;
    root["Value-fc"] = intensity_in_fc;

    root.prettyPrintTo(JsonPrint);
  }
   /********************/
    else  if (j_ask_s == "Voltmeter")
  {
    //float datav = analogRead(A0);
    float  volt = vm.getVoltage();
    Serial.println(volt);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    root["Value-volt"] = volt;
    root.prettyPrintTo(JsonPrint);
  }
   /********************/     
       else if (j_ask_s == "Moisture")
  {
    int data = analogRead(MoiPIN);
    Serial.println(data);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    root["Moisture"] = data;
    root.prettyPrintTo(JsonPrint);
  }
   /********************/    
     else if (j_ask_s == "Touch")
  {
    pinMode(tchpin, INPUT_PULLUP);
    int statetch = digitalRead(tchpin);
    if (statetch == HIGH)
    {

      Serial.println("contact detected");
      tchstate = "1";
    }
    if (statetch == LOW) // If the pin reads low, the switch is closed.
    {
      Serial.println("no contact detected");
      tchstate = "0";
    }

    Serial.println();
    StaticJsonBuffer<512> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
  
    root["Value-tch"] = tchstate;
    root.prettyPrintTo(JsonPrint);
  }
 }
}
/*********************************ReadData************************************/
void NioKit::read_Sensor_result()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    IPAddress remote = Udp.remoteIP();
    Udp.read(UDP_packetBuffer, packetSize);
    Json_Parse(UDP_packetBuffer);
    memset(UDP_packetBuffer, 0, sizeof(UDP_packetBuffer));
    Udp.beginPacket(Udp.remoteIP(), 48000);
    Udp.print(JsonPrint);
    Udp.endPacket();
    JsonPrint = "";
  }
}
/*******************************************MQ5************************************************/
float NioKit::MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE_MQ5 * (1023 - raw_adc) / raw_adc));
}
/*********************/
float NioKit::MQCalibration(int mq_pin)
{
  int i;
  float RS_AIR_val = 0, r0;
  for (i = 0; i < CALIBARAION_SAMPLE_TIMES; i++) {               //take multiple samples
    RS_AIR_val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  RS_AIR_val = RS_AIR_val / CALIBARAION_SAMPLE_TIMES;            //calculate the average value
  r0 = RS_AIR_val / RO_CLEAN_AIR_FACTOR_MQ5;                    //RS_AIR_val divided by RO_CLEAN_AIR_FACTOR yields the Ro
  //according to the chart in the datasheet
  return r0;
}
/*********************/
float NioKit::MQRead(int mq_pin)
{
  int i;
  float rs = 0;
  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    delay(READ_SAMPLE_INTERVAL);
  }
  rs = rs / READ_SAMPLE_TIMES;
  return rs;
}
/*************************/
int NioKit::MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
  if ( accuracy == 0 ) {
    if ( gas_id == GAS_HYDROGEN ) {
      return (pow(10, ((-3.986 * (log10(rs_ro_ratio))) + 3.075)));
    } else if ( gas_id == GAS_LPG ) {
      return (pow(10, ((-2.513 * (log10(rs_ro_ratio))) + 1.878)));
    } else if ( gas_id == GAS_METHANE ) {
      return (pow(10, ((-2.554 * (log10(rs_ro_ratio))) + 2.265 )));
    } else if ( gas_id == GAS_CARBON_MONOXIDE ) {
      return (pow(10, ((-6.900 * (log10(rs_ro_ratio))) + 6.241)));
    } else if ( gas_id == GAS_ALCOHOL ) {
      return (pow(10, ((-4.590 * (log10(rs_ro_ratio))) + 4.851)));
    }
  }

  else if ( accuracy == 1 ) {
    if ( gas_id == GAS_HYDROGEN ) {
      return (pow(10, (-22.89 * pow((log10(rs_ro_ratio)), 3) + 8.873 * pow((log10(rs_ro_ratio)), 2) - 3.587 * (log10(rs_ro_ratio)) + 2.948)));
    } else if ( gas_id == GAS_LPG ) {
      return (pow(10, ((-2.513 * (log10(rs_ro_ratio))) + 1.878)));
    } else if ( gas_id == GAS_METHANE ) {
      return (pow(10, (-0.428 * pow((log10(rs_ro_ratio)), 2) - 2.867 * (log10(rs_ro_ratio)) + 2.224)));
    } else if ( gas_id == GAS_CARBON_MONOXIDE ) {
      return (pow(10, (1401 * pow((log10(rs_ro_ratio)), 4) - 2777 * pow((log10(rs_ro_ratio)), 3) + 2059 * pow((log10(rs_ro_ratio)), 2) - 682.5 * (log10(rs_ro_ratio)) + 88.81)));
    } else if ( gas_id == GAS_ALCOHOL ) {
      return (pow(10, (14.90 * pow((log10(rs_ro_ratio)), 3) - 19.26 * pow((log10(rs_ro_ratio)), 2) + 3.108 * (log10(rs_ro_ratio)) + 3.922)));
    }
  }
  return 0;
}
/*********************************************************RGB*******************************************************/

int NioKit::stoi(char ss)
{
  if (ss == 'a')return 10;
  if (ss == 'b')return 11;
  if (ss == 'c')return 12;
  if (ss == 'd')return 13;
  if (ss == 'e')return 14;
  if (ss == 'f')return 15;
  if (ss == '0')return 0;
  if (ss == '1')return 1;
  if (ss == '2')return 2;
  if (ss == '3')return 3;
  if (ss == '4')return 4;
  if (ss == '5')return 5;
  if (ss == '6')return 6;
  if (ss == '7')return 7;
  if (ss == '8')return 8;
  if (ss == '9')return 9;
}

uint32_t NioKit::hsl(uint16_t ih, uint8_t is, uint8_t il) {

  float h, s, l, t1, t2, tr, tg, tb;
  uint8_t r, g, b;

  h = (ih % 360) / 360.0;
  s = constrain(is, 0, 100) / 100.0;
  l = constrain(il, 0, 100) / 100.0;

  if ( s == 0 ) { 
    r = g = b = 255 * l;
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
  } 
  
  if ( l < 0.5 ) t1 = l * (1.0 + s);
  else t1 = l + s - l * s;
  
  t2 = 2 * l - t1;
  tr = h + 1/3.0;
  tg = h;
  tb = h - 1/3.0;

  r = hsl_convert(tr, t1, t2);
  g = hsl_convert(tg, t1, t2);
  b = hsl_convert(tb, t1, t2);

  // NeoPixel packed RGB color
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}
/**
 * HSL Convert
 * Helper function
 */
uint8_t NioKit::hsl_convert(float c, float t1, float t2) {

  if ( c < 0 ) c+=1; 
  else if ( c > 1 ) c-=1;

  if ( 6 * c < 1 ) c = t2 + ( t1 - t2 ) * 6 * c;
  else if ( 2 * c < 1 ) c = t1;
  else if ( 3 * c < 2 ) c = t2 + ( t1 - t2 ) * ( 2/3.0 - c ) * 6;
  else c = t2;
  
  return (uint8_t)(c*255); 
}