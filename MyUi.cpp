#include "MyUi.h"
#include <qmessagebox.h>
#include <QDebug>
#include <qstringlist.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "mainwindow.h"
#include <QTime>
#include <qgridlayout.h>
#include <qmenubar.h>
#include <qaction.h>
#include <qtoolbar.h>



MyUi::MyUi(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{

	this->setWindowTitle(tr("IPPG非接触式生理参数测量系统"));
	this->setIconSize(QSize(35,35));
	this->setWindowIcon(QIcon("./Resources/icon.png"));

	//人脸识别参数设置
	videoName="E:/huawei/10.avi";
	faceSizeFuncControl=0;
	sumWidth=0;
	sumHight=0;
	sumRectx=0;
	sumRecty=0;
	framesCount=900;//设置照片数目
	//主界面设计
	QHBoxLayout* main=new QHBoxLayout();
	QVBoxLayout* right=new QVBoxLayout();
	PatientMessage* patientMessage=new PatientMessage;
	main->addWidget(patientMessage,3);
	QVBoxLayout* middleLay=new QVBoxLayout;
	QHBoxLayout* middleTopLay=new QHBoxLayout;
	QLabel* labelmovie=new  QLabel;
	labelmovie->resize(this->width()*0.5,this->height()*0.1);
	//设置动画
	movie=new QMovie(labelmovie);
	movie->setFileName("./Resources/welcome.gif");
	// 设置缓存模式
	movie->setCacheMode(QMovie::CacheAll);
	// 设置动画大小为标签的大小
	QSize size=labelmovie->size();
	movie->setScaledSize(size);
	labelmovie->setMovie(movie);
	movie->start();
	middleTopLay->addStretch(1);
	QVBoxLayout* videoLay=new QVBoxLayout;
	QPushButton* buttonCarema=new QPushButton(tr("拍摄视频"));
	connect(buttonCarema,SIGNAL(clicked()),this,SLOT(onAction_carema()));
	QPushButton* buttonSelectedCarema=new QPushButton(tr("选择视频"));
	connect(buttonSelectedCarema,SIGNAL(clicked()),this,SLOT(onAction_selectedcarema()));
	videoLay->addWidget(buttonCarema);
	videoLay->addWidget(buttonSelectedCarema);
	middleTopLay->addLayout(videoLay);
	middleTopLay->addStretch(1);
	middleTopLay->addWidget(labelmovie);
	middleTopLay->addStretch(2);
	QLabel* labelTimeInfo=new  QLabel(tr("北京时间："));
	middleTopLay->addWidget(labelTimeInfo);
	labeltime=new QLabel;
	middleTopLay->addWidget(labeltime);
	middleTopLay->addStretch(1);

	VideoPlayer* videoplay=new VideoPlayer;
	middleLay->addLayout(middleTopLay);
	middleLay->addWidget(videoplay);
	main->addLayout(middleLay,5);

	QVBoxLayout* rightmax=new QVBoxLayout;
	main->addLayout(rightmax,3);
	QHBoxLayout* rightTitle=new QHBoxLayout;
	QLabel* labelCameraTitle=new QLabel(tr("<h1>检测演示</h1>"));
	rightTitle->addStretch(1);
	rightTitle->addWidget(labelCameraTitle,1);
	rightTitle->addStretch(1);
	rightmax->addLayout(rightTitle);

	//QPushButton* selectVideo=new QPushButton(tr("选择视频"));
	//QHBoxLayout* rightVideo=new QHBoxLayout;
	//rightVideo->addStretch(1);
	//rightVideo->addWidget(selectVideo,1);
	//rightVideo->addStretch(1);
	//rightmax->addLayout(rightVideo);

	QGroupBox* group=new QGroupBox;
	group->setTitle(tr("检测心率和呼吸频率"));
	group->setAlignment(Qt::AlignHCenter);
	QFormLayout* formHeart=new QFormLayout();
	group->setLayout(formHeart);
	QLabel* label1=new QLabel(tr("视频转化为帧序列："));
	QLabel* label2=new QLabel(tr("人脸检测并得到ROI："));
	QLabel* label3=new QLabel(tr("彩色图像分离成三通道："));
	QLabel* label4=new QLabel(tr("ICA分析："));
	QLabel* label5=new QLabel(tr("带通滤波："));
	button1=new  QPushButton(tr("运行"));
	connect(button1,SIGNAL(clicked()),this,SLOT(videoToImage()));
	button2=new  QPushButton(tr("运行"));
	connect(button2,SIGNAL(clicked()),this,SLOT(FindROI()));
	button3=new  QPushButton(tr("运行"));
	connect(button3,SIGNAL(clicked()),this,SLOT(GetThreeChannel()));
	button4=new  QPushButton(tr("运行"));
	connect(button4,SIGNAL(clicked()),this,SLOT(ICA()));
	button5=new  QPushButton(tr("运行"));
	connect(button5,SIGNAL(clicked()),this,SLOT(bandPass()));

	formHeart->addRow(label1,button1);
	formHeart->addRow(label2,button2);
	formHeart->addRow(label3,button3);
	formHeart->addRow(label4,button4);
	formHeart->addRow(label5,button5);
	formHeart->setContentsMargins(20,10,20,10);
	formHeart->setHorizontalSpacing(30);
	formHeart->setVerticalSpacing(10);
	rightmax->addWidget(group);

	QGroupBox* groupblood=new QGroupBox;
	groupblood->setTitle(tr("检测血氧饱和度"));
	groupblood->setAlignment(Qt::AlignHCenter);
	QFormLayout* formBlood=new QFormLayout();
	groupblood->setLayout(formBlood);
	QLabel* label21=new QLabel(tr("视频转化为帧序列："));
	QLabel* label22=new QLabel(tr("人脸检测并得到ROI："));
	QLabel* label23=new QLabel(tr("彩色图像分离成三通道："));
	button21=new  QPushButton(tr("运行"));
	connect(button21,SIGNAL(clicked()),this,SLOT(videoToImageButton()));
	button22=new  QPushButton(tr("运行"));
	connect(button22,SIGNAL(clicked()),this,SLOT(FindROIButton()));
	button23=new  QPushButton(tr("运行"));
	connect(button23,SIGNAL(clicked()),this,SLOT(GetThreeChannel()));
	QLabel* label6=new QLabel(tr("平滑滤波："));
	QLabel* label7=new QLabel(tr("极值点序列："));
	QLabel* label8=new QLabel(tr("求R值："));
	QLabel* label9=new QLabel(tr("求血氧饱和度："));
	button6=new  QPushButton(tr("运行"));
	connect(button6,SIGNAL(clicked()),this,SLOT(smooth()));
	button7=new  QPushButton(tr("运行"));
	connect(button7,SIGNAL(clicked()),this,SLOT(getServalMax()));
    button8=new  QPushButton(tr("运行"));
	connect(button8,SIGNAL(clicked()),this,SLOT(getR()));
	button9=new  QPushButton(tr("运行"));
	connect(button9,SIGNAL(clicked()),this,SLOT(getBloodResult()));
	formBlood->addRow(label21,button21);
	formBlood->addRow(label22,button22);
	formBlood->addRow(label23,button23);
	formBlood->addRow(label6,button6);
	formBlood->addRow(label7,button7);
	formBlood->addRow(label8,button8);
	formBlood->addRow(label9,button9);
	formBlood->setContentsMargins(20,10,20,10);
	formBlood->setHorizontalSpacing(30);
	formBlood->setVerticalSpacing(10);
	rightmax->addWidget(groupblood);

	button2->setDisabled(true);
	button3->setDisabled(true);
	button4->setDisabled(true);
	button5->setDisabled(true);
	button6->setDisabled(true);
	button7->setDisabled(true);
	button8->setDisabled(true);
	button9->setDisabled(true);
	button22->setDisabled(true);
	button23->setDisabled(true);

	QGroupBox* groupResult=new QGroupBox;
	groupResult->setTitle(tr("检测结果"));
	groupResult->setAlignment(Qt::AlignHCenter);
	QFormLayout* formResult=new QFormLayout();
	groupResult->setLayout(formResult);
	QLabel* label10=new QLabel(tr("<h1>心率：</h1>"));
	QLabel* label12=new QLabel(tr("<h1>呼吸频率：</h1>"));
	QLabel* label11=new QLabel(tr("<h1>血氧饱和度：</h1>"));
	heartResult=new QLineEdit;
	breathe=new QLineEdit;
	bloodResult=new QLineEdit;
	heartResult->setReadOnly(true);
	bloodResult->setReadOnly(true);
	breathe->setReadOnly(true);
	formResult->addRow(label10,heartResult);
	formResult->addRow(label12,breathe);
	formResult->addRow(label11,bloodResult);
	formResult->setAlignment(Qt::AlignBottom);
	formResult->setContentsMargins(20,10,20,10);
	formResult->setHorizontalSpacing(80);
	formResult->setVerticalSpacing(10);
	rightmax->addWidget(groupResult);


	QWidget* widget=new QWidget;
	widget->setLayout(main);
	this->setCentralWidget(widget);

	this->showMaximized();


	//布局
	QMenuBar* menu=this->menuBar();
	menu->setFont(QFont("Helvetica [Cronyx]", 16));
	QMenu* user=menu->addMenu(tr("用户登记"));
	QMenu* carema=menu->addMenu(tr("相机模块"));
	QMenu* platform=menu->addMenu(tr("云台模块"));
	QMenu* information=menu->addMenu(tr("检查报告"));
	QMenu* data=menu->addMenu(tr("数据管理"));
	QMenu* account=menu->addMenu(tr("账户管理"));
	QMenu* browser=menu->addMenu(tr("浏览器"));
	QMenu* video=menu->addMenu(tr("视频回放"));
	QMenu* system=menu->addMenu(tr("系统"));
	QAction* action_shortcutText=new QAction(QIcon("./Resources/shortcutkey.png"),tr("快捷键说明"),system);
	QAction* action_systemMessage=new QAction(QIcon("./Resources/systemInformation.png"),tr("系统信息"),system);
	QAction* action_exit=new QAction(QIcon("./Resources/exit.png"),tr("退出系统"),system);
	QAction* action_videoPlay=new QAction(QIcon("./Resources/playvideo.png"),tr("视频播放"),video);
	QAction* action_brower=new QAction(QIcon("./Resources/brower.png"),tr("浏览器"),browser);
	QAction* action_calc=new QAction(QIcon("./Resources/calc.ico"),tr("计算器"),system);
	QAction* action_carema=new QAction(QIcon("./Resources/camera.png"),tr("相机拍摄"),carema);
	QAction* action_addUserData=new QAction(QIcon("./Resources/data.png"),tr("录入病人数据"),user);
	QAction* action_measure=new QAction(QIcon("./Resources/measure.png"),tr("相机测量"),carema);
	QAction* action_platform=new QAction(QIcon("./Resources/platform.png"),tr("云台控制"),platform);

	QAction* action_paitentManegent=new QAction(QIcon("./Resources/journal.png"),tr("用户信息管理"),user);
	QAction* action_special=new QAction(QIcon("./Resources/special.png"),tr("用户病情管理"),user);
	QAction* action_queue=new QAction(QIcon("./Resources/queue.png"),tr("预约排队"),user);
	QAction* action_test=new QAction(QIcon("./Resources/journal.png"),tr("检查日志"),information);
	QAction* action_report=new QAction(QIcon("./Resources/report.png"),tr("检查报告"),information);

	QAction* action_historyUserData=new QAction(QIcon("./Resources/historydata.png"),tr("用户历史数据"),data);
	QAction* action_historyTest=new QAction(QIcon("./Resources/historyjournal.png"),tr("历史检查日志"),data);
	QAction* action_historyReport=new QAction(QIcon("./Resources/historyreport.png"),tr("历史检查报告"),data);
	QAction* action_account=new QAction(QIcon("./Resources/account.png"),tr("注册账户"),account);

	user->addAction(action_addUserData);//1
	user->addAction(action_queue);
    user->addAction(action_paitentManegent);
	user->addAction(action_special);
	carema->addAction(action_carema);//2
	carema->addAction(action_measure);
#if 1
	platform->addAction(action_platform);//3
#endif 
	information->addAction(action_test);//4
	information->addAction(action_report);
	data->addAction(action_historyUserData);//5
	data->addAction(action_historyTest);
	data->addAction(action_historyReport);
	account->addAction(action_account);//6
	browser->addAction(action_brower);//7
	video->addAction(action_videoPlay);//8
	system->addAction(action_shortcutText);//9
	system->addAction(action_systemMessage);
	system->addAction(action_exit);

 
	action_addUserData->setFont(QFont("Helvetica [Cronyx]", 16));
	action_queue->setFont(QFont("Helvetica [Cronyx]", 16));
	action_paitentManegent->setFont(QFont("Helvetica [Cronyx]", 16));
	action_special->setFont(QFont("Helvetica [Cronyx]", 16));
	action_carema->setFont(QFont("Helvetica [Cronyx]", 16));
	action_measure->setFont(QFont("Helvetica [Cronyx]", 16));
	action_platform->setFont(QFont("Helvetica [Cronyx]", 16));
	action_test->setFont(QFont("Helvetica [Cronyx]", 16));
	action_report->setFont(QFont("Helvetica [Cronyx]", 16));
	action_historyUserData->setFont(QFont("Helvetica [Cronyx]", 16));
	action_historyTest->setFont(QFont("Helvetica [Cronyx]", 16));
	action_historyReport->setFont(QFont("Helvetica [Cronyx]", 16));
	action_account->setFont(QFont("Helvetica [Cronyx]", 16));
	action_brower->setFont(QFont("Helvetica [Cronyx]", 16));
	action_videoPlay->setFont(QFont("Helvetica [Cronyx]", 16));
	action_shortcutText->setFont(QFont("Helvetica [Cronyx]", 16));
	action_systemMessage->setFont(QFont("Helvetica [Cronyx]", 16));
	action_exit->setFont(QFont("Helvetica [Cronyx]", 16));

	action_queue->setShortcut(QKeySequence(tr("Ctrl+A")));
	action_paitentManegent->setShortcut(QKeySequence(tr("Ctrl+B")));
	action_special->setShortcut(QKeySequence(tr("Ctrl+Y")));
	action_test->setShortcut(QKeySequence(tr("Ctrl+D")));
	action_report->setShortcut(QKeySequence(tr("Ctrl+E")));
	action_historyUserData->setShortcut(QKeySequence(tr("Ctrl+F")));
	action_videoPlay->setShortcut(QKeySequence(tr("Ctrl+G")));
	action_historyTest->setShortcut(QKeySequence(tr("Ctrl+H")));
	action_historyReport->setShortcut(QKeySequence(tr("Ctrl+I")));
	action_account->setShortcut(QKeySequence(tr("Ctrl+K")));
	action_systemMessage->setShortcut(QKeySequence(tr("Ctrl+L")));
	action_exit->setShortcut(QKeySequence(tr("Ctrl+M")));
	action_shortcutText->setShortcut(QKeySequence(tr("Ctrl+N")));


//工具栏
	QToolBar* toolBar=new QToolBar;
	toolBar->setSizeIncrement(QSize(30,30));
	toolBar->addAction(action_addUserData);//1
	toolBar->addAction(action_queue);
    toolBar->addAction(action_paitentManegent);
	toolBar->addAction(action_special);
	toolBar->addAction(action_carema);//2
	toolBar->addAction(action_videoPlay);//8
#if 0
	toolBar->addAction(action_measure);
	toolBar->addAction(action_platform);//3
#endif 
	toolBar->addAction(action_test);//4
	toolBar->addAction(action_report);
	toolBar->addAction(action_historyUserData);//5
	toolBar->addAction(action_historyTest);
	toolBar->addAction(action_historyReport);
	toolBar->addAction(action_account);//6
	toolBar->addAction(action_brower);//7
	toolBar->addAction(action_shortcutText);//9
	toolBar->addAction(action_systemMessage);
	toolBar->addAction(action_calc);
	toolBar->addAction(action_exit);
	
	this->addToolBar(toolBar);
	

#if 0
	this->setBackgroundPixmap(QPixmap("./Resources/background5.jpg"));
#endif
	timeClock=new QTimer(this);
	connect(timeClock,SIGNAL(timeout()),this,SLOT(onTimeOut()));
	timeClock->setInterval(500);
	timeClock->start();
	//QGraphicsView* view=new QGraphicsView(&scene);
	//view->setForegroundBrush(QColor(255, 255, 255, 100));
	//view->setBackgroundBrush(QPixmap("./Resources/background.jpg"));
	//view->show();

	//布局
	//QGridLayout* grid=new QGridLayout(this);
	//QVBoxLayout* main=new QVBoxLayout(this);
	//QHBoxLayout* top=new QHBoxLayout;
	//QVBoxLayout* right=new QVBoxLayout;
	//QHBoxLayout* small=new QHBoxLayout;
	//QHBoxLayout* time=new QHBoxLayout;
	//time->addWidget(ui.label_2);
	//time->addWidget(ui.labeltime);
	//small->addWidget(ui.labelmovie);
	//small->addLayout(time);
	////small->addWidget(ui.label_2);
	////small->addWidget(ui.labeltime);
	//right->addLayout(small);
	//right->addWidget(ui.label);
	//top->addWidget(ui.calendarWidget);
	//top->addLayout(right);
	//main->addLayout(top);
	//main->addWidget(ui.labelback);
	//grid->addLayout(main,1,1);
	//grid->setColumnStretch(0,1);
	//grid->setColumnStretch(1,8);
	//grid->setColumnStretch(2,1);
	//grid->setRowStretch(0,1);
	//grid->setRowStretch(1,8);
	//grid->setRowStretch(2,1);
	//this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	//this->setLayout(grid);
	//this->showMaximized();



	caremaProcess=new QProcess() ; 
	connect(caremaProcess,SIGNAL(error(QProcess::ProcessError)),this,SLOT(processError (QProcess::ProcessError)));

	QObject::connect(action_shortcutText,SIGNAL(triggered()),this,SLOT(onAction_shortcutText()));
	QObject::connect(action_systemMessage,SIGNAL(triggered()),this,SLOT(onAction_systemMessage()));
	QObject::connect(action_exit,SIGNAL(triggered()),this,SLOT(onAction_exit()));
	QObject::connect(action_videoPlay,SIGNAL(triggered()),this,SLOT(onAction_videoPlayer()));
	QObject::connect(action_brower,SIGNAL(triggered()),this,SLOT(onAction_browser()));
	QObject::connect(action_calc,SIGNAL(triggered()),this,SLOT(onAction_calc()));
	QObject::connect(action_carema,SIGNAL(triggered()),this,SLOT(onAction_carema()));
	QObject::connect(action_addUserData,SIGNAL(triggered()),this,SLOT(onAction_addUserData()));
#if 0
	QObject::connect(action_measure,SIGNAL(triggered()),this,SLOT(onAction_measure()));
	QObject::connect(action_platform,SIGNAL(triggered()),this,SLOT(onAction_platform()));
#endif

	QObject::connect(action_paitentManegent,SIGNAL(triggered()),this,SLOT(onAction_paitentManegent()));
	QObject::connect(action_special,SIGNAL(triggered()),this,SLOT(onAction_special()));
	QObject::connect(action_queue,SIGNAL(triggered()),this,SLOT(onAction_queue()));

	QObject::connect(action_test,SIGNAL(triggered()),this,SLOT(onAction_test()));
	QObject::connect(action_report,SIGNAL(triggered()),this,SLOT(onAction_testReport()));

	QObject::connect(action_historyUserData,SIGNAL(triggered()),this,SLOT(onAction_historyUserData()));
	QObject::connect(action_historyTest,SIGNAL(triggered()),this,SLOT(onAction_historyLog()));
	QObject::connect(action_historyReport,SIGNAL(triggered()),this,SLOT(onAction_historyReport()));

	QObject::connect(action_account,SIGNAL(triggered()),this,SLOT(onAction_RegisterAccount()));

	connect(timeClock,SIGNAL(timeout()),this,SLOT(onTimeOut()));


	//background=new QMovie(ui.labelback);
	//background->setFileName("./Resources/scene.gif");
	//// 设置缓存模式
	//background->setCacheMode(QMovie::CacheAll);
	//// 设置动画大小为标签的大小
	//QSize sizeback=ui.labelback->size();
	//background->setScaledSize(sizeback);
	//ui.labelback->setMovie(background);
	//background->start();
	


	//this->setBackgroundPixmap(QPixmap("./Resources/background.jpg"));

	connect(buttonCarema,SIGNAL(clicked()),this,SLOT(onAction_carema()));
	action_historyUserData->setIcon(QIcon("./Resources/historydata.png"));
	action_historyTest->setIcon(QIcon("./Resources/historyjournal.png"));
	action_historyReport->setIcon(QIcon("./Resources/historyreport.png"));
	action_account->setIcon(QIcon("./Resources/account.png"));
}
void MyUi::onAction_systemMessage()
{
	SystemMessage* systemMessage=new SystemMessage;
	systemMessage->show();
}
void MyUi::onAction_shortcutText()
{
	ShortcutText* shortcutText=new ShortcutText;
	shortcutText->show();
}
//退出窗口
void MyUi::onAction_exit()
{	
	QMessageBox::StandardButton ret;
    QMessageBox exitInformation;
	exitInformation.setWindowIcon(QIcon("./Resources/systemInformation.png"));
	ret=exitInformation.information(this,tr("提示"),tr("确定要退出程序么？"),QMessageBox::Yes|QMessageBox::No);
	if(ret==QMessageBox::Yes)
		this->close();	
}
void MyUi::onAction_videoPlayer()
{	
	VideoPlayer* videoplay=new VideoPlayer;
	videoplay->resize(800,600);
	videoplay->show();
}

void MyUi::mouseDoubleClickEvent(QMouseEvent *ev)
{
	if(ev->button()==Qt::LeftButton)
	{
		if(windowState()!=Qt::WindowMaximized)
			setWindowState(Qt::WindowMaximized);
	}
}
void MyUi::onAction_browser()
{	
	QString program="../webbrowser.exe";
	browserProcess.start(program);
	
}
void MyUi::onAction_calc()
{
	QString program="calc.exe";
	browserProcess.start(program);

}
void MyUi::onAction_addUserData()
{
	AddUserData* addUserData=new AddUserData;
	addUserData->show();
}
void MyUi::onAction_carema()
{
	//QString programe = "cmd.exe";
        //QStringList arguments;
        //arguments.append("calc.exe");
        //arguments << "D:/360Downloads/MindVision/Measure.exe";
        //caremaProcess->execute(programe, arguments);
	//caremaProcess->waitForFinished();
	//qDebug()<<QString::fromLocal8Bit(caremaProcess->readAllStandardError());
	//QProcess p(0);
	//QString command=tr("MVDCP.exe");
	//p.execute(command);
	//p.waitForFinished(2000);
	//qDebug()<<QString::fromLocal8Bit(p.readAllStandardError());
	QString program=tr("D:/programtext/vsqt/MVDCP.exe");	
	browserProcess.start(program);
}
void MyUi::onAction_selectedcarema()
{
	QFileDialog* fileDialog=new QFileDialog(this);
	fileDialog->setWindowIcon(QIcon("./Resources/openfile.png"));
	fileDialog->setWindowTitle(tr("选择操作视频"));
	fileDialog->setDir(QDir("E:/huawei"));
	fileDialog->exec();
	//videoName=fileDialog->selectedFile().toLatin1().data();
	videoName=fileDialog->selectedFile().toStdString();
	//char* tempVideoCon=new char[tempVideoName.size()];


}
void MyUi::onAction_measure()
{
	//QString program=tr("D:/programtext/vsqt/MVDCP.exe");
	//caremaProcess->start(program);
	QString program=tr("D:/programtext/vsqt/Measure.exe");	
	browserProcess.start(program);
}

void MyUi::onAction_platform()
{
	QString program=tr("../Control.exe");
	browserProcess.start(program);

}
//检测进程错误
void MyUi::processError(QProcess::ProcessError error)
{
 switch(error)
 {
  case QProcess::FailedToStart:
    QMessageBox::information(0,"FailedToStart","FailedToStart");
    break; 
  case QProcess::Crashed:
    QMessageBox::information(0,"Crashed","Crashed");
    break;
  case QProcess::Timedout:
    QMessageBox::information(0,"FailedToStart","FailedToStart");
    break;
  case QProcess::WriteError:
    QMessageBox::information(0,"Timedout","Timedout");
    break;
  case QProcess::ReadError:
    QMessageBox::information(0,"ReadError","ReadError");
    break;
  case QProcess::UnknownError:
    QMessageBox::information(0,"UnknownError","UnknownError");
    break;
  default:
    QMessageBox::information(0,"default","default");
    break;
 }
}
//调出用户信息管理界面
void MyUi::onAction_paitentManegent()
{
	MainWindow* paientMessage=new MainWindow;
	paientMessage->show();
	
}
//调出用户病情管理界面
void MyUi::onAction_special()
{
	SpecialMessage* specialMessage=new SpecialMessage;
	specialMessage->show();
	//Special* special=new Special;
	//special->show();
}
void MyUi::onAction_queue()
{
    Queue* queue=new Queue;
	queue->show();
}
void MyUi::onTimeOut()
{
	QTime currentTime=QTime::currentTime();
	QString stringTime=currentTime.toString(Qt::TextDate);
	labeltime->setText(stringTime);
}
void MyUi::onAction_test()
{
	TestLog* testLog=new TestLog;
	testLog->show();
}
void MyUi::onAction_testReport()
{
	TestReport* report=new TestReport;
	report->show();
}
void MyUi::onAction_historyUserData()
{
    HistoryUserData* userData=new HistoryUserData;
	userData->show();
}
void MyUi::onAction_historyLog()
{
	HistoryLog* historylog=new HistoryLog;
	historylog->show();
}
void MyUi::onAction_historyReport()
{
	HistoryReport* historyreport=new HistoryReport;
	historyreport->show();
}
void MyUi::onAction_RegisterAccount()
{
	RegisterAccount* registerAccount=new RegisterAccount;
	registerAccount->show();
}
//算法


//去均值
void MyUi::remean(cv::Mat input,cv::Mat & output)
{
   cv::Mat mean;
   cv::reduce(input,mean,0,CV_REDUCE_AVG);
   cv::Mat temp = cv::Mat::ones(input.rows, 1, CV_64FC1);
   output=input-temp*mean;
   
}
//白化
void MyUi::whiten(cv::Mat input,cv::Mat &output)
{
// need to be remean before whiten	

const int N=input.rows;  //num of data
const int M=input.cols;  //dimention	
    
 cv::Mat cov;
 cv::Mat D;
 cv::Mat E;
 cv::Mat temp=cv::Mat::eye(M,M,CV_64FC1);
 cv::Mat temp2;
 
 cov=input.t()*input/N;
 cv::eigen(cov,D,E);
 cv::sqrt(D,D);
 
 for(int i=0;i<M;i++)
 { temp.at<double>(i,i)=D.at<double>(i,0);}
 
 temp2=E*temp.inv()*E.t()*input.t();
 
 
 output=temp2.t();
 

} 
void MyUi::whiten(cv::Mat input,cv::Mat &output,cv::Mat &E,cv::Mat &D)
{
 // need to be remean before whiten	

const int N=input.rows;  //num of data
const int M=input.cols;  //dimention	
    
 cv::Mat cov;
 cv::Mat D2;
 cv::Mat temp=cv::Mat::eye(M,M,CV_64FC1);
 cv::Mat temp2;
 cv::Mat E2;

 cov=input.t()*input/N;
 cv::eigen(cov,D,E2);
 cv::sqrt(D,D2);
 E=E2.t();

 for(int i=0;i<M;i++)
 { temp.at<double>(i,i)=D2.at<double>(i,0);}
 
   temp2=E2*temp.inv()*E2.t()*input.t();
 
    Mat a=E2*temp.inv();

  // qDebug()<<"a:"<<endl;
   for(int i=0;i<a.rows;i++)
  {
	  for(int j=0;j<a.cols;j++)
	  {
		 // qDebug()<<i<<" row "<<j<<" col "<<a.at<double>(i,j)<<endl;
	  }
  }

  output=temp2.t();
 } 	 
 
 void MyUi::runICA(cv::Mat input, cv::Mat &output,cv::Mat &W,int snum)     //output =Independent components matrix,W=Un-mixing matrix
 {      
        const  int M=input.rows;    // number of data
        const  int N=input.cols;    // data dimension
	
        const int maxIterations=1000;
        const double epsilon=0.0001;
        
        if(N<snum)
        { 
	       snum=M;
           printf(" Can't estimate more independent components than dimension of data ");}    
		   cv::Mat R(snum,N,CV_64FC1);
		   cv::randn(R, cv::Scalar(0), cv::Scalar(1));
		   cv::Mat ONE=cv::Mat::ones(M,1,CV_64FC1);
    
	      for(int i=0;i<snum;++i)
         {
			 int iteration=0;
			 cv::Mat P(1,N,CV_64FC1);
			 R.row(i).copyTo(P.row(0));
               
          while(iteration<=maxIterations)
          { 
            iteration++;
           	cv::Mat P2;
			P.copyTo(P2);
           	cv::Mat temp1,temp2,temp3,temp4;
           	temp1=P*input.t();
           	cv::pow(temp1,3,temp2);
           	cv::pow(temp1,2,temp3);
           	temp3=3*temp3;
           	temp4=temp3*ONE;
           	P=temp2*input/M-temp4*P/M;
                      
            if(i!=0)
           {
			 cv::Mat temp5;
			 cv::Mat wj(1,N,CV_64FC1);
			 cv::Mat temp6=cv::Mat::zeros(1,N,CV_64FC1);			
			
			 for(int j=0;j<i;++j)
			 {
				R.row(j).copyTo(wj.row(0));
				temp5=P*wj.t()*wj;				
				temp6=temp6+temp5;
			    
			 }
			 P=P-temp6;
	     	}
			 double Pnorm=cv::norm(P,4);
             P=P/Pnorm;				 
			 double j1=cv::norm(P-P2,4);
			 double j2=cv::norm(P+P2,4);
             if(j1<epsilon || j2<epsilon)
             {  
	            P.row(0).copyTo(R.row(i));
	            break;
	          }
	          else if( iteration==maxIterations)
	          {
				  P.row(0).copyTo(R.row(i));
			  }
            }
          }
          output=R*input.t();
          W=R;
  } 
 //计算两个数组的相关系数
 double MyUi::getColrelationNum(QList<double> arrayOne,QList<double> arrayTwo)
 {
	 //求两数组和
	 long double sumArrayOne,sumArrayTwo,sumArrayOneAndTwo;
	 sumArrayOne=0.0;
	 sumArrayTwo=0.0;
	 sumArrayOneAndTwo=0.0;
	 for(int i=0;i<arrayOne.size();i++)
	 {
		 sumArrayOne+=arrayOne.at(i);
		 sumArrayTwo+=arrayTwo.at(i);
		 sumArrayOneAndTwo+=arrayOne.at(i)*arrayTwo.at(i);
	 }
	 long double upRes=sumArrayOneAndTwo*arrayOne.size()-sumArrayOne*sumArrayTwo;
	 long double bottomLeft=0.0;
	 long double bottomRight=0.0;
	 long double sumOnePow=0.0;
	 long double sumTwoPow=0.0;
	 for(int i=0;i<arrayOne.size();i++)
	 {
		 sumOnePow+=pow(arrayOne.at(i),2);
		 sumTwoPow+=pow(arrayTwo.at(i),2);
	 }
	 bottomLeft=sqrt(sumOnePow*arrayOne.size()-pow(sumArrayOne,2));
	 bottomRight=sqrt(sumTwoPow*arrayOne.size()-pow(sumArrayTwo,2));
	 long double bottomRes=bottomLeft*bottomRight;
	 double result=0.0;
	 result=upRes/bottomRes;
	 return abs(result);
 }
 //DFS将时域转频域
QList<double> MyUi::timeToFrequency(QList<double>  containOneICA)
 {


      SIZE=containOneICA.size();
	 //int m = cv::getOptimalDFTSize(SIZE);
	 //qDebug()<<"m="<<m<<endl;
	 int m=0;
	 if(SIZE<8)
	 {
		 m=8;
	 }
	 else if((SIZE>8)&&(SIZE<16))
	 {
		 m=16;
	 }
	 else if((SIZE>16)&&(SIZE<32))
	 {
		 m=32;
	 }
	 else if((SIZE>32)&&(SIZE<64))
	 {
		 m=64;
	 }
	 else if((SIZE>64)&&(SIZE<128))
	 {
		 m=128;
	 }
	  else if((SIZE>128)&&(SIZE<256))
	 {
		 m=256;
	 }
	 else if((SIZE>256)&&(SIZE<512))
	 {
		 m=512;
	 }
	 else if((SIZE>512)&&(SIZE<1024))
	 {
		 m=1024;
	 }
	 else if((SIZE>512)&&(SIZE<1024))
	 {
		 m=1024;
	 }
	 else if((SIZE>1024)&&(SIZE<2048))
	 {
		 m=2048;
	 }
	 else if((SIZE>1024)&&(SIZE<2048))
	 {
		 m=2048;
	 }
	 else if((SIZE>2048)&&(SIZE<4096))
	 {
		 m=4096;
	 }
	 else if((SIZE>4096)&&(SIZE<8192))
	 {
		 m=8192;
	 }
	 else if((SIZE>8192)&&(SIZE<16384))
	 {
		 m=16384;
	 }

	 if(m>SIZE)
	 {
		SIZE=m;
	 }
	 qDebug()<<"SIZE="<<SIZE<<endl;
	 samples=new float[SIZE];
	 fft=new float[SIZE];

	//Creating sample values
	for(int i = 0; i < containOneICA.size(); ++i)
	{
		samples[i] = (float)containOneICA.at(i);
	}
	if(SIZE>containOneICA.size())
	{
		for(int i=containOneICA.size();i<SIZE;i++)
		{
			samples[i] = 0.0;
		}
	}

	QFourierTransformer transformer;

	QStringList functions = transformer.windowFunctions();
	qDebug()<<"The following window functions are available:\n";
	for(int i = 0; i < functions.size(); ++i)
	{
		//qDebug()<<QString::number(i + 1) << ". " << functions[i] <<endl; 
	}
	

	qDebug()<<"Samples before transformation:\n";
	for(int i = 0; i < SIZE; ++i)
	{
		//qDebug()<<"samples["<<i<<"]="<<samples[i]<<endl;
		
	}
	//qDebug()<<"size="<<SIZE<<endl;


	//Setting a fixed size for the transformation
	if(transformer.setSize(SIZE) == QFourierTransformer::VariableSize)
	{
		qDebug()<<"This size is not a default fixed size of QRealFourier. Using a variable size instead.\n";
	}
	else if(transformer.setSize(SIZE) == QFourierTransformer::InvalidSize)
	{
		qDebug()<<"Invalid FFT size.\n";
	}

	if(!transformer.setWindowFunction("Hamming"))
	{
		qDebug()<<"Could not find this window function. Defaulting to the previous one.\n";
	}

	transformer.forwardTransform(samples, fft);
	//transformer.inverseTransform(fft, samples);
	//qDebug()<<"fft after transformation and before rescaling:\n";
	

	QComplexVector complexVector=transformer.toComplex(fft);
	qDebug()<<"Samples after transformation and before rescaling:\n";
	QList<double> showFFT;
	for(int i=0;i<complexVector.size();i++)
	{
		double result=(double)sqrt(pow(complexVector[i].real(),2)+pow(complexVector[i].imaginary(),2));
		showFFT.push_back(result);
	}

	return showFFT;

 }

 QList<double> MyUi::bandPassFilter(QList<double> &FFRresult,double radius,double radius2)
 {
	 double interval=(double)myfps/SIZE;
	 qDebug()<<"myfps="<<myfps<<endl;
	 qDebug()<<"SIZE="<<SIZE<<endl;
	 qDebug()<<"interval="<<interval<<endl;
	 qDebug()<<"FFRresult.size()="<<FFRresult.size()<<endl;
	 double small=radius/interval;
	 double large=radius2/interval;
	 qDebug()<<"small="<<(int)small<<endl;
	 qDebug()<<"large="<<(int)large<<endl;
	 double max=0.0;
	 int maxId=0;
	 for(int i=(int)small;i<((int)large+2);i++)
	 {
		 //qDebug()<<"FFRresult.at(i)="<<FFRresult.at(i)<<endl;
		 if(FFRresult.at(i)>max)
		 {
			  max=FFRresult.at(i);
			  maxId=i;
		 }
	 }
	 qDebug()<<"max="<<max<<endl;
	 qDebug()<<"maxId="<<maxId<<endl;
	 qDebug()<<"对应的频率是"<<maxId*interval<<endl;
	 qDebug()<<"心率是"<<maxId*interval*60<<endl;
	 double heartFre=maxId*interval*60;
	 heartResult->setText(QString::number(heartFre));
	 return FFRresult;
 }

 double MyUi::getBreathe(QList<double> &FFRresult,double radius,double radius2)
 {
	 double interval=(double)myfps/SIZE;
	 qDebug()<<"myfps="<<myfps<<endl;
	 qDebug()<<"SIZE="<<SIZE<<endl;
	 qDebug()<<"interval="<<interval<<endl;
	 qDebug()<<"FFRresult.size()="<<FFRresult.size()<<endl;
	 double small=radius/interval;
	 double large=radius2/interval;
	 qDebug()<<"small="<<(int)small<<endl;
	 qDebug()<<"large="<<(int)large<<endl;
	 double max=0.0;
	 int maxId=0;
	 for(int i=(int)small;i<((int)large+2);i++)
	 {
		 //qDebug()<<"FFRresult.at(i)="<<FFRresult.at(i)<<endl;
		 if(FFRresult.at(i)>max)
		 {
			  max=FFRresult.at(i);
			  maxId=i;
		 }
	 }
	 qDebug()<<"max="<<max<<endl;
	 qDebug()<<"maxId="<<maxId<<endl;
	 qDebug()<<"对应的频率是"<<maxId*interval<<endl;
	 qDebug()<<"呼吸速率是"<<maxId*interval*60<<endl;
	 return maxId*interval*60;
 }
void MyUi::videoToImage()
{
	button2->setDisabled(true);
	button3->setDisabled(true);
	button4->setDisabled(true);
	button5->setDisabled(true);
	//删除目录下所有照片
	QDir d("./PictureSequence");
	d.setFilter(QDir::Files);
	int fileNum,fileSumNum=d.count()-1;
	for (fileNum=0;fileNum<=fileSumNum;fileNum++)
	    d.remove(d[fileNum]);

	
	char* outDir="./PictureSequence/";

	int maxFrameCount=framesCount;
	char* imgExt=".png";
	qDebug()<<"videoName="<<videoName.c_str()<<endl;
	const char* videoUseName=videoName.c_str();
	 CvCapture* capture = cvCaptureFromAVI(videoUseName);
	


	//获取视频信息
	 cvQueryFrame(capture);
	 myframeH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	 myframeW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	 myfps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	 mynumFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);

	qDebug()<<"frameH="<<myframeH<<",frameW="<<myframeW<<",fps="<<myfps<<",numFrames="<<mynumFrames<<endl;
	
	//定义和初始化变量
	int i = 0;
	IplImage* img = 0;	
	char image_name[30];
	cvNamedWindow( "视频转化为帧图片" );//, CV_WINDOW_AUTOSIZE
	int frame=0;
	//读取和显示
	while((img = cvQueryFrame(capture))!=NULL)	//获取一帧图片
	{
		frame++;
		qDebug()<<"frame="<<frame<<endl;
		QString frameShow=tr("帧照片数目=");
		frameShow+=QString::number(frame);
		button1->setText(frameShow);
		cvShowImage( "视频转化为帧图片", img ); //将其显示
		char key = cvWaitKey(20);
		sprintf(image_name, "%s%d%s", "./PictureSequence/", frame, ".png");//保存的图片名
		cvSaveImage( image_name, img);   //保存一帧图片
		if(frame == maxFrameCount) break;
	}
		cvReleaseCapture(&capture);
		cvDestroyWindow("视频转化为帧图片");
		button1->setText(tr("运行"));
		button2->setDisabled(false);
		button3->setDisabled(false);
		button4->setDisabled(false);
		button5->setDisabled(false);

}
Mat MyUi::detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale, bool tryflip )
{
	faceSizeFuncControl++;
    int i = 0;
    double t = 0;

    //建立用于存放人脸的向量容器
    vector<Rect> faces, faces2;
    //定义一些颜色，用来标示不同的人脸
    const static Scalar colors[] =  { CV_RGB(0,0,255),
        CV_RGB(0,128,255),
        CV_RGB(0,255,255),
        CV_RGB(0,255,0),
        CV_RGB(255,128,0),
        CV_RGB(255,255,0),
        CV_RGB(255,0,0),
        CV_RGB(255,0,255)} ;
    //建立缩小的图片，加快检测速度
    //nt cvRound (double value) 对一个double型的数进行四舍五入，并返回一个整型数！
    Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );
    //转成灰度图像，Harr特征基于灰度图
    cvtColor( img, gray, CV_BGR2GRAY );
    //改变图像大小，使用双线性差值
    cv::resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    //变换后的图像进行直方图均值化处理
    equalizeHist( smallImg, smallImg );

    //程序开始和结束插入此函数获取时间，经过计算求得算法执行时间
    t = (double)cvGetTickCount();
    //检测人脸
    //detectMultiScale函数中smallImg表示的是要检测的输入图像为smallImg，faces表示检测到的人脸目标序列，1.1表示
    //每次图像尺寸减小的比例为1.1，2表示每一个目标至少要被检测到3次才算是真的目标(因为周围的像素和不同的窗口大
    //小都可以检测到人脸),CV_HAAR_SCALE_IMAGE表示不是缩放分类器来检测，而是缩放图像，Size(30, 30)为目标的
    //最小最大尺寸
    cascade.detectMultiScale( smallImg, faces,
        1.1, 2, 0
        //|CV_HAAR_FIND_BIGGEST_OBJECT
        //|CV_HAAR_DO_ROUGH_SEARCH
        |CV_HAAR_SCALE_IMAGE
        ,
        Size(30, 30));
    //如果使能，翻转图像继续检测
    if( tryflip )
    {
        flip(smallImg, smallImg, 1);
        cascade.detectMultiScale( smallImg, faces2,
                                 1.1, 2, 0
                                 //|CV_HAAR_FIND_BIGGEST_OBJECT
                                 //|CV_HAAR_DO_ROUGH_SEARCH
                                 |CV_HAAR_SCALE_IMAGE
                                 ,
                                 Size(30, 30) );
        for( vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); r++ )
        {
            faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
        }
    }
    t = (double)cvGetTickCount() - t;
 //   qDebug( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
    for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
    {
        Mat smallImgROI;
        vector<Rect> nestedObjects;
        Point center;
        Scalar color = colors[i%8];
        int radius;

        double aspect_ratio = (double)r->width/r->height;
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
        {
            //标示人脸时在缩小之前的图像上标示，所以这里根据缩放比例换算回去
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );

			Mat initial_img=img.clone();
			Rect rect;
			rect.x=cvRound((r->x+r->width*0.2)*scale);
			rect.y=cvRound((r->y+r->height*0.5)*scale);
			if(faceSizeFuncControl>0&&faceSizeFuncControl<faceSizeCount-1)
			{
				 rect.width=cvRound((r->width + r->height)*0.32*scale);
			     rect.height=cvRound((r->width + r->height)*0.125*scale);

				 sumWidth+=rect.width;
	             sumHight+=rect.height;

				 sumRectx+=rect.x;
				 sumRecty+=rect.y;

				 widthVector.push_back(rect.x);
				 lengthVector.push_back(rect.y);

				 widthToVector.push_back(rect.width);
				 heightVector.push_back(rect.height);
			}
			else if(faceSizeFuncControl>=faceSizeCount-1)
			{
				//rect.x=sumRectx/(faceSizeCount-2);
				//rect.y=sumRecty/(faceSizeCount-2);
				for(int i=0;i<widthVector.size()-1;i++)
				{
					for(int j=i+1;j<widthVector.size();j++)
					{
						if(widthVector[i]>widthVector[j])
						{
							int  temp=widthVector[i];
							widthVector[i]=widthVector[j];
							widthVector[j]=temp;
						}
					}
				}
				
				for(int i=0;i<lengthVector.size()-1;i++)
				{
					for(int j=i+1;j<lengthVector.size();j++)
					{
						if(lengthVector[i]>lengthVector[j])
						{
							int  temp=lengthVector[i];
							lengthVector[i]=lengthVector[j];
							lengthVector[j]=temp;
						}
					}
				}
				for(int i=0;i<widthToVector.size()-1;i++)
				{
					for(int j=i+1;j<widthToVector.size();j++)
					{
						if(widthToVector[i]>widthToVector[j])
						{
							int  temp=widthToVector[i];
							widthToVector[i]=widthToVector[j];
							widthToVector[j]=temp;
						}
					}
				}
				for(int i=0;i<heightVector.size()-1;i++)
				{
					for(int j=i+1;j<heightVector.size();j++)
					{
						if(heightVector[i]>heightVector[j])
						{
							int  temp=heightVector[i];
							heightVector[i]=heightVector[j];
							heightVector[j]=temp;
						}
					}
				}
				rect.x=widthVector[widthVector.size()/2];
				rect.y=lengthVector[lengthVector.size()/2];
				qDebug()<<"rect.x="<<rect.x<<endl;
				qDebug()<<"rect.y="<<rect.y<<endl;
				//rect.width=sumWidth/(faceSizeCount-2);
				//rect.height=sumHight/(faceSizeCount-2);
				rect.width=widthToVector[widthToVector.size()/2];
				rect.height=heightVector[heightVector.size()/2];
			}			
			rectangle( img, Point(rect.x,rect.y),Point(rect.x+rect.width,rect.y+rect.height),Scalar( 0, 255, 255 ), 3, 8 );

			Mat image_roi = initial_img(rect);  
			cv::namedWindow("人脸识别");
			cv::imshow( "人脸识别", img );

			//namedWindow("ROI区域",WINDOW_NORMAL);
			//cv::imshow( "ROI区域", image_roi );

			return image_roi;
        }
        else
          rectangle( img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
                       cvPoint(cvRound((r->x + r->width-1)*scale), cvRound((r->y + r->height-1)*scale)),
                       color, 3, 8, 0);
        smallImgROI = smallImg(*r);


    }

    //cv::imshow( "result", img );
	return img;
}
void MyUi::FindROI()
{
	button1->setDisabled(true);
	button3->setDisabled(true);
	button4->setDisabled(true);
	button5->setDisabled(true);
	roi_list.clear();
	//对序列图像进行人脸识别和追踪
	bool stop = false;
	CascadeClassifier cascade, nestedCascade;
    //训练好的文件名称，放置在可执行文件同目录下
    cascade.load("D:\\opencv3.2\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt2.xml");
    nestedCascade.load("D:\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml");

	QDir dir("./PictureSequence/");
	QFileInfoList list=dir.entryInfoList();

	
	//得到图片ROI
	int i=2;

	faceSizeCount=11;//7
	//固定黄色区域
	char image_name[30];
	int frameCount=0;
	for(;i<faceSizeCount;i++)  
	{
		frameCount++;
		sprintf(image_name, "%s%d%s", "./PictureSequence/", frameCount, ".png");//保存的图片名
		qDebug()<<"image_name="<<image_name<<endl;
		Mat img=imread(image_name,2|4);
		//cv::imshow("img",img);
		detectAndDraw( img, cascade,2,0 );	
		if(waitKey(30) >=0)
             stop = true;
	}
	//得到图片ROI
	for(;i<list.size();i++)  
	{

		frameCount++;
		sprintf(image_name, "%s%d%s", "./PictureSequence/", frameCount, ".png");//保存的图片名
		qDebug()<<"image_name="<<image_name<<endl;
		Mat srcImg=imread(image_name,2|4);
		QString buttonText=QString::number(frameCount);
		buttonText+="张图片";
		button2->setText(buttonText);
		Mat ROI_img=detectAndDraw( srcImg, cascade,2,0 );
		cv::namedWindow("ROI",WINDOW_NORMAL);
		cv::imshow("ROI",ROI_img);
		roi_list.push_back(ROI_img);
	
		if(waitKey(30) >=0)
             stop = true;
	}
	cv::destroyWindow("ROI");
	cv::destroyWindow("人脸识别");
	button2->setText(tr("运行"));

		button1->setDisabled(false);
	button3->setDisabled(false);
	button4->setDisabled(false);
	button5->setDisabled(false);
}

void MyUi::GetThreeChannel()
{


	//将图片ROI分离三个彩色通道，加入对应序列中
	containBlue.clear();
	containRed.clear();
	containGreen.clear();

   //QList<double>  containBlue,containRed,containGreen;
	for(int i=0;i<roi_list.size();i++)
	{
		vector<Mat> channels;
		//ROI图片归一化
		//normalize(roi_list[i],roi_list[i],0,1,CV_MINMAX);
		cv::split(roi_list[i],channels);//分离色彩通道
		namedWindow("蓝色",WINDOW_AUTOSIZE);
		namedWindow("绿色",WINDOW_AUTOSIZE);
		namedWindow("红色",WINDOW_AUTOSIZE);
		cv::imshow( "蓝色", channels[0] );			
		cv::imshow( "绿色", channels[1] );
		cv::imshow( "红色", channels[2] );
		for(int color=0;color<3;color++)
		{
			long int sum=0;
			double average=0.0;
			for(int row=0;row<channels[color].rows;row++)
			{
				for(int col=0;col<channels[color].cols;col++)
				{				
					//qDebug()<<"channels[color].at<uchar>(row,col)="<<channels[color].at<uchar>(row,col)<<endl;
					sum+=channels[color].at<uchar>(row,col);
					//qDebug()<<"sum="<<sum<<endl;
				}
			}
			//qDebug()<<"sum"<<(double)sum<<endl;
			//qDebug()<<"channels[color].rows*channels[color].cols"<<(channels[color].rows*channels[color].cols)<<endl;
			average=((double)sum)/(channels[color].rows*channels[color].cols);
			switch(color)
			{
			    case 0:containBlue.push_back(average);break;
				case 1:containGreen.push_back(average);break;
				case 2:containRed.push_back(average);break;
			}
		}	
	}


	QWidget* allColorWidget=new QWidget;
	QVBoxLayout* main=new QVBoxLayout(allColorWidget);
	QString titleRed=tr("红色通道");
	Drawer* drawerSmallRed=new Drawer(containRed,titleRed);
	QString titleGreen=tr("绿色通道");
	Drawer* drawerSmallGreen=new Drawer(containGreen,titleGreen);
	QString titleBlue=tr("蓝色通道");
	Drawer* drawerSmallBlue=new Drawer(containBlue,titleBlue);
	main->addWidget(drawerSmallRed);
	main->addWidget(drawerSmallGreen);
	main->addWidget(drawerSmallBlue);
	allColorWidget->showMaximized();

	//cv::destroyWindow("蓝色");
	//cv::destroyWindow("绿色");
	//cv::destroyWindow("红色");

}
void MyUi::ICA()
{
	button1->setDisabled(true);
	button3->setDisabled(true);
	button2->setDisabled(true);
	button5->setDisabled(true);
	//构造三列多行数组,这里按照BGR排列,这里的数组设定的是固定值
     double* buf=new double[3*containBlue.size()];
	 int blueCount=0;
	 int greenCount=0;
	 int redCount=0;
	 for(int i=0;i<containBlue.size();i++)
	 {
		 for(int j=0;j<3;j++)
		 {
			 switch(j)
			 {
			    case 0:buf[i*3+j]=containBlue.at(blueCount++);break;
				case 1:buf[i*3+j]=containGreen.at(greenCount++);break;
				case 2:buf[i*3+j]=containRed.at(redCount++);break;
			 }
			 
		 }
	 }
#if 0
	 for(int i=0;i<3;i++)
	 {
		 for(int j=0;j<containBlue.size();j++)
		 {
			 qDebug()<<"buf[i][j]="<<buf[i*containBlue.size()+j]<<endl;
		 }
	 }
#endif

	 
	cv::Mat  ICA_img(framesCount-faceSizeCount, 3, CV_64FC1, (double*)buf);
	qDebug()<<"framesCount="<<framesCount<<endl;
	qDebug()<<"faceSizeCount="<<faceSizeCount<<endl;


		//qDebug()<<"rows="<<ICA_img.rows<<endl;
		//qDebug()<<"clos="<<ICA_img.cols<<endl;
	//cv::Mat ICA_img=(cv::Mat_<double>(framesCount,3)<<131.1323,125.3454,343.5456,454.6456,657.4323,676.4645,671.5464,878.6788,569.5677,100.6576,611.4543,812.1232);

     //最后的S矩阵是我们要求得的矩阵
	 cv::Mat D,E,W,S;
	 //去均值
	 remean(ICA_img,ICA_img);
#if 0
	qDebug()<<"average:"<<endl;
   for(int i=0;i<ICA_img.rows;i++)
  {
	  for(int j=0;j<ICA_img.cols;j++)
	  {
		  qDebug()<<i<<" row "<<j<<" col "<<ICA_img.at<double>(i,j)<<endl;
	  }
  }
#endif
	 //白化
	 whiten(ICA_img,ICA_img,E,D);
#if 0
	 	qDebug()<<"white:"<<endl;
	   for(int i=0;i<ICA_img.rows;i++)
	  {
		  for(int j=0;j<ICA_img.cols;j++)
		  {
			  qDebug()<<i<<" row "<<j<<" col "<<ICA_img.at<double>(i,j)<<endl;
		  }
	  }
 #endif
	 //ICA
	 runICA(ICA_img,S,W,ICA_img.cols);
#if 0
	qDebug()<<"ICA_img.channels()"<<ICA_img.channels()<<endl;

    qDebug()<<"S.channels()"<<S.channels()<<endl;


   qDebug()<<"S:"<<endl;
   qDebug()<<(double)S.at<double>(0,0)<<endl;
#endif
	   for(int i=0;i<S.rows;i++)
	  {
		  for(int j=0;j<S.cols;j++)
		  {
			 // qDebug()<<i<<" row "<<j<<" col "<<(double)S.at<double>(i,j)<<endl;
			  switch(i)
			  {
			      case 0:containOneICA.push_back((double)S.at<double>(i,j));break;
				  case 1:containTwoICA.push_back((double)S.at<double>(i,j));break;
				  case 2:containThreeICA.push_back((double)S.at<double>(i,j));break;
			  }
		  }
	  }

    QWidget* ICAallColorWidget=new QWidget;
	QVBoxLayout* main=new QVBoxLayout(ICAallColorWidget);
	QString titleOne=tr("ICA第一行通道");
	Drawer* drawerSmallOne=new Drawer(containOneICA,titleOne);
	QString titleTwo=tr("ICA第二行通道");
	Drawer* drawerSmallTwo=new Drawer(containTwoICA,titleTwo);
	QString titleThree=tr("ICA第三行通道");
	Drawer* drawerSmallThree=new Drawer(containThreeICA,titleThree);
	main->addWidget(drawerSmallOne);
	main->addWidget(drawerSmallTwo);
	main->addWidget(drawerSmallThree);
	ICAallColorWidget->showMaximized();

	delete[] buf;
	button1->setDisabled(false);
	button3->setDisabled(false);
	button2->setDisabled(false);
	button5->setDisabled(false);

}
void MyUi::bandPass()
{
	button1->setDisabled(true);
	button3->setDisabled(true);
	button2->setDisabled(true);
	button4->setDisabled(true);
	//将每个ICA处理后的信号与绿通道计算相关系数，得到相关系数最大的哪个信号
	double colRelationOne=getColrelationNum(containOneICA,containGreen);
	double colRelationTwo=getColrelationNum(containTwoICA,containGreen);
	double colRelationThree=getColrelationNum(containThreeICA,containGreen);
	double colRelationMax=0.0;
     if(colRelationOne>colRelationMax)
		 colRelationMax=abs(colRelationOne);
	 if(colRelationTwo>colRelationMax)
		 colRelationMax=abs(colRelationTwo);
	 if(colRelationThree>colRelationMax)
		 colRelationMax=abs(colRelationThree);
	 qDebug()<<"colRelationMax="<<colRelationMax<<endl;


	 double interval=(double)myfps/SIZE;
	 //将相关系数最大的那个信号转化为频域通过带通滤波器
	 if(colRelationMax==colRelationOne)
	 {

		    FFRresult=timeToFrequency(containOneICA);
			QString title1=tr("频域图像");		
			Drawer* drawerFFRresult=new Drawer(FFRresult,title1,interval);
			 QWidget* timeToFrequencyWidget=new QWidget;
	        QVBoxLayout* main=new QVBoxLayout(timeToFrequencyWidget);
			QString title=tr("时域图像");
	        Drawer* drawerContainOne=new Drawer(containOneICA,title);
			main->addWidget(drawerContainOne);
			main->addWidget(drawerFFRresult);
			timeToFrequencyWidget->setWindowTitle(tr("时域频域转换"));
			timeToFrequencyWidget->showMaximized();
	 }
	 else if(colRelationMax==colRelationTwo)
	 {
		    FFRresult=timeToFrequency(containTwoICA);
			QString title1=tr("频域图像");
			Drawer* drawerFFRresult=new Drawer(FFRresult,title1,interval);
			 QWidget* timeToFrequencyWidget=new QWidget;
	        QVBoxLayout* main=new QVBoxLayout(timeToFrequencyWidget);
			QString title=tr("时域图像");
	        Drawer* drawerContainOne=new Drawer(containTwoICA,title);
			main->addWidget(drawerContainOne);
			main->addWidget(drawerFFRresult);
			timeToFrequencyWidget->setWindowTitle(tr("时域频域转换"));
			timeToFrequencyWidget->showMaximized();
	 }
	 else if(colRelationMax==colRelationThree)
	 {
		    FFRresult=timeToFrequency(containThreeICA);
			QString title1=tr("频域图像");
			Drawer* drawerFFRresult=new Drawer(FFRresult,title1,interval);
			 QWidget* timeToFrequencyWidget=new QWidget;
	        QVBoxLayout* main=new QVBoxLayout(timeToFrequencyWidget);
			QString title=tr("时域图像");
	        Drawer* drawerContainOne=new Drawer(containThreeICA,title);
			main->addWidget(drawerContainOne);
			main->addWidget(drawerFFRresult);
			timeToFrequencyWidget->setWindowTitle(tr("时域频域转换"));
			timeToFrequencyWidget->showMaximized();
	 }

	 bandPassFilter(FFRresult,0.7,3.0);
	 //得到呼吸频率
     double breath= getBreathe(FFRresult,0.25,0.35);
	 qDebug()<<"呼吸频率="<<breath<<endl;
	 breathe->setText(QString::number(breath));
	button1->setDisabled(false);
	button3->setDisabled(false);
	button2->setDisabled(false);
	button4->setDisabled(false);

}
#if 1
void MyUi::videoToImageButton()
{

	button6->setDisabled(true);
	button7->setDisabled(true);
	button8->setDisabled(true);
	button9->setDisabled(true);
	button22->setDisabled(true);
	button23->setDisabled(true);

		//删除目录下所有照片
	QDir d("./PictureSequence");
	d.setFilter(QDir::Files);
	int fileNum,fileSumNum=d.count()-1;
	for (fileNum=0;fileNum<=fileSumNum;fileNum++)
	    d.remove(d[fileNum]);

	
	char* outDir="./PictureSequence/";

	int maxFrameCount=framesCount;
	char* imgExt=".png";
	qDebug()<<"1hello!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	qDebug()<<"videoName="<<videoName.c_str()<<endl;
	qDebug()<<"2hello!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	 CvCapture* capture = cvCaptureFromAVI(videoName.c_str());


	//获取视频信息
	 cvQueryFrame(capture);
	 myframeH    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
	 myframeW    = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
	 myfps       = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
	 mynumFrames = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);
	 qDebug()<<"3hello!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	qDebug()<<"frameH="<<myframeH<<",frameW="<<myframeW<<",fps="<<myfps<<",numFrames="<<mynumFrames<<endl;
	qDebug()<<"4hello!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	
	//定义和初始化变量
	int i = 0;
	IplImage* img = 0;	
	char image_name[30];
	cvNamedWindow( "视频转化为帧图片" );//, CV_WINDOW_AUTOSIZE
	int frame=0;
	//读取和显示
	while((img = cvQueryFrame(capture))!=NULL)	//获取一帧图片
	{
		frame++;
		qDebug()<<"frame="<<frame<<endl;
		QString frameShow=tr("帧照片数目=");
		frameShow+=QString::number(frame);
		button21->setText(frameShow);
		cvShowImage( "视频转化为帧图片", img ); //将其显示
		char key = cvWaitKey(20);
		sprintf(image_name, "%s%d%s", "./PictureSequence/", frame, ".png");//保存的图片名
		cvSaveImage( image_name, img);   //保存一帧图片
		if(frame == maxFrameCount) break;
	}
		cvReleaseCapture(&capture);
		cvDestroyWindow("视频转化为帧图片");
		button21->setText(tr("运行"));

		button6->setDisabled(false);
		button7->setDisabled(false);
		button8->setDisabled(false);
		button9->setDisabled(false);
		button22->setDisabled(false);
		button23->setDisabled(false);
}
void MyUi::FindROIButton()
{
	button6->setDisabled(true);
	button7->setDisabled(true);
	button8->setDisabled(true);
	button9->setDisabled(true);
	button21->setDisabled(true);
	button23->setDisabled(true);
   	roi_list.clear();
	//对序列图像进行人脸识别和追踪
	bool stop = false;
	CascadeClassifier cascade, nestedCascade;
    //训练好的文件名称，放置在可执行文件同目录下
    cascade.load("D:\\opencv3.2\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt2.xml");
    nestedCascade.load("D:\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml");

	QDir dir("./PictureSequence/");
	QFileInfoList list=dir.entryInfoList();

	
	//得到图片ROI
	int i=2;

	faceSizeCount=11;//7
	//固定黄色区域
	char image_name[30];
	int frameCount=0;
	for(;i<faceSizeCount;i++)  
	{
		frameCount++;
		sprintf(image_name, "%s%d%s", "./PictureSequence/", frameCount, ".png");//保存的图片名
		qDebug()<<"image_name="<<image_name<<endl;
		Mat img=imread(image_name,2|4);
		//cv::imshow("img",img);
		detectAndDraw( img, cascade,2,0 );	
		if(waitKey(30) >=0)
             stop = true;
	}
	//得到图片ROI
	for(;i<list.size();i++)  
	{

		frameCount++;
		sprintf(image_name, "%s%d%s", "./PictureSequence/", frameCount, ".png");//保存的图片名
		qDebug()<<"image_name="<<image_name<<endl;
		Mat srcImg=imread(image_name,2|4);
		QString buttonText=QString::number(frameCount);
		buttonText+="张图片";
		button22->setText(buttonText);
		Mat ROI_img=detectAndDraw( srcImg, cascade,2,0 );
		cv::namedWindow("ROI",WINDOW_NORMAL);
		cv::imshow("ROI",ROI_img);
		roi_list.push_back(ROI_img);
	
		if(waitKey(30) >=0)
             stop = true;
	}
	cv::destroyWindow("ROI");
	cv::destroyWindow("人脸识别");
	button22->setText(tr("运行"));

	button6->setDisabled(false);
	button7->setDisabled(false);
	button8->setDisabled(false);
	button9->setDisabled(false);
	button21->setDisabled(false);
	button23->setDisabled(false);
}
#endif
QList<double>  MyUi::smoothFilter(QList<double> list)
{
	QList<double> averageFive;
	for(int i=0;i<list.size()-4;i++)
	{
		double average=(list.at(i)+list.at(i+1)+list.at(i+2)+list.at(i+3)+list.at(i+4))/5;
		averageFive.push_back(average);
	}

	return averageFive;
}
QList<double> MyUi::getMaxArray(QList<double> list)
{
	QList<double> result;
	int getBigger=0;
	for(int i=0,j=i+1;j<list.size();i++,j++)
	{
		if(list.at(i)<=list.at(j))
			getBigger++;
		else if(list.at(i)>list.at(j))
		{
			if(getBigger>0)
			{
				result.push_back(list.at(i));
				getBigger=0;
			}
			getBigger=0;
		}
	}
	return result;
}

double MyUi::getAverage(QList<double> list)
{
	double sum=0.0;
	for(int i=0;i<list.size();i++)
		sum+=list.at(i);
	double average=sum/list.size();
	return average;
}
void MyUi::smooth()
{
	 containBlueLater=smoothFilter(containBlue);
	 containRedLater=smoothFilter(containRed);
	 QWidget* smoothWidget=new QWidget;
	QVBoxLayout* main=new QVBoxLayout(smoothWidget);
	QString titleOne=tr("蓝色通道平滑滤波");
	Drawer* drawerSmallOne=new Drawer(containBlueLater,titleOne);
	QString titleTwo=tr("红色通道平滑滤波");
	Drawer* drawerSmallTwo=new Drawer(containRedLater,titleTwo);
	main->addWidget(drawerSmallOne);
	main->addWidget(drawerSmallTwo);
	smoothWidget->setWindowTitle(tr("平滑滤波图像"));
	smoothWidget->showMaximized();
}
void MyUi::getServalMax()
{
	  IdcRed=getAverage(containRedLater);
	 IdcBlue=getAverage(containBlueLater);

	 QList<double> blueMaxArray=getMaxArray(containBlueLater);
	 QList<double> redMaxArray=getMaxArray(containRedLater);
	 blueMaxArrayAverage=getAverage(blueMaxArray);
	 redMaxArrayAverage=getAverage(redMaxArray);

	QWidget* ServalMaxWidget=new QWidget;
	QVBoxLayout* main=new QVBoxLayout(ServalMaxWidget);
	QString titleOne=tr("蓝色通道极值点序列");
	Drawer* drawerSmallOne=new Drawer(blueMaxArray,titleOne);
	QString titleTwo=tr("红色通道极值点序列");
	Drawer* drawerSmallTwo=new Drawer(redMaxArray,titleTwo);
	main->addWidget(drawerSmallOne);
	main->addWidget(drawerSmallTwo);
	ServalMaxWidget->setWindowTitle(tr("极值点序列图像"));
	ServalMaxWidget->showMaximized();

	 

	
}
void MyUi::getR()
{
	R=(redMaxArrayAverage/IdcRed)/(blueMaxArrayAverage/IdcBlue);
	
	
		QWidget* RShow=new QWidget;
		RShow->setWindowTitle(tr("R值"));
		QHBoxLayout* main=new QHBoxLayout(RShow);
		QLabel* mainlabel=new QLabel;
		QString rshowText="R值为";
		rshowText+=QString::number(R);
		mainlabel->setText(rshowText);
		mainlabel->setTextFormat(Qt::RichText);
		//mainlabel->resize(RShow->width(),RShow->height());
		main->addStretch();
		main->addWidget(mainlabel);
		main->addStretch();
		RShow->resize(500,200);
		RShow->setWindowIcon(QIcon("./Resources/background.jpg"));
		RShow->show();
}
void MyUi::getBloodResult()
{
	 double result=97.61+0.42*R;
	 bloodResult->setText(QString::number(result));
	 qDebug()<<"血糖饱和度为："<<result<<endl;
}
MyUi::~MyUi()
{

}
