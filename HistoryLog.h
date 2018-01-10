#ifndef HISTORYLOG_H
#define HISTORYLOG_H

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
//#include "ui_HistoryLog.h"

class HistoryLog : public QWidget
{
	Q_OBJECT

public:
	HistoryLog(QWidget *parent = 0);
	~HistoryLog();
private:
	QList<QString> getAllFileName();
	QPushButton* button;
public slots:
	void onPushButtonClicked();

private:
	//Ui::HistoryLog ui;
};

#endif // HISTORYLOG_H
