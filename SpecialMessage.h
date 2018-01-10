#ifndef SPECIALMESSAGE_H
#define SPECIALMESSAGE_H

#include <QWidget>
#include "ALLSPACE_VARIABLES.h"
#include <qkeyeventtransition.h>
#include <QKeyEvent>
#include "ALLSPACE_VARIABLES.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qlabel.h>
#include <qtableview.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class QSqlTableModel;

class SpecialMessage : public QWidget
{
	Q_OBJECT

public:
	SpecialMessage(QWidget *parent = 0);
	~SpecialMessage();

public slots:
	void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

	void slotModelDataChanged(QModelIndex,QModelIndex);

	void slotFilterChanged(QString filter);

private:

	QSqlTableModel *model;
	QTableView* tableView;

	QLineEdit* lineEdit;
	QPushButton* pushButton;
	QPushButton* pushButton_2;
	QPushButton* pushButton_3;
	QPushButton* pushButton_4;
	QPushButton* pushButton_5;
};

#endif // SPECIALMESSAGE_H