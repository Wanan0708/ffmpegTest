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
    void run() override;
    void setPlayFlag(bool flag);

signals:

private:
    UserData *userData;
    bool bPlay;
};

//void _audioCallback(void *userdata, Uint8 *stream, int len);

#endif // PLAYTHREAD_H
