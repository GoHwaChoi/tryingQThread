#include "drawingThread_bar.h"
#include <QDebug>
#include <iostream>
#include <QRandomGenerator>


drawingThread_bar::drawingThread_bar(QObject* parent, bool bStop) :
	QThread(parent), Stop(bStop)
{
}

drawingThread_bar::~drawingThread_bar()
{
}

void drawingThread_bar::run()
{
	m_stopFlag = false;
	Stop = false;

	qDebug() << "m_stopFlag = " << m_stopFlag;
	qDebug() << "m_ramdomFlag = " << m_randomFlag;

	//while (!m_stopFlag && m_randomFlag)
	while (!Stop && m_randomFlag)
	{
		QRandomGenerator::system();
		auto random = QRandomGenerator::global()->bounded(0, 99);

		emit calcAmount_bar(random);

		qDebug() << "thread_inWhile_Bar : " << random;

		this->msleep(100);
	}
	qDebug() << "<Bar> thread_outOfWhile";
}

//void drawingThread_bar::stop()
//{
//	m_stopFlag = true;
//	m_randomFlag = false;
//}


void drawingThread_bar::selectRandom()
{
	m_randomFlag = true;
}
