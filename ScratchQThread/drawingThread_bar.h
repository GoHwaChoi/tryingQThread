#pragma once

#include <QThread>
#include <QDebug>


class drawingThread_bar : public QThread
{
	Q_OBJECT

public:
	explicit drawingThread_bar(QObject* parent = 0, bool bStop = false);
	~drawingThread_bar();
	void run();
	// if Stop = true, the thread will break
	// out of the loop, and will be disposed
	//void stop();
	void selectRandom();

	bool Stop;

signals:
	// Signal 은 데이터를 GUI 클래스(GUI Thread)로 보냄
	void calcAmount_bar(int);
	
public slots:
	// Signal 은 데이터를 GUI 클래스(GUI Thread)로 보냄

private:
	bool m_stopFlag = false;
	bool m_randomFlag = false;
};

