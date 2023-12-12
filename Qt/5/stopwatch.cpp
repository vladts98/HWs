#include "stopwatch.h"

StopWatch::StopWatch(QObject *parent) : QObject{parent}
{
    isStarted = false;
    Time = 0.;
    LapStartTime = 0.;
    NumLap = 1;
    qTimer = new QTimer(this);
    qTimer->setInterval(10);
}
StopWatch::~StopWatch()
{
    delete qTimer;
}

void StopWatch::Start()
{
    isStarted = true;
    qTimer->start();
}
void StopWatch::Stop()
{
    isStarted = false;
    qTimer->stop();
}
void StopWatch::Clear()
{
    Time = 0.;
    LapStartTime = 0.;
    NumLap = 1;
    emit sig_Clear();
}
bool StopWatch::isStart()
{
    return isStarted;
}

void StopWatch::Lap()
{
    emit sig_Lap();
    LapStartTime = Time;
    ++NumLap;
}

float StopWatch::getLapTime()
{
    return Time - LapStartTime;
}
int StopWatch::getNumLap()
{
    return NumLap;
}
float StopWatch::getTime()
{
    if(isStarted)
        Time += float(qTimer->interval())/1000;
    return Time;
}
QTimer* StopWatch::getQTimer()
{
    return qTimer;
}

