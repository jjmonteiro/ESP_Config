/*******************************************************************//**
 * @file    web_man.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 *
**//*********************************************************************/

#ifndef web_man_h
#define web_man_h

void notFound(AsyncWebServerRequest* request);
void webManager(bool spiffs);
String processor(const String& var);

#endif
/**********************************end of file**********************************/