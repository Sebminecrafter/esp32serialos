#include <Arduino.h>
#include "utilities/utilities.h"
#include "WiFi.h"
#include "commands/command/wifi/main.h"

void startWifi()
{
    println("WiFi initialized");
    // Enable Station Interface
    WiFi.begin();
    WiFi.mode(WIFI_MODE_STA);
}

void ScanWiFi()
{
    println("Scanning...");
    // WiFi.scanNetworks will return the number of networks found.
    int n = WiFi.scanNetworks();
    println("Scan done");
    print(n);
    println(" networks found");
    println("Nr | SSID                             | RSSI | CH | Encryption");
    for (int i = 0; i < n; ++i)
    {
        // Print SSID and RSSI for each network found
        printf("%2d", i + 1);
        print(" | ");
        printf("%-32.32s", WiFi.SSID(i).c_str());
        print(" | ");
        printf("%4ld", WiFi.RSSI(i));
        print(" | ");
        printf("%2ld", WiFi.channel(i));
        print(" | ");
        switch (WiFi.encryptionType(i))
        {
        case WIFI_AUTH_OPEN:
            print("OPEN");
            break;
        case WIFI_AUTH_WEP:
            print("WEP");
            break;
        case WIFI_AUTH_WPA_PSK:
            print("WPA");
            break;
        case WIFI_AUTH_WPA2_PSK:
            print("WPA2");
            break;
        case WIFI_AUTH_WPA_WPA2_PSK:
            print("WPA+WPA2");
            break;
        case WIFI_AUTH_WPA2_ENTERPRISE:
            print("WPA2-EAP");
            break;
        case WIFI_AUTH_WPA3_PSK:
            print("WPA3");
            break;
        case WIFI_AUTH_WPA2_WPA3_PSK:
            print("WPA2+WPA3");
            break;
        case WIFI_AUTH_WAPI_PSK:
            print("WAPI");
            break;
        default:
            print("unknown");
        }
        println();
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
    println("2.4G networks:");
    WiFi.setBandMode(WIFI_BAND_MODE_2G_ONLY);
    ScanWiFi();
    // Wait a bit before scanning again.
    delay(1000);
    println("5G networks:");
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
        println("\n");
        print("Connecting to ");
        println(ssid);

        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            print(".");
        }

        println();
        print("WiFi connected, local IP is ");
        println(WiFi.localIP());
    }
    else
    {
        println("Usage: connect [SSID] [PASSWORD]");
    }
}

void disconnect(String arguments)
{
    if (arguments == "force")
    {
        WiFi.disconnect(true, false);
        println("WiFi disconnected and radio stopped");
    }
    else
    {
        WiFi.disconnect(false, false);
        println("WiFi disconnected from network (radio still running, stop with `disconnect force`)");
    }
}