#include "Login.h"
#include <QString>
#include "ALLSPACE_VARIABLES.h"
#include <qvariant.h>
#include <qstringlist.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include <QtSql/QSqlResult>
#include <QSqlQuery>
#include <qvector.h>
#include <qsqlresult.h>


Login::Login(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	this->setWindowIcon(QIcon("./Resources/login.png"));
	this->setWindowTitle(tr("��½����"));
	this->resize(500,300);
	QLabel* name=new QLabel(tr("�û�����"));
	QLabel* password=new QLabel(tr("����  ��"));
	LineEdit =new QLineEdit;
	LineEdit->setLineWidth(30);
	LineEdit_2 =new QLineEdit;
	LineEdit_2->setLineWidth(30);
	pushButton=new QPushButton(tr("ȷ��"));
	QFormLayout* lay=new QFormLayout;
	lay->addRow(name,LineEdit);
	lay->addRow(password,LineEdit_2);
	lay->setHorizontalSpacing(30);
	lay->setVerticalSpacing(30);
	lay->setMargin(40);
	lay->setContentsMargins(70,20,70,30);
	QVBoxLayout* main=new QVBoxLayout;
	QHBoxLayout* top=new QHBoxLayout;
	QLabel* title=new QLabel(tr("<h2>��ӭʹ�ñ�������人��ѧ����ѧԺ��</h2>"));
	top->addStretch();
	top->addWidget(title);
	top->addStretch();
	main->addStretch(1);
	main->addLayout(top);
	main->addStretch(1);
	main->addLayout(lay);
	QHBoxLayout* bottom=new QHBoxLayout;
	bottom->addStretch();
	bottom->addWidget(pushButton);
	bottom->addStretch();
	main->addLayout(bottom);
	main->addStretch(1);

	this->setLayout(main);
	

	connect(pushButton,SIGNAL(clicked()),this,SLOT(onPushBottonClicked()));
}
void Login::onPushBottonClicked()
{
	QString userName=LineEdit->text();
	QString password=LineEdit_2->text();

	QSqlQuery queryPre=db.exec("select * from softwareUser");
	int num=0;
	while(queryPre.next())
	{
		num++;
	}
	int sqlSize=num;

	QSqlQuery query=db.exec("select * from softwareUser");
	// QSqlQuery q("select * from employees");
    QSqlRecord rec = query.record();
	
    qDebug() << "Number of columns: " << rec.count();
	//ͨ����Ŀͷ�ҵ��к�
    int nameCol = rec.indexOf("userName"); // index of the field "name"
	int passwordCol=rec.indexOf("password");

	int realNum=0;
	int passwordNum=0;
	//���ñ�־λ���ж����û��������������
	bool flag=false;
	//ע��query����Ͷ�Ӧÿһ��
	//ͨ���к��ҵ����ݿ��ӦԪ��
    while (query.next())
	{
		realNum++;
		if(query.value(nameCol).toString()==userName)
		{
			passwordNum++;
			if(query.value(passwordCol).toString()==password)
			{
				welcome=new Welcome;
				welcome->show();
				this->hide();
				flag=true;
				break;
			}			
		}
	}
	
	qDebug()<<"realNum:"<<realNum<<endl;
	qDebug()<<"sqlSize:"<<sqlSize<<endl;
	qDebug()<<"passwordNum:"<<passwordNum<<endl;
	if(flag==false&&passwordNum==0)
	{
		QMessageBox::warning(this,tr("����"),tr("��������˻������ڣ�����������"));
	}
	else if(flag==false&&passwordNum>0)
	{
		QMessageBox::warning(this,tr("����"),tr("������������������������"));
	}
	
     
	//bool b=query.first();
	//while(b)
	//{
	//	QSqlResult* result=const_cast<QSqlResult*>(query.result());
	//	 qDebug() << "Number of columns: " << result->count();

 //     int nameCol = result->indexOf("name"); // index of the field "name"
 //      while (query.next())
 //          qDebug() << query.value(nameCol).toString(); // output all names
	//	//QVariant values=query.result()->boundValue(0);
	//	qDebug()<<values;
	//}
	//modelUser=new QSqlTableModel;
	//modelUser->setTable("softwareUser");
	//modelUser->select();
	//QSqlRecord record=modelUser->record();

	//for(int i=0;i<record.count();i++)
	//{
	//	QVariant var = record.fieldName(i);
	//	if(i==0)
	//	    modelUser->setFilter(QString("'%1'='%2'").arg(var.toString()).arg(ui.LineEdit->text()));
	//	else if(i==1)
	//		modelUser->setFilter(QString("'%1'='%2'").arg(var.toString()).arg(ui.LineEdit_2->text()));	
	//}
	//modelUser->select();
	//QSqlRecord record1=modelUser->record();
	//if(!record1.isEmpty())
	//	QMessageBox::information(this,tr("asd"),tr("success!"));
	//else 
	//	QMessageBox::information(this,tr("aaa"),tr("fail!"));

}
Login::~Login()
{

}
