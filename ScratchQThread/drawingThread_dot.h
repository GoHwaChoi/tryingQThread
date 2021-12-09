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
	// Signal �� �����͸� GUI Ŭ����(GUI Thread)�� ����
	// To communicate with Gui Thread
	// we need to emit a signal
	void calcAmount_dot(int);
	//void calcAmount_bar(int);

	//thread �׽�Ʈ�ڵ�
	//void calcDotAmount(float, float);

public slots:
	// slot �� �����͸� �̰� Ŭ������ ����

private:
	bool m_stopFlag = false;
	bool m_ramdomFlag = false;
};

