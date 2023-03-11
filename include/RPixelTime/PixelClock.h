#include <RPixelTime/config.h>
#include <RPixelTime/app.h>
#include <RPixelTime/tools.h>
#include <WiFiUdp.h>
#include <NTPClient.h>


namespace pixel
{

class PixelClock : public App
{
public:
    PixelClock(MatrixPtr matrix)
    : App(matrix)
    , _timeClient(_udp, "ntp1.aliyun.com", 60 * 60 * 8, 30 * 60 * 1000)
    {}

    ~PixelClock() override {};

    void update(bool impl) override
    {
        // TODO: show search WiFi animation when WiFi disconnected.
        _timeClient.update();
        Serial.println(_timeClient.getFormattedTime());
        auto hour = _timeClient.getFormattedTime().substring(0, 2);
        auto minute = _timeClient.getFormattedTime().substring(3, 5);
        auto second = _timeClient.getFormattedTime().substring(6, 8);
        auto day = _timeClient.getDay();

        if(impl || millis() - GlobalVar::lastTime > 1000)
        {
            if(!impl)
            {
                GlobalVar::lastTime = millis();
            }
            tools::showBitNumber(_matrix, hour, 3, 5, 2, 1, _matrix->Color(130, 20, 121));
            tools::showColon(_matrix, 10, 2, true, _matrix->Color(30, 120, 221));
            tools::showBitNumber(_matrix, minute, 3, 5, 12, 1, _matrix->Color(130, 20, 121));
            tools::showColon(_matrix, 20, 2, true, _matrix->Color(30, 120, 221));
            tools::showBitNumber(_matrix, second, 3, 5, 22, 1, _matrix->Color(130, 20, 121));

            tools::showWeek(_matrix, 2, 7, _matrix->Color(30, 30, 230));
            tools::showWeekDay(_matrix, day, 2, 7, _matrix->Color(230, 30, 30));
        }
    };

private:
    WiFiUDP _udp;
    NTPClient _timeClient;
};

} // namespace pixel
