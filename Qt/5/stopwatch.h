#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class StopWatch : public QObject
{
    Q_OBJECT
public:
    explicit StopWatch(QObject *parent = nullptr);
    ~StopWatch();

    void Start();
    void Stop();
    void Clear();
    void Lap();

    bool isStart();
    float getLapTime();
    int getNumLap();
    float getTime();
    QTimer* getQTimer();
signals:
    void sig_Clear();
    void sig_Lap();
private:
    bool isStarted;
    float Time;
    float LapStartTime;
    int NumLap;
    QTimer* qTimer;

};

#endif // STOPWATCH_H
