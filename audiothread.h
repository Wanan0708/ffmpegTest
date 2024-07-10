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
    ~AudioThread();
    void run() override;
    void setRecordFlag(bool flag);
    void setSaveAudioPath(QString path);

private:
    bool bFlag;
    QString filePath;

signals:

};

#endif // AUDIOTHREAD_H
