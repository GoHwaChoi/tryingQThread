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

	//윈도우 함수
	void closeEvent(QCloseEvent* event);                //alt+f4 종료 기능 비활성화
    void finishedGUI();

public slots:
    //쓰레드
    void setThreadStart();              //Active
    void setVolumeRandom();             //랜덤

    //슬라이더 slots
    void setVolumeSlider();             //textEdit

    //Active 버튼 slots
    void setCalcAmount_dot(int nDot);   //Active dot 가감소
    //Control 버튼 slots
    void setCalcAmount_bar(int nBar);        //Control Bar 가감소

private:
    Ui::ScratchQThreadClass *ui;
    drawingThread_dot* drwThread_dot;   //Active dot 용 스레드 객체
    drawingThread_bar* drwThread_bar;   //Control bar 용 스레드 객체
};
