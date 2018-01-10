#include "RegisterAccount.h"
#include <qmessagebox.h>
#include <qstring.h>
#include <qsqlquery.h>

RegisterAccount::RegisterAccount(QWidget *parent)
	: QWidget(parent)
{
	//setupUi(this);
	this->setWindowTitle(tr("�˻�ע��"));
	this->setWindowIcon(QIcon("./Resources/account.png"));
	this->resize(400,200);

	QVBoxLayout* main=new QVBoxLayout(this);
	QHBoxLayout* top=new QHBoxLayout;
	QLabel* title=new QLabel(tr("<h1>��ӭע���˻�</h1>"));
	top->addStretch();
	top->addWidget(title);
	top->addStretch();
	main->addLayout(top);
	QFormLayout* form=new QFormLayout;
	QLabel* name=new QLabel(tr("�˻���"));
	QLabel* password=new QLabel(tr("����"));
	LineEdit=new QLineEdit;
	LineEdit_2=new QLineEdit;
	form->addRow(name,LineEdit);
	form->addRow(password,LineEdit_2);
	form->setVerticalSpacing(30);
	form->setMargin(40);
	form->setContentsMargins(70,20,70,30);
	main->addLayout(form);
	QHBoxLayout* bottom=new QHBoxLayout;
	QPushButton* pushButtton=new QPushButton(tr("ȷ��ע��"));
	pushButtton->resize(30,15);
	bottom->addStretch();
	bottom->addWidget(pushButtton);
	bottom->addStretch();
	main->addLayout(bottom);
	connect(pushButtton,SIGNAL(clicked()),this,SLOT(onPushButtonClicked()));
}

void RegisterAccount::onPushButtonClicked()
{
	QString userName=LineEdit->text();
	QString password=LineEdit_2->text();
	 if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1",
            "Unable to establish a database connection.", QMessageBox::Cancel);
    }
	 QSqlQuery query(db);
	bool success= query.exec(QString("insert into softwareUser values('%1', '%2')").arg(userName).arg(password));
	if(success==true)
	     QMessageBox::information(this,tr("��ʾ"),tr("��ϲע���˻��ɹ���"));
	else if(success==false)
		 QMessageBox::information(this,tr("��ʾ"),tr("ע���˻�ʧ�ܣ�"));
}

RegisterAccount::~RegisterAccount()
{

}

