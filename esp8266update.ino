/*
nhấn nút flash, gpio0 hoặc D3 kéo gnd để update
update phần mềm file .bin từ github truy cập http://địa chỉ ip/update
upload chứng chỉ http://địa chỉ ip/fs
tải file chứng chỉ upload vào esp: https://raw.githubusercontent.com/minhvn09/k-meter/main/certs.ar
*/
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#include <ESP8266HTTPUpdateServer.h>
ESP8266WebServer server1(80);
ESP8266HTTPUpdateServer u;
#include <ESP8266httpUpdate.h>
#include <FS.h>
#include <CertStoreBearSSL.h>
BearSSL::CertStore certStore;
File fsUploadFile;
unsigned long times = 0;
String diachifilebin="https://raw.githubusercontent.com/minhvn09/k-meter/main/899.bin";//thay địa chỉ thành của bạn

void setup() {
 Serial.begin(9600);
 pinMode(0, INPUT_PULLUP);
 SPIFFS.begin();
 int numCerts = certStore.initCertStore(SPIFFS, PSTR("/certs.idx"), PSTR("/certs.ar"));
WiFi.mode(WIFI_STA);
wifiMulti.addAP("abc", "12345678");//wifi 1
wifiMulti.addAP("xyz", "876543218");//wifi 2
//nháy led kết nối
     for ( int i = 1; i < 240&& wifiMulti.run() != WL_CONNECTED; ++i) 
            {
         delay(250);
        digitalWrite(2, LOW);
        delay(250);
        digitalWrite(2, HIGH);
            }

  u.setup(&server1,"/update");
   server1.on("/fs",[]{ 
 server1.send(200,"text/html",
"<html>"
"<meta charset='utf-8'>"
"<title>Upload chứng chỉ</title>"
"<form method='POST' action='/getfile' enctype='multipart/form-data'>"
"<input type='file' name='Chọn file'>"
"<input type='submit' value='Gửi file'>"
"</form>"
"</html>"
); 
 });
server1.on("/getfile",HTTP_POST,[]{
 server1.send(200,"text/html",
 "<html>"
 "<meta charset='utf-8'>"
 "<title>Upload chứng chỉ</title>"
 "<body>Upload thành công !</body>"
 "</html>"
); 
 },uploadchungchi);  
  server1.begin();
}

void loop() {
if (digitalRead(0)==LOW) {up();}
 server1.handleClient();

  if(millis() - times>3000){//kết nối lại wifi 
   if (wifiMulti.run() != WL_CONNECTED) {}
  times = millis();
  }
}
 
 void up(){//update phần mềm 

  configTime(7*3600, 0, "pool.ntp.org", "time.nist.gov");  // UTC
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    yield();
    delay(500);
    now = time(nullptr); }
    
    BearSSL::WiFiClientSecure client;
    bool mfln = client.probeMaxFragmentLength("raw.githubusercontent.com", 443, 1024);
    if (mfln) {
      client.setBufferSizes(1024, 1024);
    }
    client.setCertStore(&certStore); 
     ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);
    t_httpUpdate_return ret = ESPhttpUpdate.update(client,diachifilebin);
 
}

void uploadchungchi()
{
  HTTPUpload& upload = server1.upload();
  if(upload.status == UPLOAD_FILE_START)
  {
    String filename = upload.filename;
    if(!filename.startsWith("/"))
      filename = "/"+filename;
    //Serial.print("handleFileUpload Name: "); Serial.println(filename);
    fsUploadFile = SPIFFS.open(filename, "w");
  } else if(upload.status == UPLOAD_FILE_WRITE)
  {
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  } else if(upload.status == UPLOAD_FILE_END)
  {
    if(fsUploadFile)
      fsUploadFile.close();
    //Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
  }
}