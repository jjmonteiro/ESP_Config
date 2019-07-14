

void Debug(String dbgMessage, int Type) {
    String message;
    String time = String(millis()) + "            ";

    switch (Type) {
    case t_TIME:
        time.remove(11, time.length());
        message = "[" + time + "] ";
        break;
    case t_INFO:
        message = "[   INFO    ] ";
        
        break;
    case t_WARN:
        message = "[  WARNING  ] ";
        break;

    case t_ERROR:
        message = "[   ERROR   ] ";
        break;

    case t_OK:
        message = "[    OK     ] ";
        break;

    case t_FAIL:
        message = "[   FAIL    ] ";
        break;

    default:
        message = "[   DEBUG   ] ";
        break;
    }

    Serial.println(message += dbgMessage);
}

