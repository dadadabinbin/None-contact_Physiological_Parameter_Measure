#include "Queue.h"
#include <qsize.h>
#include <QIcon>
#include <qmessagebox.h>


Queue::Queue(QWidget *parent)
	: QWidget(parent)
{
	this->setWindowTitle(tr("�Ŷ�ϵͳ"));
	this->setWindowIcon(QIcon("./Resources/line.ico"));
	this->resize(800,600);
	QVBoxLayout* lay=new QVBoxLayout(this);
	QHBoxLayout* top=new QHBoxLayout;
	QLabel* title=new QLabel(tr("<h1>�𾴵Ŀͻ�����ӭʹ��ҽ����Ƶ���ϵͳ!<h1/>"));
	top->addStretch();
	top->addWidget(title);
	top->addStretch();
	lay->addLayout(top);
	QHBoxLayout* bottom=new QHBoxLayout;
	QLabel* label_2=new QLabel();
	QVBoxLayout* right=new QVBoxLayout;
	lay->addLayout(bottom);
	bottom->addWidget(label_2);
	bottom->addLayout(right);
	
	QHBoxLayout* smalltop=new QHBoxLayout;
	QLabel* smallTopLabel=new QLabel(tr("<h2>��ǰ�Ŷ�����Ϊ</h2>"));
	label_4=new QLabel();
	smalltop->addWidget(smallTopLabel);
	smalltop->addWidget(label_4);
	right->addStretch();
	right->addLayout(smalltop);
	right->addStretch();
	QHBoxLayout* smallbottom=new QHBoxLayout;
	pushButton=new QPushButton(tr("��Ҫ�Ŷ�"));
	pushButton_2=new QPushButton(tr("��Ҫ�뿪"));
	smallbottom->addWidget(pushButton);
	smallbottom->addWidget(pushButton_2);
	right->addLayout(smallbottom);
	right->addStretch();

	//ui.setupUi(this);
	this->setWindowIcon(QIcon("./Resources/line.ico"));
	//��ʼ�����Ŷ�����Ϊ0
	sum=0;
	label_4->setText(QString::number(sum));

	movie=new QMovie(label_2);
	movie->setFileName("./Resources/queue1.gif");
	// ���û���ģʽ
	movie->setCacheMode(QMovie::CacheAll);
	// ���ö�����СΪ��ǩ�Ĵ�С
	QSize size=label_2->size();
	movie->setScaledSize(size);
	label_2->setMovie(movie);
	movie->start();

	connect(pushButton,SIGNAL(clicked()),this,SLOT(onQueueClicked()));
	connect(pushButton_2,SIGNAL(clicked()),this,SLOT(onLeaveClicked()));
}
void Queue::onQueueClicked()
{
	sum++;
	label_4->setText(QString::number(sum));
	QMessageBox::information(this,tr("�Ŷ�"),QString("�����Ŷ������%1").arg(QString::number(sum)));
	
}
void Queue::onLeaveClicked()
{
	sum-=1;
	if(sum<0)
		sum=0;
	label_4->setText(QString::number(sum));
	label_4->setTextFormat(Qt::RichText);

}

Queue::~Queue()
{

}
