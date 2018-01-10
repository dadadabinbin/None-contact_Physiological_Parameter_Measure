#include "Welcome.h"
#include <qmovie.h>
#include <QHBoxLayout>

Welcome::Welcome(QWidget *parent)
	: QWidget(parent)
{
	 timer=new QTimer;
	 timer->setInterval(10000);
	 this->showFullScreen();
	 QHBoxLayout* main=new QHBoxLayout(this);
	 label=new QLabel;	 
	 main->addWidget(label);
	 label->resize(this->width(),this->height());
	 movie=new QMovie(label);
	 movie->setFileName("./Resources/welcomeGUI.gif");
	 // 设置动画大小为标签的大小
	 QSize size=label->size();
	 movie->setScaledSize(size);
	 label->setMovie(movie);
	 movie->start();
	 timer->start();
	
	 connect(timer,SIGNAL(timeout()),this,SLOT(onfinished()));
}

void  Welcome::onfinished()
{

				mainUI=new MyUi;
				this->close();
				mainUI->show();
				delete timer;
				delete movie;
}

Welcome::~Welcome()
{

}
