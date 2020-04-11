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

String spiffsManager::getFileName(File currentDir, File currentFile)
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

String spiffsManager::getFileSize(File currentDir, File currentFile)
{
    int filesize = currentFile.size();
    return String(filesize);
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
String spiffsManager::getFileName(Dir currentDir, bool currentFile)
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

String spiffsManager::getFileSize(Dir currentDir, bool currentFile)
{
    int filesize = currentDir.fileSize();
    return String(filesize);
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
        if (DEBUG_LEVEL <= level)
        {
            String filename = getFileName(thisDir, thisFile);
            String filesize = getFileSize(thisDir, thisFile);
            PRINT_LINE("   " + filename + " - " + filesize);
        }
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