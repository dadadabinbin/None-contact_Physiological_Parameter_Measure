
#include "TextReport.h"
#include <QIcon>
#include <qdebug.h>
#include <qdir.h>
#include "qfile.h"
#include "qfileinfo.h"
#include <qdatetime.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <qformlayout.h>

TestReport::TestReport(QWidget *parent)
	: QWidget(parent)
{


	this->setWindowIcon(QIcon("./Resources/report.png"));
	this->setWindowTitle(tr("用户身体检查报告"));
	this->resize(400,500);

	pushButton=new QPushButton(tr("同步到文档"));
	LineEdit=new QLineEdit;
	LineEdit_2=new QLineEdit;
	LineEdit_3=new QLineEdit;
	LineEdit_4=new QLineEdit;
	LineEdit_5=new QLineEdit;
	QVBoxLayout* main=new QVBoxLayout;
	QHBoxLayout* top=new QHBoxLayout;
	top->addStretch();
	QLabel* title=new QLabel(tr("<h1>用户身体检查报告</h1>"));
	top->addWidget(title);
	top->addStretch();
	main->addLayout(top);
	QFormLayout* form=new QFormLayout;
	QLabel* name=new QLabel(tr("姓名："));
	QLabel* age=new QLabel(tr("年龄："));
	QLabel* arg1=new QLabel(tr("心率："));
	QLabel* arg2=new QLabel(tr("呼吸频率："));
	QLabel* result=new QLabel(tr("血氧饱和度："));
	form->addRow(name,LineEdit);
	form->addRow(age,LineEdit_2);
	form->addRow(arg1,LineEdit_3);
	form->addRow(arg2,LineEdit_4);
	form->addRow(result,LineEdit_5);
	form->setContentsMargins(40,10,40,20);
	form->setHorizontalSpacing(40);
	main->addLayout(form);
	QHBoxLayout* middle=new QHBoxLayout;
	QVBoxLayout* left=new QVBoxLayout;
	QLabel* suggest=new QLabel(tr("       医生建议："));
	left->addWidget(suggest);
	left->addStretch();
	middle->addLayout(left);
	lineEditSugestion=new QTextEdit;
	lineEditSugestion->setMaximumHeight(200);
	middle->addWidget(lineEditSugestion);
	QVBoxLayout* right=new QVBoxLayout;
	right->addStretch();
	right->addWidget(pushButton);
	middle->addLayout(right);
	main->addLayout(middle);
	QHBoxLayout* bottom=new QHBoxLayout;
	bottom->addStretch();
	QLabel* tip=new QLabel(tr("武汉大学物理学院出具  -珞珈山"));
	bottom->addWidget(tip);
	bottom->addStretch();
	main->addLayout(bottom);

	this->setLayout(main);
	connect(pushButton,SIGNAL(clicked()),this,SLOT(onPushButtonClicked()));
	
}
void TestReport::onPushButtonClicked()
{
	QMessageBox::information(this,tr("提示"),tr("同步文档成功！"));
	//在当前目录下搜索是否有testReport文件夹，没有就创建，并将用户信息文档放入其中
	QDir dir("../");
	QFileInfoList list=dir.entryInfoList();
	QString currentPath=dir.absolutePath();
	qDebug()<<"currentPath="<<currentPath<<endl;

	QString temp;

	if(LineEdit->text()=="")
	{
		 temp="未知用户";

	}
	else
	{
		temp=LineEdit->text();
	}


	int i=0;
	for(;i<list.size();i++)  
	{
		QFileInfo fileInfo=list.at(i);
		qDebug()<<"fileInfo"<<i<<"="<<fileInfo.fileName()<<endl;
		if(fileInfo.fileName()=="testReport")
		{
			QString targetPath=currentPath+"/testReport";
			QDateTime currentTime;
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hh时mm分ss秒")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr("                                  用户身体检查报告")<<endl<<endl<<endl<<endl;
				out<<tr("姓名：")<<tr(temp)<<endl<<endl;
				out<<tr("年龄：")<<tr(LineEdit_2->text())<<endl<<endl;
				out<<tr("心率：")<<tr(LineEdit_3->text())<<endl<<endl;
				out<<tr("呼吸频率：")<<tr(LineEdit_4->text())<<endl<<endl;
				out<<tr("血氧饱和度：")<<tr(LineEdit_5->text())<<endl<<endl;
				out<<tr("医生建议：")<<tr(lineEditSugestion->text())<<endl<<endl;
		
			}
			  //关闭文件，避免发生错误
			myfile.close();
			break;
		}
	}
	if(i==list.size())
	{		
			QString targetPath=currentPath+"/testReport";
			qDebug()<<"targetPath="<<targetPath<<endl;
			dir.mkdir(targetPath);
			QDateTime currentTime;		
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hh时mm分ss秒")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr("                                     用户身体检查报告")<<endl<<endl<<endl<<endl;
				out<<tr("姓名：")<<tr(temp)<<endl<<endl;
				out<<tr("年龄：")<<tr(LineEdit_2->text())<<endl<<endl;
				out<<tr("心率：")<<tr(LineEdit_3->text())<<endl<<endl;
				out<<tr("呼吸频率：")<<tr(LineEdit_4->text())<<endl<<endl;
				out<<tr("血氧饱和度：")<<tr(LineEdit_5->text())<<endl<<endl;
				out<<tr("医生建议：")<<tr(lineEditSugestion->text())<<endl<<endl;
			}
			  //关闭文件，避免发生错误
			myfile.close();

	}

}

TestReport::~TestReport()
{

}
