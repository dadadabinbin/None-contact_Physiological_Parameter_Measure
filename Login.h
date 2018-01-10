#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qformlayout.h>
#include "Welcome.h"

class Login : public QWidget
{
	Q_OBJECT

public:
	Login(QWidget *parent = 0);
	~Login();
public slots:
	void onPushBottonClicked();
private:
	//Ui::Login ui;

	QPushButton* pushButton;
	QLineEdit* LineEdit;
	QLineEdit* LineEdit_2;
	Welcome* welcome;
};

#endif // LOGIN_H
