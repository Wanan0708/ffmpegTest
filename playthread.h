#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <SDL2/SDL.h>

struct UserData
{
    int len;
    Uint8 *data;
};

class PlayThread : public QThread
{
    Q_OBJECT
public:
    explicit PlayThread(QObject *parent = nullptr);
    ~PlayThread();
    void run() override;
    void setPlayFlag(bool flag);
    void setAudioPath(QString path);

signals:
    void fileToEndSig();

private:
    UserData *userData;
    bool bPlay;
    QString filePath;
};

//void _audioCallback(void *userdata, Uint8 *stream, int len);

#endif // PLAYTHREAD_H
