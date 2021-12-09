#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ScratchQThread.h"
#include "drawingThread_dot.h"
#include <QDebug>
#include <QSlider>
#include <QLabel>


class ScratchQThread : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScratchQThread(QWidget *parent = Q_NULLPTR);
    //~ScratchQThread();

public slots:
    //������
    void setThreadStart();              //Active
    void setVolumeRandom();             //����

    //�����̴� slots
    void setVolumeSlider();             //textEdit

    //Active ��ư slots
    void setCalcAmount_dot(int nDot);   //Active dot ������
    //Control ��ư slots
    void setCalcAmount_bar(int nBar);        //Control Bar ������

private:
    Ui::ScratchQThreadClass ui;
    drawingThread_dot* drwThread_dot;   //Active dot �� ������ ��ü
    drawingThread_dot* drwThread_bar;   //Control bar �� ������ ��ü
};
