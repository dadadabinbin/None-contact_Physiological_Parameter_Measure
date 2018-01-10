//#include "mainwindow.h"
////#include "ui_mainwindow.h"
//#include <QSqlQueryModel>
//#include <QSqlTableModel>
//#include <QSqlRelationalTableModel>
//#include <QTableView>
//#include <QDebug>
//#include <QMessageBox>
//#include <QSqlError>
//#include <qcompleter.h>
//#include <qstringlist.h>
//#include <qmessagebox.h>
//
//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//
//	QVBoxLayout* lay=new QVBoxLayout(this);
//	QHBoxLayout* top=new QHBoxLayout(this);
//	QLabel* label=new QLabel(tr("<h3>病人病情管理（与数据库实时同步）</h3>"));
//	top->addStretch();
//	top->addWidget(label);
//	top->addStretch();
//	lay->addLayout(top);
//	tableView=new QTableView();
//	lay->addWidget(tableView);
//	QHBoxLayout* bottom=new QHBoxLayout();
//	lineEdit=new QLineEdit();
//	 pushButton=new QPushButton(tr("增加"));
//	 pushButton_2=new QPushButton(tr("删除选中行"));
//	 pushButton_3=new QPushButton(tr("撤销修改"));
//	 pushButton_4=new QPushButton(tr("提交数据库"));
//	// pushButton_5=new QPushButton(tr("显示全表"));
//	bottom->addWidget(lineEdit);
//	bottom->addStretch();
//	//bottom->addWidget(pushButton_5);
//	bottom->addWidget(pushButton);
//	bottom->addWidget(pushButton_2);
//	bottom->addWidget(pushButton_3);
//	bottom->addWidget(pushButton_4);
//	lay->addLayout(bottom);
//    model = new QSqlTableModel(this);
//    model->setTable("patient");
//	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//	 // 设置编辑策略
//	model->setHeaderData(0, Qt::Horizontal, "姓名");
//    model->setHeaderData(1, Qt::Horizontal, "身份证号码");
//    model->setHeaderData(2, Qt::Horizontal, "年龄");
//	model->setHeaderData(3, Qt::Horizontal, "性别");
//	model->setHeaderData(4, Qt::Horizontal, "民族");
//	model->setHeaderData(5, Qt::Horizontal, "检查仪器");
//	model->setHeaderData(6, Qt::Horizontal, "检查时间");
//    model->setHeaderData(7, Qt::Horizontal, "科室");
//
//	
//    ui->tableView->setModel(model);
//
//	connect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(slotModelDataChanged(QModelIndex,QModelIndex)));
//
//	model->select();
//    
//	connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(slotFilterChanged(QString)));
//
//	slotModelDataChanged(QModelIndex(),QModelIndex());
//
//	//搜索全字符串，测试
//#if 0
//	QString list;
//	for(int j=0;j<model->rowCount();j++)
//	{
//			QSqlRecord record=model->record(j);
//			for(int i=0;i<record.count();++i)
//			{
//				QVariant var=record.value(i);
//				if(var.isNull()) continue;
//				QString field=var.toString();
//				qDebug()<<"field="<<field<<endl;
//				list+=field;
//			}
//	}
//	qDebug()<<"list="<<list<<endl;
//#endif
//}
//
//MainWindow::~MainWindow()
//{
//    delete ui;
//}
//
//// 提交数据库按钮
//void MainWindow::on_pushButton_clicked()
//{
//    // 开始事务操作
//    model->database().transaction();
//    if (model->submitAll()) {
//		//QMessageBox*  commitSuccess=new QMessageBox;
//		//commitSuccess->setWindowIcon(QIcon(":/commitSuccess.ico"));
//		//commitSuccess->setWindowTitle(tr("提交成功"));
//		//commitSuccess->setText(tr("恭喜你同步数据库成功！"));
//		//commitSuccess->show();
//		QMessageBox::information(this,tr("提示"),tr("恭喜你数据库同步成功！"));
//        model->database().commit(); //提交
//    } else {
//        model->database().rollback(); //回滚
//        QMessageBox::warning(this, tr("警告"),
//                             tr("数据库错误: %1").arg(model->lastError().text()));
//    }
//}
//
//// 撤销修改按钮
//void MainWindow::on_pushButton_2_clicked()
//{
//    model->revertAll();
//}
//
//// 查询按钮，进行筛选,模糊搜索
//void MainWindow::on_pushButton_7_clicked()
//{
//    QString name = ui->lineEdit->text();
//    //根据姓名进行筛选，一定要使用单引号
//    model->setFilter(QString("name = '%1'").arg(name));
//    model->select();
//}
//
////// 显示全表按钮
////void MainWindow::on_pushButton_8_clicked()
////{
////    model->setTable("patient");
////    model->select();
////}
//
//// 按id升序排列按钮
//void MainWindow::on_pushButton_5_clicked()
//{
//    //id属性，即第0列，升序排列
//    model->setSort(0, Qt::AscendingOrder);
//    model->select();
//}
//
//// 按id降序排列按钮
//void MainWindow::on_pushButton_6_clicked()
//{
//    model->setSort(0, Qt::DescendingOrder);
//    model->select();
//}
//
//// 删除选中行按钮
//void MainWindow::on_pushButton_4_clicked()
//{
//    // 获取选中的行
//    int curRow = ui->tableView->currentIndex().row();
//
//    // 删除该行
//    model->removeRow(curRow);
//    int ok = QMessageBox::warning(this,tr("删除当前行!"),
//                  tr("你确定删除当前行吗？"),QMessageBox::Yes, QMessageBox::No);
//    if(ok == QMessageBox::No)
//    { // 如果不删除，则撤销
//        model->revertAll();
//    } else { // 否则提交，在数据库中删除该行
//        model->submitAll();
//    }
//}
//
//// 添加记录按钮
//void MainWindow::on_pushButton_3_clicked()
//{
//    // 获得表的行数
//    //int rowNum = model->rowCount();
//    //int id = 10;
//    //// 添加一行
//    //model->insertRow(rowNum);
//    //model->setData(model->index(rowNum,0), id);
//    // 可以直接提交
//    model->submitAll();
//	 model->database().transaction();
//    QSqlRecord record = model->record();
//    model->insertRecord(-1, record);
//}
//void MainWindow::slotModelDataChanged(QModelIndex,QModelIndex)
//{
//	QStringList strList;
//    for(int i=0; i<model->rowCount(); ++i)
//    {
//        QSqlRecord record = model->record(i);
//        for(int j=0; j<record.count(); ++j)
//        {
//            QVariant var = record.value(j);
//            if(var.isNull()) continue;
//            strList << var.toString();
//        }
//    }
//    qDebug() << strList;
//    QCompleter* completer=new QCompleter(strList);
//    ui->lineEdit->setCompleter(completer);
//
//}
//void MainWindow::slotFilterChanged(QString filter)
//{
//	if(filter.isEmpty())
//    {
//        model->setFilter("");
//        model->select();
//        return;
//    }
//    //  username like filter or password like  filter .......
//    QSqlRecord record = model->record();
//    QString modelFilter;
//    for(int i=0; i<record.count(); ++i)
//    {
//        if(i!=0)
//        {
//            modelFilter += " or ";
//        }
//        QString field = record.fieldName(i);
//        QString subFilter = QString().sprintf("%s like '%%%s%%'", field.toUtf8().data(), filter.toUtf8().data());
//        //  qDebug() << subFilter;
// 
//        modelFilter += subFilter;
// 
//    }
//    qDebug() << modelFilter;
//    model->setFilter(modelFilter);
//    model->select();
//
//}
//
//void MainWindow::keyPressEvent(QKeyEvent* event)
//{
//
//	if(event->key()==Qt::Key_Up)
//	{
//		
//		on_pushButton_7_clicked();
//	}
//}

#include "mainwindow.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <qcompleter.h>
#include <qstringlist.h>
#include <qmessagebox.h>
#include <QSqlQuery.h>
#include <qsqlresult.h>

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{

#if 0
	    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1",
            "Unable to establish a database connection.", QMessageBox::Cancel);
        }
		    QSqlQuery query = db.exec("select * from case");
   // int size = query.size();

    bool b = query.first();
    while(b)
    {
        QSqlResult* result = query.result();
        QVector<QVariant> values =  result->boundValues();
        qDebug() << values;
        b = query.next();
    }
#endif

	QVBoxLayout* lay=new QVBoxLayout(this);
	QHBoxLayout* top=new QHBoxLayout;
	QLabel* label=new QLabel(tr("<h4>用户信息管理（与数据库实时同步）</h4>"));
	top->addStretch();
	top->addWidget(label);
	top->addStretch();
	lay->addLayout(top);
	tableView=new QTableView();
	lay->addWidget(tableView);
	QHBoxLayout* bottom=new QHBoxLayout();
	lineEdit=new QLineEdit();
	 pushButton=new QPushButton(tr("增加"));
	 pushButton_2=new QPushButton(tr("删除选中行"));
	 pushButton_3=new QPushButton(tr("撤销修改"));
	 pushButton_4=new QPushButton(tr("提交数据库"));
	// pushButton_5=new QPushButton(tr("显示全表"));
	bottom->addWidget(lineEdit);
	bottom->addStretch();
	//bottom->addWidget(pushButton_5);
	bottom->addWidget(pushButton);
	bottom->addWidget(pushButton_2);
	bottom->addWidget(pushButton_3);
	bottom->addWidget(pushButton_4);
	lay->addLayout(bottom);
	this->setWindowTitle(tr("用户信息管理管理"));
	this->setWindowIcon(QIcon("./Resources/special.png"));
	this->resize(800,500);

	//ui->setupUi(this);
	//model = new QSqlTableModel(this);
 //   model->setTable("singlecase");
	//model->setEditStrategy(QSqlTableModel::OnManualSubmit);
 //   // 设置编辑策略
	//model->setHeaderData(0, Qt::Horizontal, "姓名");
 //   model->setHeaderData(1, Qt::Horizontal, "住院号码");
 //   model->setHeaderData(2, Qt::Horizontal, "临床印象");
	//model->setHeaderData(3, Qt::Horizontal, "用户特殊情况");
	

    model = new QSqlTableModel(this);
    model->setTable("patient");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	 // 设置编辑策略
	model->setHeaderData(0, Qt::Horizontal, "姓名");
    model->setHeaderData(1, Qt::Horizontal, "身份证号码");
    model->setHeaderData(2, Qt::Horizontal, "年龄");
	model->setHeaderData(3, Qt::Horizontal, "性别");
	model->setHeaderData(4, Qt::Horizontal, "民族");
	model->setHeaderData(5, Qt::Horizontal, "检查仪器");
	model->setHeaderData(6, Qt::Horizontal, "检查时间");
    model->setHeaderData(7, Qt::Horizontal, "科室");


    tableView->setModel(model);
	//tableView->setColumnWidth(0,this->width()*0.1);
	//tableView->setColumnWidth(1,this->width()*0.1);
	//tableView->setColumnWidth(2,this->width()*0.37);
	//tableView->setColumnWidth(3,this->width()*0.37);

	connect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(slotModelDataChanged(QModelIndex,QModelIndex)));

	model->select();

	connect(pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
	connect(pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
	connect(pushButton_3,SIGNAL(clicked()),this,SLOT(on_pushButton_3_clicked()));
	connect(pushButton_4,SIGNAL(clicked()),this,SLOT(on_pushButton_4_clicked()));
	//connect(pushButton_5,SIGNAL(clicked()),this,SLOT(on_pushButton_5_clicked()));
    
	connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(slotFilterChanged(QString)));

	slotModelDataChanged(QModelIndex(),QModelIndex());

	this->resize(900,400);

}

MainWindow::~MainWindow()
{

}
// 提交数据库按钮
void MainWindow::on_pushButton_4_clicked()
{
    // 开始事务操作
    model->database().transaction();
    if (model->submitAll()) {
		//QMessageBox*  commitSuccess=new QMessageBox;
		//commitSuccess->setWindowIcon(QIcon(":/commitSuccess.ico"));
		//commitSuccess->setWindowTitle(tr("提交成功"));
		//commitSuccess->setText(tr("恭喜你同步数据库成功！"));
		//commitSuccess->show();
		QMessageBox::information(this,tr("提示"),tr("恭喜你数据库同步成功！"));
        model->database().commit(); //提交
    } else {
        model->database().rollback(); //回滚
        QMessageBox::warning(this, tr("警告"),
                             tr("数据库错误: %1").arg(model->lastError().text()));
    }
}

// 撤销修改按钮
void MainWindow::on_pushButton_3_clicked()
{
    model->revertAll();
}


// 显示全表按钮
void MainWindow::on_pushButton_5_clicked()
{
    model->setTable("case");
    model->select();
}


// 删除选中行按钮
void MainWindow::on_pushButton_2_clicked()
{
    // 获取选中的行
    int curRow =tableView->currentIndex().row();

    // 删除该行
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                  tr("你确定删除当前行吗？"),QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    { // 如果不删除，则撤销
        model->revertAll();
    } else { // 否则提交，在数据库中删除该行
        model->submitAll();
    }
}

// 添加记录按钮
void MainWindow::on_pushButton_clicked()
{
    // 获得表的行数
    //int rowNum = model->rowCount();
    //int id = 10;
    //// 添加一行
    //model->insertRow(rowNum);
    //model->setData(model->index(rowNum,0), id);
    // 可以直接提交
    model->submitAll();
	 model->database().transaction();
    QSqlRecord record = model->record();
    model->insertRecord(-1, record);
}
void MainWindow::slotModelDataChanged(QModelIndex,QModelIndex)
{
	QStringList strList;
    for(int i=0; i<model->rowCount(); ++i)
    {
        QSqlRecord record = model->record(i);
        for(int j=0; j<record.count(); ++j)
        {
            QVariant var = record.value(j);
            if(var.isNull()) continue;
            strList << var.toString();
        }
    }
    qDebug() << strList;
    QCompleter* completer=new QCompleter(strList);
    lineEdit->setCompleter(completer);

}
void MainWindow::slotFilterChanged(QString filter)
{
	if(filter.isEmpty())
    {
        model->setFilter("");
        model->select();
        return;
    }
    //  username like filter or password like  filter .......
    QSqlRecord record = model->record();
    QString modelFilter;
    for(int i=0; i<record.count(); ++i)
    {
        if(i!=0)
        {
            modelFilter += " or ";
        }
        QString field = record.fieldName(i);
        QString subFilter = QString().sprintf("%s like '%%%s%%'", field.toUtf8().data(), filter.toUtf8().data());
        //  qDebug() << subFilter;
 
        modelFilter += subFilter;
 
    }
    qDebug() << modelFilter;
    model->setFilter(modelFilter);
    model->select();

}


