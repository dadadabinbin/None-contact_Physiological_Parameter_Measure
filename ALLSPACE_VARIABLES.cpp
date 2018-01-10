
//这个类用来存放全局变量
#include "ALLSPACE_VARIABLES.h"
#include <QSqlDatabase>
#include <qsqltablemodel.h>
#include <qsqlrecord.h>
#include <qsqlrelationaltablemodel.h>
#include <QSqlQuery>
#include <qvector.h>
#include "TreePatient.h"

QSqlDatabase dbUser;//这个数据库存储用户信息
QSqlDatabase dbCase;//这个数据库存储用户情况
QSqlTableModel* modelUser;
QSqlTableModel* modelCase;
QSqlDatabase db;
QVector<TreePatient*> listTreePatient;
