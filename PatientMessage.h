#ifndef PATIENTMESSAGE_H
#define PATIENTMESSAGE_H

#include <QWidget>
#include <QTableView>
#include <QSqlTableModel>
#include <QTreeWidgetItem>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qgroupbox.h>
#include <qformlayout.h>
#include <qregexp.h>
#include <QLabel>
#include <qlineedit.h>
#include <QMessageBox>
#include <QTreeWidget>
#include "ALLSPACE_VARIABLES.h"
#include "SpecialMessage.h"
#include "mainwindow.h"

class PatientMessage : public QWidget
{
	Q_OBJECT

public:
	PatientMessage(QWidget *parent=0);
	~PatientMessage();

private:
	QTableView* tableView;
	QSqlTableModel* model;
	QLineEdit* lineEdit1;
	QLineEdit* lineEdit2;
	QLineEdit* lineEdit3;
	QLineEdit* lineEdit4;
	QLineEdit* lineEdit5;
	QLineEdit* lineEdit6;
	QLineEdit* lineEdit7;
	QLineEdit* lineEdit8;
	QLineEdit* lineEdit9;

	QTextBrowser* lineEdit11;
	QTextBrowser* lineEdit12;

public slots:
		void onTreeView(QTreeWidgetItem* item,int column);
	
};

#endif // PATIENTMESSAGE_H
