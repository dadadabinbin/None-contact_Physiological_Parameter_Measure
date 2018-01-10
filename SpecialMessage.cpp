#include "SpecialMessage.h"
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

SpecialMessage::SpecialMessage(QWidget *parent)
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
	QHBoxLayout* top=new QHBoxLayout(this);
	QLabel* label=new QLabel(tr("<h3>病人病情管理（与数据库实时同步）</h3>"));
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
	this->setWindowTitle(tr("用户病情管理"));
	this->setWindowIcon(QIcon("./Resources/special.png"));
	this->resize(800,500);

	//ui->setupUi(this);
	model = new QSqlTableModel(this);
    model->setTable("singlecase");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // 设置编辑策略
	model->setHeaderData(0, Qt::Horizontal, "姓名");
    model->setHeaderData(1, Qt::Horizontal, "住院号码");
    model->setHeaderData(2, Qt::Horizontal, "临床印象");
	model->setHeaderData(3, Qt::Horizontal, "用户特殊情况");


    tableView->setModel(model);
	tableView->setColumnWidth(0,this->width()*0.1);
	tableView->setColumnWidth(1,this->width()*0.1);
	tableView->setColumnWidth(2,this->width()*0.37);
	tableView->setColumnWidth(3,this->width()*0.37);

	connect(model,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(slotModelDataChanged(QModelIndex,QModelIndex)));

	model->select();

	connect(pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
	connect(pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
	connect(pushButton_3,SIGNAL(clicked()),this,SLOT(on_pushButton_3_clicked()));
	connect(pushButton_4,SIGNAL(clicked()),this,SLOT(on_pushButton_4_clicked()));
	//connect(pushButton_5,SIGNAL(clicked()),this,SLOT(on_pushButton_5_clicked()));
    
	connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(slotFilterChanged(QString)));

	slotModelDataChanged(QModelIndex(),QModelIndex());

}

SpecialMessage::~SpecialMessage()
{

}
// 提交数据库按钮
void SpecialMessage::on_pushButton_4_clicked()
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
void SpecialMessage::on_pushButton_3_clicked()
{
    model->revertAll();
}


// 显示全表按钮
void SpecialMessage::on_pushButton_5_clicked()
{
    model->setTable("case");
    model->select();
}


// 删除选中行按钮
void SpecialMessage::on_pushButton_2_clicked()
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
void SpecialMessage::on_pushButton_clicked()
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
void SpecialMessage::slotModelDataChanged(QModelIndex,QModelIndex)
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
void SpecialMessage::slotFilterChanged(QString filter)
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


