/*--------------------------------------------------------------------
	VERSION 2.0.1

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



#include "Arduino.h"
#include "NioKit.h"




NioKit::NioKit(const char*  m_pchSSID,const char*  m_pchPASS, IPAddress m_IP, int m_nPort,String m_strWifiMode)
  : pixels(NUMPIXELS, NEO_GRB + NEO_KHZ800),photocell(OTHER_RESISTOR, USED_PHOTOCELL) ,DHT_sensor(),vm(R1, R2, REFERENCE)
{
	Serial.begin(115200);
	IPAddress m_NioIP;
	IPAddress m_NioGW = IPAddress(192, 168, 1, 1);
	IPAddress m_NioSN = IPAddress(255, 255, 255, 0);
	uint16_t m_nUDPort;
	m_nUDPort = m_nPort;
	m_NioIP = m_IP;
	const char* Wifi_config_name;
	const char* Wifi_config_pass;
	Wifi_config_name = m_pchSSID;
	Wifi_config_pass = m_pchPASS;

	if (m_strWifiMode == "AP")
	{
		Serial.print("Setting soft-AP configuration ... ");
		Serial.println(WiFi.softAPConfig(m_NioIP, m_NioGW, m_NioSN) ? "Ready" : "Failed!");
		Serial.print("Setting soft-AP ... ");
		Serial.println(WiFi.softAP(Wifi_config_name, Wifi_config_pass) ? "Ready" : "Failed!");
		Serial.print("Soft-AP IP address = ");
		Serial.println(WiFi.softAPIP());
	}
	if (m_strWifiMode== "STA")
	{
		IPAddress _gw = IPAddress(192, 168, 1, 1);
		IPAddress _sn = IPAddress(255, 255, 255, 0);
		IPAddress _dns = IPAddress(192, 168, 1, 1);
		WiFi.config(m_NioIP,_dns,_gw,_sn);
		WiFi.begin(Wifi_config_name,Wifi_config_pass);
		Serial.println(WiFi.localIP());
		Serial.println("connected.. )");
	}
	Udp.begin(m_nUDPort);        // start UDP server
	Serial.println(m_nUDPort);

}
/****************************pubnubconnection*****************************/
void NioKit::pubnub(const char*  m_host, const char*  m_pubKey, const char*  m_subKey, const char*  m_channel)
{
  // JsonPrint.replace("\"", "'");
  //Serial.println(JsonPrint);
	g_host = m_host;
	g_pubKey = m_pubKey;
	g_subKey = m_subKey;
	g_channel = m_channel;
    g_bEnablePubnub = true;
	Serial.println(g_bEnablePubnub);
	Serial.println("pubnub is set ...");
}
/*****************************SetupFunctions******************************/
void NioKit::SetupVoltmeter(int pin)
{
	int m_nVoltagepin = pin;
	vm.Setup_Voltage(m_nVoltagepin);
	Serial.println("Voltmeter Started");
	g_bEnablevoltmeter=true;
}
/***************/
void NioKit::SetupLdr(int pin)
{
	int m_nLdrpin = pin;
	photocell.setpin(m_nLdrpin);
	Serial.println("LDR Started");
	g_bEnableldr=true;
}
/***************/
void NioKit::SetupMoisture(int pin)
{
	g_nMoisturepin = pin;
	Serial.println("Moisture Started");
	g_bEnablemoisture=true;
}
/***************/

void NioKit::SetupAnalog(int pin)
{
	g_nAnalog = pin;
	Serial.println("analog sensor Started");
	g_bEnableanalog=true;
}
/***************/
void NioKit::SetupLiqlevel(int pin)
{
	int m_nLiqlevelpin = pin;
	Serial.println("Liquid level detector Started");
	g_bEnableliqlevel=true;
}
/***************/
void NioKit::SetupTouch(int pin)
{
	g_nTouchpin = pin;
	pinMode(g_nTouchpin, INPUT_PULLUP);
	Serial.println("Touch Sensor Started");
	g_bEnabletouch=true;
}

/***************/
void NioKit::SetupReed(int pin)
{
	g_nReedpin = pin;
	pinMode(g_nReedpin, INPUT_PULLUP);  
	Serial.println("Reed Switch Started");
	g_bEnablereed=true;
}

/***************/
void NioKit::SetupRelay(int pin)
{
	g_nRelaypin = pin;
	pinMode(g_nRelaypin, OUTPUT);  
	Serial.println("Relay Started");
	g_bEnablerelay=true;
}
/***************/
void NioKit::SetupBuzzer(int pin)
{ 
	g_nBuzzerpin = pin;
	pinMode(g_nBuzzerpin, OUTPUT);  
	Serial.println("Buzzer Started");
	g_bEnablebuzzer=true;
}
/***************/
void NioKit::SetupDht(int pin)
{ 
	DHT_sensor.begin(pin);
	Serial.println("DHT Sensor Started");
	g_bEnabledht=true;
}
/***************/
void NioKit::SetupRgb(int pin)
{
	pixels.begin(pin);
	Serial.println("RGB LED Started");
	g_bEnablergb=true;
}
/***************/
void NioKit::SetupMq5(int pin)
{
	g_nMq5pin = pin;
	g_fMq5Res = Mq5Calibration(g_nMq5pin);
	Serial.println("MQ5 Sensor Started"); 
	g_bEnablemq5=true;	
}  
/***************/
void NioKit::SetupServo(int pin)
{ 
	m_nServopin = pin;
	myservo.attach(m_nServopin);
	Serial.println("Servo Started");
	g_bEnableservo=true;
}
/***************/
void NioKit::SetupPir(int pin)
{ 
	g_nPirpin = pin;
	pinMode(g_nPirpin, INPUT);
	Serial.println("PIR Started");
	g_bEnablepir=true;
}
/***************/
void NioKit::SetupDCmotor(int pin11,int pin12,int pin13)
{ 
	g_nDC11pin = pin11;
	g_nDC12pin = pin12;
	g_nDC13pin = pin13;
	pinMode(g_nDC11pin, OUTPUT);
	pinMode(g_nDC12pin, OUTPUT);
	pinMode(g_nDC13pin, OUTPUT);
	Serial.println("DCmotor Started");
	g_bEnabledcmotor=true;
}


/*************************************PublicJsonParseFunction***********************************/

void NioKit::JsonParse(String json_string)
{
	DynamicJsonBuffer jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(json_string);
	if (!root.success()) 
	{
		Serial.println("parseObject() failed");
		//return NULL;
	} 
	
    else 
    {
	   const char* m_pchJsonAsk;		//Gets json ask parameter in order to decide which sensor to activate (pointer)	  
	   String m_strJsonAsk;				//Gets json ask parameter in order to decide which sensor to activate (String)
	   m_pchJsonAsk = root["ask"];
	   int m_nJsonPort = root["port"];
	   m_strJsonAsk = m_pchJsonAsk;
	   Serial.print(m_strJsonAsk);
	   Serial.print(" -->> ");
  /********************/
		if (m_strJsonAsk == "DHT")
		{
			if(g_bEnabledht == true)
			{
				float m_fHumid = DHT_sensor.readHumidity();
				float m_fTemp = DHT_sensor.readTemperature(false); 		//For Read temperature as Fahrenheit (isFahrenheit = true)
				if (isnan(m_fHumid) || isnan(m_fTemp)) 		// Check if any reads failed and exit early (to try again).
				{
					Serial.print("DHT Error");
					return; 		//Failed to read from DHT sensor!
				}
				Serial.print("Temp :");
				Serial.print(m_fTemp);
				Serial.print("   Humidity: ");
				Serial.print(m_fHumid);
				Serial.println();
				StaticJsonBuffer<200> jsonBuffer;
				JsonObject& root = jsonBuffer.createObject();
				root["temp"] = m_fTemp;
				root["hum"] = m_fHumid;
				root.printTo(g_strJsonPrint);
			}
			else
			{
				Serial.println("DHT is disabled...");
			}
		}
	  /********************/
		else if (m_strJsonAsk == "Servo")
		{
			if(g_bEnableservo == true)
			{
				int m_nJsonangle;
				m_nJsonangle = root["angle"];
				uint8_t m_nServoSpeed=254;               // 255=fastest, else 255-X msec delay per single degree 


				if (m_nJsonangle > 180) m_nJsonangle = 180;
				if (m_nServoSpeed < 255) 
				{
					int m_nServostate = myservo.read();
					Serial.printf("moving servo from %d to %d speed %d\n", m_nServostate, m_nJsonangle, m_nServoSpeed);
					if (m_nServostate < m_nJsonangle) 
					{
					  for (; m_nServostate < m_nJsonangle; m_nServostate += 1) 
					  {
						myservo.write(m_nServostate);
						delay(255-m_nServoSpeed);
					  }
					} 
					else 
					{
					  for (; m_nServostate > m_nJsonangle; m_nServostate -= 1) 
					  {
						myservo.write(m_nServostate);
						delay(255-m_nServoSpeed);      
					  }
					}
				}
				Serial.printf("moved servo to %d\n", m_nJsonangle);
				myservo.write(m_nJsonangle);
			}

			  
			else
			{
				Serial.println("Servo motor is disabled...");
			}
		}

	  /********************/  
		else if (m_strJsonAsk == "RGB")
		{
			if (g_bEnablergb == true )
			{
				const char* m_pachJsoncolor = root["color"];
				int m_nRed = (Strtoint(m_pachJsoncolor[2]) * 16) + Strtoint(m_pachJsoncolor[3]);
				int m_nGreen = (Strtoint(m_pachJsoncolor[4]) * 16) + Strtoint(m_pachJsoncolor[5]);
				int m_nBlue = (Strtoint(m_pachJsoncolor[6]) * 16) + Strtoint(m_pachJsoncolor[7]);
				Serial.print("RED:");
				Serial.print(m_nRed);
				Serial.print("   Green:");
				Serial.print(m_nGreen);
				Serial.print("   Blue:");
				Serial.print(m_nBlue);
				Serial.println("");
				for (int m_nPixelnum = 0; m_nPixelnum < NUMPIXELS; m_nPixelnum++)
				{
					pixels.setPixelColor(m_nPixelnum, m_nRed, m_nGreen, m_nBlue); 		// Sets pixel colors Red, Green, and Blue to the specific Pixel Number.
					pixels.show();		 // This sends the updated pixel color to the hardware.
				}
			}
			else
			{
				Serial.println("RGB is disabled...");
			}
		
		}
	   /********************/  
		else if (m_strJsonAsk == "RGB_HSL")
		{
			if (g_bEnablergb == true )
			{
				uint16_t m_nHue = root["hue"];
				Serial.print("hue: ");
				Serial.println(m_nHue);
				for (int m_nPixelnum = 0; m_nPixelnum < NUMPIXELS; m_nPixelnum++)
				{
					uint8_t m_nSaturation = 100;
					uint8_t m_nLightness = 50;
					pixels.setPixelColor(m_nPixelnum, HSL(m_nHue, m_nSaturation, m_nLightness));
					pixels.show();

				}
			}
			else
			{
				Serial.println("RGB is disabled...");
			}
		
		}
	   /********************/
		else if (m_strJsonAsk == "MQ5")
		{
		
			if(g_bEnablemq5 == true)
			{	
				int m_nGasvalue = Mq5Read(g_nMq5pin);
				int m_nHydrogen = Mq5GetGasPercentage(m_nGasvalue / g_fMq5Res, GAS_HYDROGEN);
				int m_nLpg = Mq5GetGasPercentage(m_nGasvalue / g_fMq5Res, GAS_LPG);
				int m_nMethane = Mq5GetGasPercentage(m_nGasvalue / g_fMq5Res, GAS_METHANE) ;
				int m_nCarbonmonoxide = Mq5GetGasPercentage(m_nGasvalue / g_fMq5Res, GAS_CARBON_MONOXIDE);
				int m_nAlcohol = Mq5GetGasPercentage(m_nGasvalue / g_fMq5Res, GAS_ALCOHOL);
				Serial.printf("Hydrogen: %d LPG: %d Methane: %d Carbon: %d Alcohol: %d ", m_nHydrogen, m_nLpg, m_nMethane, m_nCarbonmonoxide, m_nAlcohol);
				Serial.println();
				DynamicJsonBuffer jsonBuffer;
				JsonObject& root = jsonBuffer.createObject();
				root["hyd"] = m_nHydrogen;
				root["lpg"] = m_nLpg;
				root["met"] = m_nMethane;
				root["co"] = m_nCarbonmonoxide;
				root["alc"] = m_nAlcohol;
				root.printTo(g_strJsonPrint);
			}
			else
			{
				Serial.println("MQ5 is disabled...");
			}
		}
	   /********************/
		else if (m_strJsonAsk == "Buzzer")
		{
			if(g_bEnablebuzzer == true)
			{	
				int m_nJsonfreq;				//Gets buzzer frequency (json format)
				m_nJsonfreq = root["freq"];
				if (m_nJsonfreq == 0)
				{
					noTone(g_nBuzzerpin);
				}
				else
				{
					tone(g_nBuzzerpin,  m_nJsonfreq);
					Serial.print("freq: ");
					Serial.println(m_nJsonfreq);
				}

			}
			else
			{
				Serial.println("Buzzer is disabled...");
			}	  

		}
	   /********************/  
		else if (m_strJsonAsk == "Rswitch")
		{
			if(g_bEnablereed == true)
			{
				const char* m_pchSwitchState;
				int m_nProximity = digitalRead(g_nReedpin);
				if (m_nProximity == HIGH)
				{
					Serial.println("Switch is closed");
					m_pchSwitchState = "1";
				}
				if (m_nProximity == LOW)
				{
					Serial.println("Switch is open");
					m_pchSwitchState = "0";
				}

				Serial.println();
				StaticJsonBuffer<200> jsonBuffer;
				JsonObject& root = jsonBuffer.createObject();
			  
				root["Value-on"] = m_pchSwitchState;
				root.printTo(g_strJsonPrint);
			}
			else
			{
				Serial.println("Reed switch is disabled...");
			}	  	  
	  }

	   /********************/
		else if (m_strJsonAsk == "Lqlevel")
		{
			if(g_bEnableliqlevel == true)
			{	  
				int m_nAnalogdata = analogRead(A0);
				Serial.println(m_nAnalogdata);
				StaticJsonBuffer<200> jsonBuffer;
				JsonObject& root = jsonBuffer.createObject();

				root["Lqlevel"] = m_nAnalogdata;
				root.printTo(g_strJsonPrint);
			}
			else
			{
				  Serial.println("liquid level is disabled...");
			}	  	  
		}
	   /********************/
		else if (m_strJsonAsk == "A_sensor")
		{
			if(g_bEnableanalog == true)
			{	  
				int m_nAnalogdata = analogRead(A0);
				Serial.println(m_nAnalogdata);
				StaticJsonBuffer<200> jsonBuffer;
				JsonObject& root = jsonBuffer.createObject();

				root["Value-data"] = m_nAnalogdata;
				root.printTo(g_strJsonPrint);
			}
			else
			{
				  Serial.println("liquid level is disabled...");
			}	  	  
		}
	   /********************/  
		else if (m_strJsonAsk == "RELAY")
		{
			if(g_bEnablerelay == true)
			{	  
				int m_nJsonIndex = root["pwr"];
				Serial.printf("Set relay to %d \n", m_nJsonIndex);

				if (m_nJsonIndex == 1)
				{
					digitalWrite(g_nRelaypin, HIGH);
					Serial.println(m_nJsonIndex);
				}
				if (m_nJsonIndex == 0)
				{
					digitalWrite(g_nRelaypin, LOW);
					Serial.println(m_nJsonIndex);
				}
			}
			else
			{
				Serial.println("RELAY is disabled...");
			}	  
		  
		}
		
	   /********************/  
		else if (m_strJsonAsk == "LDR")
		{
			if(g_bEnableldr == true)
			{	  
				float m_fIntensitylux = photocell.getCurrentLux();
				float m_fIntensityfc = LightDependentResistor::luxToFootCandles(m_fIntensitylux);
				StaticJsonBuffer<200> jsonBuffer;
				JsonObject& root = jsonBuffer.createObject();

				root["Value-lux"] = m_fIntensitylux;
				root["Value-fc"] = m_fIntensityfc;

				root.printTo(g_strJsonPrint);
			}
			else
			{
				Serial.println("LDR is disabled...");
			}	  
		}
	   /********************/
		else  if (m_strJsonAsk == "Voltmeter")
		{
			if(g_bEnablevoltmeter == true)
			{	  

				float  m_fVolt = vm.getVoltage();
				Serial.println(m_fVolt);
				StaticJsonBuffer<200> jsonBuffer;
				JsonObject& root = jsonBuffer.createObject();

				root["Value-volt"] = m_fVolt;
				root.printTo(g_strJsonPrint);
			}
			else
			{
				Serial.println("Voltmeter is disabled...");
			}	
		}
	   /********************/     
		else if (m_strJsonAsk == "Moisture")
		{
			if(g_bEnablemoisture == true)
			{
				int m_nMoistdata = analogRead(g_nMoisturepin);
				Serial.println(m_nMoistdata);
				StaticJsonBuffer<200> jsonBuffer;
				JsonObject& root = jsonBuffer.createObject();

				root["Moisture"] = m_nMoistdata;
				root.printTo(g_strJsonPrint);
			}
			else
			{
				Serial.println("Moisture is disabled...");
			}	
		}
	   /********************/    
		 else if (m_strJsonAsk == "Touch")
		{
		if(g_bEnabletouch == true)
			{
				const char* m_pchTouchState;
				int m_nStatetouch = digitalRead(g_nTouchpin);
				if (m_nStatetouch == HIGH)
				{
					Serial.println("contact detected");
					m_pchTouchState = "1";
				}
				if (m_nStatetouch == LOW)
				{
					Serial.println("no contact detected");
					m_pchTouchState = "0";
				}

				Serial.println();
				StaticJsonBuffer<512> jsonBuffer;
				JsonObject& root = jsonBuffer.createObject();
			  
				root["Value-tch"] = m_nStatetouch;
				root.printTo(g_strJsonPrint);
			}
			else
			{
				Serial.println("Touch is disabled...");
			}	
		}
		else if (m_strJsonAsk == "PIR")
		{
			if(g_bEnablepir == true)
			{
				const char* m_pchPirState;
				int m_nDetect = digitalRead(g_nPirpin);
				if (m_nDetect == HIGH)
				{
					Serial.println("Motion detected!");
					m_pchPirState = "1";
				}
				if (m_nDetect == LOW)
				{
					Serial.println("No Motion detected!");
					m_pchPirState = "0";
				}

				Serial.println();
				StaticJsonBuffer<200> jsonBuffer;
				JsonObject& root = jsonBuffer.createObject();
			  
				root["detect"] = m_pchPirState;
				root.printTo(g_strJsonPrint);
			}
			else
			{
				Serial.println("PIR is disabled...");
			}	  	  
	    }
		else if (m_strJsonAsk == "DCmotor")
		{
			if(g_bEnabledcmotor == true)
			{
				int m_nDCindex = root["Index"];
				const char* m_pchDCdir = root["Direction"];
				String m_strDCdir = m_pchDCdir;
				int m_nDCspeed = root["Speed"];
				if (m_nDCindex == 1)
				{
				  analogWrite(g_nDC13pin, m_nDCspeed);
				  if (m_strDCdir == "Right")
				  {
					digitalWrite(g_nDC11pin, HIGH);
					digitalWrite(g_nDC12pin, LOW);
				  }
				  if (m_strDCdir == "Left")
				  {
					digitalWrite(g_nDC11pin, LOW);
					digitalWrite(g_nDC12pin, HIGH);
				  }
				  if (m_strDCdir == "Stop")
				  {
					digitalWrite(g_nDC11pin, LOW);
					digitalWrite(g_nDC12pin, LOW);
				  }
				}

				root.printTo(g_strJsonPrint);
			}
			else
			{
				Serial.println("DCmotor is disabled...");
			}	  	  
	    }
	}
}
/*********************************ReadData************************************/
void NioKit::ReadSensor()
{
	int packetSize = Udp.parsePacket();
	if (packetSize)
	{
		IPAddress remote = Udp.remoteIP();
		Udp.read(UDP_packetBuffer, packetSize);
		JsonParse(UDP_packetBuffer);
		memset(UDP_packetBuffer, 0, sizeof(UDP_packetBuffer));
		Udp.beginPacket(Udp.remoteIP(), 48000);
		Udp.print(g_strJsonPrint);
		Udp.endPacket();

	}
		if (g_bEnablePubnub == true)
			if(g_strJsonPrint != "")
			{
		{
		Serial.println("pubnub begins ...");
		const int l_httpPort = 80;
		
		if (!client.connect(g_host, l_httpPort))
		{
			Serial.println("Pubnub Connection Failed");
			g_strJsonPrint= "";
			return;
		}
		g_strJsonPrint.replace("\"", "");
		Serial.println(g_strJsonPrint);
		Serial.println("Connected to pubnub");
		String url = "/publish/";
		url += g_pubKey;
		url += "/";
		url += g_subKey;
		url += "/0/";
		url += g_channel;
		url += "/myCallback/";
		url += "\""+g_strJsonPrint+"\"";

		  
		Serial.println(url);
  
		client.print(String("GET ") + url + " HTTP/1.1\r\n" +
        "Host: " + g_host + "\r\n" + 
        "Connection: close\r\n\r\n");
		delay(50);
   
	    while(client.available())
		{
			String line = client.readStringUntil('\r');
			Serial.print(line);
		}
		Serial.println();
		Serial.println("Pubnub Connection Closed");
		}
		g_strJsonPrint = "";
			}
}
/*******************************************MQ5************************************************/
float NioKit::Mq5ResistanceCalculation(int m_nADCin)
{
	return ( ((float)RL_VALUE_MQ5 * (1023 - m_nADCin) / m_nADCin));
}
/*********************/
float NioKit::Mq5Calibration(int m_nMqPin)
{
	int m_nCSampletime;
	float m_fRsAirVal = 0, m_fRout;
	for (m_nCSampletime = 0; m_nCSampletime < CALIBARAION_SAMPLE_TIMES; m_nCSampletime++) 
	{               //take multiple samples
		m_fRsAirVal += Mq5ResistanceCalculation(analogRead(m_nMqPin));
		delay(CALIBRATION_SAMPLE_INTERVAL);
	}
	m_fRsAirVal = m_fRsAirVal / CALIBARAION_SAMPLE_TIMES;            //calculate the average value
	m_fRout = m_fRsAirVal / RO_CLEAN_AIR_FACTOR_MQ5;                 //m_fRsAirVal divided by RO_CLEAN_AIR_FACTOR yields the Rout
	return m_fRout;
}
/********************/
float NioKit::Mq5Read(int m_nMqPin)
{
	int m_nRSampletime;
	float m_fRes = 0;
	for (m_nRSampletime = 0; m_nRSampletime < READ_SAMPLE_TIMES; m_nRSampletime++) 
	{
		m_fRes += Mq5ResistanceCalculation(analogRead(m_nMqPin));
		delay(READ_SAMPLE_INTERVAL);
	}
	m_fRes = m_fRes / READ_SAMPLE_TIMES;
	return m_fRes;
}
/*************************/
int NioKit::Mq5GetGasPercentage(float m_fRsRoRatio, int m_nGasid)
{
	if ( MQ5_accuracy == 0 ) 
	{
		if ( m_nGasid == GAS_HYDROGEN ) 
		{
			return (pow(10, ((-3.986 * (log10(m_fRsRoRatio))) + 3.075)));
		} 
		else if ( m_nGasid == GAS_LPG ) 
		{
			return (pow(10, ((-2.513 * (log10(m_fRsRoRatio))) + 1.878)));
		}
		else if ( m_nGasid == GAS_METHANE ) 
		{
			return (pow(10, ((-2.554 * (log10(m_fRsRoRatio))) + 2.265 )));
		}
		else if ( m_nGasid == GAS_CARBON_MONOXIDE ) 
		{
			return (pow(10, ((-6.900 * (log10(m_fRsRoRatio))) + 6.241)));
		} 
		else if ( m_nGasid == GAS_ALCOHOL ) 
		{
			return (pow(10, ((-4.590 * (log10(m_fRsRoRatio))) + 4.851)));
		}
	}

	else if ( MQ5_accuracy == 1 ) 
	{
		if ( m_nGasid == GAS_HYDROGEN ) 
		{
		  return (pow(10, (-22.89 * pow((log10(m_fRsRoRatio)), 3) + 8.873 * pow((log10(m_fRsRoRatio)), 2) - 3.587 * (log10(m_fRsRoRatio)) + 2.948)));
		} else if ( m_nGasid == GAS_LPG ) 
		{
		  return (pow(10, ((-2.513 * (log10(m_fRsRoRatio))) + 1.878)));
		} else if ( m_nGasid == GAS_METHANE ) 
		{
		  return (pow(10, (-0.428 * pow((log10(m_fRsRoRatio)), 2) - 2.867 * (log10(m_fRsRoRatio)) + 2.224)));
		} else if ( m_nGasid == GAS_CARBON_MONOXIDE ) 
		{
		  return (pow(10, (1401 * pow((log10(m_fRsRoRatio)), 4) - 2777 * pow((log10(m_fRsRoRatio)), 3) + 2059 * pow((log10(m_fRsRoRatio)), 2) - 682.5 * (log10(m_fRsRoRatio)) + 88.81)));
		} else if ( m_nGasid == GAS_ALCOHOL ) 
		{
		  return (pow(10, (14.90 * pow((log10(m_fRsRoRatio)), 3) - 19.26 * pow((log10(m_fRsRoRatio)), 2) + 3.108 * (log10(m_fRsRoRatio)) + 3.922)));
		}
	}
	return 0;
}
/*********************************************************RGB*******************************************************/

int NioKit::Strtoint(char m_chStr)
{
	if (m_chStr == 'a')return 10;
	if (m_chStr == 'b')return 11;
	if (m_chStr == 'c')return 12;
	if (m_chStr == 'd')return 13;
	if (m_chStr == 'e')return 14;
	if (m_chStr == 'f')return 15;
	if (m_chStr == '0')return 0;
	if (m_chStr == '1')return 1;
	if (m_chStr == '2')return 2;
	if (m_chStr == '3')return 3;
	if (m_chStr == '4')return 4;
	if (m_chStr == '5')return 5;
	if (m_chStr == '6')return 6;
	if (m_chStr == '7')return 7;
	if (m_chStr == '8')return 8;
	if (m_chStr == '9')return 9;
}


uint32_t NioKit:: HSL(uint16_t m_nH, uint8_t m_nS, uint8_t m_nL) 
{

	float m_fH, m_fS, m_fL, m_fTemp1, m_fTemp2, m_fTred, m_fTgreen, m_fTblue;
	 uint8_t m_nR, m_nG, m_nB;

	m_fH = (m_nH % 360) / 360.0;
	m_fS = constrain(m_nS, 0, 100) / 100.0;
	m_fL = constrain(m_nL, 0, 100) / 100.0;

	if ( m_fS == 0 )
	{ 
		m_nR = m_nG = m_nB = 255 * m_fL;
		return ((uint32_t)m_nR << 16) | ((uint32_t)m_nG <<  8) | m_nB;
	} 
	  
	if ( m_fL < 0.5 ) m_fTemp1 = m_fL * (1.0 + m_fS);
	else m_fTemp1 = m_fL + m_fS - m_fL * m_fS;
	  
	m_fTemp2 = 2 * m_fL - m_fTemp1;
	m_fTred = m_fH + 1/3.0;
	m_fTgreen = m_fH;
	m_fTblue = m_fH - 1/3.0;

	m_nR = HSLConvert(m_fTred, m_fTemp1, m_fTemp2);
	m_nG = HSLConvert(m_fTgreen, m_fTemp1, m_fTemp2);
	m_nB = HSLConvert(m_fTblue, m_fTemp1, m_fTemp2);

	return ((uint32_t)m_nR << 16) | ((uint32_t)m_fTgreen <<  8) | m_nB;
}
/*
 * HSL Convert
 * Helper function
 */
uint8_t NioKit::HSLConvert(float m_fColor, float m_fTemp1, float m_fTemp2) 
{

	if ( m_fColor < 0 ) m_fColor+=1; 
	else if ( m_fColor > 1 ) m_fColor-=1;

	if ( 6 * m_fColor < 1 ) m_fColor = m_fTemp2 + ( m_fTemp1 - m_fTemp2 ) * 6 * m_fColor;
	else if ( 2 * m_fColor < 1 ) m_fColor = m_fTemp1;
	else if ( 3 * m_fColor < 2 ) m_fColor = m_fTemp2 + ( m_fTemp1 - m_fTemp2 ) * ( 2/3.0 - m_fColor ) * 6;
	else m_fColor = m_fTemp2;
	  
	return (uint8_t)(m_fColor*255); 

}