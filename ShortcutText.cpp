#include "ShortcutText.h"
#include <qicon.h>
#include <QVBoxLayout>
#include <qlistwidget.h>
#include <qlabel.h>
#include <qaction.h>

ShortcutText::ShortcutText(QWidget *parent)
	: QWidget(parent)
{
	this->setWindowTitle(tr("快捷键说明"));
	this->setWindowIcon(QIcon("./Resources/shortcutkey.png"));
	this->resize(800,400);

	QVBoxLayout* lay=new QVBoxLayout;
	QHBoxLayout* bottom=new QHBoxLayout;
	QLabel* label=new QLabel(tr("<h3>版本号：V2.1</h3>"));
	bottom->addStretch();
	bottom->addWidget(label);
	QListWidget* list=new QListWidget;
	QListWidgetItem* listitem1= new QListWidgetItem(tr("预约排队									Ctrl+A"));
	QListWidgetItem* listitem2= new QListWidgetItem(tr("病例管理									Ctrl+B"));
	QListWidgetItem* listitem3= new QListWidgetItem(tr("特殊情况									Ctrl+Y"));
	QListWidgetItem* listitem4= new QListWidgetItem(tr("检查日志									Ctrl+D"));
	QListWidgetItem* listitem5= new QListWidgetItem(tr("检查报告									Ctrl+E"));
	QListWidgetItem* listitem6= new QListWidgetItem(tr("历史数据									Ctrl+F"));
	QListWidgetItem* listitem7= new QListWidgetItem(tr("视频播放									Ctrl+G"));
	QListWidgetItem* listitem8= new QListWidgetItem(tr("历史日志									Ctrl+H"));
	QListWidgetItem* listitem9= new QListWidgetItem(tr("历史报告									Ctrl+I"));
	//QListWidgetItem* listitem10= new QListWidgetItem(tr("注册账户									Ctrl+K"));
	QListWidgetItem* listitem11= new QListWidgetItem(tr("系统信息									Ctrl+L"));
	QListWidgetItem* listitem12= new QListWidgetItem(tr("退出系统									Ctrl+M"));
	QListWidgetItem* listitem13= new QListWidgetItem(tr("快捷说明									Ctrl+N"));
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
