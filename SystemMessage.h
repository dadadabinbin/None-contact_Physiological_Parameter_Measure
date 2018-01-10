#ifndef SYSTEMMESSAGE_H
#define SYSTEMMESSAGE_H

#include <QWidget>
#include <qlistwidget.h>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <qpushbutton.h>
#include "SuggestionFeedback.h"

class SystemMessage : public QWidget
{
	Q_OBJECT

public:
	SystemMessage(QWidget *parent=0);
	~SystemMessage();
public slots:
		void onButtonLeftClicked();
		void onButtonRightClicked();
private:
	
};

#endif // SYSTEMMESSAGE_H

//#ifndef SYSTEMMESSAGE_H
//#define SYSTEMMESSAGE_H
//#include <QWidget>
//#include <qlistwidget.h>
//#include <QListWidgetItem>
//
//class HistoryLog : public QWidget
//{
//	Q_OBJECT
//
//public:
//	HistoryLog(QWidget *parent = 0);
//	~HistoryLog();
//private:
//	QList<QString> getAllFileName();
//	QPushButton* button;
//public slots:
//	void onPushButtonClicked();
//
//private:
//	//Ui::HistoryLog ui;
//};
//
//#endif 
