void wifiManager() {
    String dbgName = "wifiManager() ";

    Debug(dbgName + "Connecting to: " + String(ssid), t_INFO);
    WiFi.begin(ssid, psk);


    if (!WiFi.isConnected()) {	//attempt #1
        for (size_t attempt = 0; (WiFi.status() != WL_CONNECTED && attempt < 10); attempt++) {
            delay(1000);
        }
    }

    if (!WiFi.isConnected()) {	//attempt #2
        ESP.restart();
        /*
        Debug("Failed.");
        Debug("Attempting WPS connection..");
        WiFi.beginWPSConfig();
        for (size_t attempt = 0; (WiFi.status() != WL_CONNECTED && attempt < 10); attempt++) {
        delay(4000);
        Serial.print(".");
        if (Serial.read() == 'c')
        break;
        }*/
    }

    //Debug("");
    Debug(dbgName + "WiFi connected!", t_OK);
    Debug(dbgName + "IP address: " + WiFi.localIP().toString(), t_INFO);
    Debug(dbgName + "Signal: " + String(WiFi.RSSI()), t_INFO);
    Debug(dbgName + "MAC address: " + String(WiFi.macAddress()), t_INFO);


}

