
#include "TextLog.h"
#include <QIcon>
#include <qdebug.h>
#include <qdir.h>
#include "qfile.h"
#include "qfileinfo.h"
#include <qdatetime.h>
#include <qtextstream.h>
#include <qmessagebox.h>
#include <Qdate>



TestLog::TestLog(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	this->setWindowIcon(QIcon("./Resources/testlog.ico"));
	this->setWindowTitle(tr("用户检查日志"));
	this->resize(800,500);

	pushButton=new QPushButton(tr("确定（同步数据）"));
	QLabel* label1=new QLabel(tr("姓名"));
	QLabel* label2=new QLabel(tr("性别"));
	QLabel* label3=new QLabel(tr("科室"));
	QLabel* label4=new QLabel(tr("就诊时间"));
	QLabel* label5=new QLabel(tr("病史"));
	QLabel* label6=new QLabel(tr("婚姻史"));
	QLabel* label7=new QLabel(tr("遗传病"));
	QLabel* label8=new QLabel(tr("家族史"));
	QLabel* label9=new QLabel(tr("心率"));
	QLabel* label10=new QLabel(tr("呼吸频率"));
	QLabel* label11=new QLabel(tr("血氧饱和度"));
	QLabel* label15=new QLabel(tr("初步诊断"));
	LineEdit=new QLineEdit;
	LineEdit_2=new QLineEdit;
	LineEdit_3=new QLineEdit;
	LineEdit_4=new QLineEdit;
	LineEdit_5=new QLineEdit;
	LineEdit_6=new QLineEdit;
	LineEdit_7=new QLineEdit;
	LineEdit_8=new QLineEdit;
	LineEdit_9=new QLineEdit;
	LineEdit_10=new QLineEdit;
	LineEdit_11=new QLineEdit;
	LineEdit_12=new QLineEdit;
	LineEdit_13=new QLineEdit;
	DateEdit=new QDateTimeEdit;
	DateEdit->setDate(QDate::currentDate());
	ComboBox=new QComboBox;
	ComboBox->addItem(tr("男"));
	ComboBox->addItem(tr("女"));
	ComboBox->setCurrentItem(0);

	QHBoxLayout* main=new QHBoxLayout;
	QGroupBox* left=new QGroupBox;
	left->setTitle(tr("用户信息"));
	QFormLayout* leftForm=new QFormLayout;
	leftForm->addRow(label1,LineEdit);
	leftForm->addRow(label2,ComboBox);
	leftForm->addRow(label3,LineEdit_2);
	leftForm->addRow(label4,DateEdit);
	leftForm->addRow(label5,LineEdit_3);
	leftForm->addRow(label6,LineEdit_4);
	leftForm->addRow(label7,LineEdit_5);
	leftForm->addRow(label8,LineEdit_6);
	leftForm->setContentsMargins(30,30,30,30);
	leftForm->setHorizontalSpacing(30);
	leftForm->setVerticalSpacing(30);
	left->setLayout(leftForm);
	main->addWidget(left);

	QGroupBox* right=new QGroupBox;
	QFormLayout* rightForm=new QFormLayout;
	rightForm->addRow(label9,LineEdit_7);
	rightForm->addRow(label10,LineEdit_8);
	rightForm->addRow(label11,LineEdit_9);
	rightForm->addRow(label15,LineEdit_13);
	rightForm->setContentsMargins(30,40,30,40);
	rightForm->setHorizontalSpacing(30);
	rightForm->setVerticalSpacing(30);
	right->setLayout(rightForm);
	main->addWidget(right);

	QVBoxLayout* hLay=new QVBoxLayout;
	hLay->addStretch(8);
	hLay->addWidget(pushButton);
	pushButton->resize(20,15);
	hLay->addStretch(1);
	main->addLayout(hLay);

	this->setLayout(main);
	connect(pushButton,SIGNAL(clicked()),this,SLOT(onPushButtonClicked()));
}
//同步文件
void TestLog::onPushButtonClicked()
{
	QMessageBox::information(this,tr("提示"),tr("同步文档成功！"));
	//在当前目录下搜索是否有testlog文件夹，没有就创建，并将用户信息文档放入其中
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
		if(fileInfo.fileName()=="testlog")
		{
			QString targetPath=currentPath+"/testlog";
			QDateTime currentTime;
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hh时mm分ss秒")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr(temp)<<tr("用户个人检查信息：")<<endl<<endl<<endl<<endl;
				out<<tr("科室：")<<tr(LineEdit_2->text())<<endl;
				out<<tr("用户姓名：")<<tr(temp)<<endl;
				out<<tr("用户性别：")<<tr(ComboBox->currentText())<<endl;
				out<<tr("就诊时间：")<<tr(DateEdit->text())<<endl;
				out<<tr("病史：")<<tr(LineEdit_3->text())<<endl;
				out<<tr("婚姻史：")<<tr(LineEdit_4->text())<<endl;
				out<<tr("遗传病：")<<tr(LineEdit_5->text())<<endl;
				out<<tr("家族史：")<<tr(LineEdit_6->text())<<endl;
				out<<tr("心率：")<<tr(LineEdit_7->text())<<endl;
				out<<tr("呼吸频率：")<<tr(LineEdit_8->text())<<endl;
				out<<tr("血氧饱和度：")<<tr(LineEdit_9->text())<<endl;
				out<<tr("初步诊断：")<<tr(LineEdit_13->text())<<endl;
		
			}
			  //关闭文件，避免发生错误
			myfile.close();
			break;
		}
	}
	if(i==list.size())
	{		
			QString targetPath=currentPath+"/testlog";
			qDebug()<<"targetPath="<<targetPath<<endl;
			dir.mkdir(targetPath);
			QDateTime currentTime;		
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hh时mm分ss秒")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);			
				out<<tr(temp)<<tr("用户个人检查信息：")<<endl<<endl<<endl<<endl;
				out<<tr("科室：")<<tr(LineEdit_2->text())<<endl;
				out<<tr("用户姓名：")<<tr(temp)<<endl;
				out<<tr("用户性别：")<<tr(ComboBox->currentText())<<endl;
				out<<tr("就诊时间：")<<tr(DateEdit->text())<<endl;
				out<<tr("病史：")<<tr(LineEdit_3->text())<<endl;
				out<<tr("婚姻史：")<<tr(LineEdit_4->text())<<endl;
				out<<tr("遗传病：")<<tr(LineEdit_5->text())<<endl;
				out<<tr("家族史：")<<tr(LineEdit_6->text())<<endl;
				out<<tr("心率：")<<tr(LineEdit_7->text())<<endl;
				out<<tr("呼吸频率：")<<tr(LineEdit_8->text())<<endl;
				out<<tr("血氧饱和度：")<<tr(LineEdit_9->text())<<endl;
				out<<tr("初步诊断：")<<tr(LineEdit_13->text())<<endl;
			}
			  //关闭文件，避免发生错误
			myfile.close();

	}
}

TestLog::~TestLog()
{

}
