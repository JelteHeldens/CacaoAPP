# CacaoAPP

CacaoAPP is an ESP32-based hobby project to measure some parameters in the environment of a group of cacao (or cocoa) seedlings placed in a small greenhouse.

when powered, the device hosts a webserver accessible on "cacao.local". When connected to the same network as provided in [secrets.h](https://github.com/JelteHeldens/CacaoAPP/blob/main/CacaoAPP_code/arduino_secrets.h) in the "CacaoAPP_code" folder.

## Local Network Webserver

When the device is powered, it hosts a webserver accessible on "cacao.local". The resulting webpage is available on any device that is connected to the same network as the ESP32-device.

![image](https://github.com/JelteHeldens/CacaoAPP/blob/main/Images/Computer.png)
![image](https://github.com/JelteHeldens/CacaoAPP/blob/main/Images/Mobile.png)


## Version 1.0

Version 1.0 of this project contains a single DT22 temperature & humidity sensor.

Future plans include a soil humidity sensor, photoelectric resistors to measure the light, ...
