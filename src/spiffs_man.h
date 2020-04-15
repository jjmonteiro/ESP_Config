/*******************************************************************//**
 * @file    spiffs_man.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 **//*********************************************************************/

#ifndef spiffs_man_h
#define spiffs_man_h

#if defined ESP32
#include <SPIFFS.h>
#include "debug_api.h"

class spiffsManager : public fs::SPIFFSFS
{
public:
    spiffsManager() : fs::SPIFFSFS(SPIFFS) {};
    bool init();
    void printRoot(dbgLevel level);
    File openRoot();
    File openNext(File currentFile);
    String getFileName(File currentDir, File currentFile);
    size_t getUsedBytes();
    size_t getTotalBytes();
    String getFileSize(File currentDir, File currentFile);
};

#else
#include <FS.h>
#include "debug_api.h"

class spiffsManager : public FS
{
public:
    spiffsManager() : fs::FS(SPIFFS) {};
    bool init();
    void printRoot(dbgLevel level);
    Dir openRoot();
    bool openNext(Dir currentFile);
    String getFileName(Dir currentDir, bool currentFile);
    size_t getUsedBytes();
    size_t getTotalBytes();
    String getFileSize(Dir currentDir, bool currentFile);
};

#endif

extern spiffsManager FileSystem;

#endif 
/**********************************end of file**********************************/