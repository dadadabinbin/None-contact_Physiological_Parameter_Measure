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
	this->setWindowTitle(tr("用户信息登记"));
	this->setWindowIcon(QIcon("./Resources/data.png"));
	this->resize(700,400);
	QGridLayout* grid=new QGridLayout;
	

	QPushButton* confirmButton=new QPushButton(tr("确定"));
	QPushButton* closedButton=new QPushButton(tr("关闭"));
	QLabel* label1=new QLabel(tr("用户号码"));
	QLabel* label2=new QLabel(tr("姓名"));
	QLabel* label3=new QLabel(tr("年龄"));
	QLabel* label4=new QLabel(tr("性别"));
	QLabel* label5=new QLabel(tr("民族"));
	QLabel* label6=new QLabel(tr("身份证号"));
	QLabel* label7=new QLabel(tr("检查仪器"));
	QLabel* label8=new QLabel(tr("检查日期"));
	QLabel* label9=new QLabel(tr("科室"));
	QLabel* label10=new QLabel(tr("住院号"));
	QLabel* label11=new QLabel(tr("临床印象"));
	QLabel* label12=new QLabel(tr("用户特殊情况"));
	sexComboBox=new QComboBox;
	sexComboBox->addItem(tr("男"));
	sexComboBox->addItem(tr("女"));
	sexComboBox->setCurrentItem(0);
	testDateEdit=new QDateEdit;
	testDateEdit->setDate(QDate::currentDate());
	houseComboBox=new QComboBox;
	houseComboBox->addItem(tr("外科"));
	houseComboBox->addItem(tr("内科"));
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
	tabWidget->addTab(widgetLeft,tr("用户基本信息"));
	tabWidget->addTab(widgetRight,tr("用户病情信息"));
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
//用户信息本地保存一份，数据库保存一份
void AddUserData::onConfirmButtonClicked()
{
	QMessageBox::information(this,tr("提示"),tr("同步数据库和文档成功！"));
	//在当前目录下搜索是否有userData文件夹，没有就创建，并将用户信息文档放入其中
	qDebug()<<"asd"<<endl;
	QDir dir("../");
	QFileInfoList list=dir.entryInfoList();
	QString currentPath=dir.absolutePath();
	qDebug()<<"currentPath="<<currentPath<<endl;


	QString temp;

	if(userNameLineEdit->text()=="")
	{
		 temp="未知用户";

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
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hh时mm分ss秒")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr(temp)<<tr("用户个人检查信息：")<<endl<<endl<<endl<<endl;
				out<<tr("用户号码：")<<tr(userNumLineEdit->text())<<endl;
				out<<tr("用户姓名：")<<tr(temp)<<endl;
				out<<tr("用户年龄：")<<tr(ageLineEdit->text())<<endl;
				out<<tr("用户性别：")<<tr(sexComboBox->currentText())<<endl;
				out<<tr("用户民族：")<<tr(nationLineEdit->text())<<endl;
				out<<tr("身份证号码：")<<tr(IDLineEdit->text())<<endl;
				out<<tr("检查仪器：")<<tr(instrumentLineEdit->text())<<endl;
				//注意一下这里有没有问题
				out<<tr("检查时间：")<<tr(testDateEdit->text())<<endl;
				out<<tr("科室   ：")<<tr(houseComboBox->currentText())<<endl;
				out<<tr("住院号码：")<<tr(numLineEdit->text())<<endl;
				out<<tr("临床印象：")<<tr(caseTextEdit->text())<<endl;
				out<<tr("用户特殊情况：")<<tr(SpecialTextEdit->text())<<endl;
		
			}
			  //关闭文件，避免发生错误
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
			QString saveName=targetPath+"/"+tr(temp)+currentTime.currentDateTime().toString("yyyy-MM-dd-hh时mm分ss秒")+".docx";
			QFile myfile(saveName);
			if (myfile.open(QIODevice::WriteOnly | QIODevice::Text))
			{
				QTextStream out(&myfile);
				out<<tr(temp)<<tr("用户个人检查信息：")<<endl<<endl<<endl<<endl;
				out<<tr("用户号码：")<<tr(userNumLineEdit->text())<<endl;
				out<<tr("用户姓名：")<<tr(temp)<<endl;
				out<<tr("用户年龄：")<<tr(ageLineEdit->text())<<endl;
				out<<tr("用户性别：")<<tr(sexComboBox->currentText())<<endl;
				out<<tr("用户民族：")<<tr(nationLineEdit->text())<<endl;
				out<<tr("身份证号码：")<<tr(IDLineEdit->text())<<endl;
				out<<tr("检查仪器：")<<tr(instrumentLineEdit->text())<<endl;
				//注意一下这里有没有问题
				out<<tr("检查时间：")<<tr(testDateEdit->text())<<endl;
				out<<tr("科室   ：")<<tr(houseComboBox->currentText())<<endl;
				out<<tr("住院号码：")<<tr(numLineEdit->text())<<endl;
				out<<tr("临床印象：")<<tr(caseTextEdit->text())<<endl;
				out<<tr("用户特殊情况：")<<tr(SpecialTextEdit->text())<<endl;		
			}
			  //关闭文件，避免发生错误
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
				//注意一下这里有没有问题
				qDebug()<<tr(testDateEdit->text())<<endl;
				qDebug()<<tr(houseComboBox->currentText())<<endl;
				qDebug()<<tr(numLineEdit->text())<<endl;
				qDebug()<<tr(caseTextEdit->text())<<endl;
				qDebug()<<tr(SpecialTextEdit->text())<<endl;	
				qDebug()<<"end"<<endl;
	//表是以姓名为主关键字
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
	//将数据添加到两个数据库
	 if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1",
            "Unable to establish a database connection.", QMessageBox::Cancel);
      }
	 {
		 qDebug()<<"open db success!"<<endl;
	 }
	QSqlQuery query(db);
	//qDebug()<<query.exec(QString("select * from patient"));
	//qDebug()<<query.exec(QString("insert into patient values('马亮',23, 11,'男','汉族','以阿斯顿','时间','呵呵呵')"));
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

	//qDebug()<<query.exec(QString("insert into patient values('马亮','你哈','你哈','男','汉族','以阿斯顿','时间','呵呵呵')"));
	//注意这是错误的写法！！！！下次要知道
	//qDebug()<<query.exec("insert into patient values(撒旦,你哈,阿迪斯,男,打算,阿迪斯,打算,和)");
	/*qDebug()<<query.exec("insert into patient values(tr(userNameLineEdit->text()),tr(userNumLineEdit->text())),tr(ageLineEdit->text()),"
		"tr(sexComboBox->currentText()),tr(nationLineEdit->text()),tr(IDLineEdit->text()),"
		"tr(instrumentLineEdit->text()),tr(testDateEdit->text()),tr(houseComboBox->currentText()))");*/
	//QSqlRecord recordUser=modelUser.record();
	//recordUser.setValue("姓名","asdas");
	//recordUser.setValue("号码","asd");
	//recordUser.setValue("年龄","asda");
	//recordUser.setValue("性别","sdas");
	////recordUser.setValue("姓名",userNameLineEdit->text());
	////recordUser.setValue("号码",userNumLineEdit->text());
	////recordUser.setValue("年龄",ageLineEdit->text());
	////recordUser.setValue("性别",sexComboBox->currentText());
	//recordUser.setValue("民族",nationLineEdit->text());
	//recordUser.setValue("身份证号码",IDLineEdit->text());
	//recordUser.setValue("检查仪器",instrumentLineEdit->text());
	//recordUser.setValue("科室",houseComboBox->currentText());
 //   modelUser.insertRecord(-1, recordUser);
 //   modelUser.submitAll();

	//QSqlRecord recordCase=modelCase.record();
	//recordCase.setValue("姓名",userNameLineEdit->text());
	//recordCase.setValue("住院号码",numLineEdit->text());
	//recordCase.setValue("临床印象",caseTextEdit->text());
	//recordCase.setValue("用户特殊情况",SpecialTextEdit->text());
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
