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

#define WEBSERVER_PORT  80

void notFound(AsyncWebServerRequest* request);
void webManager();
String processor(const String& var);

#endif
/**********************************end of file**********************************/