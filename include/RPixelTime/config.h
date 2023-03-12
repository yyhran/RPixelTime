#pragma once

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

#define MCOLOR(r, g, b) \
    (uint16_t)(((uint16_t)((r) & 0xF8) << 8) | ((uint16_t)((g) & 0xFc) << 3) | ((b) >> 3))

class GlobalVar
{
    GlobalVar() = delete;
    GlobalVar(const GlobalVar&) = delete;
    GlobalVar& operator=(const GlobalVar&) = delete;

public:
    static uint16_t colorPalette[3];
    static uint32_t lastTime;
    static int colorIndex;
    static int displacement;
    static int freqGain[LED_XRES];
    static int intensity[LED_XRES];
    static double vReal[SAMPLES];
    static double vImage[SAMPLES];
};

uint16_t GlobalVar::colorPalette[3] = { MCOLOR(255, 0, 0), MCOLOR(0, 255, 0), MCOLOR(0, 0, 255) };
uint32_t GlobalVar::lastTime = 0;
int GlobalVar::displacement = 1;
int GlobalVar::colorIndex = 0;
int GlobalVar::freqGain[] = { 40, 42, 45, 47, 51, 55, 57, 59, 62, 65, 69, 71, 73, 76, 80, 82, 80, 78, 76, 74, 72, 70, 68, 66, 64, 60, 56, 52, 50, 46, 54, 40 };
int GlobalVar::intensity[LED_XRES] = { 0 };
double GlobalVar::vReal[] = { 0.0 };
double GlobalVar::vImage[] = { 0.0 };
