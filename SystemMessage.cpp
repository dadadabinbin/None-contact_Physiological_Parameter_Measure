#include "SystemMessage.h"
#include <qgridlayout.h>
#include <qmessagebox.h>

SystemMessage::SystemMessage(QWidget *parent)
	: QWidget(parent)
{
       this->setWindowTitle(tr("系统信息"));
	   this->resize(600,400);
	   this->setWindowIcon(QIcon("./Resources/systemInformation.png"));
	   QListWidget* list=new QListWidget;
	   QListWidgetItem* listitem0= new QListWidgetItem(tr("系统名称                                   IPPG非接触式生理参数测量系统"));
	   QListWidgetItem* listitem1= new QListWidgetItem(tr("系统版本号                                 V.2.1"));
	   QListWidgetItem* listitem2= new QListWidgetItem(tr("归属单位                                   武汉大学物理科学与技术学院"));
	   QListWidgetItem* listitem3= new QListWidgetItem(tr("系统功能                                   对人脸拍摄一段时频"));
	   QListWidgetItem* listitem4= new QListWidgetItem(tr("                                               通过对视频分析得到人体的一些生理参数"));
	   QListWidgetItem* listitem5= new QListWidgetItem(tr("                                               比如血氧饱和度，心率，呼吸频率等"));
	  // QListWidgetItem* listitem6= new QListWidgetItem(tr("											  3 跟着做"));
	   list->addItem(listitem0);
	   list->addItem(listitem1);
	   list->addItem(listitem2);
	   list->addItem(listitem3);
	   list->addItem(listitem4);
	   list->addItem(listitem5);
	  // list->addItem(listitem6);
        QGridLayout* grid=new QGridLayout;
		QHBoxLayout* hBox=new QHBoxLayout;
		QPushButton* buttonleft=new QPushButton(tr("检查更新"));
		QPushButton* buttonRight=new QPushButton(tr("意见反馈"));
		hBox->addStretch();
		hBox->addWidget(buttonleft);		
		hBox->addWidget(buttonRight);
		grid->addLayout(hBox,2,1);
	    grid->addWidget(list,1,1);
		grid->setColumnStretch(0,1);
		grid->setColumnStretch(1,10);
		grid->setColumnStretch(2,1);
		grid->setRowStretch(0,1);
		grid->setRowStretch(1,10);
		grid->setRowStretch(2,1);
		grid->setRowStretch(3,1);
		this->setLayout(grid);
		connect(buttonleft,SIGNAL(clicked()),this,SLOT(onButtonLeftClicked()));
		connect(buttonRight,SIGNAL(clicked()),this,SLOT(onButtonRightClicked()));

}
//检查更新
void SystemMessage::onButtonLeftClicked()
{
	QMessageBox::information(this,tr("版本检查"),tr("您的版本已经是最新版本!"));
}
void SystemMessage::onButtonRightClicked()
{
	SuggestionFeedback* feedback=new SuggestionFeedback();
	feedback->show();
}

SystemMessage::~SystemMessage()
{

}
