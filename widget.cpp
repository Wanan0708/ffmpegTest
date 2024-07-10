#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

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
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_record_clicked()
{
    if (recordFlag)
    {
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


void Widget::on_pushButton_play_clicked()
{
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

