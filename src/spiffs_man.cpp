/*******************************************************************//**
 * @file    spiffs_man.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 **//*********************************************************************/

#include <Arduino.h>
#include "spiffs_man.h"

spiffsManager FileSystem;

#if defined ESP32

File spiffsManager::openRoot()
{
    return FileSystem.open("/");
}

File spiffsManager::openNext(File currentFile)
{
    return currentFile.openNextFile();
}

String spiffsManager::getFilename(File currentDir, File currentFile)
{
    return String(currentFile.name());
}

size_t spiffsManager::getUsedBytes()
{
    return FileSystem.usedBytes();
}

size_t spiffsManager::getTotalBytes()
{
    return FileSystem.totalBytes();
}

#else

Dir spiffsManager::openRoot()
{
    return FileSystem.openDir("/");
}
bool spiffsManager::openNext(Dir currentFile)
{
    return currentFile.next();
}
String spiffsManager::getFilename(Dir currentDir, bool currentFile)
{
    return String(currentDir.fileName());
}

size_t spiffsManager::getUsedBytes()
{
    FSInfo storageInfo;
    FileSystem.info(storageInfo);
    return storageInfo.usedBytes;
}

size_t spiffsManager::getTotalBytes()
{
    FSInfo storageInfo;
    FileSystem.info(storageInfo);
    return storageInfo.totalBytes;
}

#endif

bool spiffsManager::init()
{
    bool result = false;
    if (FileSystem.begin())
    {
        DEBUG(__FILENAME__, "SPIFFS mounted.", t_INFO);
        FileSystem.printRoot(t_INFO);
        DEBUG(__FILENAME__, "SPIFFS Size: " + String(getTotalBytes()), t_TRACE);
        DEBUG(__FILENAME__, "SPIFFS Used: " + String(getUsedBytes()), t_TRACE);
        result = true;
    }
    else 
    {
        DEBUG(__FILENAME__, "SPIFFS not mounted!", t_ERROR);
    }
    return result;
}

void spiffsManager::printRoot(dbgLevel level)
{
    auto thisDir = openRoot();
    auto thisFile = openNext(thisDir);
    int  ifileCount = 0;

    while (thisFile)
    {
        (DEBUG_LEVEL <= level) ? PRINT_LINE("   " + getFilename(thisDir, thisFile)) : (0);
        ifileCount++;
        thisFile = openNext(thisDir);
    }
    if (ifileCount)
    {
        DEBUG(__FILENAME__, String(ifileCount) + " files found.", t_INFO);
    }
    else
    {
        DEBUG(__FILENAME__, "No files found.", t_ERROR);
    }
}

/**********************************end of file**********************************/