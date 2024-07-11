#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowTitle("录音机1.0");
    this->setWindowIcon(QIcon(":/new/prefix1/image/recorder.png"));

    qDebug() << "ffmpeg version: " << avcodec_version();

    recordFlag = true;
    playFlag = true;
    audioThread = new AudioThread;
    connect(this, &QWidget::destroyed, [=](){
        audioThread->setRecordFlag(false);
        audioThread->exit();
        audioThread->wait();
    });

    playThread = new PlayThread(this);
    connect(this, &QWidget::destroyed, [=](){
        playThread->exit();
        playThread->wait(3000);
        playThread->deleteLater();
    });
    connect(playThread, &PlayThread::finished, [=](){
        playThread->exit();
        if (playThread->wait(3000))
        {
            playThread->terminate();
        }
    });
    connect(playThread, &PlayThread::fileToEndSig, [=]()
    {
        playThread->exit();
        playThread->wait(3000);
        ui->pushButton_play->setText("开始播放");
    });

    ui->pushButton_play->setObjectName("pushButton"); //使用样式pushbutton
    ui->pushButton_record->setObjectName("pushbutton1");//使用样式pushbutton
}

Widget::~Widget()
{
    delete ui;
}

//开始录音
void Widget::on_pushButton_record_clicked()
{
    if (recordFlag)
    {
        QString filter = "pcm files (*.pcm)";
        QString savePath = QFileDialog::getSaveFileName(nullptr, "选择保存音频位置", "./", "All Files (*.*);pcm Files (*.pcm)", &filter);
        if (!savePath.isEmpty())
        {
            qDebug() << "选择的文件路径为：" << savePath;
        }
        else
        {
            return;
        }
        audioThread->setSaveAudioPath(savePath);
        audioThread->setRecordFlag(true);
        audioThread->start();
        recordFlag = false;
        ui->pushButton_record->setText("停止录音");
    }
    else
    {
        audioThread->setRecordFlag(false);
        audioThread->exit();
        if (!audioThread->wait(2000)) {
            audioThread->terminate(); // 如果超时，可以选择终止线程
        }
        recordFlag = true;
        ui->pushButton_record->setText("开始录音");
    }
}

//播放录音
void Widget::on_pushButton_play_clicked()
{
    //停止播放
    if (playThread->isRunning())
    {
        playThread->setPlayFlag(false);
//        playThread->exit();
//        playThread->wait();
        ui->pushButton_play->setText("开始播放");
        return ;
    }

    //选择要播放的音频文件
    QString filePath = QFileDialog::getOpenFileName(nullptr, "选择音频文件", "./", "All Files (*.*);pcm Files (*.pcm)");
    QFile audioFile(filePath);
    if (!audioFile.exists())
    {
        qDebug() << "音频文件不存在";
        return;
    }

    playThread->setAudioPath(filePath);
    if (playFlag)
    {
        playThread->setPlayFlag(true);
        playThread->start();
        ui->pushButton_play->setText("停止播放");
    }
    else
    {
        playThread->setPlayFlag(false);
        playThread->exit();
        playThread->wait();
    }
}

