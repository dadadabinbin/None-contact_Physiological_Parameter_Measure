#include "HistoryUserData.h"
#include <QStandardItemModel>
#include <qbrush.h>
#include <qfiledialog.h>

HistoryUserData::HistoryUserData(QWidget *parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	this->setWindowTitle(tr("�û����ݹ���"));
	this->setWindowIcon(QIcon("./Resources/historydata.png"));
	this->resize(800,600);

	QStandardItemModel* standardItemModel = new QStandardItemModel(this);  

	QVBoxLayout* lay=new QVBoxLayout(this);
	QHBoxLayout* top=new QHBoxLayout();
	QLabel* label=new QLabel(tr("<h3>��ʷ�û�����</h3>"));
	top->addStretch();
	top->addWidget(label);
	top->addStretch();
	lay->addLayout(top);
	QListView* list=new QListView;
	list->setModel(standardItemModel);
	lay->addWidget(list);
	QHBoxLayout* bottom=new QHBoxLayout;
    button=new QPushButton(tr("�򿪱�����Ӧ�ļ���"));
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
void HistoryUserData::onPushButtonClicked()
{
	QFileDialog* fileDialog=new QFileDialog(this);
	fileDialog->setWindowIcon(QIcon("./Resources/openfile.png"));
	fileDialog->setWindowTitle(tr("����ʷ�û������ļ���"));
	fileDialog->setDir(QDir("../userData"));
	fileDialog->exec();

}

QList<QString> HistoryUserData:: getAllFileName()
{
	QDir dir("../userData");
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
HistoryUserData::~HistoryUserData()
{

}
