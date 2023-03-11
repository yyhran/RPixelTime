#pragma once
#include <memory>
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
                matrix->drawPixel(xPos, j, matrix->Color(0, 0, 0));
            }
        }
        else
        {
            matrix->drawPixel(xPos, j, matrix->Color(0, 0, 0));
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
                matrix->drawPixel(i, j, matrix->Color(0, 0, 0));
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

void showWeek(MatrixPtr matrix, int xPos, int yPos, uint16_t colorxy)
{
    for(int i = 0; i < 7; i++)
    {
        drawXLine(matrix, xPos + i * 4, yPos, 3, colorxy);
    }
}

void showWeekDay(MatrixPtr matrix, int day, int xPos, int yPos, uint16_t colorxy)
{
    if(day == 0)
    {
        day = 7;
    }
    drawXLine(matrix, xPos + 4 * (day - 1), yPos, 3, colorxy);
}

void showTempPattern(MatrixPtr matrix)
{
    drawYLine(matrix, 1, 4, 3, matrix->Color(255, 255, 255));
    drawYLine(matrix, 2, 0, 8, matrix->Color(255, 255, 255));
    drawYLine(matrix, 3, 0, 8, matrix->Color(255, 255, 255));
    drawYLine(matrix, 4, 0, 8, matrix->Color(255, 255, 255));
    drawYLine(matrix, 5, 4, 3, matrix->Color(255, 255, 255));

    drawYLine(matrix, 2, 5, 2, matrix->Color(255, 48, 48));
    drawYLine(matrix, 3, 1, 6, matrix->Color(255, 48, 48));
    drawYLine(matrix, 4, 5, 2, matrix->Color(255, 48, 48));
}

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

void showPercentage(MatrixPtr matrix, int xPos, int yPos, uint16_t colorxy)
{
    matrix->drawPixel(xPos + 2, yPos + 2, colorxy);
    drawYLine(matrix, xPos + 4, yPos + 3, yPos + 3, colorxy);
    matrix->drawPixel(xPos + 5, yPos + 2, colorxy);
    matrix->drawPixel(xPos + 6, yPos + 2, colorxy);
    matrix->drawPixel(xPos + 5, yPos + 6, colorxy);
    matrix->drawPixel(xPos + 6, yPos + 6, colorxy);
}

} // namespace tools

} // namespace pixel
