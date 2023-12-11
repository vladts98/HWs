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
    void UpdateTime();
    void Stop();
    void Clear();
    void Lap();

    bool isStart();
    float getLapTime();
    int getNumLap();
    float getTime();
    QTimer* qTimer;
signals:
    void sig_Clear();
    void sig_Lap();
private:
    QTimer* getQTimer();
    bool isStarted;
    float Time;
    float LapStartTime;
    int NumLap;

};

#endif // STOPWATCH_H
