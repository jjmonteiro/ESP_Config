/*******************************************************************//**
 * @file     timer_man.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief    Time tracking facility
 * @details  Provides date and time keeping functionality with NTP support
 *
 **//*********************************************************************/

#ifndef timer_man_h
#define timer_man_h

class timerManager
{
public:
    void init();
    tm*  getTime();
    void updateNTP(long gmt_offset, int dst_offset, const char* ntp_server);
    bool updateLocalTime();
private:
    time_t rawtime;
    tm* timeinfo;
};

extern timerManager Timer;

#endif 
/**********************************end of file**********************************/

