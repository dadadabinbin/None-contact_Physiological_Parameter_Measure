#ifndef ADDUSERDATA_H
#define ADDUSERDATA_H

//#include "ui_AddUserData.h"

#include <QWidget>
#include <qlineedit.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qdatetimeedit.h>
#include <QTextEdit>
#include <qpushbutton.h>
#include <qformlayout.h>
#include <qgroupbox.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qtabwidget.h>
#include "TreePatient.h"
#include "ALLSPACE_VARIABLES.h"

class AddUserData : public QWidget
{
	Q_OBJECT
public:
	AddUserData(QWidget *parent = 0);
	~AddUserData();
public slots:
	void onConfirmButtonClicked();
	void onClosedButtonClicked();


private:
	//Ui::AddUserDataClass ui;
	QComboBox* sexComboBox;
	QDateEdit* testDateEdit;
	QComboBox* houseComboBox;
	QLineEdit* userNameLineEdit;
	QLineEdit* userNumLineEdit;
	QLineEdit* ageLineEdit;
	QLineEdit* nationLineEdit;
	QLineEdit* IDLineEdit;
	QLineEdit* instrumentLineEdit;
	QLineEdit* numLineEdit;
    QTextEdit* caseTextEdit;
	QTextEdit* SpecialTextEdit;
	
};

#endif // ADDUSERDATA_H
