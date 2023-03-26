#pragma once

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#include <RPixelTime/config.h>
#include <RPixelTime/app.h>
#include <RPixelTime/tools.h>

namespace pixel
{

class PixelWeather : public App
{
public:
    PixelWeather(MatrixPtr matrix)
    : App(matrix)
    , _url("https://api.seniverse.com/v3/weather/daily.json?days=1&location=" + GlobalVar::cityID + "&key=" + GlobalVar::weatherKey)
    , _innerTimer(-1)
    , _doc(1024)
    , _weather({String(""), String(""), String("")})
    {
        _http.begin(_url);
    }

    void update(bool impl) override
    {
        if((_innerTimer == -1) || (millis() - _innerTimer > 1000 * 60 * 60 * 6))
        {
            _innerTimer = millis();
            getWeather();
        }

        if(impl || millis() - GlobalVar::lastTime > 1000)
        {
            GlobalVar::lastTime = millis();
            tools::showWeather(_matrix, _weather.text);
            tools::showBitNumber(_matrix, _weather.minTemp, 3, 5, 10, 2, GlobalVar::colorPalette[GlobalVar::colorIndex]);
            tools::showBitNumber(_matrix, _weather.maxTemp, 3, 5, 23, 2, GlobalVar::colorPalette[GlobalVar::colorIndex]);
        }

    }

private:
    void getWeather()
    {
        auto ret  = _http.GET();
        if(ret > 0)
        {
            Serial.println("HTTP get code: " + String(ret));
            if(ret == HTTP_CODE_OK)
            {
                auto recv = _http.getString();
                Serial.println(recv);

                deserializeJson(_doc, recv);
                _weather.minTemp = _doc["results"][0]["daily"][0]["low"].as<String>();
                _weather.maxTemp = _doc["results"][0]["daily"][0]["high"].as<String>();
                _weather.text = _doc["results"][0]["daily"][0]["text_day"].as<String>();
                Serial.printf("temp = (%s ~ %s), day = %s\n", _weather.minTemp, _weather.maxTemp, _weather.text);
            }
        }
        else
        {
            Serial.println("HTTP get error: " + _http.errorToString(ret));
        }
    }

private:
    String _url;
    uint32_t _innerTimer;
    HTTPClient _http;
    DynamicJsonDocument _doc;

    struct
    {
        String minTemp;
        String maxTemp;
        String text;
    } _weather;
};

} // namespace pixel
