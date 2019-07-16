void webManager(bool spiffs) {
    String dbgName = "webManager() ";

    if (spiffs) {
        Debug("SPIFFS server instructions loaded.", t_INFO);

        ws.onEvent(onWsEvent);
        server.addHandler(&ws);

        server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
            request->send(SPIFFS, "/index.html");
            });

        server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest* request) {
            request->send(SPIFFS, "/main.js", String(), false, processor);
            });

        server.on("/json_handler.js", HTTP_GET, [](AsyncWebServerRequest* request) {
            request->send(SPIFFS, "/json_handler.js");
            });

        server.on("/table_generator.js", HTTP_GET, [](AsyncWebServerRequest* request) {
            request->send(SPIFFS, "/table_generator.js");
            });
    }else{
        Debug("PROGMEM server instructions loaded.", t_INFO);
        server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
            request->send_P(200, "text/html", PAGEFAIL);
            });
    }
    // Start server
    server.begin();
}

String processor(const String& var) {
    Serial.println(var);
    if (var == "IPADDR") {
        return WiFi.localIP().toString();
    }
}