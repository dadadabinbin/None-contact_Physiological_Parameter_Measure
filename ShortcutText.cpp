#include "ShortcutText.h"
#include <qicon.h>
#include <QVBoxLayout>
#include <qlistwidget.h>
#include <qlabel.h>
#include <qaction.h>

ShortcutText::ShortcutText(QWidget *parent)
	: QWidget(parent)
{
	this->setWindowTitle(tr("��ݼ�˵��"));
	this->setWindowIcon(QIcon("./Resources/shortcutkey.png"));
	this->resize(800,400);

	QVBoxLayout* lay=new QVBoxLayout;
	QHBoxLayout* bottom=new QHBoxLayout;
	QLabel* label=new QLabel(tr("<h3>�汾�ţ�V2.1</h3>"));
	bottom->addStretch();
	bottom->addWidget(label);
	QListWidget* list=new QListWidget;
	QListWidgetItem* listitem1= new QListWidgetItem(tr("ԤԼ�Ŷ�									Ctrl+A"));
	QListWidgetItem* listitem2= new QListWidgetItem(tr("��������									Ctrl+B"));
	QListWidgetItem* listitem3= new QListWidgetItem(tr("�������									Ctrl+Y"));
	QListWidgetItem* listitem4= new QListWidgetItem(tr("�����־									Ctrl+D"));
	QListWidgetItem* listitem5= new QListWidgetItem(tr("��鱨��									Ctrl+E"));
	QListWidgetItem* listitem6= new QListWidgetItem(tr("��ʷ����									Ctrl+F"));
	QListWidgetItem* listitem7= new QListWidgetItem(tr("��Ƶ����									Ctrl+G"));
	QListWidgetItem* listitem8= new QListWidgetItem(tr("��ʷ��־									Ctrl+H"));
	QListWidgetItem* listitem9= new QListWidgetItem(tr("��ʷ����									Ctrl+I"));
	//QListWidgetItem* listitem10= new QListWidgetItem(tr("ע���˻�									Ctrl+K"));
	QListWidgetItem* listitem11= new QListWidgetItem(tr("ϵͳ��Ϣ									Ctrl+L"));
	QListWidgetItem* listitem12= new QListWidgetItem(tr("�˳�ϵͳ									Ctrl+M"));
	QListWidgetItem* listitem13= new QListWidgetItem(tr("���˵��									Ctrl+N"));
	list->addItem(listitem1);
	list->addItem(listitem2);
	list->addItem(listitem3);
	list->addItem(listitem4);
	list->addItem(listitem5);
	list->addItem(listitem6);
	list->addItem(listitem7);
	list->addItem(listitem8);
	list->addItem(listitem9);
	//list->addItem(listitem10);
	list->addItem(listitem11);
	list->addItem(listitem12);
	list->addItem(listitem13);
    
	lay->addWidget(list);
	lay->addLayout(bottom);


	this->setLayout(lay);

}

ShortcutText::~ShortcutText()
{

}
