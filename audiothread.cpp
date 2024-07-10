#include "audiothread.h"

AudioThread::AudioThread(QObject *parent) : QThread(parent)
{
    bFlag = false;
    qDebug() << "thread strating..." << this->currentThreadId();
}

void AudioThread::run()
{
//    avcodec_register_all();
//    av_register_all(); //已经过时

    avformat_network_init(); // 初始化网络模块，如果你需要的话
    avdevice_register_all(); // 注册所有设备

    AVInputFormat *pFmt = av_find_input_format("dshow");
    AVFormatContext *pCtx = nullptr;
    const char* audio_device = "audio=麦克风 (USB2.0 MIC)";

    int ret = avformat_open_input(&pCtx, audio_device, pFmt, nullptr);
    if (ret != 0) {
        char errbuf[256];
        av_strerror(ret, errbuf, sizeof(errbuf));
        std::cerr << "Failed to open input device: " << errbuf << "\n";
        return;
    }

    QFile audioFile("./audio.pcm");
    if (!audioFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "filed to open audioFile;";
        return;
    }

    int iCount = 0;
    AVPacket pkt;
    while (bFlag && av_read_frame(pCtx, &pkt) == 0) {
        qDebug() << "pkt.size: " << pkt.size;
        audioFile.write((const char*)pkt.data, pkt.size);
        qDebug() << "recording..." << iCount++;
    }

    audioFile.close();
    avformat_close_input(&pCtx);
}

void AudioThread::setRecordFlag(bool flag)
{
    this->bFlag = flag;
}
