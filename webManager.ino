void webManager() {

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

    // Start server
    server.begin();
}

String processor(const String& var) {
    Serial.println(var);
    if (var == "IPADDR") {
        return WiFi.localIP().toString();
    }
}