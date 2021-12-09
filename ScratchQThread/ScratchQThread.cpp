#include "ScratchQThread.h"


ScratchQThread::ScratchQThread(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	//thread �׽�Ʈ�ڵ�
	//we are linking the thread signal to the slot defined here
	//connect(drwThread_dot, SIGNAL(calcDotAmount(float, float)), this, SLOT(setCalcAmount_dot(float, float)));
	
	connect(ui.pushButton_Active, &QAbstractButton::clicked, this, &ScratchQThread::setThreadStart);	//Active ��ư���� ������ ����
	connect(ui.pushButton_Control, &QAbstractButton::clicked, this, &ScratchQThread::setVolumeRandom);		//�����̴��� �� �� ���
	connect(ui.horizontalSlider, &QSlider::valueChanged, this, &ScratchQThread::setVolumeSlider);
}

//ScratchQThread::~ScratchQThread()
//{
//	if (drwThread_dot)
//	{
//		drwThread_dot->stop();
//		drwThread_dot->quit();
//		drwThread_dot->wait();
//	}
//	drwThread_dot->wait();
//}

void ScratchQThread::setCalcAmount_bar(int _cal_Bar)
{
	QString strBar = "";
	strBar.fill('|', _cal_Bar);
	ui.textEdit_Control->setText(strBar);
	ui.label_ControlNum->setText(QString::number(_cal_Bar));
}

void ScratchQThread::setVolumeRandom()
{
	
	if (ui.pushButton_Control->isChecked())
	{
		
		//initialize the thread
		drwThread_bar = new drawingThread_dot(this);

		//signal �� �Ű������� slot �� �Ű������� �����ϰ� �Ͽ� �����͸� �ְ����
		connect(drwThread_bar, SIGNAL(calcAmount_bar(int)), this, SLOT(setCalcAmount_bar(int)));

		drwThread_bar->selectRandom();
		//start the thread
		drwThread_bar->start();

		ui.horizontalSlider->setDisabled(true);		//�����̴� ���� ��Ȱ��ȭ
		ui.label_SliderNum->setText("Disabled");	//�����̴� �󺧿� ��Ȱ������ ǥ��

		qDebug() << "pushButton_Control : Checked";
	}
	else
	{
		//�����尡 ������(run() �� ������) ��ü ����
		connect(drwThread_bar, SIGNAL(finished()), drwThread_bar, SLOT(deleteLater()));

		//while �� ����
		drwThread_bar->stop();
		drwThread_bar->quit();
		drwThread_bar->wait();

		ui.textEdit_Control->clear();	//textEdit �� dot ����
		ui.label_ControlNum->clear();	//label �� dot ���� ����

		ui.horizontalSlider->setEnabled(true);	//�����̴� ���� Ȱ��ȭ
		ui.label_SliderNum->setText("Enabled");	//�����̴� �󺧿� Ȱ������ ǥ��

		qDebug() << "pushButton_Control : UnChecked";
	}
}

void ScratchQThread::setVolumeSlider()
{
	//�����̵��� ���� int ������ ��ȯ�ǹǷ� QString ���� ��ȯ�Ͽ� ����
	unsigned int sliderNum = ui.horizontalSlider->value();
	QString strVolumeVal = QString::number(sliderNum);

	if (!ui.pushButton_Control->isChecked())
	{
		ui.label_SliderNum->setText(strVolumeVal);	//�󺧿� �� ���

		setCalcAmount_bar(sliderNum);		//Control textEdit �� slider �� ����
	}	
}

void ScratchQThread::setCalcAmount_dot(int _cal_dot)
{
	QString strDot = "";			//���ڿ� �ʱ�ȭ
	strDot.fill('.', _cal_dot);		//���� ' . ' ���� ä���ֱ�. _cal_dot ����ŭ
	ui.textEdit_Active->setText(strDot);	//ui �� dot ���

	ui.label_ActiveNum->setText(QString::number(_cal_dot));	//label �� dot ���� ���
}

void ScratchQThread::setThreadStart()
{
	if (ui.pushButton_Active->isChecked())
	{
		//initialize the thread
		drwThread_dot = new drawingThread_dot(this);

		//signal �� �Ű������� slot �� �Ű������� �����ϰ� �Ͽ� �����͸� �ְ����
		connect(drwThread_dot, SIGNAL(calcAmount_dot(int)), this, SLOT(setCalcAmount_dot(int)));

		//start the thread
		drwThread_dot->start();

		qDebug() << "pushButton_Active : Checked";
	}
	else
	{	
		//�����尡 ������(run() �� ������) ��ü ����
		connect(drwThread_dot, SIGNAL(finished()), drwThread_dot, SLOT(deleteLater()));

		//while �� ����
		drwThread_dot->stop();
		drwThread_dot->quit();
		drwThread_dot->wait();

		ui.textEdit_Active->clear();	//textEdit �� dot ����
		ui.label_ActiveNum->clear();	//label �� dot ���� ����

		qDebug() << "pushButton_Active : UnChecked";
	}
}

//thread �׽�Ʈ�ڵ�
//void ScratchQThread::setCalcAmount_dot(float _cal_a, float _cal_b)
//{
//	ui.textEdit_Active->setText(QString::number(_cal_a));
//	ui.textEdit_Control->setText(QString::number(_cal_b));
//}
