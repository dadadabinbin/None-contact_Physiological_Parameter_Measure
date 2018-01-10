#include "SystemMessage.h"
#include <qgridlayout.h>
#include <qmessagebox.h>

SystemMessage::SystemMessage(QWidget *parent)
	: QWidget(parent)
{
       this->setWindowTitle(tr("ϵͳ��Ϣ"));
	   this->resize(600,400);
	   this->setWindowIcon(QIcon("./Resources/systemInformation.png"));
	   QListWidget* list=new QListWidget;
	   QListWidgetItem* listitem0= new QListWidgetItem(tr("ϵͳ����                                   IPPG�ǽӴ�ʽ�����������ϵͳ"));
	   QListWidgetItem* listitem1= new QListWidgetItem(tr("ϵͳ�汾��                                 V.2.1"));
	   QListWidgetItem* listitem2= new QListWidgetItem(tr("������λ                                   �人��ѧ�����ѧ�뼼��ѧԺ"));
	   QListWidgetItem* listitem3= new QListWidgetItem(tr("ϵͳ����                                   ����������һ��ʱƵ"));
	   QListWidgetItem* listitem4= new QListWidgetItem(tr("                                               ͨ������Ƶ�����õ������һЩ�������"));
	   QListWidgetItem* listitem5= new QListWidgetItem(tr("                                               ����Ѫ�����Ͷȣ����ʣ�����Ƶ�ʵ�"));
	  // QListWidgetItem* listitem6= new QListWidgetItem(tr("											  3 ������"));
	   list->addItem(listitem0);
	   list->addItem(listitem1);
	   list->addItem(listitem2);
	   list->addItem(listitem3);
	   list->addItem(listitem4);
	   list->addItem(listitem5);
	  // list->addItem(listitem6);
        QGridLayout* grid=new QGridLayout;
		QHBoxLayout* hBox=new QHBoxLayout;
		QPushButton* buttonleft=new QPushButton(tr("������"));
		QPushButton* buttonRight=new QPushButton(tr("�������"));
		hBox->addStretch();
		hBox->addWidget(buttonleft);		
		hBox->addWidget(buttonRight);
		grid->addLayout(hBox,2,1);
	    grid->addWidget(list,1,1);
		grid->setColumnStretch(0,1);
		grid->setColumnStretch(1,10);
		grid->setColumnStretch(2,1);
		grid->setRowStretch(0,1);
		grid->setRowStretch(1,10);
		grid->setRowStretch(2,1);
		grid->setRowStretch(3,1);
		this->setLayout(grid);
		connect(buttonleft,SIGNAL(clicked()),this,SLOT(onButtonLeftClicked()));
		connect(buttonRight,SIGNAL(clicked()),this,SLOT(onButtonRightClicked()));

}
//������
void SystemMessage::onButtonLeftClicked()
{
	QMessageBox::information(this,tr("�汾���"),tr("���İ汾�Ѿ������°汾!"));
}
void SystemMessage::onButtonRightClicked()
{
	SuggestionFeedback* feedback=new SuggestionFeedback();
	feedback->show();
}

SystemMessage::~SystemMessage()
{

}
