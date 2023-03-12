#pragma once

#include <arduinoFFT.h>
#include <FastLED.h>

#include <RPixelTime/config.h>
#include <RPixelTime/tools.h>
#include <RPixelTime/app.h>

namespace pixel
{
    
class PixelFFT : public App
{
public:
    PixelFFT(MatrixPtr matrix) : App(matrix), _FFT(arduinoFFT()) {}

    void update(bool)
    {
        getSamles();

        int color = 0;
        for(int i = 0; i < LED_XRES; i++)
        {
            CRGB tmpColor = CHSV(color, 255, 255);

            tools::drawYLine(_matrix, i, 8 - GlobalVar::intensity[i],
                             GlobalVar::intensity[i], MCOLOR(tmpColor.r, tmpColor.g, tmpColor.b));
            tools::drawYLine(_matrix, i, 0, 7 - GlobalVar::intensity[i], MCOLOR(0, 0, 0));

            color += 255 / LED_XRES;
            color %= 255;
        }
    }

private:
    void getSamles()
    {
        for(int i = 0; i < SAMPLES; i++)
        {
            GlobalVar::vReal[i] = analogRead(MIC_IN);
            GlobalVar::vImage[i] = 0;
        }

        _FFT.Windowing(GlobalVar::vReal, 1, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        _FFT.Compute(GlobalVar::vReal, GlobalVar::vImage, SAMPLES, FFT_FORWARD);
        _FFT.ComplexToMagnitude(GlobalVar::vReal, GlobalVar::vImage, SAMPLES);

        for(int i = 2; i < (LED_XRES * GlobalVar::displacement) + 2; i += GlobalVar::displacement)
        {
            GlobalVar::vReal[i] = constrain(GlobalVar::vReal[i], GlobalVar::freqGain[i - 2], 1300);
            GlobalVar::vReal[i] = map(GlobalVar::vReal[i], GlobalVar::freqGain[i - 2], 1300, 0, LED_YRES);
            GlobalVar::intensity[(i / GlobalVar::displacement) - 2]--;

            if(GlobalVar::vReal[i] > GlobalVar::intensity[(i / GlobalVar::displacement) - 2])
            {
                GlobalVar::intensity[(i / GlobalVar::displacement) - 2] = GlobalVar::vReal[i];
            }
        }
    }

private:
    arduinoFFT _FFT;
};

} // namespace pixel
