/*******************************************************************//**
 * @file    web_socket.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 *
**//*********************************************************************/

#ifndef web_socket_h
#define web_socket_h

#define JSON_INCOMING_BUFFER 1024*2
#define JSON_OUTGOING_BUFFER 1024*2

enum
{
    BACKEND_PING,
    SYSTEM_STATS,
    WIFI_SCAN,


} web_request_type;

void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len);

#endif
/**********************************end of file**********************************/