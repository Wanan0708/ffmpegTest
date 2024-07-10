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
        playThread->wait();
        playThread->deleteLater();
    });

    ui->pushButton_play->setObjectName("pushButton");
    ui->pushButton_record->setObjectName("pushbutton1");
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
        audioThread->wait(3000);
        recordFlag = true;
        ui->pushButton_record->setText("开始录音");
    }
}

//播放录音
void Widget::on_pushButton_play_clicked()
{
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
    }
    else
    {
        playThread->setPlayFlag(false);
        playThread->exit();
        playThread->wait();
    }
}

