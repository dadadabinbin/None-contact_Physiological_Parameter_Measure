#ifndef HISTORYUSERDATA_H
#define HISTORYUSERDATA_H

#include <QWidget>
#include <qlist.h>
#include <qstring.h>
#include <qdir.h>
#include <qfile.h>
#include <qdebug.h>
#include <qlistview.h>
#include <QVBoxLayout>
#include <qlabel.h>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileInfoList>

//#include "ui_HistoryUserData.h"

class HistoryUserData : public QWidget
{
	Q_OBJECT

public:
	HistoryUserData(QWidget *parent = 0);
	~HistoryUserData();

private:
	QList<QString> getAllFileName();
	QPushButton* button;
public slots:
	void onPushButtonClicked();

private:
	//Ui::HistoryUserData ui;
};

#endif // HISTORYUSERDATA_H
