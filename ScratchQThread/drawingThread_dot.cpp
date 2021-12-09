#include "drawingThread_dot.h"
#include <QDebug>
#include <iostream>
#include <QRandomGenerator>

//drawingThread_dot::drawingThread_dot(QObject* parent, bool b) :
//	QThread(parent), Stop(b)
//{
//
//}

drawingThread_dot::drawingThread_dot(QObject* parent) :
	QThread(parent)
{

}

// run() will be called when this thread start
void drawingThread_dot::run()
{
	int i=0;
	bool revNum = false;
	m_stopFlag = false;

	qDebug() << "m_stopFlag = " << m_stopFlag;
	qDebug() << "m_ramdomFlag = " << m_ramdomFlag;

	while (!m_stopFlag && !m_ramdomFlag)
	{
		if (revNum == false && i < 10)
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

		this->msleep(500);
	}

	while (!m_stopFlag && m_ramdomFlag)
	{
		QRandomGenerator::system();
		auto random = QRandomGenerator::global()->bounded(0, 99);

		emit calcAmount_bar(random);

		qDebug() << "thread_inWhile_Bar : " << random;

		this->msleep(100);
	}

	qDebug() << "thread_outOfWhile";
}

void drawingThread_dot::stop()
{
	m_stopFlag = true;
}

void drawingThread_dot::selectRandom()
{
	m_ramdomFlag = true;
}
//thread 테스트코드
//drawingThread_dot::drawingThread_dot(QObject* parent, bool b) :
//	QThread(parent), Stop(b)
//{
//
//}
//
//// run() will be called when this thread start
//void drawingThread_dot::run()
//{
//	//to prevent consuming memory every time, I defined the variables at once
//	int calculated_a=65565;
//	int calculated_b = 1;
//
//	for(int i=0; i<10; i++)
//	{
//		emit calcDotAmount(
//			calculated_a = calculated_a / 12.0,
//			calculated_b = calculated_b * 60.2
//			
//		);
//		this->msleep(500);
//		qDebug() << "calculated_a : " << calculated_a;
//		qDebug() << "calculated_b : " << calculated_b;
//	}
//}