#include <Arduino.h>
#include "utilities/utilities.h"
#include "WiFi.h"
#include "commands/command/wifi/main.h"

void startWifi()
{
    Serial.println("WiFi initialized");
    // Enable Station Interface
    WiFi.begin();
    WiFi.mode(WIFI_MODE_STA);
}

void ScanWiFi()
{
    Serial.println("Scanning...");
    // WiFi.scanNetworks will return the number of networks found.
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");
    Serial.print(n);
    Serial.println(" networks found");
    Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
    for (int i = 0; i < n; ++i)
    {
        // Print SSID and RSSI for each network found
        Serial.printf("%2d", i + 1);
        Serial.print(" | ");
        Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
        Serial.print(" | ");
        Serial.printf("%4ld", WiFi.RSSI(i));
        Serial.print(" | ");
        Serial.printf("%2ld", WiFi.channel(i));
        Serial.print(" | ");
        switch (WiFi.encryptionType(i))
        {
        case WIFI_AUTH_OPEN:
            Serial.print("OPEN");
            break;
        case WIFI_AUTH_WEP:
            Serial.print("WEP");
            break;
        case WIFI_AUTH_WPA_PSK:
            Serial.print("WPA");
            break;
        case WIFI_AUTH_WPA2_PSK:
            Serial.print("WPA2");
            break;
        case WIFI_AUTH_WPA_WPA2_PSK:
            Serial.print("WPA+WPA2");
            break;
        case WIFI_AUTH_WPA2_ENTERPRISE:
            Serial.print("WPA2-EAP");
            break;
        case WIFI_AUTH_WPA3_PSK:
            Serial.print("WPA3");
            break;
        case WIFI_AUTH_WPA2_WPA3_PSK:
            Serial.print("WPA2+WPA3");
            break;
        case WIFI_AUTH_WAPI_PSK:
            Serial.print("WAPI");
            break;
        default:
            Serial.print("unknown");
        }
        Serial.println();
        delay(10);
    }

    // Delete the scan result to free memory for code below.
    WiFi.scanDelete();
}
void scan()
{
#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 4, 2)
    WiFi.setBandMode(WIFI_BAND_MODE_AUTO);
#endif
    ScanWiFi();
#if CONFIG_SOC_WIFI_SUPPORT_5G
    // Wait a bit before scanning again.
    delay(1000);
    Serial.println("2.4G networks:");
    WiFi.setBandMode(WIFI_BAND_MODE_2G_ONLY);
    ScanWiFi();
    // Wait a bit before scanning again.
    delay(1000);
    Serial.println("5G networks:");
    WiFi.setBandMode(WIFI_BAND_MODE_5G_ONLY);
    ScanWiFi();
#endif
    // Wait a bit before scanning again.
    delay(10000);
}

void connect(String arguments)
{
    int args = getNumOf(arguments, ' ');
    if (args == 2)
    {
        int endOfSsid = arguments.indexOf(" ");
        String ssid = arguments.substring(0, endOfSsid - 1);
        String password = arguments.substring(endOfSsid + 1);
        Serial.println("\n");
        Serial.print("Connecting to ");
        Serial.println(ssid);

        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }

        Serial.println();
        Serial.print("WiFi connected, local IP is ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("Usage: connect [SSID] [PASSWORD]");
    }
}

void disconnect(String arguments)
{
    if (arguments == "force")
    {
        WiFi.disconnect(true, false);
        Serial.println("WiFi disconnected and radio stopped");
    }
    else
    {
        WiFi.disconnect(false, false);
        Serial.println("WiFi disconnected from network (radio still running, stop with `disconnect force`)");
    }
}