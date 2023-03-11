#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <memory>
#include <vector>

namespace pixel
{

class App
{
public:
    using MatrixPtr = std::shared_ptr<Adafruit_NeoMatrix>;
    App(MatrixPtr ptr) : _matrix(ptr) {};
    virtual ~App() {};

    void changeToApp()
    {
        _matrix->clear();
        _matrix->show();

        update(true);

        _matrix->show();

    }

    void runApp()
    {
        update(false);
        _matrix->show();
    }

    virtual void update(bool) = 0;

protected:
    MatrixPtr _matrix;
};

template<typename T>
class Singleton
{
protected:
    Singleton() = default;

public:
    static T& getInstance() noexcept
    {
        static T instance;
        return instance;
    }

    virtual ~Singleton() noexcept = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

class AppManager : public Singleton<AppManager>
{
public:
    friend Singleton<AppManager>;
    using AppPtr = std::shared_ptr<App>;
    using AppList = std::vector<AppPtr>;

    void addApp(const AppPtr& app)
    {
        _appList.emplace_back(app);
    }

    void addApp(AppPtr&& app)
    {
        _appList.emplace_back(app);
    }

    void runCurApp()
    {
        _appList[_mode]->runApp();
    }

    void changeToApp(int mode)
    {
        mode %= static_cast<int>(_appList.size());
        _mode = mode;
        Serial.println("Change mode to " + String(_mode));
        _appList[_mode]->changeToApp();
    }

    void changeToNextApp()
    {
        _mode++;
        changeToApp(_mode);
    }

    void setMde(int mode)
    {
        _mode = mode;
    }

private:
    AppManager() = default;

private:
    AppList _appList;
    int _mode = 0;
};


class GlobalVar
{
    GlobalVar() = delete;
    GlobalVar(const GlobalVar&) = delete;
    GlobalVar& operator=(const GlobalVar&) = delete;

public:
    using MatrixPtr = std::shared_ptr<Adafruit_NeoMatrix>;

    static uint32_t lastTime;
};
uint32_t GlobalVar::lastTime = 0;

} // namespace pixel