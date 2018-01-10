#ifndef SUGGESTIONFEEDBACK_H
#define SUGGESTIONFEEDBACK_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtextedit.h>


class SuggestionFeedback : public QWidget
{
	Q_OBJECT

public:
	SuggestionFeedback(QWidget *parent = 0);
	~SuggestionFeedback();
public slots:
		void onButtonClicked();
private:
	QTextEdit* textEidt;
	
};

#endif // SUGGESTIONFEEDBACK_H
