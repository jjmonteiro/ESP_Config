

bool spiffsManager() {
    String dbgName = "spiffsManager() ";

    if (!SPIFFS.begin(true)) {
        Debug(dbgName + "SPIFFS not mounted!", t_FAIL);
        return false;
    }
    else {
        Debug(dbgName + "SPIFFS mounted.", t_OK);
        listDir("/");
        if (!SPIFFS.exists("/index.html")) {
            Debug(dbgName + "Couldn't find startup webpage!", t_FAIL);
            return false;
        }
        return true;
    }

}
void listDir(char* dir) {
    File root = SPIFFS.open(dir);
    File file = root.openNextFile();
    while (file) {
        LOG("   " + String(file.name()));
        file = root.openNextFile();
    }
}

//void addFileToServer(String file) {
//    server.on(file.c_str(), HTTP_GET, [](AsyncWebServerRequest* request) {
//        request->send(SPIFFS, [&file](String a) {a = file; });
//        });
//}