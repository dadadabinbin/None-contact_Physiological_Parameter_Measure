#include "PatientMessage.h"



PatientMessage::PatientMessage(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout* main=new QVBoxLayout(this);
	QGroupBox* group=new QGroupBox;
	group->setTitle(tr("检查时间"));
	group->setAlignment(Qt::AlignHCenter);
	QVBoxLayout* top=new QVBoxLayout();
	//tableView=new QTableView();
	////tableView->resize(this->width(),600);
	////tableView->resize(this->width(),this->height());
	//model = new QSqlTableModel(this);
 //   model->setTable("patientTime");
 //   // 设置编辑策略
	//model->setHeaderData(0, Qt::Horizontal, "检查时间");
 //   model->setHeaderData(1, Qt::Horizontal, "用户姓名");
	//tableView->setModel(model);
	//tableView->setColumnWidth(0,this->width()*0.5);
	//tableView->setColumnWidth(1,this->width()*0.5); 
	//model->select();



	QTreeWidget* tree=new QTreeWidget();
	tree->setAnimated(true);
	tree->setAutoFillBackground(true);
	tree->setStyleSheet("QTreeView::branch {image:none;}"); 
	tree->setStyleSheet("QTreeView::item:hover{background-color:rgb(0,255,0,50)}" "QTreeView::item:selected{background-color:rgb(255,0,0,100)}");
	tree->setHeaderLabels(QStringList()<<tr("时间")<<tr("用户"));
	tree->setColumnWidth(0,this->width()*0.5);
	tree->setColumnWidth(1,this->width()*0.5);
	for(int i=0;i<listTreePatient.size();i++)
	{
		QString title=listTreePatient.at(i)->date;
		QTreeWidgetItem* treeWidgetItem=new QTreeWidgetItem(QStringList()<<title);
		tree->addTopLevelItem(treeWidgetItem);
		for(int j=0;j<listTreePatient.at(i)->name.size();j++)
		{
			QString titleName=listTreePatient.at(i)->name.at(j);
			treeWidgetItem->addChild(new QTreeWidgetItem(QStringList()<<titleName));
		}
	}



	top->addStretch(1);
	top->addWidget(tree,10);
	top->addStretch(1);
	group->setLayout(top);
	

	QTabWidget* tabWidgetTop=new QTabWidget;
	tabWidgetTop->resize(this->width(),this->height()*0.7);
	SpecialMessage* special=new SpecialMessage;
	MainWindow* mainwindow=new MainWindow;
	tabWidgetTop->addTab(group,QIcon("./Resources/user.png"),tr("用户列表"));
	tabWidgetTop->addTab(mainwindow,QIcon("./Resources/journal.png"),tr("全部用户信息"));
	tabWidgetTop->addTab(special,QIcon("./Resources/special.png"),tr("全部用户病情"));
	tabWidgetTop->setCurrentPage(0);
	main->addWidget(tabWidgetTop,7);
	QTabWidget* tabWidget=new QTabWidget;
	main->addWidget(tabWidget,3);
	QWidget* widgetLeft=new QWidget;
	QWidget* widgetMiddle=new QWidget;
	QWidget* widgetRight=new QWidget;
	tabWidget->addTab(widgetLeft,tr("用户基本信息1"));
	tabWidget->addTab(widgetMiddle,tr("用户基本信息2"));
	tabWidget->addTab(widgetRight,tr("用户病情信息"));
	tabWidget->setCurrentPage(0);
	

    QFormLayout* formLeft=new QFormLayout(widgetLeft);
	QFormLayout* formMiddle=new QFormLayout(widgetMiddle);
	QFormLayout* formRight=new QFormLayout(widgetRight);

	formLeft->setContentsMargins(30,20,30,20);
	formLeft->setHorizontalSpacing(30);
	formLeft->setVerticalSpacing(20);
	formMiddle->setContentsMargins(30,20,30,20);
	formMiddle->setHorizontalSpacing(30);
	formMiddle->setVerticalSpacing(20);
	formRight->setContentsMargins(30,20,30,20);
	formRight->setHorizontalSpacing(30);
	formRight->setVerticalSpacing(20);
	

	QLabel* label1=new QLabel(tr("身份证号"));
	QLabel* label2=new QLabel(tr("姓名"));
	QLabel* label3=new QLabel(tr("年龄"));
	QLabel* label4=new QLabel(tr("性别"));
	QLabel* label5=new QLabel(tr("民族"));
	QLabel* label6=new QLabel(tr("检查仪器"));
	QLabel* label7=new QLabel(tr("检查日期"));
	QLabel* label8=new QLabel(tr("科室"));
	QLabel* label10=new QLabel(tr("住院号"));
	QLabel* label11=new QLabel(tr("临床印象"));
	QLabel* label12=new QLabel(tr("用户特殊情况"));

	lineEdit1=new QLineEdit;
	lineEdit2=new QLineEdit;
	lineEdit3=new QLineEdit;
	lineEdit4=new QLineEdit;
	lineEdit5=new QLineEdit;
	lineEdit6=new QLineEdit;
	lineEdit7=new QLineEdit;
	lineEdit8=new QLineEdit;
	lineEdit9=new QLineEdit;

	lineEdit1->setReadOnly (true);
	lineEdit2->setReadOnly(true);
	lineEdit3->setReadOnly(true);
	lineEdit4->setReadOnly(true);
	lineEdit5->setReadOnly(true);
	lineEdit6->setReadOnly(true);
	lineEdit7->setReadOnly(true);
	lineEdit8->setReadOnly(true);
	lineEdit9->setReadOnly(true);

	lineEdit11=new QTextBrowser;
	lineEdit12=new QTextBrowser;

	formLeft->addRow(label1,lineEdit1);
	formLeft->addRow(label2,lineEdit2);
	formLeft->addRow(label3,lineEdit3);
	formLeft->addRow(label4,lineEdit4);
	formLeft->addRow(label5,lineEdit5);

	formMiddle->addRow(label6,lineEdit6);
	formMiddle->addRow(label7,lineEdit7);
	formMiddle->addRow(label8,lineEdit8);

	formMiddle->addRow(label10,lineEdit9);

	formRight->addRow(label11,lineEdit11);
	formRight->addRow(label12,lineEdit12);

	connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(onTreeView(QTreeWidgetItem*,int)));
}

void PatientMessage::onTreeView(QTreeWidgetItem* item,int column)
{
	QRegExp regexp("[0-9]+");
	regexp.exactMatch(item->text(column));
	if(regexp.matchedLength()==0)
	{
		QSqlQuery query(db);
       	QString cmdPatientTime;
		cmdPatientTime="select * from patient where name='";
		cmdPatientTime+=item->text(column);
		cmdPatientTime+="'";
		qDebug()<<"hehe23"<<cmdPatientTime<<endl;
		qDebug()<<"hehe234"<<query.exec(cmdPatientTime);

		query.first();
		qDebug() << query.value(0).toString()<<endl;
		qDebug() << query.value(1).toString()<<endl;
		qDebug() << query.value(2).toString()<<endl;
		qDebug() << query.value(3).toString()<<endl;
		qDebug() << query.value(4).toString()<<endl;
		lineEdit1->setText(query.value(1).toString());
		lineEdit2->setText(query.value(0).toString());
		lineEdit3->setText(query.value(2).toString());
		lineEdit4->setText(query.value(3).toString());
		lineEdit5->setText(query.value(4).toString());
		lineEdit6->setText(query.value(5).toString());
		lineEdit7->setText(query.value(6).toString());
		lineEdit8->setText(query.value(7).toString());

		QString cmdPatient;
		cmdPatient="select * from singlecase where singlename='";
		cmdPatient+=item->text(column);
		cmdPatient+="'";
		qDebug()<<"hehe23"<<cmdPatient<<endl;
		qDebug()<<"hehe234"<<query.exec(cmdPatient);

		query.last();
		qDebug() << query.value(0).toString()<<endl;
		qDebug() << query.value(1).toString()<<endl;
		qDebug() << query.value(2).toString()<<endl;
		qDebug() << query.value(3).toString()<<endl;
		lineEdit9->setText(query.value(1).toString());
		lineEdit11->setText(query.value(2).toString());
		lineEdit12->setText(query.value(3).toString());

;

	}
	
}

PatientMessage::~PatientMessage()
{

}
