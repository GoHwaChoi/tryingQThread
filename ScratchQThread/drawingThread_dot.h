#pragma once

#include <QThread>


class drawingThread_dot : public QThread
{
	Q_OBJECT

public:
	explicit drawingThread_dot(QObject* parent = 0, bool bStop = false);
	~drawingThread_dot();
	//explicit drawingThread_dot(QObject* parent = 0);
	void run();
	
	// if Stop = true, the thread will break
	// out of the loop, and will be disposed
	//void stop();
	//void selectRandom();
	bool Stop;

signals:
	// Signal 은 데이터를 GUI 클래스(GUI Thread)로 보냄
	// To communicate with Gui Thread
	// we need to emit a signal
	void calcAmount_dot(int);
	//void calcAmount_bar(int);

	//thread 테스트코드
	//void calcDotAmount(float, float);

public slots:
	// slot 은 데이터를 이곳 클래스로 받음

private:
	bool m_stopFlag = false;
	bool m_ramdomFlag = false;
};

