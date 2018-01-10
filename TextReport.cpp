
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
	this->setWindowTitle(tr("�û������鱨��"));
	this->resize(400,500);

	pushButton=new QPushButton(tr("ͬ�����ĵ�"));
	LineEdit=new QLineEdit;
	LineEdit_2=new QLineEdit;
	LineEdit_3=new QLineEdit;
	LineEdit_4=new QLineEdit;
	LineEdit_5=new QLineEdit;
	QVBoxLayout* main=new QVBoxLayout;
	QHBoxLayout* top=new QHBoxLayout;
	top->addStretch();
	QLabel* title=new QLabel(tr("<h1>�û������鱨��</h1>"));
	top->addWidget(title);
	top->addStretch();
	main->addLayout(top);
	QFormLayout* form=new QFormLayout;
	QLabel* name=new QLabel(tr("������"));
	QLabel* age=new QLabel(tr("���䣺"));
	QLabel* arg1=new QLabel(tr("���ʣ�"));
	QLabel* arg2=new QLabel(tr("����Ƶ�ʣ�"));
	QLabel* result=new QLabel(tr("Ѫ�����Ͷȣ�"));
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
	QLabel* suggest=new QLabel(tr("       ҽ�����飺"));
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
	QLabel* tip=new QLabel(tr("�人��ѧ����ѧԺ����  -����ɽ"));
	bottom->addWidget(tip);
	bottom->addStretch();
	main->addLayout(bottom);

	this->setLayout(main);
	connect(pushButton,SIGNAL(clicked()),this,SLOT(onPushButtonClicked()));
	
}
void TestReport::onPushButtonClicked()
{
	QMessageBox::information(this,tr("��ʾ"),tr("ͬ���ĵ��ɹ���"));
	//�ڵ�ǰĿ¼�������Ƿ���testReport�ļ��У�û�оʹ����������û���Ϣ�ĵ���������
	QDir dir("../");
	QFileInfoList list=dir.entryInfoList();
	QString currentPath=dir.absolutePath();
	qDebug()<<"currentPath="<<currentPath<<endl;

	QString temp;

	if(LineEdit->text()=="")
	{
		 temp="δ֪�û�";

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
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hhʱmm��ss��")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr("                                  �û������鱨��")<<endl<<endl<<endl<<endl;
				out<<tr("������")<<tr(temp)<<endl<<endl;
				out<<tr("���䣺")<<tr(LineEdit_2->text())<<endl<<endl;
				out<<tr("���ʣ�")<<tr(LineEdit_3->text())<<endl<<endl;
				out<<tr("����Ƶ�ʣ�")<<tr(LineEdit_4->text())<<endl<<endl;
				out<<tr("Ѫ�����Ͷȣ�")<<tr(LineEdit_5->text())<<endl<<endl;
				out<<tr("ҽ�����飺")<<tr(lineEditSugestion->text())<<endl<<endl;
		
			}
			  //�ر��ļ������ⷢ������
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
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hhʱmm��ss��")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr("                                     �û������鱨��")<<endl<<endl<<endl<<endl;
				out<<tr("������")<<tr(temp)<<endl<<endl;
				out<<tr("���䣺")<<tr(LineEdit_2->text())<<endl<<endl;
				out<<tr("���ʣ�")<<tr(LineEdit_3->text())<<endl<<endl;
				out<<tr("����Ƶ�ʣ�")<<tr(LineEdit_4->text())<<endl<<endl;
				out<<tr("Ѫ�����Ͷȣ�")<<tr(LineEdit_5->text())<<endl<<endl;
				out<<tr("ҽ�����飺")<<tr(lineEditSugestion->text())<<endl<<endl;
			}
			  //�ر��ļ������ⷢ������
			myfile.close();

	}

}

TestReport::~TestReport()
{

}
