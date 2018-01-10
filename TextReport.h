#ifndef TESTREPORT_H
#define TESTREPORT_H

#include <QWidget>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <QTextEdit>


class TestReport : public QWidget
{
	Q_OBJECT

public:
	TestReport(QWidget *parent = 0);
	~TestReport();
public slots:
	void onPushButtonClicked();
private:

	QPushButton* pushButton;
	QLineEdit* LineEdit;
	QLineEdit* LineEdit_2;
	QLineEdit* LineEdit_3;
	QLineEdit* LineEdit_4;
	QLineEdit* LineEdit_5;
	QTextEdit* lineEditSugestion;

};

#endif // TESTREPORT_H
