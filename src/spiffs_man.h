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

class spiffsManager
{
public:
    bool init();
    void printRoot(dbgLevel Type);
};

extern spiffsManager FileSystem;

#endif 
/**********************************end of file**********************************/