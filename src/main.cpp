#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <OneButton.h>

#include <vector>
#include <memory>

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

void changeColor()
{
  // TODO: change the theme color
}

void changeMode()
{
  pixel::AppManager::getInstance().changeToNextApp();
}

void connectWIFI()
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

void setup()
{
  Serial.begin(9600);
  delay(300);

  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(70);
  matrix->setTextColor(colors[1]);

  button.attachClick(changeMode);

  connectWIFI();

  // add apps
  pixel::AppManager::getInstance().addApp(std::make_shared<pixel::PixelClock>(matrix));
  pixel::AppManager::getInstance().addApp(std::make_shared<pixel::PixelDHT>(matrix));
  pixel::AppManager::getInstance().addApp(std::make_shared<pixel::PixelFFT>(matrix));
}

void loop()
{
  button.tick();
  pixel::AppManager::getInstance().runCurApp();
  // TODO: reconnecting the WiFi when WiFi disconnected ?
}