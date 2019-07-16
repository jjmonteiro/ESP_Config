#include <esp_wifi.h>
// Returns String NONE, ssid or pass
// Requires:  WiFi.mode(WIFI_AP_STA); preceeding call
// ie   String var = getSsidPass( "pass" );  //returns pass phrase
String getSSID() {
    wifi_config_t conf;
    esp_wifi_get_config(WIFI_IF_STA, &conf);
    return String(reinterpret_cast<const char*>(conf.sta.ssid));
}


void wifiManager() {
    String dbgName = "wifiManager() ";
    WiFi.mode(WIFI_AP_STA);

    if (!WiFi.isConnected()) {
        Debug(dbgName + "#1 attempt connection to " + getSSID(), t_INFO);
        WiFi.begin();
        for (size_t attempt = 0; (WiFi.status() != WL_CONNECTED && attempt < 10); attempt++) {
            delay(1000);
        }
    }

    if (!WiFi.isConnected()) {
        Debug(dbgName + "#2 attempt connection to " + String(mydata.ssid), t_INFO);
        WiFi.begin(mydata.ssid, mydata.psk);
        for (size_t attempt = 0; (WiFi.status() != WL_CONNECTED && attempt < 10); attempt++) {
            delay(1000);
        }
    }

    if (WiFi.isConnected()) {

        Debug(dbgName + "wifi connection established.", t_OK);
        Debug(dbgName + "IP address: " + WiFi.localIP().toString(), t_INFO);
        Debug(dbgName + "Signal: " + String(WiFi.RSSI()), t_INFO);
        Debug(dbgName + "MAC address: " + String(WiFi.macAddress()), t_INFO);
    }

}

