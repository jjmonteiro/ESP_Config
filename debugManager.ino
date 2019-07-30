

void Debug(String dbgMessage, int Type) {
    String msgHeader;
    String time = String(millis()) + "            ";

    switch (Type) {
    case t_TIME:
        time.remove(11, time.length());
        msgHeader = "[" + time + "] ";
        break;
    case t_INFO:
        msgHeader = "[   INFO    ] ";
        
        break;
    case t_WARN:
        msgHeader = "[  WARNING  ] ";
        break;

    case t_ERROR:
        msgHeader = "[   ERROR   ] ";
        break;

    case t_OK:
        msgHeader = "[    OK     ] ";
        break;

    case t_FAIL:
        msgHeader = "[   FAIL    ] ";
        break;

    default:
        msgHeader = "[   DEBUG   ] ";
        break;
    }

    Serial.print(msgHeader + dbgMessage + "\r\n");
}

