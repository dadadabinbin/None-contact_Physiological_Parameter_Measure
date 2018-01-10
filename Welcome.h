#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include <qlabel.h>
#include <qtimer.h>
#include "MyUI.h"

class Welcome : public QWidget
{
	Q_OBJECT

public:
	Welcome(QWidget *parent=0);
	~Welcome();
public slots:
	void  onfinished();
private:
	QLabel* label;
	MyUi* mainUI;
	QMovie*	movie;
	QTimer* timer;
};

#endif // WELCOME_H
