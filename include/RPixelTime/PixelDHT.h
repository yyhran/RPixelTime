#pragma once

#include <DHT.h>
#include <tuple>

#include <Adafruit_Sensor.h>
#include <RPixelTime/app.h>
#include <RPixelTime/tools.h>

namespace pixel
{
    
class PixelDHT : public App
{
public:
    PixelDHT(MatrixPtr matrix)
    : App(matrix)
    , _dht(DHT_PIN, DHT_TYPE)
    , _innerMode(false)
    , _innerTime(0)
    {
        _dht.begin();
    }

    void update(bool impl) override
    {
        if(GlobalVar::lastTime - _innerTime > 5000)
        {
            _innerTime = millis();
            GlobalVar::lastTime = millis();
            _innerMode = !_innerMode;

            _matrix->clear();
            tools::showTempPattern(_matrix);
            _matrix->show();
        }

        if(_innerMode)
        {
            updateTemperature(impl);
        }
        else
        {
            updateHumidity(impl);
        }
    }

private:
    void updateTemperature(bool impl)
    {
        if(impl || millis() - GlobalVar::lastTime > 1000)
        {
            GlobalVar::lastTime = millis();

            auto temperature = _dht.readTemperature(true);
            if(isnan(temperature))
            {
                Serial.println("Read temperature from DHT failed!");
            }

            temperature = _dht.convertFtoC(temperature);
            Serial.println("Temperature: " + String(temperature) + " *C");
            tools::showTempPattern(_matrix);
            
            tools::showBitNumber(_matrix, String(static_cast<int>(temperature)), 3, 5,
                                 13, 2, GlobalVar::colorPalette[GlobalVar::colorIndex]);
            tools::showPercentage(_matrix, 23, 0, GlobalVar::colorPalette[GlobalVar::colorIndex]);
        }
    }

    void updateHumidity(bool impl)
    {
        if(impl || millis() - GlobalVar::lastTime > 1000)
        {
            GlobalVar::lastTime = millis();

            auto humidity = _dht.readHumidity(true);
            if(isnan(humidity))
            {
                Serial.println("Read humidity from DHT failed!");
            }

            Serial.println("Humidity: " + String(humidity) + " %");
            tools::showTempPattern(_matrix);
            tools::showBitNumber(_matrix, String(static_cast<int>(humidity)), 3, 5,
                                 13, 2, GlobalVar::colorPalette[GlobalVar::colorIndex]);
            tools::showHumidity(_matrix, 23, 0, GlobalVar::colorPalette[GlobalVar::colorIndex]);
        }
    }

    DHT _dht;
    bool _innerMode;
    uint32_t _innerTime;
};

} // namespace pixel
