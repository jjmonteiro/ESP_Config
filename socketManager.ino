void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {
    String dbgName = "socketManager() ";
    if (type == WS_EVT_CONNECT) {
        Debug("WS_EVT_CONNECT " + String(client->id()), t_INFO);
        //Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
        //client->printf("Hello Client %u :)", client->id());
        //client->ping();
    }
    else if (type == WS_EVT_DISCONNECT) {
        Debug("WS_EVT_DISCONNECT " + String(client->id()), t_INFO);
    }
    else if (type == WS_EVT_ERROR) {
        Debug("WS_EVT_ERROR " + String(client->id()) + " Code: " + String(*((uint16_t*)arg)) + " Error Data: " + String((char*)data), t_ERROR);
    }
    else if (type == WS_EVT_DATA) {
        AwsFrameInfo* info = (AwsFrameInfo*)arg;
        String msg = "";

        if (info->final && info->index == 0 && info->len == len) {
            //the whole message is in a single frame and we got all of it's data
            //Serial.printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT) ? "text" : "binary", info->len);

            if (info->opcode == WS_TEXT) {
                for (size_t i = 0; i < info->len; i++) {
                    msg += (char)data[i];
                }
            }
            else {
                char buff[3];
                for (size_t i = 0; i < info->len; i++) {
                    sprintf(buff, "%02x ", (uint8_t)data[i]);
                    msg += buff;
                }
            }

            Debug("WS_EVT_DATA " + String(client->id()) + " Message: " + String(msg.c_str()), t_INFO);
            ////Serial.printf("%s\n", msg.c_str());

            //if (info->opcode == WS_TEXT)
            //    client->text("I got your text message");
            //else
            //    client->binary("I got your binary message");

            msg = "";
            jsonBuffer["type"] = 2;

            JsonArray value = jsonBuffer.createNestedArray("value");
            JsonObject key = value.createNestedObject();
            key["battery"] = 77;
            key["memory"] = 30;
            key["storage"] = 83;

            serializeJson(jsonBuffer, msg);
            client->text(msg);

        }
    }
}
