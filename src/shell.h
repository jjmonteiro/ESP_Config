/*******************************************************************//**
 * @file    shell.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 *
**//*********************************************************************/

#ifndef shell_h
#define shell_h

typedef enum system_cli_handler_t {
    //INTERNALS
    SYSTEM_GET_PING,            /**< ESP32 WiFi ready */
    SYSTEM_GET_VERSION,         /**< ESP32  */
    SYSTEM_GET_DATE,            /**< ESP32  */


};

#endif
/**********************************end of file**********************************/
