#include "Arduino.h"
#include "NioKit.h"

NioKit::NioKit(char*  ssid,char*  pass, IPAddress ip, int port,String wifi_mode)
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
    WiFiManager wifiManager;
    Serial.println("wifiManager started");
    wifiManager.setSTAStaticIPConfig(nio_ip, nio_gw, nio_sn);
    wifiManager.setTimeout(60);
    configModeCallback(&wifiManager);
    wifiManager.setAPCallback(configModeCallback);
    if (!wifiManager.autoConnect(Wifi_config_name))
    {
      Serial.println("failed to connect and hit timeout");
      ESP.reset();
      delay(1000);
    }
    Serial.println("connected.. )");
  }
    Udp.begin(UDP_port);        // start UDP server
    Serial.println(UDP_port);

}

/*********************************************************/
void NioKit::configModeCallback (WiFiManager *myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}
/*****************************SetupFunctions******************************/

void NioKit::setupnio()
{
  Serial.println("Niomatic setup function begins...");
}
/***************/
void NioKit::setup_voltmeter(int pin)
{
  voltagePIN = pin;
  vm.Setup_Voltage(voltagePIN);
}
/***************/
void NioKit::setup_LDR(int pin)
{
  LDRpin = pin;
  photocell.setpin(LDRpin);
}
/***************/
void NioKit::setup_moisture(int pin)
{
  MoiPIN = pin;
}
/***************/
void NioKit::setup_liqlevel(int pin)
{
  liqPIN = pin;
}
/***************/
void NioKit::setup_touch(int pin)
{
  tchpin = pin;
}

/***************/
void NioKit::setup_Rswitch(int pin)
{
  swtPIN = pin;
  pinMode(swtPIN, INPUT_PULLUP);  
}

/***************/
void NioKit::setup_RELAY(int pin)
{
  RSPIN = pin;
  pinMode(RSPIN, OUTPUT);  
}
/***************/
void NioKit::setup_BUZZER(int pin)
{ 
      bzrPIN = pin;
      pinMode(bzrPIN, OUTPUT);  
}
/***************/
void NioKit::setup_DHT(int pin)
{ 
    DHT_sensor.begin(pin);
    Serial.println("DHT Sensor Starts...");   
}
/***************/
void NioKit::setup_RGB(int pin)
{
  pixels.begin(pin);
}
/***************/
void NioKit::setup_MQ5(int pin)
{
    MQ5PIN = pin;
    Ro = 10;
    Ro = MQCalibration(MQ5PIN);
    Serial.println("MQ5 Sensor Starts...");   
}  



/*************************************PublicJsonParseFunction***********************************/
JsonObject& NioKit::parse_json_object(String json_string)
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json_string);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    //return NULL;
  } else {
    return root;
  }
}


void NioKit::Json_Parse(String json_string)
{
  JsonObject& root = parse_json_object(json_string);
  j_ask = root["ask"];
  j_port = root["port"];
  j_ask_s = j_ask;
  /********************/
  if (j_ask_s == "DHT")
  {
    float h = DHT_sensor.readHumidity();
    float t = DHT_sensor.readTemperature(false); //For Read temperature as Fahrenheit (isFahrenheit = true)
    if (isnan(h) || isnan(t)) {// Check if any reads failed and exit early (to try again).
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
  if (j_ask_s == "RGB")
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
    for (int i = 0; i < 5; i++)
    {
      pixels.setPixelColor(i, red, green, blue); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
   }
   /********************/
      if (j_ask_s == "MQ5")
  {

    int hydrogen = MQGetGasPercentage(MQRead(MQ5PIN) / Ro, GAS_HYDROGEN);
    int lpg = MQGetGasPercentage(MQRead(MQ5PIN) / Ro, GAS_LPG);
    int methane = MQGetGasPercentage(MQRead(MQ5PIN) / Ro, GAS_METHANE) ;
    int carbon_monoxide = MQGetGasPercentage(MQRead(MQ5PIN) / Ro, GAS_CARBON_MONOXIDE);
    int alcohol = MQGetGasPercentage(MQRead(MQ5PIN) / Ro, GAS_ALCOHOL);
    Serial.printf("Hydrogen: %d LPG: %d Methane: %d Carbon: %d Alcohol: %d ", hydrogen, lpg, methane, carbon_monoxide, alcohol);
    Serial.println();
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    root["hydrogen"] = hydrogen;
    root["lpg"] = lpg;
    root["methane"] = methane;
    root["co"] = carbon_monoxide;
    root["Value-alcohol"] = alcohol;
    root.prettyPrintTo(JsonPrint);

  }
   /********************/
    if (j_ask_s == "Buzzer")
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
    if (j_ask_s == "Rswitch")
  {
    pinMode(swtPIN, INPUT_PULLUP);
    int proximity = digitalRead(swtPIN);
    if (proximity == HIGH)
    {

      Serial.println("Switch is closed");
      switchstate = "switch is closed";
    }
    if (proximity == LOW) // If the pin reads low, the switch is closed.
    {
      Serial.println("Switch is open");
      switchstate = "Switch is open";
    }

    Serial.println();
    StaticJsonBuffer<512> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
  
    //root["Value-switch"] = proximity;
    root["Value-on"] = switchstate;
    root.prettyPrintTo(JsonPrint);
  }

   /********************/
    if (j_ask_s == "A_sensor")
  {
    int data = analogRead(A0);
    Serial.println(data);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    root["Value-data"] = data;
    root.prettyPrintTo(JsonPrint);
  }

   /********************/  
    if (j_ask_s == "RELAY")

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
  if (j_ask_s == "LDR")
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
      if (j_ask_s == "Voltmeter")
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
        if (j_ask_s == "Moisture")
  {
    int data = analogRead(MoiPIN);
    Serial.println(data);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    root["Moisture"] = data;
    root.prettyPrintTo(JsonPrint);
  }
   /********************/    
      if (j_ask_s == "Touch")
  {
    pinMode(tchpin, INPUT_PULLUP);
    int statetch = digitalRead(tchpin);
    if (statetch == HIGH)
    {

      Serial.println("contact detected");
      tchstate = "contact detected";
    }
    if (statetch == LOW) // If the pin reads low, the switch is closed.
    {
      Serial.println("no contact detected");
      tchstate = "no contact detected";
    }

    Serial.println();
    StaticJsonBuffer<512> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
  
    root["Value-tch"] = tchstate;
    root.prettyPrintTo(JsonPrint);
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
