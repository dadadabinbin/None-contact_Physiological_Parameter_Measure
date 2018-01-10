#ifndef TESTLOG_H
#define TESTLOG_H

#include <QWidget>
#include <qgroupbox.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qdatetimeedit.h>


class TestLog : public QWidget
{
	Q_OBJECT

public:
	TestLog(QWidget *parent = 0);
	~TestLog();
public slots:
	void onPushButtonClicked();
private:

	QPushButton* pushButton;
	QLineEdit* LineEdit;
	QLineEdit* LineEdit_2;
	QLineEdit* LineEdit_3;
	QLineEdit* LineEdit_4;
	QLineEdit* LineEdit_5;
	QLineEdit* LineEdit_6;
	QLineEdit* LineEdit_7;
	QLineEdit* LineEdit_8;
	QLineEdit* LineEdit_9;
	QLineEdit* LineEdit_10;
	QLineEdit* LineEdit_11;
	QLineEdit* LineEdit_12;
	QLineEdit* LineEdit_13;
	QDateTimeEdit* DateEdit;
	QComboBox* ComboBox;
};

#endif // TESTLOG_H
