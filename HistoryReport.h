#ifndef HISTORYREPORT_H
#define HISTORYREPORT_H

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


class HistoryReport : public QWidget
{
	Q_OBJECT

public:
	HistoryReport(QWidget *parent = 0);
	~HistoryReport();

private:
	QList<QString> getAllFileName();
	QPushButton* button;
public slots:
	void onPushButtonClicked();

private:
	
};

#endif // HISTORYREPORT_H
