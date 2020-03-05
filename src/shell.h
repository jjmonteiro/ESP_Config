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
    SYSTEM_CLI_PING = 0,           /**< ESP32 WiFi ready */
    SYSTEM_CLI_VERSION,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    
    //WIFI
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */

    //EEPROM
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */

    //SPIFFS
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */

    //SPIFFS
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */

    //TASKS
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */
    SYSTEM_CLI_,                /**< ESP32  */

};

#endif
/**********************************end of file**********************************/
