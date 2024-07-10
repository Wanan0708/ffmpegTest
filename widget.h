#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QFileDialog>
#include "audiothread.h"
#include "playthread.h"

extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavdevice/avdevice.h>
}

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_record_clicked();

    void on_pushButton_play_clicked();

private:
    Ui::Widget *ui;
    AudioThread *audioThread;
    bool recordFlag;
    bool playFlag;

    PlayThread *playThread;
};
#endif // WIDGET_H
