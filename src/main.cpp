#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>

#include <WebServer.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <OneButton.h>

#include <vector>
#include <memory>

#include <RPixelTime/PixelWeather.h>
#include <RPixelTime/PixelClock.h>
#include <RPixelTime/PixelDHT.h>
#include <RPixelTime/PixelFFT.h>


auto matrix = std::make_shared<Adafruit_NeoMatrix>(LED_XRES, LED_YRES, 1, 1, LED_PIN,
                                                   NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                                                   NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                                   NEO_GRB + NEO_KHZ800);

const uint16_t colors[] = {
    matrix->Color(255, 0, 0),
    matrix->Color(0, 255, 0),
    matrix->Color(0, 0, 255),
};

OneButton button(BUTTON_PIN);

#if USE_ASYNC_SERVER
AsyncWebServer server(80);
#else
WebServer server(80);
#endif

void changeColor()
{
  // TODO: change the theme color
  GlobalVar::colorIndex = (GlobalVar::colorIndex + 1) % GlobalVar::colorPalette.size();
}

void changeMode()
{
  pixel::AppManager::getInstance().changeToNextApp();
}

void initMatrix()
{
  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(70);
  matrix->setTextColor(colors[GlobalVar::colorIndex]);
}

void connectWiFi()
{
  Serial.print("WiFi Connecting..");
  WiFi.begin("Redmi_K60", "12345678");

  do
  {
    // TODO: show connecting animation...
    delay(300);
    Serial.print(".");
  } while (WiFi.status() != WL_CONNECTED);

  Serial.println();
  Serial.print("WiFi Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // TODO: show connected animation...
}

void initLocalWiFi()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP(GlobalVar::apName.c_str(), GlobalVar::apPasswd.c_str());
}

#if USE_ASYNC_SERVER
void startWebServer()
{
  server.serveStatic("/", SPIFFS, "/");

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.begin();
}
#else
void stratWebServer()
{

}
#endif

void mountFileSystem()
{
  if(!SPIFFS.begin())
  {
    Serial.println("Mount SPIFFS failed.");
  }
  Serial.println("Mount SPIFFS success.");
}

void initButton()
{
  button.attachClick(changeMode);
  button.attachDoubleClick(changeColor);
}

void loadApps()
{
  pixel::AppManager::getInstance().addApp(std::make_shared<pixel::PixelClock>(matrix));
  pixel::AppManager::getInstance().addApp(std::make_shared<pixel::PixelWeather>(matrix));
  pixel::AppManager::getInstance().addApp(std::make_shared<pixel::PixelDHT>(matrix));
  pixel::AppManager::getInstance().addApp(std::make_shared<pixel::PixelFFT>(matrix));
}

void setup()
{
  Serial.begin(9600);
  delay(300);

  initMatrix();
  initButton();

  connectWiFi();
  initLocalWiFi();

  mountFileSystem();
  startWebServer(); // must after tcp_init(local WiFi or connected WiFi)

  loadApps();
}


void loop()
{
  // TODO: reconnecting the WiFi when WiFi disconnected ?
  button.tick();
  pixel::AppManager::getInstance().runCurApp();

#if !USE_ASYNC_SERVER
  server.handClient();
#endif
}