#include <esp_wifi.h>


//ssid while not connected?
String getSSID() {
    wifi_config_t conf;
    esp_wifi_get_config(WIFI_IF_STA, &conf);
    return String(reinterpret_cast<const char*>(conf.sta.ssid));
}



void WiFiEvent(WiFiEvent_t event) {
    String dbgName = "WiFiEvent() ";

    switch (event) {

    case SYSTEM_EVENT_WIFI_READY:
        Debug(dbgName + "SYSTEM_EVENT_WIFI_READY", t_TIME);
        //WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
        break;

    case SYSTEM_EVENT_SCAN_DONE:
        Debug(dbgName + "SYSTEM_EVENT_SCAN_DONE", t_TIME);
        break;

    case SYSTEM_EVENT_STA_START:
        Debug(dbgName + "SYSTEM_EVENT_STA_START", t_TIME);
        break;

    case SYSTEM_EVENT_STA_STOP:
        Debug(dbgName + "SYSTEM_EVENT_STA_STOP", t_TIME);
        break;

    case SYSTEM_EVENT_STA_CONNECTED://or STARTED ?
        Debug(dbgName + "SYSTEM_EVENT_STA_CONNECTED", t_TIME);
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
        Debug(dbgName + "SYSTEM_EVENT_STA_DISCONNECTED", t_TIME);
        break;

    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
        Debug(dbgName + "SYSTEM_EVENT_STA_AUTHMODE_CHANGE", t_TIME);
        break;

    case SYSTEM_EVENT_STA_GOT_IP:
        Debug(dbgName + "SYSTEM_EVENT_STA_GOT_IP", t_TIME);
        break;

    case SYSTEM_EVENT_STA_LOST_IP:
        Debug(dbgName + "SYSTEM_EVENT_STA_LOST_IP", t_TIME);
        break;

    case SYSTEM_EVENT_AP_START:
        Debug(dbgName + "SYSTEM_EVENT_AP_START", t_TIME);

        WiFi.softAPsetHostname(mydata.hostname);
        WiFi.softAP(mydata.ap_ssid, mydata.ap_psk);
        delay(100);
        Debug(dbgName + "SSID: " + String(mydata.ap_ssid), t_INFO);
        Debug(dbgName + "WiFi.softAPgetHostname(): " + String(WiFi.softAPgetHostname()), t_INFO);
        Debug(dbgName + "WiFi.softAPIP(): " + String(WiFi.softAPIP().toString()), t_INFO);
        Debug(dbgName + "WiFi.softAPmacAddress(): " + String(WiFi.softAPmacAddress()), t_INFO);
        break;

    case SYSTEM_EVENT_AP_STOP:
        Debug(dbgName + "SYSTEM_EVENT_AP_STOP", t_TIME);
        break;

    case SYSTEM_EVENT_AP_STACONNECTED:
        Debug(dbgName + "SYSTEM_EVENT_AP_STACONNECTED", t_TIME);
        break;

    case SYSTEM_EVENT_AP_STADISCONNECTED:
        Debug(dbgName + "SYSTEM_EVENT_AP_STADISCONNECTED", t_TIME);
        break;

    case SYSTEM_EVENT_AP_STAIPASSIGNED:
        Debug(dbgName + "SYSTEM_EVENT_AP_STAIPASSIGNED", t_TIME);
        break;

    case SYSTEM_EVENT_AP_PROBEREQRECVED:
        Debug(dbgName + "SYSTEM_EVENT_AP_PROBEREQRECVED", t_TIME);
        break;

    default:
        break;
    }
}


void wifiManager() {
    String dbgName = "wifiManager() ";

    if (!WiFi.isConnected()) {
        
        size_t wifi_list_max = sizeof mydata.ssid / sizeof mydata.ssid[0];

        for (size_t index = 0; ((!WiFi.isConnected()) && (index < wifi_list_max)); index++) {

            if (index) {//attempts 1 to wifi_list_max
                Debug(dbgName + "Connecting to list entry #" + String(index), t_INFO);
                WiFi.begin(*mydata.ssid[index], *mydata.psk[index]);
            }
            else {//first attempt
                WiFi.begin();
                Debug(dbgName + "Connecting to last known AP", t_INFO);
            }

            for (size_t attempt = 0; (!WiFi.isConnected() && attempt < 10); attempt++) {
                delay(1000);
            }

            if (WiFi.isConnected()) {

                WiFi.setHostname(mydata.hostname);
                Debug(dbgName + "Connection successful.", t_INFO);
                Debug(dbgName + "SSID: " + String(WiFi.SSID()), t_INFO);
                Debug(dbgName + "RSSI: " + String(WiFi.RSSI()) + "dBm", t_INFO);
                Debug(dbgName + "WiFi.localIP(): " + String("http://" + WiFi.localIP().toString()), t_INFO);
                Debug(dbgName + "WiFi.getHostname(): " + String("http://") + WiFi.getHostname(), t_INFO);
                Debug(dbgName + "WiFi.macAddress(): " + String(WiFi.macAddress()), t_INFO);
            }
            else {

                Debug(dbgName + "Connection failed.", t_FAIL);
            }
                

        }
        
        
        //still not connected! switch to AP?
        if (!WiFi.isConnected()) {
            WiFi.mode(WIFI_MODE_AP);

        }

    }

}
