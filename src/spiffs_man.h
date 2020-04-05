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
    String getFilename(File currentDir, File currentFile);
    size_t getUsedBytes();
    size_t getTotalBytes();
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
    String getFilename(Dir currentDir, bool currentFile);
    size_t getUsedBytes();
    size_t getTotalBytes();
};

#endif

extern spiffsManager FileSystem;

#endif 
/**********************************end of file**********************************/