#pragma once

#include <vector>

#define LED_XRES 32
#define LED_YRES 8
#define NUM_LEDS 256
#define BRIGHTNESS 150
#define LED_TYPE WS2812
#define COLOR_ORDER GBR
#define DHT_PIN 13
#define DHT_TYPE DHT11
#define LED_PIN 32
#define BUTTON_PIN 14
#define NUMPIXELS 256
#define SAMPLES 64
#define MIC_IN 33

#define USE_ASYNC_SERVER 1

#define MCOLOR(r, g, b) \
    (uint16_t)(((uint16_t)((r) & 0xF8) << 8) | ((uint16_t)((g) & 0xFc) << 3) | ((b) >> 3))

class GlobalVar
{
    GlobalVar() = delete;
    GlobalVar(const GlobalVar&) = delete;
    GlobalVar& operator=(const GlobalVar&) = delete;

public:
    static uint32_t lastTime;

public:
    static std::vector<uint16_t> colorPalette;
    static int colorIndex;

public:
    static String apName;
    static String apPasswd;

public:
    static int displacement;
    static int freqGain[LED_XRES];
    static int intensity[LED_XRES];
    static double vReal[SAMPLES];
    static double vImage[SAMPLES];

public:
    static String cityID;
    static String weatherKey;
};

// global time
uint32_t GlobalVar::lastTime = 0;

// global color
std::vector<uint16_t> GlobalVar::colorPalette = { MCOLOR(255, 0, 0), MCOLOR(0, 255, 0), MCOLOR(0, 0, 255) };
int GlobalVar::colorIndex = 0;

// wifi ap mode
String GlobalVar::apName = "wifi test";
String GlobalVar::apPasswd = "1145141919";

// FFT global
int GlobalVar::displacement = 1;
int GlobalVar::freqGain[] = { 40, 42, 45, 47, 51, 55, 57, 59, 62, 65, 69, 71, 73, 76, 80, 82, 80, 78, 76, 74, 72, 70, 68, 66, 64, 60, 56, 52, 50, 46, 54, 40 };
int GlobalVar::intensity[] = { 0 };
double GlobalVar::vReal[] = { 0.0 };
double GlobalVar::vImage[] = { 0.0 };

// weather global
String GlobalVar::cityID = "beijing";
String GlobalVar::weatherKey = "SLfw0pwKxdurbQwdp";
