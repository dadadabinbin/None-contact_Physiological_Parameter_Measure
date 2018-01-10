#include "HistoryReport.h"
#include <QStandardItemModel>
#include <qbrush.h>
#include <qfiledialog.h>


HistoryReport::HistoryReport(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);

	this->setWindowTitle(tr("用户数据管理"));
	this->setWindowIcon(QIcon("./Resources/historydata.png"));
	this->resize(800,600);

	QStandardItemModel* standardItemModel = new QStandardItemModel(this);  

	QVBoxLayout* lay=new QVBoxLayout(this);
	QHBoxLayout* top=new QHBoxLayout();
	QLabel* label=new QLabel(tr("<h3>历史用户数据</h3>"));
	top->addStretch();
	top->addWidget(label);
	top->addStretch();
	lay->addLayout(top);
	QListView* list=new QListView;
	list->setModel(standardItemModel);
	lay->addWidget(list);
	QHBoxLayout* bottom=new QHBoxLayout;
    button=new QPushButton(tr("打开本机对应文件夹"));
	bottom->addStretch();
	bottom->addWidget(button);
	lay->addLayout(bottom);

	QList<QString> filesName=getAllFileName();
	int count=filesName.size();
	 for(int i = 0; i < count; i++)  
    {  
        QStandardItem *item = new QStandardItem(filesName.at(i));  
        if(i % 2 == 1)  
        {  
            QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));  
            linearGrad.setColorAt(0, Qt::darkGreen);  
            linearGrad.setColorAt(1, Qt::yellow);  
            QBrush brush(linearGrad);  
            item->setBackground(brush);  
        } 
		if(i!=0&&i!=1)
		{
			  standardItemModel->appendRow(item);  
		}
 
    }  
	 connect(button,SIGNAL(clicked()),this,SLOT(onPushButtonClicked()));

}

void HistoryReport::onPushButtonClicked()
{
	QFileDialog* fileDialog=new QFileDialog(this);
	fileDialog->setWindowIcon(QIcon("./Resources/openfile.png"));
	fileDialog->setWindowTitle(tr("打开历史用户数据文件夹"));
	fileDialog->setDir(QDir("../testReport"));
	fileDialog->exec();

}

QList<QString> HistoryReport::getAllFileName()
{
	QDir dir("../testReport");
	QFileInfoList list=dir.entryInfoList();
	int i=0;
	QList<QString> strlist;
	for(;i<list.size();i++)  
	{
		QFileInfo fileInfo=list.at(i);
		strlist.push_back(fileInfo.fileName());
		qDebug()<<"file ="<<fileInfo.fileName()<<endl;
	}
	return strlist;
}

HistoryReport::~HistoryReport()
{

}
