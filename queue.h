#ifndef QUEUE_H
#define QUEUE_H

#include <QWidget>
//#include "ui_Queue.h"
#include <qmovie.h>
#include <QLabel>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBOxLayout>
#include <qpushbutton.h>

class Queue : public QWidget
{
	Q_OBJECT

public:
	Queue(QWidget *parent = 0);
	~Queue();
public slots:
	void onQueueClicked();
	void onLeaveClicked();
private:
	QMovie* movie;
	int sum;
	QLabel* label_4;
	QPushButton* pushButton;
	QPushButton* pushButton_2;

private:
	//Ui::Queue ui;
};

#endif // QUEUE_H
