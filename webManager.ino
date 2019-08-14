
void notFound(AsyncWebServerRequest* request) {
    request->send(404, "text/plain", "Not found");
}

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
            request->send(SPIFFS, "/main.js", String(), false, processor);//updates main.js with current ip address
            });

        server.on("/w3.css", HTTP_GET, [](AsyncWebServerRequest* request) {
            request->send(SPIFFS, "/w3.css");
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

    server.onNotFound(notFound);

    server.begin();
}


String processor(const String& var) {

    if (var == "IPADDR") {
        if (WiFi.getMode() == WIFI_MODE_STA) {
            return WiFi.localIP().toString();
        }
        else {
            return WiFi.softAPIP().toString();
        }
    }
}