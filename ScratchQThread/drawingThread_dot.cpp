#include "drawingThread_dot.h"
#include <QDebug>
#include <iostream>


drawingThread_dot::drawingThread_dot(QObject* parent, bool bStop) :
	QThread(parent), Stop(bStop)
{

}
drawingThread_dot::~drawingThread_dot()
{
}
// run() will be called when this thread start
void drawingThread_dot::run()
{
	int i=0;
	bool revNum = false;
	m_stopFlag = false;
	Stop = false;

	qDebug() << "m_stopFlag = " << m_stopFlag;

	//while (!m_stopFlag)
	while (!Stop)
	{
		if (revNum == false && i < 99)
		{
			i++;
		}
		else if (revNum == true && i > 0)
		{
			i--;
		}
		else
		{
			revNum = true;
			if (i <= 0)
			{
				revNum = false;
			}
		}

		emit calcAmount_dot(i);

		qDebug() << "thread_inWhile_Dot : " << i;

		this->msleep(200);
	}
}

//void drawingThread_dot::stop()
//{
//	m_stopFlag = true;
//}
