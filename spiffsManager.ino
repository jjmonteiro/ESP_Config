

void spiffsManager() {
    String dbgName = "spiffsManager() ";

    if (!SPIFFS.begin(true)) {
        Debug(dbgName + "SPIFFS not mounted!", t_FAIL);
        return;
    }
    else {
        Debug(dbgName + "SPIFFS mounted.", t_OK);
        listDir("/");
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