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
	QLabel* label=new QLabel(tr("<h3>���˲�������������ݿ�ʵʱͬ����</h3>"));
	top->addStretch();
	top->addWidget(label);
	top->addStretch();
	lay->addLayout(top);
	tableView=new QTableView();
	lay->addWidget(tableView);
	QHBoxLayout* bottom=new QHBoxLayout();
	lineEdit=new QLineEdit();
	 pushButton=new QPushButton(tr("����"));
	 pushButton_2=new QPushButton(tr("ɾ��ѡ����"));
	 pushButton_3=new QPushButton(tr("�����޸�"));
	 pushButton_4=new QPushButton(tr("�ύ���ݿ�"));
	// pushButton_5=new QPushButton(tr("��ʾȫ��"));
	bottom->addWidget(lineEdit);
	bottom->addStretch();
	//bottom->addWidget(pushButton_5);
	bottom->addWidget(pushButton);
	bottom->addWidget(pushButton_2);
	bottom->addWidget(pushButton_3);
	bottom->addWidget(pushButton_4);
	lay->addLayout(bottom);
	this->setWindowTitle(tr("�û��������"));
	this->setWindowIcon(QIcon("./Resources/special.png"));
	this->resize(800,500);

	//ui->setupUi(this);
	model = new QSqlTableModel(this);
    model->setTable("singlecase");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // ���ñ༭����
	model->setHeaderData(0, Qt::Horizontal, "����");
    model->setHeaderData(1, Qt::Horizontal, "סԺ����");
    model->setHeaderData(2, Qt::Horizontal, "�ٴ�ӡ��");
	model->setHeaderData(3, Qt::Horizontal, "�û��������");


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
// �ύ���ݿⰴť
void SpecialMessage::on_pushButton_4_clicked()
{
    // ��ʼ�������
    model->database().transaction();
    if (model->submitAll()) {
		//QMessageBox*  commitSuccess=new QMessageBox;
		//commitSuccess->setWindowIcon(QIcon(":/commitSuccess.ico"));
		//commitSuccess->setWindowTitle(tr("�ύ�ɹ�"));
		//commitSuccess->setText(tr("��ϲ��ͬ�����ݿ�ɹ���"));
		//commitSuccess->show();
		QMessageBox::information(this,tr("��ʾ"),tr("��ϲ�����ݿ�ͬ���ɹ���"));
        model->database().commit(); //�ύ
    } else {
        model->database().rollback(); //�ع�
        QMessageBox::warning(this, tr("����"),
                             tr("���ݿ����: %1").arg(model->lastError().text()));
    }
}

// �����޸İ�ť
void SpecialMessage::on_pushButton_3_clicked()
{
    model->revertAll();
}


// ��ʾȫ����ť
void SpecialMessage::on_pushButton_5_clicked()
{
    model->setTable("case");
    model->select();
}


// ɾ��ѡ���а�ť
void SpecialMessage::on_pushButton_2_clicked()
{
    // ��ȡѡ�е���
    int curRow =tableView->currentIndex().row();

    // ɾ������
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("ɾ����ǰ��!"),
                  tr("��ȷ��ɾ����ǰ����"),QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    { // �����ɾ��������
        model->revertAll();
    } else { // �����ύ�������ݿ���ɾ������
        model->submitAll();
    }
}

// ���Ӽ�¼��ť
void SpecialMessage::on_pushButton_clicked()
{
    // ��ñ�������
    //int rowNum = model->rowCount();
    //int id = 10;
    //// ����һ��
    //model->insertRow(rowNum);
    //model->setData(model->index(rowNum,0), id);
    // ����ֱ���ύ
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

