#include "SuggestionFeedback.h"
#include <qmessagebox.h>
#include <qdir.h>
#include <qdatetime.h>
#include <QTextStream>
#include <qdebug.h>

SuggestionFeedback::SuggestionFeedback(QWidget *parent)
	: QWidget(parent)
{
	this->setWindowTitle(tr("�������"));
	this->setWindowIcon(QIcon("./Resources/feedback.png"));
	QVBoxLayout* main=new QVBoxLayout();
	QHBoxLayout* top=new QHBoxLayout();
	QLabel* label=new QLabel(tr("<h3>�������:</h3>"));
	textEidt=new QTextEdit;
	top->addWidget(label);
	top->addWidget(textEidt);
	main->addLayout(top);
	QHBoxLayout* bottom=new QHBoxLayout();
	QPushButton* submit=new QPushButton(tr("�ύ"));
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
	QMessageBox::information(this,tr("��ʾ"),tr("��������ɹ����Ѿ��ɹ�������̨��"));
	//�ڵ�ǰĿ¼�������Ƿ���suggestionFeedback�ļ��У�û�оʹ����������û���Ϣ�ĵ���������
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
			QString saveName=targetPath+"/"+tr("�������")+currentTime.currentDateTime().toString("yyyy-MM-dd-hhʱmm��ss��")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr("���������")<<endl<<endl<<endl<<endl;
				out<<tr(textEidt->text())<<endl;
			}
			  //�ر��ļ������ⷢ������
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
			QString saveName=targetPath+"/"+tr("�������")+currentTime.currentDateTime().toString("yyyy-MM-dd-hhʱmm��ss��")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr("���������")<<endl<<endl<<endl<<endl;
				out<<tr(textEidt->text())<<endl;	
			}
			  //�ر��ļ������ⷢ������
			myfile.close();

	}

}
SuggestionFeedback::~SuggestionFeedback()
{

}
