#pragma once
#include <QSqlDatabase>
#include <qsqltablemodel.h>
#include <qsqlrecord.h>
#include <qsqlrelationaltablemodel.h>
#include <QSqlQuery>
#include "TreePatient.h"
#include <QVector>

extern QSqlDatabase dbUser;//这个数据库存储用户信息
extern QSqlDatabase dbCase;//这个数据库存储用户情况
extern QSqlTableModel* modelUser;
extern QSqlTableModel* modelCase;
extern QSqlDatabase db;
extern QVector<TreePatient*> listTreePatient;