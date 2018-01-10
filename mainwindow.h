//#ifndef MAINWINDOW_H
//#define MAINWINDOW_H
//
//#include <QMainWindow>
//#include <qkeyeventtransition.h>
//#include <QKeyEvent>
//#include "ALLSPACE_VARIABLES.h"
//#include <QHBoxLayout>
//#include <QVBoxLayout>
//#include <qlabel.h>
//#include <qtableview.h>
//#include <qlineedit.h>
//#include <qpushbutton.h>
//
//class QSqlTableModel;
//
//namespace Ui {
//    class MainWindow;
//}
//
//class MainWindow : public QMainWindow
//{
//    Q_OBJECT
//
//public:
//    explicit MainWindow(QWidget *parent = 0);
//    ~MainWindow();
//private:
//	void keyPressEvent(QKeyEvent* event);
//
//private slots:
//    void on_pushButton_clicked();
//
//    void on_pushButton_2_clicked();
//
//    void on_pushButton_7_clicked();
//
//   // void on_pushButton_8_clicked();
//
//    void on_pushButton_5_clicked();
//
//    void on_pushButton_6_clicked();
//
//    void on_pushButton_4_clicked();
//
//    void on_pushButton_3_clicked();
//
//	void slotModelDataChanged(QModelIndex,QModelIndex);
//
//	void slotFilterChanged(QString filter);
//private:
//    Ui::MainWindow *ui;
//    QSqlTableModel *model;
//};
//
//#endif // MAINWINDOW_H
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

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

#endif // MAINWINDOW_H