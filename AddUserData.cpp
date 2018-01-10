#include "AddUserData.h"
#include "qdir.h"
#include "qfile.h"
#include "qfileinfo.h"
#include <qdebug.h>
#include <qdatetime.h>
#include <qtextstream.h>
#include <qsqlquery.h>
#include <qsqlrecord.h>
#include <qmessagebox.h>
#include <QDate>
#include <qgridlayout.h>

AddUserData::AddUserData(QWidget *parent)
	: QWidget(parent)
{
	//setupUi(this);
	this->setWindowTitle(tr("�û���Ϣ�Ǽ�"));
	this->setWindowIcon(QIcon("./Resources/data.png"));
	this->resize(700,400);
	QGridLayout* grid=new QGridLayout;
	

	QPushButton* confirmButton=new QPushButton(tr("ȷ��"));
	QPushButton* closedButton=new QPushButton(tr("�ر�"));
	QLabel* label1=new QLabel(tr("�û�����"));
	QLabel* label2=new QLabel(tr("����"));
	QLabel* label3=new QLabel(tr("����"));
	QLabel* label4=new QLabel(tr("�Ա�"));
	QLabel* label5=new QLabel(tr("����"));
	QLabel* label6=new QLabel(tr("���֤��"));
	QLabel* label7=new QLabel(tr("�������"));
	QLabel* label8=new QLabel(tr("�������"));
	QLabel* label9=new QLabel(tr("����"));
	QLabel* label10=new QLabel(tr("סԺ��"));
	QLabel* label11=new QLabel(tr("�ٴ�ӡ��"));
	QLabel* label12=new QLabel(tr("�û��������"));
	sexComboBox=new QComboBox;
	sexComboBox->addItem(tr("��"));
	sexComboBox->addItem(tr("Ů"));
	sexComboBox->setCurrentItem(0);
	testDateEdit=new QDateEdit;
	testDateEdit->setDate(QDate::currentDate());
	houseComboBox=new QComboBox;
	houseComboBox->addItem(tr("���"));
	houseComboBox->addItem(tr("�ڿ�"));
	houseComboBox->setCurrentItem(0);
	userNameLineEdit=new QLineEdit;
	userNumLineEdit=new QLineEdit;
	ageLineEdit=new QLineEdit;
	nationLineEdit=new QLineEdit;
	IDLineEdit=new QLineEdit;
	instrumentLineEdit=new QLineEdit;
	numLineEdit=new QLineEdit;
    caseTextEdit=new QTextEdit;
	SpecialTextEdit=new QTextEdit;

	QTabWidget* tabWidget=new QTabWidget;
	QWidget* widgetLeft=new QWidget;
	QWidget* widgetRight=new QWidget;
	tabWidget->addTab(widgetLeft,tr("�û�������Ϣ"));
	tabWidget->addTab(widgetRight,tr("�û�������Ϣ"));
	tabWidget->setCurrentPage(0);
	QHBoxLayout* left=new QHBoxLayout;
	QFormLayout* leftForm=new QFormLayout;
	QFormLayout* rightForm=new QFormLayout;
	left->addLayout(leftForm);
	left->addLayout(rightForm);
	leftForm->addRow(label1,userNumLineEdit);
	leftForm->addRow(label2,userNameLineEdit);
	leftForm->addRow(label3,ageLineEdit);
	leftForm->addRow(label4,sexComboBox);
	leftForm->addRow(label5,nationLineEdit);
	leftForm->addRow(label6,IDLineEdit);
	leftForm->setContentsMargins(30,40,30,40);
	leftForm->setHorizontalSpacing(30);
	leftForm->setVerticalSpacing(30);
	rightForm->addRow(label7,instrumentLineEdit);
	rightForm->addRow(label8,testDateEdit);
	rightForm->addRow(label9,houseComboBox);
	rightForm->addRow(label10,numLineEdit);
	rightForm->setContentsMargins(30,40,30,40);
	rightForm->setHorizontalSpacing(30);
	rightForm->setVerticalSpacing(30);
	widgetLeft->setLayout(left);

	QVBoxLayout* right=new QVBoxLayout;
	QHBoxLayout* rightTop=new QHBoxLayout;
	QHBoxLayout* rightBottom=new QHBoxLayout;
	rightTop->addWidget(label11);
	rightTop->addWidget(caseTextEdit);
	rightTop->addWidget(label12);
	rightTop->addWidget(SpecialTextEdit);
	right->addLayout(rightTop);
	rightBottom->addStretch();
	rightBottom->addWidget(confirmButton);
	rightBottom->addWidget(closedButton);
	right->addLayout(rightBottom);
	widgetRight->setLayout(right);

	grid->addWidget(tabWidget,1,1);
	grid->setColStretch(0,1);
	grid->setColStretch(0,10);
	grid->setColStretch(0,1);
	grid->setRowStretch(0,1);
	grid->setRowStretch(0,10);
	grid->setRowStretch(0,1);

	this->setLayout(grid);
    
	connect(confirmButton,SIGNAL(clicked()),this,SLOT(onConfirmButtonClicked()));
	connect(closedButton,SIGNAL(clicked()),this,SLOT(onClosedButtonClicked()));
}
//�û���Ϣ���ر���һ�ݣ����ݿⱣ��һ��
void AddUserData::onConfirmButtonClicked()
{
	QMessageBox::information(this,tr("��ʾ"),tr("ͬ�����ݿ���ĵ��ɹ���"));
	//�ڵ�ǰĿ¼�������Ƿ���userData�ļ��У�û�оʹ����������û���Ϣ�ĵ���������
	qDebug()<<"asd"<<endl;
	QDir dir("../");
	QFileInfoList list=dir.entryInfoList();
	QString currentPath=dir.absolutePath();
	qDebug()<<"currentPath="<<currentPath<<endl;


	QString temp;

	if(userNameLineEdit->text()=="")
	{
		 temp="δ֪�û�";

	}
	else
	{
		temp=userNameLineEdit->text();
	}

	int i=0;
	for(;i<list.size();i++)  
	{
		QFileInfo fileInfo=list.at(i);
		qDebug()<<"fileInfo"<<i<<"="<<fileInfo.fileName()<<endl;
		if(fileInfo.fileName()=="userData")
		{
			QString targetPath=currentPath+"/userData";
			QDateTime currentTime;
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hhʱmm��ss��")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr(temp)<<tr("�û����˼����Ϣ��")<<endl<<endl<<endl<<endl;
				out<<tr("�û����룺")<<tr(userNumLineEdit->text())<<endl;
				out<<tr("�û�������")<<tr(temp)<<endl;
				out<<tr("�û����䣺")<<tr(ageLineEdit->text())<<endl;
				out<<tr("�û��Ա�")<<tr(sexComboBox->currentText())<<endl;
				out<<tr("�û����壺")<<tr(nationLineEdit->text())<<endl;
				out<<tr("���֤���룺")<<tr(IDLineEdit->text())<<endl;
				out<<tr("���������")<<tr(instrumentLineEdit->text())<<endl;
				//ע��һ��������û������
				out<<tr("���ʱ�䣺")<<tr(testDateEdit->text())<<endl;
				out<<tr("����   ��")<<tr(houseComboBox->currentText())<<endl;
				out<<tr("סԺ���룺")<<tr(numLineEdit->text())<<endl;
				out<<tr("�ٴ�ӡ��")<<tr(caseTextEdit->text())<<endl;
				out<<tr("�û����������")<<tr(SpecialTextEdit->text())<<endl;
		
			}
			  //�ر��ļ������ⷢ������
			myfile.close();
			break;
		}
	}
	if(i==list.size())
	{		
			QString targetPath=currentPath+"/userData";
			qDebug()<<"targetPath="<<targetPath<<endl;
			dir.mkdir(targetPath);
			QDateTime currentTime;		
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hhʱmm��ss��")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr(temp)<<tr("�û����˼����Ϣ��")<<endl<<endl<<endl<<endl;
				out<<tr("�û����룺")<<tr(userNumLineEdit->text())<<endl;
				out<<tr("�û�������")<<tr(temp)<<endl;
				out<<tr("�û����䣺")<<tr(ageLineEdit->text())<<endl;
				out<<tr("�û��Ա�")<<tr(sexComboBox->currentText())<<endl;
				out<<tr("�û����壺")<<tr(nationLineEdit->text())<<endl;
				out<<tr("���֤���룺")<<tr(IDLineEdit->text())<<endl;
				out<<tr("���������")<<tr(instrumentLineEdit->text())<<endl;
				//ע��һ��������û������
				out<<tr("���ʱ�䣺")<<tr(testDateEdit->text())<<endl;
				out<<tr("����   ��")<<tr(houseComboBox->currentText())<<endl;
				out<<tr("סԺ���룺")<<tr(numLineEdit->text())<<endl;
				out<<tr("�ٴ�ӡ��")<<tr(caseTextEdit->text())<<endl;
				out<<tr("�û����������")<<tr(SpecialTextEdit->text())<<endl;		
			}
			  //�ر��ļ������ⷢ������
			myfile.close();

	}
	qDebug()<<"begin"<<endl;
					qDebug()<<tr(userNumLineEdit->text())<<endl;
				qDebug()<<tr(userNameLineEdit->text())<<endl;
				qDebug()<<tr(ageLineEdit->text())<<endl;
				qDebug()<<tr(sexComboBox->currentText())<<endl;
				qDebug()<<tr(nationLineEdit->text())<<endl;
				qDebug()<<tr(IDLineEdit->text())<<endl;
				qDebug()<<tr(instrumentLineEdit->text())<<endl;
				//ע��һ��������û������
				qDebug()<<tr(testDateEdit->text())<<endl;
				qDebug()<<tr(houseComboBox->currentText())<<endl;
				qDebug()<<tr(numLineEdit->text())<<endl;
				qDebug()<<tr(caseTextEdit->text())<<endl;
				qDebug()<<tr(SpecialTextEdit->text())<<endl;	
				qDebug()<<"end"<<endl;
	//����������Ϊ���ؼ���
	//query.exec("create table patient(name varchar(20) primary key,usernum int,age int,sex varchar(4),nation varchar(20),"
	//	"instrument varchar(20),time varchar(30),housenum int,impression varchar(200),specialcase varchar(200))");
	//query.exec("insert into patient values(tr(userNameLineEdit->text()),tr(userNumLineEdit->text())),tr(ageLineEdit->text()),"
	//	"tr(sexComboBox->currentText()),tr(nationLineEdit->text()),tr(IDLineEdit->text()),"
	//	"tr(instrumentLineEdit->text()),tr(testDateEdit->text()),tr(numLineEdit->text()),tr(caseTextEdit->text()),tr(SpecialTextEdit->text())");
	//QSqlQuery outquery;
	//outquery=db.exec("select *from patient");
	//while(outquery.next())
 //   {
 //       qDebug() << outquery.value(0).toString() << outquery.value(1).toInt();
 //   }
	//��������ӵ��������ݿ�
	 if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1",
            "Unable to establish a database connection.", QMessageBox::Cancel);
      }
	 {
		 qDebug()<<"open db success!"<<endl;
	 }
	QSqlQuery query(db);
	//qDebug()<<query.exec(QString("select * from patient"));
	//qDebug()<<query.exec(QString("insert into patient values('����',23, 11,'��','����','�԰�˹��','ʱ��','�ǺǺ�')"));
	QString cmd;
	cmd="insert into patient values('";
	cmd+=temp;
	cmd+="','";
	cmd+=userNumLineEdit->text();
	cmd+="','";
	cmd+=ageLineEdit->text();
	cmd+="','";
	cmd+=sexComboBox->currentText();
	cmd+="','";
	cmd+=nationLineEdit->text();
	cmd+="','";
	cmd+=instrumentLineEdit->text();
	cmd+="','";
	cmd+=testDateEdit->text();
	cmd+="','";
	cmd+=houseComboBox->currentText();
	cmd+="')";
	qDebug()<<cmd<<endl;
	qDebug()<<query.exec(cmd);
	QString cmdcase;

	cmdcase="insert into singlecase values('";
	cmdcase+=temp;
	cmdcase+="','";
	cmdcase+=numLineEdit->text();
	cmdcase+="','";
	cmdcase+=caseTextEdit->text();
    cmdcase+="','";
	cmdcase+=SpecialTextEdit->text();
	cmdcase+="')";
	qDebug()<<cmdcase<<endl;
	qDebug()<<query.exec(cmdcase);

	QString cmdPatientTime;
	cmdPatientTime="insert into patientTime values('";
	cmdPatientTime+=testDateEdit->text();
	cmdPatientTime+="','";
	cmdPatientTime+=temp;
	cmdPatientTime+="')";
	qDebug()<<cmdPatientTime<<endl;
	qDebug()<<query.exec(cmdPatientTime);

	//for(int i=0;i<listTreePatient.size();i++)
	//{
	//	if(listTreePatient.at(i)->date==testDateEdit->text())
	//	{
	//		listTreePatient.at(i)->name.push_back(temp);
	//		break;
	//	}

	//}
	//if(i==listTreePatient.size())
	//{
	//		TreePatient* treePatient=new TreePatient;
	//		treePatient->date=testDateEdit->text();
	//		treePatient->name.push_back(temp);
	//}

	//qDebug()<<query.exec(QString("insert into patient values('����','���','���','��','����','�԰�˹��','ʱ��','�ǺǺ�')"));
	//ע�����Ǵ����д�����������´�Ҫ֪��
	//qDebug()<<query.exec("insert into patient values(����,���,����˹,��,����,����˹,����,��)");
	/*qDebug()<<query.exec("insert into patient values(tr(userNameLineEdit->text()),tr(userNumLineEdit->text())),tr(ageLineEdit->text()),"
		"tr(sexComboBox->currentText()),tr(nationLineEdit->text()),tr(IDLineEdit->text()),"
		"tr(instrumentLineEdit->text()),tr(testDateEdit->text()),tr(houseComboBox->currentText()))");*/
	//QSqlRecord recordUser=modelUser.record();
	//recordUser.setValue("����","asdas");
	//recordUser.setValue("����","asd");
	//recordUser.setValue("����","asda");
	//recordUser.setValue("�Ա�","sdas");
	////recordUser.setValue("����",userNameLineEdit->text());
	////recordUser.setValue("����",userNumLineEdit->text());
	////recordUser.setValue("����",ageLineEdit->text());
	////recordUser.setValue("�Ա�",sexComboBox->currentText());
	//recordUser.setValue("����",nationLineEdit->text());
	//recordUser.setValue("���֤����",IDLineEdit->text());
	//recordUser.setValue("�������",instrumentLineEdit->text());
	//recordUser.setValue("����",houseComboBox->currentText());
 //   modelUser.insertRecord(-1, recordUser);
 //   modelUser.submitAll();

	//QSqlRecord recordCase=modelCase.record();
	//recordCase.setValue("����",userNameLineEdit->text());
	//recordCase.setValue("סԺ����",numLineEdit->text());
	//recordCase.setValue("�ٴ�ӡ��",caseTextEdit->text());
	//recordCase.setValue("�û��������",SpecialTextEdit->text());
	//modelCase.insertRecord(-1, recordCase);
 //   modelCase.submitAll();


}
void AddUserData::onClosedButtonClicked()
{
	this->close();
}

AddUserData::~AddUserData()
{

}
