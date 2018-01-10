#include "SuggestionFeedback.h"
#include <qmessagebox.h>
#include <qdir.h>
#include <qdatetime.h>
#include <QTextStream>
#include <qdebug.h>

SuggestionFeedback::SuggestionFeedback(QWidget *parent)
	: QWidget(parent)
{
	this->setWindowTitle(tr("意见反馈"));
	this->setWindowIcon(QIcon("./Resources/feedback.png"));
	QVBoxLayout* main=new QVBoxLayout();
	QHBoxLayout* top=new QHBoxLayout();
	QLabel* label=new QLabel(tr("<h3>意见反馈:</h3>"));
	textEidt=new QTextEdit;
	top->addWidget(label);
	top->addWidget(textEidt);
	main->addLayout(top);
	QHBoxLayout* bottom=new QHBoxLayout();
	QPushButton* submit=new QPushButton(tr("提交"));
	bottom->addStretch();
	bottom->addWidget(submit);
	main->addLayout(bottom);
	QGridLayout* grid=new QGridLayout;
	grid->addLayout(main,1,1);
	grid->setColumnStretch(0,1);
	grid->setColumnStretch(1,10);
	grid->setColumnStretch(2,1);
	grid->setRowStretch(0,1);
	grid->setRowStretch(1,10);
	grid->setRowStretch(2,1);
	this->setLayout(grid);
	this->setGeometry(600,100,600,400);
	connect(submit,SIGNAL(clicked()),this,SLOT(onButtonClicked()));
}
void SuggestionFeedback::onButtonClicked()
{
	QMessageBox::information(this,tr("提示"),tr("意见反馈成功！已经成功传到后台！"));
	//在当前目录下搜索是否有suggestionFeedback文件夹，没有就创建，并将用户信息文档放入其中
	QDir dir("../");
	QFileInfoList list=dir.entryInfoList();
	QString currentPath=dir.absolutePath();

	int i=0;
	for(;i<list.size();i++)  
	{
		QFileInfo fileInfo=list.at(i);
		if(fileInfo.fileName()=="suggestionFeedback")
		{
			QString targetPath=currentPath+"/suggestionFeedback";
			QDateTime currentTime;
			QString saveName=targetPath+"/"+tr("意见反馈")+currentTime.currentDateTime().toString("yyyy-MM-dd-hh时mm分ss秒")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr("反馈意见：")<<endl<<endl<<endl<<endl;
				out<<tr(textEidt->text())<<endl;
			}
			  //关闭文件，避免发生错误
			myfile.close();
			break;
		}
	}
	if(i==list.size())
	{		
			QString targetPath=currentPath+"/suggestionFeedback";
			qDebug()<<"targetPath="<<targetPath<<endl;
			dir.mkdir(targetPath);
			QDateTime currentTime;		
			QString saveName=targetPath+"/"+tr("意见反馈")+currentTime.currentDateTime().toString("yyyy-MM-dd-hh时mm分ss秒")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr("反馈意见：")<<endl<<endl<<endl<<endl;
				out<<tr(textEidt->text())<<endl;	
			}
			  //关闭文件，避免发生错误
			myfile.close();

	}

}
SuggestionFeedback::~SuggestionFeedback()
{

}
