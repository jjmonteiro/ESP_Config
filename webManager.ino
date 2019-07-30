void webManager(bool spiffs) {
    String dbgName = "webManager() ";

        /// enumerator.js
        /// iconify.min.js
        /// index.html
        /// json_handler.js
        /// main.js
        /// style.css
        /// table_generator.js

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

        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest* request) {
            request->send(SPIFFS, "/style.css");
            });

        server.on("/iconify.min.js", HTTP_GET, [](AsyncWebServerRequest* request) {
            request->send(SPIFFS, "/iconify.min.js");
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