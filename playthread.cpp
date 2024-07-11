#include "playthread.h"

PlayThread::PlayThread(QObject *parent) : QThread(parent)
{
    userData = new UserData();
    bPlay = false;
}

PlayThread::~PlayThread()
{
    delete userData;
}

void _audioCallback(void *userdata, Uint8 *stream, int len)
{
    SDL_memset(stream, 0, len);
    UserData *uData = (UserData*)userdata;
    if (uData->len == 0)
    {
        return;
    }

    len = (uData->len > len) ? uData->len : len;

    SDL_MixAudio(stream, uData->data, len, SDL_MIX_MAXVOLUME);

    uData->data += len;
    uData->len -= len;
}

void PlayThread::run()
{
    SDL_version version;
    SDL_VERSION(&version);
    qDebug() << "SDL2 version: " << version.major << version.patch << version.minor;

    SDL_Init(SDL_INIT_AUDIO);
    SDL_AudioSpec spc;
    spc.freq = 44100;
    spc.format = AUDIO_S16LSB;
    spc.channels = 2;
    spc.callback = _audioCallback;
    spc.samples = 1024;
    spc.userdata = this->userData;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        SDL_Quit();
        qDebug() << "文件打开失败;";
        return;
    }
    SDL_OpenAudio(&spc, nullptr);
    SDL_PauseAudio(0);

    int ret = 0;
    char audio_buf[4096];
    while (bPlay) {
        userData->len = file.read(audio_buf, sizeof (char[4096]));
        qDebug() << "playing..." << userData->len;
        QCoreApplication::processEvents();
        if (userData->len <= 0)
        {
            emit fileToEndSig();
            break;
        }
        userData->data = (Uint8*)audio_buf;
        while (userData->len > 0 && bPlay) {
            qDebug() << "ret" << ret++;
            SDL_Delay(1);
            QCoreApplication::processEvents();
        }
    }

    SDL_PauseAudio(1);
    emit fileToEndSig();
}

void PlayThread::setPlayFlag(bool flag)
{
    this->bPlay = flag;
}

void PlayThread::setAudioPath(QString path)
{
    this->filePath = path;
}
