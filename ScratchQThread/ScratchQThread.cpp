#include "ScratchQThread.h"


ScratchQThread::ScratchQThread(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	//thread 테스트코드
	//we are linking the thread signal to the slot defined here
	//connect(drwThread_dot, SIGNAL(calcDotAmount(float, float)), this, SLOT(setCalcAmount_dot(float, float)));
	
	connect(ui.pushButton_Active, &QAbstractButton::clicked, this, &ScratchQThread::setThreadStart);	//Active 버튼으로 쓰레드 시작
	connect(ui.pushButton_Control, &QAbstractButton::clicked, this, &ScratchQThread::setVolumeRandom);		//슬라이더로 라벨 값 출력
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

		//signal 의 매개변수와 slot 의 매개변수를 동일하게 하여 데이터를 주고받음
		connect(drwThread_bar, SIGNAL(calcAmount_bar(int)), this, SLOT(setCalcAmount_bar(int)));

		drwThread_bar->selectRandom();
		//start the thread
		drwThread_bar->start();

		ui.horizontalSlider->setDisabled(true);		//슬라이더 조작 비활성화
		ui.label_SliderNum->setText("Disabled");	//슬라이더 라벨에 비활성상태 표시

		qDebug() << "pushButton_Control : Checked";
	}
	else
	{
		//쓰레드가 끝나면(run() 이 끝나면) 객체 제거
		connect(drwThread_bar, SIGNAL(finished()), drwThread_bar, SLOT(deleteLater()));

		//while 문 중지
		drwThread_bar->stop();
		drwThread_bar->quit();
		drwThread_bar->wait();

		ui.textEdit_Control->clear();	//textEdit 에 dot 제거
		ui.label_ControlNum->clear();	//label 에 dot 개수 제거

		ui.horizontalSlider->setEnabled(true);	//슬라이더 조작 활성화
		ui.label_SliderNum->setText("Enabled");	//슬라이더 라벨에 활성상태 표시

		qDebug() << "pushButton_Control : UnChecked";
	}
}

void ScratchQThread::setVolumeSlider()
{
	//슬라이드의 값이 int 형으로 반환되므로 QString 으로 변환하여 저장
	unsigned int sliderNum = ui.horizontalSlider->value();
	QString strVolumeVal = QString::number(sliderNum);

	if (!ui.pushButton_Control->isChecked())
	{
		ui.label_SliderNum->setText(strVolumeVal);	//라벨에 값 출력

		setCalcAmount_bar(sliderNum);		//Control textEdit 에 slider 값 전달
	}	
}

void ScratchQThread::setCalcAmount_dot(int _cal_dot)
{
	QString strDot = "";			//문자열 초기화
	strDot.fill('.', _cal_dot);		//문자 ' . ' 으로 채워넣기. _cal_dot 수만큼
	ui.textEdit_Active->setText(strDot);	//ui 에 dot 출력

	ui.label_ActiveNum->setText(QString::number(_cal_dot));	//label 에 dot 개수 출력
}

void ScratchQThread::setThreadStart()
{
	if (ui.pushButton_Active->isChecked())
	{
		//initialize the thread
		drwThread_dot = new drawingThread_dot(this);

		//signal 의 매개변수와 slot 의 매개변수를 동일하게 하여 데이터를 주고받음
		connect(drwThread_dot, SIGNAL(calcAmount_dot(int)), this, SLOT(setCalcAmount_dot(int)));

		//start the thread
		drwThread_dot->start();

		qDebug() << "pushButton_Active : Checked";
	}
	else
	{	
		//쓰레드가 끝나면(run() 이 끝나면) 객체 제거
		connect(drwThread_dot, SIGNAL(finished()), drwThread_dot, SLOT(deleteLater()));

		//while 문 중지
		drwThread_dot->stop();
		drwThread_dot->quit();
		drwThread_dot->wait();

		ui.textEdit_Active->clear();	//textEdit 에 dot 제거
		ui.label_ActiveNum->clear();	//label 에 dot 개수 제거

		qDebug() << "pushButton_Active : UnChecked";
	}
}

//thread 테스트코드
//void ScratchQThread::setCalcAmount_dot(float _cal_a, float _cal_b)
//{
//	ui.textEdit_Active->setText(QString::number(_cal_a));
//	ui.textEdit_Control->setText(QString::number(_cal_b));
//}
