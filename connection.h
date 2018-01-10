#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>
#include "ALLSPACE_VARIABLES.h"
#include <qdebug.h>
#include "TreePatient.h"

static bool createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("wxj.db");
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1",
            "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);
	// 创建病人时间信息表
	qDebug()<<"create time db "<<query.exec("create table patientTime(time varchar(30),name varchar(20) )");
	
    // 创建病人信息表
	qDebug()<<"create patient db "<<query.exec("create table patient(name varchar(20) primary key,ID varchar(20),age varchar(20),sex varchar(4),nation varchar(20),"
	"instrument varchar(20),time varchar(30),housenum varchar(30))");
  /*  query.exec(QString("insert into student values(1, '李强', 11)"));
    query.exec(QString("insert into student values(2, '马亮', 11)"));
    query.exec(QString("insert into student values(3, '孙红', 12)"));*/
	 // 创建病人病情信息表
	qDebug()<<"create case db "<<query.exec("create table singlecase(singlename varchar(20) primary key,houseID varchar(20),impress varchar(200),special varchar(200))");
	//query.exec(QString("insert into singlecase values( '李强', 11,'好'，'可以')"));
    // query.exec(QString("insert into singlecase values( '马亮', 11,'好'，'可以')"));
    // query.exec(QString("insert into singlecase values( '孙红', 12,'好'，'可以')"));
	 // 创建登陆用户
	qDebug()<<"create softwareUser db "<<query.exec("create table softwareUser(userName varchar(20) primary key,password varchar(20) )");
	//qDebug()<<"create user and password "<<query.exec(QString("insert into softwareUser values( '汪秀军', 666)"));

	QString cmdPatientTime;
	cmdPatientTime="select * from patientTime";
	qDebug()<<"hehe23"<<cmdPatientTime<<endl;
	qDebug()<<"hehe234"<<query.exec(cmdPatientTime);

	query.first();
	do{
			//qDebug() << query.value(0).toString()<<endl;
			//qDebug() << query.value(1).toString()<<endl;
		    int i=0;
			for(;i<listTreePatient.size();i++)
			{
				if(listTreePatient.at(i)->date==query.value(0).toString())
				{
					listTreePatient.at(i)->name.push_back(query.value(1).toString());
					break;
				}

			}
			if(i==listTreePatient.size())
			{
					TreePatient* treePatient=new TreePatient;
					treePatient->date=query.value(0).toString();
					treePatient->name.push_back(query.value(1).toString());
					listTreePatient.push_back(treePatient);
			}

	}
	while(query.next());

	for(int i=0;i<listTreePatient.size()-1;i++)
	{
		for(int j=i+1;j<listTreePatient.size();j++)
		{
			QStringList list1 = listTreePatient.at(i)->date.split("/");
			QStringList list2 = listTreePatient.at(j)->date.split("/");
#if 0
			for(int k=0;k<list1.size();k++)
			{
				qDebug()<<list1.at(k)<<endl;
				qDebug()<<list2.at(k)<<endl;
			}
#endif
			if(list1.at(0).toInt()<list2.at(0).toInt())
			{
				TreePatient* temp=new TreePatient;
				temp->date=listTreePatient[i]->date;
				for(int k=0;k<listTreePatient[i]->name.size();k++)
				{
					temp->name.push_back(listTreePatient[i]->name.at(k));
				}
				listTreePatient[i]->date=listTreePatient[j]->date;
				listTreePatient[i]->name.clear();
				for(int k=0;k<listTreePatient[j]->name.size();k++)
				{
					listTreePatient[i]->name.push_back(listTreePatient[j]->name.at(k));
				}
				listTreePatient[j]->date=temp->date;
				listTreePatient[j]->name.clear();
				for(int k=0;k<temp->name.size();k++)
				{
					listTreePatient[j]->name.push_back(temp->name.at(k));
				}

			}
			else if((list1.at(0).toInt()==list2.at(0).toInt())&&(list1.at(1).toInt()<list2.at(1).toInt()))
			{
					TreePatient* temp=new TreePatient;
					temp->date=listTreePatient[i]->date;
					for(int k=0;k<listTreePatient[i]->name.size();k++)
					{
						temp->name.push_back(listTreePatient[i]->name.at(k));
					}
					listTreePatient[i]->date=listTreePatient[j]->date;
					listTreePatient[i]->name.clear();
					for(int k=0;k<listTreePatient[j]->name.size();k++)
					{
						listTreePatient[i]->name.push_back(listTreePatient[j]->name.at(k));
					}
					listTreePatient[j]->date=temp->date;
					listTreePatient[j]->name.clear();
					for(int k=0;k<temp->name.size();k++)
					{
						listTreePatient[j]->name.push_back(temp->name.at(k));
					}
			}
			else if((list1.at(0).toInt()==list2.at(0).toInt())&&(list1.at(1).toInt()==list2.at(1).toInt())&&(list1.at(2).toInt()<list2.at(2).toInt()))
			{
					TreePatient* temp=new TreePatient;
					temp->date=listTreePatient[i]->date;
					for(int k=0;k<listTreePatient[i]->name.size();k++)
					{
						temp->name.push_back(listTreePatient[i]->name.at(k));
					}
					listTreePatient[i]->date=listTreePatient[j]->date;
					listTreePatient[i]->name.clear();
					for(int k=0;k<listTreePatient[j]->name.size();k++)
					{
						listTreePatient[i]->name.push_back(listTreePatient[j]->name.at(k));
					}
					listTreePatient[j]->date=temp->date;
					listTreePatient[j]->name.clear();
					for(int k=0;k<temp->name.size();k++)
					{
						listTreePatient[j]->name.push_back(temp->name.at(k));
					}

			}


		}
	}
#if 0
	for(int i=0;i<listTreePatient.size();i++)
	{
		listTreePatient.at(i)->print();
	}
#endif





	return true;

  
}


#endif // CONNECTION_H
