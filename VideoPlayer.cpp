#include "VideoPlayer.h"

#include <QMenu>
#include <QAction>
#include <qDebug>
#include <QVBoxLayout>
#include <QToolBar>
#include <seekslider.h>
#include <phonon\videowidget.h>
#include <phonon\mediaobject.h>
#include <phonon\audiodataoutput.h>
#include <Phonon>
#include <QMessageBox>
#include <qdir.h>
#include <qprocess.h>
#include <QDateTime>
#include <QDesktopServices>
#include <QUrl>
#include <qpushbutton.h>
#include <QFileDialog>
#include <qstyle.h>
#include <qslider.h>

VideoPlayer::VideoPlayer(QWidget *parent)
	: QWidget(parent)
{
	this->setWindowTitle(tr("IPPG Player"));
	this->setWindowIcon(QIcon("./Resources/playvideo.png"));
	//this->resize(800,600);
	//setupUi(this);
	QLabel* label_2=new QLabel(tr("饱和度"));
	QLabel* label_3=new QLabel(tr("亮度"));
    QLabel* label_4=new QLabel(tr("色调"));
	QLabel* label_5=new QLabel(tr("对比度"));
	QSlider* horizontalSliderLight=new QSlider(Qt::Horizontal);
	QSlider* horizontalSliderTinge=new QSlider(Qt::Horizontal);
	QSlider* horizontalSliderSaturation=new QSlider(Qt::Horizontal);
	QSlider* horizontalSliderContract=new QSlider(Qt::Horizontal);

	//创建媒体图
    mediaObject=new Phonon::MediaObject(this);
	videoWidget=new Phonon::VideoWidget(this);
	createPath(mediaObject,videoWidget);
	Phonon::AudioOutput* audioOutput=new Phonon::AudioOutput(Phonon::VideoCategory,this);
	createPath(mediaObject,audioOutput);
	//mediaObject->setCurrentSource(Phonon::MediaSource("./Resources/myVideo.WMV"));
    //创建播放进度滑块
	Phonon::SeekSlider* seekSlider=new Phonon::SeekSlider(mediaObject,this);

	//创建工具栏，包含播放暂停和停止以及控制音量滑块
	QToolBar* toolBar=new QToolBar(this);
	QAction* playAction=new QAction(style()->standardIcon(QStyle::SP_MediaPlay),tr("播放"),this);
	connect(playAction, SIGNAL(triggered()), mediaObject, SLOT(play()));
	QAction *pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("暂停"), this);
    connect(pauseAction, SIGNAL(triggered()), mediaObject, SLOT(pause()));
    QAction *stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("停止"), this);
    connect(stopAction, SIGNAL(triggered()), mediaObject, SLOT(stop()));
	QAction *screenShot=new QAction(QIcon("./Resources/screenshot.png"),tr("截屏"),this);
	connect(screenShot, SIGNAL(triggered()), this, SLOT(onScreenShot()));

	Phonon::VolumeSlider*  volumeSlider=new Phonon::VolumeSlider(audioOutput,this);
	volumeSlider->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

	QPushButton* openFileButton=new QPushButton(tr("打开文件"));
	connect(openFileButton,SIGNAL(clicked()),this,SLOT(onOpenFileButtonClicked()));

    toolBar->addAction(playAction);
    toolBar->addAction(pauseAction);
    toolBar->addAction(stopAction);
	toolBar->addAction(screenShot);
    toolBar->addWidget(volumeSlider);
	toolBar->addWidget(openFileButton);
	

	// 创建布局管理器，将各个部件都添加到布局管理器中
	QVBoxLayout* mainLayout=new QVBoxLayout;
	QGridLayout* gridLayout=new QGridLayout;
	gridLayout->addWidget(label_3,0,0);
	gridLayout->addWidget(horizontalSliderLight,0,1);
	gridLayout->addWidget(label_4,0,2);
	gridLayout->addWidget(horizontalSliderTinge,0,3);
	gridLayout->addWidget(label_2,1,0);
	gridLayout->addWidget(horizontalSliderSaturation,1,1);
	gridLayout->addWidget(label_5,1,2);
	gridLayout->addWidget(horizontalSliderContract,1,3);

	videoWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	mainLayout->addWidget(videoWidget);
    mainLayout->addWidget(seekSlider);
    mainLayout->addWidget(toolBar);
    mainLayout->addLayout(gridLayout);
    setLayout(mainLayout);

	// 设置Widget和VideoWidget都使用自定义上下文菜单
	setContextMenuPolicy(Qt::CustomContextMenu);
	videoWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(videoWidget, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showContextMenu(const QPoint &)));
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showContextMenu(const QPoint &)));
    // 创建上下文菜单
    createContextMenu();

	QObject::connect(horizontalSliderLight,SIGNAL(valueChanged(int)),this,SLOT(onHorizontalSliderLightValueChanged(int)));
	QObject::connect(horizontalSliderSaturation,SIGNAL(valueChanged(int )),
		            this,SLOT(onHorizontalSliderSaturationValueChanged(int )));
	QObject::connect(horizontalSliderTinge,SIGNAL(valueChanged(int )),
		        this,SLOT(onHorizontalSliderTingeValueChanged(int )));
	QObject::connect(horizontalSliderContract,SIGNAL(valueChanged(int )),
		    this,SLOT(onHorizontalSliderContractValueChanged(int )));

}
/*
* alter lighting
*/
void VideoPlayer::onHorizontalSliderLightValueChanged(int value)
{
	videoWidget->setBrightness(value/10.0);
}
//饱和度
void VideoPlayer::onHorizontalSliderSaturationValueChanged(int value)
{
	videoWidget->setSaturation(value/10.0);
}
//色调
void VideoPlayer::onHorizontalSliderTingeValueChanged(int value)
{
	videoWidget->setHue(value/10.0);
}
//对比度
void VideoPlayer::onHorizontalSliderContractValueChanged(int value)
{
	videoWidget->setContrast(value/10.0);
}
void VideoPlayer::createContextMenu()
{
	mainMenu=new QMenu(this);
	// 创建“宽高比”子菜单
	QMenu* aspectMenu=mainMenu->addMenu(tr("宽高比"));
	QActionGroup* aspectGroup=new QActionGroup(aspectMenu);
	connect(aspectGroup,SIGNAL(triggered(QAction*)),this,SLOT(aspectChanged(QAction*)));
	aspectGroup->setExclusive(true);

	QAction *aspectActionAuto = aspectMenu->addAction(tr("自动"));
    aspectActionAuto->setCheckable(true);
    aspectActionAuto->setChecked(true);
    aspectGroup->addAction(aspectActionAuto);
    QAction *aspectActionScale = aspectMenu->addAction(tr("缩放"));
    aspectActionScale->setCheckable(true);
    aspectGroup->addAction(aspectActionScale);
    QAction *aspectAction16_9 = aspectMenu->addAction(tr("16:9"));
    aspectAction16_9->setCheckable(true);
    aspectGroup->addAction(aspectAction16_9);
    QAction *aspectAction4_3 = aspectMenu->addAction(tr("4:3"));
    aspectAction4_3->setCheckable(true);
    aspectGroup->addAction(aspectAction4_3);
	 // 创建“缩放模式”子菜单
	QMenu *scaleMenu = mainMenu->addMenu(tr("缩放模式"));
    QActionGroup *scaleGroup = new QActionGroup(scaleMenu);
    connect(scaleGroup, SIGNAL(triggered(QAction*)), this, SLOT(scaleChanged(QAction*)));
    scaleGroup->setExclusive(true);
    QAction *scaleActionFit = scaleMenu->addAction(tr("保持宽高比"));
    scaleActionFit->setCheckable(true);
    scaleActionFit->setChecked(true);
    scaleGroup->addAction(scaleActionFit);
    QAction *scaleActionCrop = scaleMenu->addAction(tr("缩放和裁剪"));
    scaleActionCrop->setCheckable(true);
    scaleGroup->addAction(scaleActionCrop);
	 // 创建“全屏”动作
    QAction *fullScreenAction = mainMenu->addAction(tr("全屏"));
    fullScreenAction->setCheckable(true);
    connect(fullScreenAction, SIGNAL(toggled(bool)), videoWidget, SLOT(setFullScreen(bool)));

}
// 显示上下文菜单
void VideoPlayer::showContextMenu(const QPoint &pos)
{
	 mainMenu->popup(videoWidget->isFullScreen() ? pos : mapToGlobal(pos));
}
// 设置宽高比
void VideoPlayer::aspectChanged(QAction* action)
{
	 if (action->text() == tr("16:9"))
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatio16_9);
    else if (action->text() == tr("缩放"))
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatioWidget);
    else if (action->text() == tr("4:3"))
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatio4_3);
    else
        videoWidget->setAspectRatio(Phonon::VideoWidget::AspectRatioAuto);
}
// 设置缩放模式
void VideoPlayer::scaleChanged(QAction* action)
{
	if (action->text() == tr("缩放和裁剪"))
        videoWidget->setScaleMode(Phonon::VideoWidget::ScaleAndCrop);
    else
        videoWidget->setScaleMode(Phonon::VideoWidget::FitInView);
}
//截屏操作
void VideoPlayer::onScreenShot()
{
	QMessageBox  screenShotDialog;
	screenShotDialog.setWindowIcon(QIcon("./Resources/screenShotDialog.png"));
	screenShotDialog.setWindowTitle("提示");
	screenShotDialog.setText(tr("恭喜截屏成功！"));
	screenShotDialog.exec();

	//在当前目录下搜索是否有videoScreenShot文件夹，没有就创建，并将截图放入其中

	QPixmap image;
	image=image.grabWidget(this,0,0,this->width(),this->height()*0.7);
	QDir dir("../");
	QFileInfoList list=dir.entryInfoList();
	QString currentPath=dir.absolutePath();
	qDebug()<<"currentPath="<<currentPath<<endl;
	int i=0;
	for(;i<list.size();i++)
	{
		QFileInfo fileInfo=list.at(i);
		qDebug()<<"fileInfo"<<i<<"="<<fileInfo.fileName()<<endl;
		if(fileInfo.fileName()=="videoScreenShot")
		{
			qDebug()<<"hello workd"<<endl;
			QString targetPath=currentPath+"/videoScreenShot";
			//if(!QDesktopServices::openUrl(QUrl(targetPath, QUrl::TolerantMode)))
			//	qDebug()<<"file open false"<<endl;
			QDateTime currentTime;		
			QString saveName=targetPath+"/"+currentTime.currentDateTime().toString("yyyy-MM-dd-hh时mm分ss秒")+".png";
			qDebug()<<"saveName="<<saveName<<endl;
			qDebug()<<image.save(saveName);
			break;
		}
	}
	if(i==list.size())
	{		
			QString targetPath=currentPath+"/videoScreenShot";
			qDebug()<<"targetPath="<<targetPath<<endl;
			dir.mkdir(targetPath);
			//if(!QDesktopServices::openUrl(QUrl(targetPath, QUrl::TolerantMode)))
			//	qDebug()<<"file open false"<<endl;
			QDateTime currentTime;		
			QString saveName=targetPath+"/"+currentTime.currentDateTime().toString("yyyy-MM-dd-hh时mm分ss秒")+".png";
			image.save(saveName);
	}
}

void VideoPlayer::onOpenFileButtonClicked()
{
	QFileDialog* fileDialog=new QFileDialog(this);
	fileDialog->setWindowIcon(QIcon("./Resources/openfile.png"));
	
	fileDialog->setWindowTitle(tr("打开视频文件"));
	//fileDialog->setDir(QDir("E:/yanjiushengdainzishejidasai/huawei"));
	fileDialog->setFilter(tr("(*.wmv *.avi *.mp4)"));
	if(fileDialog->exec()==QDialog::Accepted)
	{
		QString path=fileDialog->selectedFiles()[0];
		mediaObject->setCurrentSource(Phonon::MediaSource(path));
		mediaObject->play();
	}
}

void VideoPlayer::closeEvent(QCloseEvent* ev)
{
	mediaObject->stop();
	this->close();
}

VideoPlayer::~VideoPlayer()
{
	
}
