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

void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len);
String translateEncryptionType(wifi_auth_mode_t encryptionType);

#endif
/**********************************end of file**********************************/