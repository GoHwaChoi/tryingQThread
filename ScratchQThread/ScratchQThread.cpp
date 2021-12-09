#include "ScratchQThread.h"


ScratchQThread::ScratchQThread(QWidget *parent)
    : QMainWindow(parent)
	, ui(new Ui::ScratchQThreadClass)
{
    ui->setupUi(this);
	
	drwThread_dot = new drawingThread_dot(this, false);		//쓰레드1 동적 메모리 할당: 1씩 증가, 감소하는 수를 ui 텍스트로 표현
	drwThread_bar = new drawingThread_bar(this, false);		//쓰레드2 동적 메모리 할당: 난수 생성 및 슬라이더 조작으로 변경된 수를 ui 텍스트로 표현

	//connect(drwThread_dot, SIGNAL(calcAmount_dot(int)), this, SLOT(setCalcAmount_dot(int)));
	//connect(drwThread_dot, SIGNAL(finished()), drwThread_dot, SLOT(deleteLater()));

	//connect(drwThread_bar, SIGNAL(calcAmount_bar(int)), this, SLOT(setCalcAmount_bar(int)));
	//connect(drwThread_bar, SIGNAL(finished()), drwThread_bar, SLOT(deleteLater()));

	connect(ui->pushButton_Active, &QAbstractButton::clicked, this, &ScratchQThread::setThreadStart);		//Active 버튼으로 쓰레드 시작
	connect(ui->pushButton_Control, &QAbstractButton::clicked, this, &ScratchQThread::setVolumeRandom);		//난수 생성된 값으로 라벨 및 ui 출력
	connect(ui->horizontalSlider, &QSlider::valueChanged, this, &ScratchQThread::setVolumeSlider);			//슬라이더 조작 결과값으로 라벨 및 ui 출력
	connect(ui->pushButton_exit, &QAbstractButton::clicked, this, &ScratchQThread::finishedGUI);
}

ScratchQThread::~ScratchQThread()
{
	//delete drwThread_dot;	//쓰레드1 메모리 반환
	//delete drwThread_bar;	//쓰레드2 메모리 반환
	delete ui;				//GUI 쓰레드 메모리 반환
}



void ScratchQThread::setCalcAmount_bar(int _cal_Bar)
{
	QString strBar = "";
	strBar.fill('|', _cal_Bar);
	ui->textEdit_Control->setText(strBar);
	ui->label_ControlNum->setText(QString::number(_cal_Bar));
}

void ScratchQThread::closeEvent(QCloseEvent* event)
{
	event->ignore();
}

void ScratchQThread::finishedGUI()
{
	exit(EXIT_FAILURE);
}

void ScratchQThread::setVolumeSlider()
{
	//슬라이드의 값이 int 형으로 반환되므로 QString 으로 변환하여 저장
	unsigned int sliderNum = ui->horizontalSlider->value();
	QString strVolumeVal = QString::number(sliderNum);

	if (!ui->pushButton_Control->isChecked())		//control 버튼이 SliderBar 일 때
	{
		ui->label_SliderNum->setText(strVolumeVal);	//라벨에 값 출력

		setCalcAmount_bar(sliderNum);				//Control textEdit 에 slider 값 전달
	}
}

void ScratchQThread::setVolumeRandom()
{
	
	if (ui->pushButton_Control->isChecked())		//control 버튼이 RandomBar 일 때
	{
		
		drwThread_bar = new drawingThread_bar(this, false);		//쓰레드2 동적 메모리 할당: 난수 생성 및 슬라이더 조작으로 변경된 수를 ui 텍스트로 표현
		//signal 의 매개변수와 slot 의 매개변수를 동일하게 하여 데이터를 주고받음
		connect(drwThread_bar, SIGNAL(calcAmount_bar(int)), this, SLOT(setCalcAmount_bar(int)));

		drwThread_bar->selectRandom();				//난수 생성 Flag ON
		//start the thread
		drwThread_bar->start();

		ui->horizontalSlider->setDisabled(true);		//슬라이더 조작 비활성화
		ui->label_SliderNum->setText("Disabled");	//슬라이더 라벨에 비활성상태 표시

		ui->pushButton_exit->setDisabled(true);		//쓰레드 2 구동중에는 프로그램 종료 못함.

		qDebug() << "pushButton_Control : Checked";
	}
	else
	{
		//쓰레드가 끝나면(run() 이 끝나면) 객체 제거
		//connect(drwThread_bar, SIGNAL(finished()), drwThread_bar, SLOT(deleteLater()));

		//while 문 중지
		//drwThread_bar->stop();
		drwThread_bar->Stop = true;
		drwThread_bar->quit();			//쓰레드2 중지
		drwThread_bar->wait();			//쓰레드2 안전 종료

		ui->textEdit_Control->clear();	//textEdit 에 dot 제거
		ui->label_ControlNum->clear();	//label 에 dot 개수 제거

		ui->horizontalSlider->setEnabled(true);	//슬라이더 조작 활성화
		ui->label_SliderNum->setText("Enabled");	//슬라이더 라벨에 활성상태 표시

		if (!ui->pushButton_Active->isChecked())
		{
			ui->pushButton_exit->setEnabled(true);		//쓰레드 2 종료되어 exit버튼 활성화
		}
		qDebug() << "pushButton_Control : UnChecked";
	}
}

void ScratchQThread::setCalcAmount_dot(int _cal_dot)
{
	QString strDot = "";			//문자열 초기화
	strDot.fill('.', _cal_dot);		//문자 ' . ' 으로 채워넣기. _cal_dot 수만큼
	ui->textEdit_Active->setText(strDot);	//ui 에 dot 출력

	ui->label_ActiveNum->setText(QString::number(_cal_dot));	//label 에 dot 개수 출력
}

void ScratchQThread::setThreadStart()
{
	if (ui->pushButton_Active->isChecked())
	{
		//initialize the thread
		drwThread_dot = new drawingThread_dot(this, false);		//쓰레드1 동적 메모리 할당: 1씩 증가, 감소하는 수를 ui 텍스트로 표현
		//signal 의 매개변수와 slot 의 매개변수를 동일하게 하여 데이터를 주고받음
		connect(drwThread_dot, SIGNAL(calcAmount_dot(int)), this, SLOT(setCalcAmount_dot(int)));

		//start the thread
		drwThread_dot->start();

		ui->pushButton_exit->setDisabled(true);		//쓰레드 1 구동중에는 프로그램 종료 못함.

		qDebug() << "pushButton_Active : Checked";
	}
	else
	{	
		//쓰레드가 끝나면(run() 이 끝나면) 객체 제거
		connect(drwThread_dot, SIGNAL(finished()), drwThread_dot, SLOT(deleteLater()));

		//while 문 중지
		//drwThread_dot->stop();
		drwThread_dot->Stop = true;
		drwThread_dot->quit();
		drwThread_dot->wait();

		ui->textEdit_Active->clear();	//textEdit 에 dot 제거
		ui->label_ActiveNum->clear();	//label 에 dot 개수 제거

		if (!ui->pushButton_Control->isChecked())
		{
			ui->pushButton_exit->setEnabled(true);		//쓰레드 1 종료되어 exit버튼 활성화
		}
		qDebug() << "pushButton_Active : UnChecked";
	}
}

//thread 테스트코드
//void ScratchQThread::setCalcAmount_dot(float _cal_a, float _cal_b)
//{
//	ui->textEdit_Active->setText(QString::number(_cal_a));
//	ui->textEdit_Control->setText(QString::number(_cal_b));
//}
