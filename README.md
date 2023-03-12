# 简介
使用 Esp32 控制 32x8 ws2812，实现类似 Awtrix 的效果。所用环境为 Esp32 + vscode + platformio。

已实现功能
+ 像素时钟（依赖阿里云的 ntp 服务）
+ 现实温湿度（使用 DHT11 读取）

# 使用方法
## 运行项目
连接好硬件后，更改 WiFi 名称与密码，然后编译烧录至 Esp32 即可

## 开发自定义 app
继承 `App` 类，实现 `void update(bool)` 函数，然后在 `AppManager` 中加入实现的 app 即可。
