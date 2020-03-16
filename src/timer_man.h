/*******************************************************************//**
 * @file    spiffs_man.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 **//*********************************************************************/

#ifndef timer_man_h
#define timer_man_h

class timerManager
{
public:
    void init();
    tm* getTime();
    void updateNTP();
    bool updateLocalTime();
private:
    time_t rawtime;
    tm* timeinfo;
};

extern timerManager Timer;

#endif 
/**********************************end of file**********************************/

