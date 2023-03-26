#pragma once

#include <map>
#include <memory>
#include <functional>
#include <Adafruit_NeoMatrix.h>

namespace pixel
{
    
namespace tools
{

using MatrixPtr = std::shared_ptr<Adafruit_NeoMatrix>;

void drawXLine(MatrixPtr matrix, int xPos, int yPos, int width, uint16_t colorxy)
{
    for(int i = xPos; i < xPos + width; i++)
    {
        matrix->drawPixel(i, yPos, colorxy);
    }
}

void drawYLine(MatrixPtr matrix, int xPos, int yPos, int hight, uint16_t colorxy)
{
    for(int i = yPos; i < yPos + hight; i++)
    {
        matrix->drawPixel(xPos, i, colorxy);
    }
}

// :
void showColon(MatrixPtr matrix, int xPos, int yPos, bool l, uint16_t colorxy)
{
    String pstr = "101";
    for (int j = yPos; j < yPos + 3; j = j + (1))
    {
        if (String(pstr.charAt(j - yPos)).toInt() != 0)
        {
            if (l)
            {
                matrix->drawPixel(xPos, j, colorxy);
            }
            else
            {
                matrix->drawPixel(xPos, j, MCOLOR(0, 0, 0));
            }
        }
        else
        {
            matrix->drawPixel(xPos, j, MCOLOR(0, 0, 0));
        }
    }
}

static String bitData[10] = /* 0~9 */
{
  "111101101101111","010110010010111",
  "111001111100111","111001111001111",
  "101101111001001","111100111001111",
  "111100111101111","111001001001001",
  "111101111101111","111101111001111",
};

void showBitMap(MatrixPtr matrix, String bitStr, int xLength, int yLength,
                int xPos, int yPos, uint16_t colorxy)
{
    for(int i = xPos; i < xPos + xLength; i++)
    {
        for(int j = yPos; j < yPos + yLength; j++)
        {
            if(String(bitStr.charAt((j - yPos) * xLength + i - xPos)).toInt() != 0)
            {
                matrix->drawPixel(i, j, colorxy);
            }
            else
            {
                matrix->drawPixel(i, j, MCOLOR(0, 0, 0));
            }
        }
    }
}

void showBitNumber(MatrixPtr matrix, String number, int xLength, int yLength,
                   int xPos, int yPos, uint16_t colorxy)
{
    if(number.toInt() < 10)
    {
        showBitMap(matrix, bitData[0], xLength, yLength, xPos, yPos, colorxy);
        showBitMap(matrix, bitData[String(number.charAt(1)).toInt()],
                   xLength, yLength, xPos + 4, yPos, colorxy);
    }
    else
    {
        int num = number.toInt();
        int step = 0;
        while (num)
        {
            showBitMap(matrix, bitData[String(number.charAt(step)).toInt()],
                       xLength, yLength, xPos + 4 * step, yPos, colorxy);
            num /= 10;
            step++;
        }
    }
}

void showWeekDay(MatrixPtr matrix, int day, int xPos, int yPos, uint16_t colorw, uint16_t colorwd)
{
    for(int i = 0; i < 7; i++)
    {
        drawXLine(matrix, xPos + i * 4, yPos, 3, colorw);
    }

    if(day == 0)
    {
        day = 7;
    }
    drawXLine(matrix, xPos + 4 * (day - 1), yPos, 3, colorwd);
}

// temp icon
void showTempPattern(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    drawYLine(matrix, 1 + xPos, 4 + yPos, 3, MCOLOR(255, 255, 255));
    drawYLine(matrix, 2 + xPos, 0 + yPos, 8, MCOLOR(255, 255, 255));
    drawYLine(matrix, 3 + xPos, 0 + yPos, 8, MCOLOR(255, 255, 255));
    drawYLine(matrix, 4 + xPos, 0 + yPos, 8, MCOLOR(255, 255, 255));
    drawYLine(matrix, 5 + xPos, 4 + yPos, 3, MCOLOR(255, 255, 255));

    drawYLine(matrix, 2 + xPos, 5 + yPos, 2, MCOLOR(255, 48, 48));
    drawYLine(matrix, 3 + xPos, 1 + yPos, 6, MCOLOR(255, 48, 48));
    drawYLine(matrix, 4 + xPos, 5 + yPos, 2, MCOLOR(255, 48, 48));
}

// %
void showHumidity(MatrixPtr matrix, int xPos, int yPos, uint16_t colorxy)
{
    matrix->drawPixel(xPos + 3, yPos + 2, colorxy);
    matrix->drawPixel(xPos + 2, yPos + 6, colorxy);
    matrix->drawPixel(xPos + 3, yPos + 5, colorxy);
    matrix->drawPixel(xPos + 4, yPos + 4, colorxy);
    matrix->drawPixel(xPos + 5, yPos + 3, colorxy);
    matrix->drawPixel(xPos + 6, yPos + 2, colorxy);
    matrix->drawPixel(xPos + 5, yPos + 6, colorxy);
}

// ℃
void showPercentage(MatrixPtr matrix, int xPos, int yPos, uint16_t colorxy)
{
    matrix->drawPixel(xPos + 2, yPos + 2, colorxy);
    drawYLine(matrix, xPos + 4, yPos + 3, yPos + 3, colorxy);
    matrix->drawPixel(xPos + 5, yPos + 2, colorxy);
    matrix->drawPixel(xPos + 6, yPos + 2, colorxy);
    matrix->drawPixel(xPos + 5, yPos + 6, colorxy);
    matrix->drawPixel(xPos + 6, yPos + 6, colorxy);
}

// weathers
void showWeatherSunnyD(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->fillRect(2 + xPos, 3 + yPos, 4, 2, MCOLOR(255, 255, 0));
    matrix->fillRect(3 + xPos, 2 + yPos, 2, 4, MCOLOR(255, 255, 0));
    matrix->drawPixel(2 + xPos, 0 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(5 + xPos, 0 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(0 + xPos, 2 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(7 + xPos, 2 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(0 + xPos, 5 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(7 + xPos, 5 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(2 + xPos, 7 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(5 + xPos, 7 + yPos, MCOLOR(255, 255, 0));
}
void showWeatherSunnyN(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->drawFastVLine(0 + xPos, 3 + yPos, 3, MCOLOR(190, 190, 190));
    matrix->drawFastVLine(1 + xPos, 3 + yPos, 3, MCOLOR(255, 255, 255));
    matrix->drawFastHLine(2 + xPos, 7 + yPos, 3, MCOLOR(190, 190, 190));
    matrix->drawPixel(5 + xPos, 0 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(7 + xPos, 2 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(4 + xPos, 4 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(6 + xPos, 6 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(2 + xPos, 1 + yPos, MCOLOR(190, 190, 190));
    matrix->drawPixel(1 + xPos, 2 + yPos, MCOLOR(190, 190, 190));
    matrix->drawPixel(1 + xPos, 6 + yPos, MCOLOR(190, 190, 190));
    matrix->drawPixel(3 + xPos, 1 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(2 + xPos, 2 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(2 + xPos, 6 + yPos, MCOLOR(255, 255, 255));
}

void showWeatherCloudyD(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->drawPixel(2 + xPos, 0 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(4 + xPos, 0 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(0 + xPos, 1 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(0 + xPos, 3 + yPos, MCOLOR(255, 255, 0));
    matrix->drawFastHLine(2 + xPos, 2 + yPos, 3, MCOLOR(255, 255, 0));
    matrix->drawPixel(5 + xPos, 2 + yPos, MCOLOR(255, 255, 255));
    matrix->fillRect(2 + xPos, 3 + yPos, 5, 5, MCOLOR(255, 255, 255));
    matrix->drawPixel(2 + xPos, 3 + yPos, MCOLOR(255, 255, 0));
    matrix->drawFastHLine(4 + xPos, 3 + yPos, 3, MCOLOR(180, 180, 180));
    matrix->drawFastHLine(4 + xPos, 4 + yPos, 2, MCOLOR(150, 150, 150));
    matrix->drawPixel(4 + xPos, 5 + yPos, MCOLOR(150, 150, 150));
    matrix->drawFastVLine(1 + xPos, 5 + yPos, 2, MCOLOR(180, 180, 180));
    matrix->drawFastVLine(7 + xPos, 4 + yPos, 3, MCOLOR(180, 180, 180));
}
void showWeatherCloudyN(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->drawFastVLine(1 + xPos, 2 + yPos, 2, MCOLOR(255, 255, 255));
    matrix->drawFastVLine(2 + xPos, 1 + yPos, 4, MCOLOR(255, 255, 255));
    matrix->drawFastHLine(2 + xPos, 4 + yPos, 2, MCOLOR(255, 255, 255));
    matrix->drawFastHLine(3 + xPos, 5 + yPos, 4, MCOLOR(255, 255, 255));
    matrix->drawFastHLine(3 + xPos, 6 + yPos, 2, MCOLOR(128, 128, 128));
    matrix->drawPixel(0 + xPos, 0 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(3 + xPos, 0 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(6 + xPos, 1 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(1 + xPos, 4 + yPos, MCOLOR(128, 128, 128));
    matrix->drawPixel(7 + xPos, 4 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(2 + xPos, 5 + yPos, MCOLOR(128, 128, 128));
    matrix->drawPixel(1 + xPos, 7 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(7 + xPos, 7 + yPos, MCOLOR(255, 255, 255));
}

void showWeatherOvercast(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->drawFastVLine(1 + xPos, 2 + yPos, 2, MCOLOR(100, 100, 100));
    matrix->drawFastVLine(5 + xPos, 1 + yPos, 2, MCOLOR(100, 100, 100));
    matrix->drawPixel(4 + xPos, 2 + yPos, MCOLOR(100, 100, 100));
    matrix->drawPixel(7 + xPos, 2 + yPos, MCOLOR(100, 100, 100));
    matrix->drawFastHLine(5 + xPos, 2 + yPos, 2, MCOLOR(200, 200, 200));
    matrix->drawFastHLine(0 + xPos, 3 + yPos, 8, MCOLOR(190, 190, 190));
    matrix->drawPixel(0 + xPos, 3 + yPos, MCOLOR(100, 100, 100));
    matrix->drawPixel(3 + xPos, 3 + yPos, MCOLOR(100, 100, 100));
    matrix->drawFastHLine(0 + xPos, 4 + yPos, 7, MCOLOR(180, 180, 180));
    matrix->drawFastHLine(0 + xPos, 5 + yPos, 7, MCOLOR(150, 150, 150));
    matrix->drawPixel(0 + xPos, 5 + yPos, MCOLOR(100, 100, 100));
    matrix->drawPixel(7 + xPos, 5 + yPos, MCOLOR(100, 100, 100));
    matrix->drawFastHLine(1 + xPos, 6 + yPos, 6, MCOLOR(110, 110, 110));
}

void showWeatherRain(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->fillRect(1 + xPos, 1 + yPos, 2, 4, MCOLOR(255, 255, 255));
    matrix->fillRect(2 + xPos, 3 + yPos, 5, 2, MCOLOR(255, 255, 255));
    matrix->fillRect(4 + xPos, 1 + yPos, 4, 3, MCOLOR(255, 255, 255));

    matrix->drawPixel(5 + xPos, 0 + yPos, MCOLOR(150, 150, 150));
    matrix->drawPixel(4 + xPos, 1 + yPos, MCOLOR(150, 150, 150));
    matrix->drawPixel(7 + xPos, 1 + yPos, MCOLOR(150, 150, 150));
    matrix->drawPixel(0 + xPos, 2 + yPos, MCOLOR(150, 150, 150));
    matrix->drawPixel(1 + xPos, 4 + yPos, MCOLOR(150, 150, 150));
    matrix->drawPixel(0 + xPos, 3 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(6 + xPos, 0 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(1 + xPos, 5 + yPos, MCOLOR(0, 255, 255));
    matrix->drawPixel(0 + xPos, 6 + yPos, MCOLOR(0, 255, 255));
    matrix->drawPixel(4 + xPos, 5 + yPos, MCOLOR(0, 255, 255));
    matrix->drawPixel(3 + xPos, 6 + yPos, MCOLOR(0, 255, 255));
    matrix->drawPixel(2 + xPos, 7 + yPos, MCOLOR(0, 255, 255));
    matrix->drawPixel(7 + xPos, 5 + yPos, MCOLOR(0, 255, 255));
    matrix->drawPixel(6 + xPos, 6 + yPos, MCOLOR(0, 255, 255));
    matrix->drawPixel(5 + xPos, 7 + yPos, MCOLOR(0, 255, 255));
}

void showWeatherSleet(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->fillRect(1 + xPos, 1 + yPos, 2, 4, MCOLOR(255, 255, 255));
    matrix->fillRect(2 + xPos, 3 + yPos, 5, 2, MCOLOR(255, 255, 255));
    matrix->fillRect(4 + xPos, 1 + yPos, 4, 3, MCOLOR(255, 255, 255));

    matrix->drawPixel(5 + xPos, 0 + yPos, MCOLOR(150, 150, 150));
    matrix->drawPixel(4 + xPos, 1 + yPos, MCOLOR(150, 150, 150));
    matrix->drawPixel(7 + xPos, 1 + yPos, MCOLOR(150, 150, 150));
    matrix->drawPixel(0 + xPos, 2 + yPos, MCOLOR(150, 150, 150));
    matrix->drawPixel(1 + xPos, 4 + yPos, MCOLOR(150, 150, 150));
    matrix->drawPixel(0 + xPos, 3 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(6 + xPos, 0 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(1 + xPos, 5 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(0 + xPos, 6 + yPos, MCOLOR(0, 255, 255));
    matrix->drawPixel(4 + xPos, 5 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(3 + xPos, 6 + yPos, MCOLOR(0, 255, 255));
    matrix->drawPixel(2 + xPos, 7 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(7 + xPos, 5 + yPos, MCOLOR(0, 255, 255));
    matrix->drawPixel(6 + xPos, 6 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(5 + xPos, 7 + yPos, MCOLOR(0, 255, 255));
}

void showWeatherSnowyDay(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->fillRect(2 + xPos, 1 + yPos, 4, 3, MCOLOR(255, 255, 255));
    matrix->fillRect(1 + xPos, 4 + yPos, 6, 4, MCOLOR(255, 255, 255));
    matrix->drawFastVLine(0 + xPos, 5 + yPos, 2, MCOLOR(205, 133, 63));
    matrix->drawFastVLine(7 + xPos, 5 + yPos, 2, MCOLOR(205, 133, 63));
    matrix->drawPixel(1 + xPos, 6 + yPos, MCOLOR(205, 133, 63));
    matrix->drawPixel(6 + xPos, 6 + yPos, MCOLOR(205, 133, 63));
    matrix->drawFastHLine(3 + xPos, 0 + yPos, 2, MCOLOR(255, 0, 0));
    matrix->drawFastHLine(3 + xPos, 3 + yPos, 2, MCOLOR(100, 100, 100));
    matrix->drawPixel(2 + xPos, 2 + yPos, MCOLOR(0, 0, 255));
    matrix->drawPixel(5 + xPos, 2 + yPos, MCOLOR(0, 0, 255));
}

void showWeatherSlightSnow(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->drawFastVLine(3 + xPos, 0 + yPos, 4, MCOLOR(230, 255, 255));
    matrix->drawFastHLine(2 + xPos, 1 + yPos, 3, MCOLOR(230, 255, 255));
    matrix->drawFastVLine(1 + xPos, 3 + yPos, 3, MCOLOR(230, 255, 255));
    matrix->drawFastHLine(0 + xPos, 4 + yPos, 4, MCOLOR(230, 255, 255));
    matrix->drawFastVLine(4 + xPos, 4 + yPos, 4, MCOLOR(230, 255, 255));
    matrix->drawFastHLine(3 + xPos, 6 + yPos, 3, MCOLOR(230, 255, 255));
    matrix->drawFastVLine(6 + xPos, 2 + yPos, 3, MCOLOR(230, 255, 255));
    matrix->drawFastHLine(4 + xPos, 3 + yPos, 4, MCOLOR(230, 255, 255));
}

void showWeatherThunderstorm(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->fillRect(2 + xPos, 3 + yPos, 2, 2, MCOLOR(255, 255, 255));
    matrix->fillRect(4 + xPos, 2 + yPos, 2, 3, MCOLOR(255, 255, 255));
    matrix->drawFastVLine(1 + xPos, 3 + yPos, 2, MCOLOR(100, 100, 100));
    matrix->drawFastVLine(6 + xPos, 2 + yPos, 4, MCOLOR(100, 100, 100));
    matrix->drawFastHLine(0 + xPos, 5 + yPos, 4, MCOLOR(100, 100, 100));
    matrix->drawFastHLine(2 + xPos, 2 + yPos, 2, MCOLOR(100, 100, 100));
    matrix->drawFastHLine(4 + xPos, 1 + yPos, 2, MCOLOR(100, 100, 100));
    matrix->drawFastHLine(5 + xPos, 5 + yPos, 3, MCOLOR(100, 100, 100));
    matrix->drawPixel(4 + xPos, 3 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(3 + xPos, 4 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(4 + xPos, 5 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(3 + xPos, 6 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(2 + xPos, 7 + yPos, MCOLOR(255, 255, 0));
    matrix->drawPixel(1 + xPos, 6 + yPos, MCOLOR(0, 0, 255));
    matrix->drawPixel(0 + xPos, 7 + yPos, MCOLOR(0, 0, 255));
    matrix->drawPixel(6 + xPos, 6 + yPos, MCOLOR(0, 0, 255));
    matrix->drawPixel(5 + xPos, 7 + yPos, MCOLOR(0, 0, 255));
}

void showWeatherWindy(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->fillRect(2 + xPos, 2, 3, 2, MCOLOR(255, 255, 255));
    matrix->drawFastHLine(0 + xPos, 0 + yPos, 2, MCOLOR(255, 255, 255));
    matrix->drawFastHLine(1 + xPos, 1 + yPos, 2, MCOLOR(255, 255, 255));
    matrix->drawFastHLine(4 + xPos, 1 + yPos, 2, MCOLOR(255, 255, 255));
    matrix->drawFastHLine(5 + xPos, 0 + yPos, 2, MCOLOR(255, 255, 255));
    matrix->drawFastHLine(4 + xPos, 4 + yPos, 3, MCOLOR(255, 255, 255));
    matrix->drawPixel(6 + xPos, 5 + yPos, MCOLOR(255, 255, 255));
    matrix->drawFastVLine(1 + xPos, 3 + yPos, 2, MCOLOR(255, 255, 255));
    matrix->drawFastVLine(0 + xPos, 4 + yPos, 2, MCOLOR(255, 255, 255));
    matrix->drawFastVLine(3 + xPos, 4 + yPos, 4, MCOLOR(130, 130, 130));
}

void showWeatherUnknown(MatrixPtr matrix, int xPos = 0, int yPos = 0)
{
    matrix->drawFastHLine(4 + xPos, 5, 3, MCOLOR(255, 255, 255));

    matrix->drawPixel(1 + xPos, 1 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(2 + xPos, 2 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(3 + xPos, 3 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(2 + xPos, 4 + yPos, MCOLOR(255, 255, 255));
    matrix->drawPixel(1 + xPos, 5 + yPos, MCOLOR(255, 255, 255));
}

void showWeather(MatrixPtr matrix, String weather, int xPos = 0, int yPos = 0)
{
    std::map<String, std::function<void(MatrixPtr, int, int)>> weatherIconMap =
    {
        {String("晴"), showWeatherSunnyD},
        {String("多云"), showWeatherCloudyD},
        {String("阴"), showWeatherOvercast},
        {String("雨"), showWeatherRain},
        {String("雨夹雪"), showWeatherSleet},
        {String("雪晴"), showWeatherSnowyDay},
        {String("小雪"), showWeatherSlightSnow},
        {String("雷雨"), showWeatherThunderstorm},
        {String("风"), showWeatherWindy},
    };

    auto it = weatherIconMap.find(weather);
    if(it != std::end(weatherIconMap))
    {
        it->second(matrix, xPos, yPos);
    }
    else
    {
        showWeatherUnknown(matrix, xPos, yPos);
    }
}

} // namespace tools

} // namespace pixel
