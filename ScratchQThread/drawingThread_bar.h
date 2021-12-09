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
	// Signal �� �����͸� GUI Ŭ����(GUI Thread)�� ����
	void calcAmount_bar(int);
	
public slots:
	// Signal �� �����͸� GUI Ŭ����(GUI Thread)�� ����

private:
	bool m_stopFlag = false;
	bool m_randomFlag = false;
};

