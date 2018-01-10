#ifndef REGISTERACCOUNT_H
#define REGISTERACCOUNT_H

#include <QWidget>
//#include "ui_RegisterAccount.h"
#include "ALLSPACE_VARIABLES.h"
#include <qformlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qlineedit.h>

class RegisterAccount : public QWidget
{
	Q_OBJECT

public:
	RegisterAccount(QWidget *parent = 0);
	~RegisterAccount();
public slots:
    void onPushButtonClicked();

private:
	//Ui::RegisterAccount ui;
	QLineEdit* LineEdit;
	QLineEdit* LineEdit_2;
	
};

#endif // REGISTERACCOUNT_H
