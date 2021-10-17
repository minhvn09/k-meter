#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
ESP8266WebServer server1(80);//ip 20
ESP8266HTTPUpdateServer u;
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <EEPROM.h>
#include <PZEM004Tv30.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#include <PubSubClient.h>
String mserver  = "";
String mpass ="";
String muser ="";
String topic ="";
int mport =3883;
byte mqttac=0;
WiFiClient c;
PubSubClient MQTT(mserver.c_str(),mport,{},c);

//#include <Arduino.h>

//#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

//const char* fwImageURL = "raw.githubusercontent.com/minhvn09/k-meter/main/2ct-mqtt.bin";
byte ud=0;
String ver="161021H2V1";
const char trustRoot[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDxTCCAq2gAwIBAgIQAqxcJmoLQJuPC3nyrkYldzANBgkqhkiG9w0BAQUFADBs
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
d3cuZGlnaWNlcnQuY29tMSswKQYDVQQDEyJEaWdpQ2VydCBIaWdoIEFzc3VyYW5j
ZSBFViBSb290IENBMB4XDTA2MTExMDAwMDAwMFoXDTMxMTExMDAwMDAwMFowbDEL
MAkGA1UEBhMCVVMxFTATBgNVBAoTDERpZ2lDZXJ0IEluYzEZMBcGA1UECxMQd3d3
LmRpZ2ljZXJ0LmNvbTErMCkGA1UEAxMiRGlnaUNlcnQgSGlnaCBBc3N1cmFuY2Ug
RVYgUm9vdCBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMbM5XPm
+9S75S0tMqbf5YE/yc0lSbZxKsPVlDRnogocsF9ppkCxxLeyj9CYpKlBWTrT3JTW
PNt0OKRKzE0lgvdKpVMSOO7zSW1xkX5jtqumX8OkhPhPYlG++MXs2ziS4wblCJEM
xChBVfvLWokVfnHoNb9Ncgk9vjo4UFt3MRuNs8ckRZqnrG0AFFoEt7oT61EKmEFB
Ik5lYYeBQVCmeVyJ3hlKV9Uu5l0cUyx+mM0aBhakaHPQNAQTXKFx01p8VdteZOE3
hzBWBOURtCmAEvF5OYiiAhF8J2a3iLd48soKqDirCmTCv2ZdlYTBoSUeh10aUAsg
EsxBu24LUTi4S8sCAwEAAaNjMGEwDgYDVR0PAQH/BAQDAgGGMA8GA1UdEwEB/wQF
MAMBAf8wHQYDVR0OBBYEFLE+w2kD+L9HAdSYJhoIAu9jZCvDMB8GA1UdIwQYMBaA
FLE+w2kD+L9HAdSYJhoIAu9jZCvDMA0GCSqGSIb3DQEBBQUAA4IBAQAcGgaX3Nec
nzyIZgYIVyHbIUf4KmeqvxgydkAQV8GK83rZEWWONfqe/EW1ntlMMUu4kehDLI6z
eM7b41N5cdblIZQB2lWHmiRk9opmzN6cN82oNLFpmyPInngiK3BD41VHMWEZ71jF
hS9OMPagMRYjyOfiZRYzy78aG6A9+MpeizGLYAiJLQwGXFK3xPkKmNEVX58Svnw2
Yzi9RKR/5CYrCsSXaQ3pjOLAEFe4yHYSkVXySGnYvCoCWw9E1CAx2/S6cCZdkGCe
vEsXCS+0yx5DaMkHJ8HSXPfqIbloEpw8nL+e/IBcm2PN7EeqJSdnoDfzAIJ9VNep
+OkuE6N36B9K
-----END CERTIFICATE-----
)EOF";
X509List cert(trustRoot);

/*
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x26,16,2);
LiquidCrystal_I2C lcd2(0x27,16,2);

byte kw[8]={B10100,B11000,B10100,B10100,B00000,B10101,B10101,B11011};
byte so[8]={B01000,B10001,B01000,B10010,B00101,B00000,B00111,B00111};
byte nghin[8]={B11010,B10110,B10010,B00000,B01110,B11001,B01001,B01110};
byte hn[8]={B10010,B11110,B10010,B10010,B00000,B01101,B01011,B01001};
byte hq[8]={B10010,B11110,B10010,B10010,B00000,B01110,B01010,B01111};
byte tq[8]={B11100,B01000,B01000,B01000,B00000,B01110,B01010,B01111};
#include <Wire.h>

*/


#include <JC_Button.h>

Button myBtn(0);     
const unsigned long   LONG_PRESS(3000);

PZEM004Tv30 pzem1(5, 4);
PZEM004Tv30 pzem2(3, 1);
//PZEM004Tv30 pzem(5, 4);

//#define button D3
#define led 2
float v1=0;
float a1=0;
float w1=0;
float wh1=0;
float wh1d=0;
float f1=0;
float p1=0;
float v2=0;
float a2=0;
float w2=0;
float wh2=0;
float wh2d=0;
float f2=0;
float p2=0;


float don1=0;
float dhn1=0;
float dhq1=0;
float dot1=0;
float dtn1=0;
float dtt1=0;
float dt1=0;
float don2=0;
float dhn2=0;
float dhq2=0;
float dot2=0;
float dtn2=0;
float dtt2=0;
float dt2=0;


float ttn1=0;
float ttt1=0;
float ttn2=0;
float ttt2=0;
int den=0;
int key0=0;
int key=0;
//byte nhanlau=0;


//byte chot=0;
//float csHomqua, csHomtruoc, csThangroi, csThangtruoc;
int ngaychot=15;
byte phutbdchot=58;
byte bdchot=0;
int giochot=23, phutchot=59;
boolean resetE = false;
unsigned long times = 4000;
unsigned long nhanlau=0;
//unsigned long docpzem =4000;
unsigned long timemqtt =4000;
int giadien=1943;

//----------------------------
String ssid = "";
String pass="";
String blynk="";
String server="";
int bl=0;



WidgetRTC rtc;
//WidgetLED led_connect(V0);
WidgetTerminal terminal(V10);
//BlynkTimer timer;
//BlynkTimer timer1;
//boolean savedata = false;



void setup() {
//  Serial.begin(9600);
 
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
//pinMode(0, INPUT_PULLUP);
myBtn.begin();  
/*
  Wire.begin (12,13); //SCL-12, SDA-13
  //Wire.begin (12,14);//nha minh SCL-12, SDA-14
  lcd.init();
  lcd2.init();
lcd.backlight(); 
lcd2.backlight(); 
lcd.setCursor(0,0); //chao mung
   lcd.print("---KENHSTUDIO---");
   lcd.setCursor(0,1);
   lcd.print("CONG TO WIFI 1");

    lcd2.setCursor(0,0); //chao mung
   lcd2.print("---KENHSTUDIO---");
   lcd2.setCursor(0,1);
   lcd2.print("CONG TO WIFI 2");

  lcd.createChar(0,kw);  
  lcd.createChar(1,so);  
  lcd.createChar(2,nghin);  
  lcd.createChar(3,hn); 
  lcd.createChar(4,hq); 
  lcd.createChar(5,tq); 
    
   
  lcd2.createChar(0,kw);  
  lcd2.createChar(1,so);  
  lcd2.createChar(2,nghin);  
  lcd2.createChar(3,hn); 
  lcd2.createChar(4,hq); 
  lcd2.createChar(5,tq); 
delay(2000);
   */
         
    int can=sqrt(ESP.getChipId());
String chip="";
    chip=ESP.getChipId();
   key0=can*((chip.substring(0,2)).toInt())*(1989+(chip.substring(chip.length()-2,chip.length())).toInt());
   

  //attachInterrupt(digitalPinToInterrupt(button),resetEnergy,FALLING);
EEPROM.begin(2000);
delay(10);
EEPROM.get(340,giadien);
EEPROM.get(344,ngaychot);   
EEPROM.get(352,den);
EEPROM.get(356,key);
EEPROM.get(360,mport);
EEPROM.get(348,bl);

     for ( int i = 400; i < 440; ++i) 
            {
                ssid += char(EEPROM.read(i));
            }
            ssid.remove(ssid.indexOf("&"));
            ssid.trim();
    for ( int i = 440; i < 470; ++i) 
            {
                pass+= char(EEPROM.read(i));
            }
            pass.remove(pass.indexOf("&"));
            pass.trim();
 for ( int i = 470; i < 500; ++i) 
            {
                server+= char(EEPROM.read(i));
            }
            server.remove(server.indexOf("&"));
            server.trim();
 for ( int i = 500; i < 532; ++i) 
            {
                blynk+= char(EEPROM.read(i));
            }
            blynk.remove(blynk.indexOf("&"));
            blynk.trim();
 for ( int i = 535; i < 565; ++i) 
            {
                mserver+= char(EEPROM.read(i));
            }
            mserver.remove(mserver.indexOf("&"));
            mserver.trim();
 for ( int i = 565; i < 590; ++i) 
            {
                muser+= char(EEPROM.read(i));
            }
            muser.remove(muser.indexOf("&"));
            muser.trim();
 for ( int i = 590; i < 620; ++i) 
            {
                mpass+= char(EEPROM.read(i));
            }
            mpass.remove(mpass.indexOf("&"));
            mpass.trim();            
 for ( int i = 620; i < 650; ++i) 
            {
                topic+= char(EEPROM.read(i));
            }
            topic.remove(topic.indexOf("&"));
            topic.trim();  

WiFi.mode(WIFI_STA);
  wifiMulti.addAP("k-meter", "12345678");
  wifiMulti.addAP("chien-tang1", "876543218");
  wifiMulti.addAP("test2", "876543218");
  wifiMulti.addAP(ssid.c_str() ,pass.c_str());
  while (wifiMulti.run() != WL_CONNECTED){
delay(250);
        digitalWrite(led, LOW);
        delay(250);
        digitalWrite(led, HIGH);
 /*
   lcd.setCursor(0,0); //chao mung
   lcd.print("Dang KetNoi WiFi");
    lcd.setCursor(0,1); //chao mung
   lcd.print(millis()/1000);lcd.print("   --->>>             ");
*/
}
//timer.setInterval(3000L,doc);
//timer.setInterval(6000L,knl);
//timer.setInterval(5000L,sendblynk4);
//timer.setInterval(32000L,sendblynk30);
//timer.setInterval(300000L,sendblynk300);

/*
    lcd.setCursor(0,0); //chao mung
    lcd.print("WiFi:"+WiFi.SSID());lcd.print("          ");
    lcd.setCursor(0,1); //chao mung
    lcd.print(WiFi.localIP().toString());lcd.print("                    ");
   delay(2000);
lcd.setCursor(0,0); 
    lcd.print("                       ");
    lcd.setCursor(0,1); 
    lcd.print("                         ");
lcd2.setCursor(0,0); //chao mung
    lcd2.print("                       ");
    lcd2.setCursor(0,1); //chao mung
    lcd2.print("                         ");

if (den==0){
lcd.noBacklight(); 
lcd2.noBacklight(); }
*/

if(String(bl)!="1"){
	blynk ="c3Pirz6I2WLsI6z6BMj640OmF3_-2mD1";
	server ="blynk-cloud.com";
	}
Blynk.config(blynk.c_str(),server.c_str(),8080);
Blynk.connect();
if (mport>0&&mport<99999&&String(mport)!="nan"){
MQTT.setServer(mserver.c_str(),mport);
MQTT.connect("k-meter",muser.c_str(),mpass.c_str());
mqttac=1;
}
  readChiSo();
  setSyncInterval(60*60);
 // timer.setInterval(60000L,bdchot);
 // timer.setInterval(1000L,blinkled);
  
  terminal.clear();  

    u.setup(&server1,"/update");
    server1.begin();
    
if(giadien<=0||giadien>99999||String(giadien)=="nan")
{
        giadien=1943;
    }
 if(ngaychot<=0||ngaychot>31||String(ngaychot)=="nan")
{
        ngaychot=15;
    }

thongtin();
//Blynk.virtualWrite(V10,"wifi");
//Blynk.virtualWrite(V10,ssid);
}


void loop() {

if (ud==1) {up();}
myBtn.read();       
 if (myBtn.wasReleased()&&millis()-nhanlau>10000){  
ESP.restart();  }
       if (myBtn.pressedFor(LONG_PRESS)) { 
nhanlau=millis();
digitalWrite(led,LOW);

Blynk.disconnect(); 
Blynk.config("c3Pirz6I2WLsI6z6BMj640OmF3_-2mD1","blynk-cloud.com",8080);
Blynk.connect();

 }

  server1.handleClient();

    /*
      if(millis() - tled>2000){
    digitalWrite(led,LOW);
    tled=millis();
        }
       
      if(millis() - tled>1000){
    digitalWrite(led,HIGH);
        }
    */
/*
  if(millis() - docpzem>2000){
docpzem=millis();
  readPzem();
  readChiSo();
 rs();
 chot();
}
*/
  if(millis() - times>3000){
 //   if (wifiMulti.run() != WL_CONNECTED) {}
  times = millis();
if (key0!=key&&millis()>1200000){delay(86400000);}

//  if ( digitalRead(0) == LOW) {ESP.restart();} 
doc();
tien();
//hienthi();
sendblynk4();
knl();}
if(mqttac==1&&millis() - timemqtt>10000){
 timemqtt=millis();
 sendmqtt();
}
  Blynk.run();
 // timer.run();  
  
}
//==============Chương trình con======================//
/*
void hienthi(){
if (w1>9999){
lcd.setCursor(0,0); 
lcd.print(w1,0);lcd.print("w ");lcd.print(dtn1,0);lcd.print(" ");
lcd.print(dtt1,0);lcd.print("                ");} else {
lcd.setCursor(0,0); 
lcd.print(w1,0);lcd.print("w ");lcd.print(dtn1,2);lcd.print(" ");
lcd.print(dtt1,0);lcd.print("                ");}
if (w2>9999){
lcd.setCursor(0,1);
lcd.print(w2,0);lcd.print("w ");lcd.print(dtn2,0);lcd.print(" ");
lcd.print(dtt2,0);lcd.print("                ");
lcd2.setCursor(0,0); 
lcd2.print(w2,0);lcd2.print("w ");lcd2.print(dtn2,0);lcd2.print(" ");
lcd2.print(dtt2,0);lcd2.print("                ");
} else {
lcd.setCursor(0,1);
lcd.print(w2,0);lcd.print("w ");lcd.print(dtn2,2);lcd.print(" ");
lcd.print(dtt2,0);lcd.print("                ");
lcd2.setCursor(0,0); 
lcd2.print(w2,0);lcd2.print("w ");lcd2.print(dtn2,2);lcd2.print(" ");
lcd2.print(dtt2,0);lcd2.print("                ");
}

lcd2.setCursor(0,1);
lcd2.print(dhn2,1);lcd2.print(" ");lcd2.print(dhq2,0);lcd2.print(" ");
lcd2.print(ttn2,0);lcd2.print(" ");lcd2.print(ttt2,0);
lcd2.print("                ");

}

*/

void sendmqtt(){
String mqtt1;
mqtt1="{\"data\":[\""+String(dhn1,2)+"\",\""+String(dhq1,2)+"\",\""+String(dtn1,2)+"\",\""+String(dtt1,2)+"\",\""+String(ttn1,0)+"\",\""+String(ttt1,0)+"\",\""+String(dhn2,2)+"\",\""+String(dhq2,2)+"\",\""+String(dtn2,2)+"\",\""+String(dtt2,2)+"\",\""+String(ttn2,0)+"\",\""+String(ttt2,0)+"\",\""+String(v1,1)+"\",\""+String(a1,3)+"\",\""+String(w1,0)+"\",\""+String(wh1,2)+"\",\""+String(p1,2)+"\",\""+String(v2,1)+"\",\""+String(a2,3)+"\",\""+String(w2,0)+"\",\""+String(wh2,2)+"\",\""+String(p2,2)+"\",\""+String(f1,1)+"\"]}";

MQTT.publish(topic.c_str(),mqtt1.c_str());
}

void doc () {
readPzem();
  readChiSo();
rs();
 chot();
}

void tien(){
  if (dtn1>(1*400)) {ttn1=((dtn1-(1*400))*2927+909000*1)*1.1;} else {
  if (dtn1>(1*300))  {ttn1=((dtn1-(1*300))*2834+625600*1)*1.1;} else {
  if (dtn1>(1*200))  {ttn1=((dtn1-(1*200))*2536+372000*1)*1.1;} else {
  if (dtn1>(1*100))   { ttn1=((dtn1-(1*100))*2014+170600*1)*1.1; } else {
  if (dtn1>(1*50))     {ttn1=((dtn1-(1*50))*1734+83900*1)*1.1;} else {
     ttn1=dtn1*1678*1.1;}}}}}

     
    if (dtt1>(1*400)) {ttt1=((dtt1-(1*400))*2927+909000*1)*1.1;} else {
  if (dtt1>(1*300))  {ttt1=((dtt1-(1*300))*2834+625600*1)*1.1;} else {
  if (dtt1>(1*200))  {ttt1=((dtt1-(1*200))*2536+372000*1)*1.1;} else {
  if (dtt1>(1*100))   { ttt1=((dtt1-(1*100))*2014+170600*1)*1.1; } else {
  if (dtt1>(1*50))     {ttt1=((dtt1-(1*50))*1734+83900*1)*1.1;} else {
     ttt1=dtt1*1678*1.1;}}}}}
  if (dtn2>(1*400)) {ttn2=((dtn2-(1*400))*2927+909000*1)*1.1;} else {
  if (dtn2>(1*300))  {ttn2=((dtn2-(1*300))*2834+625600*1)*1.1;} else {
  if (dtn2>(1*200))  {ttn2=((dtn2-(1*200))*2536+372000*1)*1.1;} else {
  if (dtn2>(1*100))   { ttn2=((dtn2-(1*100))*2014+170600*1)*1.1; } else {
  if (dtn2>(1*50))     {ttn2=((dtn2-(1*50))*1734+83900*1)*1.1;} else {
     ttn2=dtn2*1678*1.1;}}}}}

     
    if (dtt2>(1*400)) {ttt2=((dtt2-(1*400))*2927+909000*1)*1.1;} else {
  if (dtt2>(1*300))  {ttt2=((dtt2-(1*300))*2834+625600*1)*1.1;} else {
  if (dtt2>(1*200))  {ttt2=((dtt2-(1*200))*2536+372000*1)*1.1;} else {
  if (dtt2>(1*100))   { ttt2=((dtt2-(1*100))*2014+170600*1)*1.1; } else {
  if (dtt2>(1*50))     {ttt2=((dtt2-(1*50))*1734+83900*1)*1.1;} else {
     ttt2=dtt2*1678*1.1;}}}}}




}


void sendblynk4 (){

Blynk.virtualWrite(V1, v1);   
Blynk.virtualWrite(V2, a1);   
Blynk.virtualWrite(V3, w1);   
Blynk.virtualWrite(V4, wh1d);   
Blynk.virtualWrite(V5, p1);   
Blynk.virtualWrite(V6, f1);   
Blynk.virtualWrite(V8, wh1);   
Blynk.virtualWrite(V11, dhn1);   
Blynk.virtualWrite(V12, dhq1);   
Blynk.virtualWrite(V13, dtn1);   
Blynk.virtualWrite(V14, dtt1);  
Blynk.virtualWrite(V15, ttn1);  
Blynk.virtualWrite(V16, ttt1);  

Blynk.virtualWrite(V41, v2);   
Blynk.virtualWrite(V42, a2);   
Blynk.virtualWrite(V43, w2);   
Blynk.virtualWrite(V44, wh2d);   
Blynk.virtualWrite(V45, p2);   
Blynk.virtualWrite(V46, f2);   
Blynk.virtualWrite(V48, wh2);   
Blynk.virtualWrite(V51, dhn2);   
Blynk.virtualWrite(V52, dhq2);   
Blynk.virtualWrite(V53, dtn2);   
Blynk.virtualWrite(V54, dtt2);   
Blynk.virtualWrite(V55, ttn2);  
Blynk.virtualWrite(V56, ttt2);  

    Blynk.virtualWrite(V7, millis()/1000);
    Blynk.virtualWrite(V25, 100+WiFi.RSSI());
}

void thongtin(){
  terminal.clear();
  if (key0==key){
     
      Blynk.virtualWrite(V30,"IP:"+(WiFi.localIP().toString())+"-ID:"+String(ESP.getChipId()));
Blynk.virtualWrite(V10,ver+"▮IP:"+(WiFi.localIP().toString())+" Wifi:"+WiFi.SSID()+"▮ID:"+String(ESP.getChipId())+"▮Ngày chốt:"+String(ngaychot));

    Blynk.setProperty(V10, "label","Nhập lệnh▮"+ver+"▮IP:"+(WiFi.localIP().toString())+"▮ID:"+String(ESP.getChipId())+"▮Ngày chốt:"+String(ngaychot)); }

else {
      Blynk.virtualWrite(V30,"HayKichHoat! IP:"+(WiFi.localIP().toString())+"-ID:"+String(ESP.getChipId()));
Blynk.virtualWrite(V10,"Hãy kích hoạt ! "+ver+"▮IP:"+(WiFi.localIP().toString())+" Wifi:"+WiFi.SSID()+"▮ID:"+String(ESP.getChipId())+"▮Ngày chốt:"+String(ngaychot));

    Blynk.setProperty(V10, "label","Hãy kích hoạt-"+ver+"▮IP:"+(WiFi.localIP().toString())+"▮ID:"+String(ESP.getChipId())+"▮Ngày chốt:"+String(ngaychot));

}
}


void rs(){
  if(resetE==true){
    resetE = false;
    pzem1.resetEnergy();
    pzem2.resetEnergy();
   EEPROM.begin(2000);
    
  for (int i = 0; i < 240; ++i) {
    EEPROM.write(i, 0);           
      delay(10);}

     EEPROM.commit();   
    EEPROM.end();   
    
    readChiSo();
  }
}

void readPzem(){
    
    wh1d = pzem1.energy();

   
    if(String(wh1d)!="nan"&&wh1d<99999)
    {
    v1 = pzem1.voltage();

    a1= pzem1.current();

    w1= pzem1.power();


    f1= pzem1.frequency();


    p1= pzem1.pf();
   wh1=wh1d;
     }
    
      wh2d = pzem2.energy();

   
    if(String(wh2d)!="nan"&&wh2d<99999)
    {
    v2 = pzem2.voltage();

    a2= pzem2.current();

    w2= pzem2.power();


    f2= pzem2.frequency();


    p2= pzem2.pf();
   wh2=wh2d;
     }
    
}

void knl(){
  if (wifiMulti.run() != WL_CONNECTED) {}
}
//-------------BLYNK----------------------
BLYNK_CONNECTED() {
  rtc.begin();
 // Blynk.syncVirtual(V32, V33,V34,V35,V36,V37);
}
/*
BLYNK_WRITE(V9){
  ngayChotSo = param.asInt();
}
*/

void readChiSo(){

  EEPROM.begin(2000);
      EEPROM.get(0,don1);
    EEPROM.get(4,dhq1);
    EEPROM.get(8,dtn1);
    EEPROM.get(12,dtt1);
    EEPROM.get(16,dt1);
    EEPROM.get(20,don2);
    EEPROM.get(24,dhq2);
    EEPROM.get(28,dtn2);
    EEPROM.get(32,dtt2);
    EEPROM.get(36,dt2);     
    
    EEPROM.end();
/////
if (wh1-don1>=0) {dhn1=wh1-don1;}
dtn1=dtn1+dhn1;
dt1=dt1+dhn1;
 if (wh2-don2>=0) {  dhn2=wh2-don2;}
dtn2=dtn2+dhn2;
dt2=dt2+dhn2;

}

void chot() {
if(minute() ==phutbdchot&&hour()==giochot){
bdchot=1;}
  if(bdchot==1&& hour()==giochot&& minute() == phutchot&&String(wh1)!="nan"&&String(wh2)!="nan"&&dhn1>=0&&dhn2>=0){
  
bdchot=0;
EEPROM.begin(2000);
        EEPROM.put(0,wh1);
        EEPROM.put(4,dhn1);
        EEPROM.put(8,dtn1);
        EEPROM.put(16,dt1);
        EEPROM.put(20,wh2);
        EEPROM.put(24,dhn2);
        EEPROM.put(28,dtn2);
        EEPROM.put(36,dt2);

        
    if(day()==ngaychot){
      EEPROM.put(8,0);
     EEPROM.put(12,dtn1);
      EEPROM.put(28,0);
     EEPROM.put(32,dtn2);
    }
    EEPROM.commit();delay(200);
     EEPROM.end();
    readChiSo();
thongtin();
  }
}

/*
void blinkled(){
  if(led_connect.getValue()){
    led_connect.off();
  }else{
    led_connect.on();
  }
}
*/

BLYNK_WRITE(V10)
{

   String code = param.asStr();
  
if (code=="timwifi") {    
    
     int n = WiFi.scanNetworks();
    if (n == 0)
    {
    }
    else
    {
        for (int i = 0; i < n; ++i)
        {

            delay(10);
        }
    }
    String st="";
    for (int i = 0; i < n; ++i)
    {       
        st += WiFi.SSID(i);
        st += "(";
        st += 100+WiFi.RSSI(i);
        st += "%)";
        st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
        st += " ";}
     terminal.println("Danh sach wifi: "+st);
    }
    else {

  if (code.substring(0,5) == "blynk")
      { EEPROM.begin(2000);
   String qblynk = code.substring(6,40);
   terminal.print(" Token blynk: "); terminal.println(qblynk);
   qblynk+="&";
                for (int i = 0; i < qblynk.length(); ++i)
                {
                    EEPROM.write(500+i, qblynk[i]);
                }
                EEPROM.put(348,1);
                EEPROM.commit();
                EEPROM.end();
                
                }

      else {
    if (code.substring(0,6) == "server")
      { EEPROM.begin(2000);
   String qser = code.substring(7,47);
   terminal.print(" Server blynk: "); terminal.println(qser);
   qser+="&";
                for (int i = 0; i < qser.length(); ++i)
                {
                    EEPROM.write(470+i, qser[i]);
                }
                EEPROM.commit();
                EEPROM.end();  
                } 
        else {          
   if (code.substring(0,7) == "mserver")
      { EEPROM.begin(2000);
   mserver = code.substring(8,47);
   terminal.print(" MQTT server: "); terminal.println(mserver);
   mserver+="&";
                for (int i = 0; i < mserver.length(); ++i)
                {
                    EEPROM.write(535+i, mserver[i]);
                }
                EEPROM.commit();
                EEPROM.end();  
                } else {   
     if (code.substring(0,5) == "muser")
      { EEPROM.begin(2000);
   muser = code.substring(6,47);
   terminal.print(" MQTT user: "); terminal.println(muser);
   muser+="&";
                for (int i = 0; i < muser.length(); ++i)
                {
                    EEPROM.write(565+i, muser[i]);
                }
                EEPROM.commit();
                EEPROM.end();  
                } 
        else {         
    if (code.substring(0,5) == "mpass")
      { EEPROM.begin(2000);
   mpass = code.substring(6,47);
   terminal.print(" MQTT pass: "); terminal.println(mpass);
   mpass+="&";
                for (int i = 0; i < mpass.length(); ++i)
                {
                    EEPROM.write(590+i, mpass[i]);
                }
                EEPROM.commit();
                EEPROM.end();  
                } 
        else {         
     if (code.substring(0,5) == "topic")
      { EEPROM.begin(2000);
   topic = code.substring(6,47);
   terminal.print(" MQTT topic: "); terminal.println(topic);
   topic+="&";
                for (int i = 0; i < topic.length(); ++i)
                {
                    EEPROM.write(620+i, topic[i]);
                }
                EEPROM.commit();
                EEPROM.end();  
                } 
        else { 
  if (code.substring(0,5) == "mport") {
     EEPROM.begin(2000);        
     EEPROM.put(360,code.substring(6,14).toInt()) ;
     EEPROM.get(360,mport);
     EEPROM.commit();
     EEPROM.end();
    terminal.print(" Port MQTT :  "); 
    terminal.println(mport); } 
else {
   if (code.substring(0,4) == "wifi")
                {EEPROM.begin(2000);
                String qsid = code.substring(5,40);
                terminal.print(" Tên Wifi: "); terminal.println(qsid);
                qsid +="&";               
                for (int i = 0; i < qsid.length(); ++i)
                {
                    EEPROM.write(400+i, qsid[i]);
                }
                EEPROM.commit();  EEPROM.end();          
                }  else {
    if (code.substring(0,4) == "pass")
      { EEPROM.begin(2000);
       String qpass = code.substring(5,37);
       terminal.print(" Mật khẩu Wifi: "); terminal.println(qpass);
       qpass+="&";
                for (int i = 0; i < qpass.length(); ++i)
                {
                    EEPROM.write(440+i, qpass[i]);
                }
                EEPROM.commit();
                EEPROM.end();
               
                }
     else {
           	    if (code.substring(0,5) == "vitri") {
     EEPROM.begin(2000);        
     EEPROM.put(code.substring(6,9).toFloat(),code.substring(10,21).toFloat()) ;
     //EEPROM.get(340,giadien);
     EEPROM.commit();
     EEPROM.end();
  terminal.print(" Vị trí "+ String(code.substring(6,9).toFloat())+"  là:  "+   String(code.substring(10,21).toFloat()));


 } 
       else {


if (code.substring(0,6) == "diachi") {pzem1.setAddress((code.substring(7,10)).toInt());           
    terminal.print(" Đã set địa chỉ là: "); terminal.println(pzem1.getAddress());
         }  else {
   if (code=="resetall") {resetE=true; terminal.println(" OK đã reset chỉ số pzem"); } else {       
    if (code=="resetcongto"){ ESP.restart();} 
        else {
    if (code.substring(0,3) == "gia") {
     EEPROM.begin(2000);        
     EEPROM.put(340,code.substring(4,14).toInt()) ;
     EEPROM.get(340,giadien);
     EEPROM.commit();
     EEPROM.end();
    terminal.print(" Giá điện là:  "); 
    terminal.println(giadien); } 
       else {
   if (code.substring(0,4) == "chot") {
     EEPROM.begin(2000);        
     EEPROM.put(344,code.substring(5,10).toInt()) ;
     EEPROM.get(344,ngaychot);
     EEPROM.commit();
     EEPROM.end();
    terminal.print(" Ngày chốt là:  "); 
    terminal.println(ngaychot); } 
else {
   if (code.substring(0,3) == "den") {
     EEPROM.begin(2000);        
     EEPROM.put(352,code.substring(4,10).toInt()) ;
     EEPROM.get(352,den);
     EEPROM.commit();
     EEPROM.end();
    terminal.print(" Bật đèn 0 tắt, 1 bật:  "); 
    terminal.println(den); 
/*
if (den==0)
{lcd.noBacklight(); 
lcd2.noBacklight();
}
if (den==1)
{lcd.backlight(); 
lcd2.backlight();
}
*/
} 
else {
   if (code.substring(0,3) == "key") {
     EEPROM.begin(2000);        
     EEPROM.put(356,code.substring(4,20).toInt()) ;
     EEPROM.get(356,key);
     EEPROM.commit();
     EEPROM.end();
    terminal.print(" Key kích hoạt là:  "); 
    terminal.println(key); } 
else {
   if (code== " key ") {
    terminal.print(" Key là:  "); 
    terminal.println(key0); } 
 else {
   if (code== "update") {
    terminal.print(" Bắt đầu update phần mềm !"); 
    ud=1;} 

    else { terminal.println(" Vui lòng nhập lại !");}}}}}}}}}}}}}}}}}}}}
terminal.flush();  
}

void up(){
ud=0;
//Serial.println("up");  
configTime(7 * 3600, 60000, "pool.ntp.org", "time.nist.gov");   
  WiFiClientSecure client2;
  client2.setTrustAnchors(&cert); 
  ESPhttpUpdate.setLedPin(2, LOW); 
    t_httpUpdate_return ret = ESPhttpUpdate.update(client2,"https://raw.githubusercontent.com/minhvn09/k-meter/main/2ct-mqtt.bin");       
    switch (ret) {
      case HTTP_UPDATE_FAILED:
        break;
      case HTTP_UPDATE_NO_UPDATES:
        break;
      case HTTP_UPDATE_OK:
        break;  }   
  
}