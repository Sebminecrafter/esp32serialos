#pragma once
#include <Arduino.h>
#include "WiFi.h"

extern void startWifi();
extern void scan(String arguments);
extern void connect(String arguments);
extern void disconnect(String arguments);