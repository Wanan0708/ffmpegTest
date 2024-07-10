#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QFile>
#include <iostream>
extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavdevice/avdevice.h>
    #include <libavformat/avformat.h>
}

class AudioThread : public QThread
{
    Q_OBJECT
public:
    explicit AudioThread(QObject *parent = nullptr);
    void run() override;
    void setRecordFlag(bool flag);

private:
    bool bFlag;

signals:

};

#endif // AUDIOTHREAD_H
