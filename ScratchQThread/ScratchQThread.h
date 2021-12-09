#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ScratchQThread.h"
#include "drawingThread_dot.h"
#include "drawingThread_bar.h"
#include <QDebug>
#include <QSlider>
#include <QLabel>
#include <QCloseEvent>


class ScratchQThread : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScratchQThread(QWidget *parent = Q_NULLPTR);
    ~ScratchQThread();

	//������ �Լ�
	void closeEvent(QCloseEvent* event);                //alt+f4 ���� ��� ��Ȱ��ȭ
    void finishedGUI();

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
    Ui::ScratchQThreadClass *ui;
    drawingThread_dot* drwThread_dot;   //Active dot �� ������ ��ü
    drawingThread_bar* drwThread_bar;   //Control bar �� ������ ��ü
};
