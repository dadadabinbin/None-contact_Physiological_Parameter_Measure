
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
	this->setWindowTitle(tr("�û������־"));
	this->resize(800,500);

	pushButton=new QPushButton(tr("ȷ����ͬ�����ݣ�"));
	QLabel* label1=new QLabel(tr("����"));
	QLabel* label2=new QLabel(tr("�Ա�"));
	QLabel* label3=new QLabel(tr("����"));
	QLabel* label4=new QLabel(tr("����ʱ��"));
	QLabel* label5=new QLabel(tr("��ʷ"));
	QLabel* label6=new QLabel(tr("����ʷ"));
	QLabel* label7=new QLabel(tr("�Ŵ���"));
	QLabel* label8=new QLabel(tr("����ʷ"));
	QLabel* label9=new QLabel(tr("����"));
	QLabel* label10=new QLabel(tr("����Ƶ��"));
	QLabel* label11=new QLabel(tr("Ѫ�����Ͷ�"));
	QLabel* label15=new QLabel(tr("�������"));
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
	ComboBox->addItem(tr("��"));
	ComboBox->addItem(tr("Ů"));
	ComboBox->setCurrentItem(0);

	QHBoxLayout* main=new QHBoxLayout;
	QGroupBox* left=new QGroupBox;
	left->setTitle(tr("�û���Ϣ"));
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
//ͬ���ļ�
void TestLog::onPushButtonClicked()
{
	QMessageBox::information(this,tr("��ʾ"),tr("ͬ���ĵ��ɹ���"));
	//�ڵ�ǰĿ¼�������Ƿ���testlog�ļ��У�û�оʹ����������û���Ϣ�ĵ���������
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
		if(fileInfo.fileName()=="testlog")
		{
			QString targetPath=currentPath+"/testlog";
			QDateTime currentTime;
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hhʱmm��ss��")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr(temp)<<tr("�û����˼����Ϣ��")<<endl<<endl<<endl<<endl;
				out<<tr("���ң�")<<tr(LineEdit_2->text())<<endl;
				out<<tr("�û�������")<<tr(temp)<<endl;
				out<<tr("�û��Ա�")<<tr(ComboBox->currentText())<<endl;
				out<<tr("����ʱ�䣺")<<tr(DateEdit->text())<<endl;
				out<<tr("��ʷ��")<<tr(LineEdit_3->text())<<endl;
				out<<tr("����ʷ��")<<tr(LineEdit_4->text())<<endl;
				out<<tr("�Ŵ�����")<<tr(LineEdit_5->text())<<endl;
				out<<tr("����ʷ��")<<tr(LineEdit_6->text())<<endl;
				out<<tr("���ʣ�")<<tr(LineEdit_7->text())<<endl;
				out<<tr("����Ƶ�ʣ�")<<tr(LineEdit_8->text())<<endl;
				out<<tr("Ѫ�����Ͷȣ�")<<tr(LineEdit_9->text())<<endl;
				out<<tr("������ϣ�")<<tr(LineEdit_13->text())<<endl;
		
			}
			  //�ر��ļ������ⷢ������
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
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hhʱmm��ss��")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);			
				out<<tr(temp)<<tr("�û����˼����Ϣ��")<<endl<<endl<<endl<<endl;
				out<<tr("���ң�")<<tr(LineEdit_2->text())<<endl;
				out<<tr("�û�������")<<tr(temp)<<endl;
				out<<tr("�û��Ա�")<<tr(ComboBox->currentText())<<endl;
				out<<tr("����ʱ�䣺")<<tr(DateEdit->text())<<endl;
				out<<tr("��ʷ��")<<tr(LineEdit_3->text())<<endl;
				out<<tr("����ʷ��")<<tr(LineEdit_4->text())<<endl;
				out<<tr("�Ŵ�����")<<tr(LineEdit_5->text())<<endl;
				out<<tr("����ʷ��")<<tr(LineEdit_6->text())<<endl;
				out<<tr("���ʣ�")<<tr(LineEdit_7->text())<<endl;
				out<<tr("����Ƶ�ʣ�")<<tr(LineEdit_8->text())<<endl;
				out<<tr("Ѫ�����Ͷȣ�")<<tr(LineEdit_9->text())<<endl;
				out<<tr("������ϣ�")<<tr(LineEdit_13->text())<<endl;
			}
			  //�ر��ļ������ⷢ������
			myfile.close();

	}
}

TestLog::~TestLog()
{

}
