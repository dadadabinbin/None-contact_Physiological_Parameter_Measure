#pragma once
#include <QSqlDatabase>
#include <qsqltablemodel.h>
#include <qsqlrecord.h>
#include <qsqlrelationaltablemodel.h>
#include <QSqlQuery>
#include "TreePatient.h"
#include <QVector>

extern QSqlDatabase dbUser;//������ݿ�洢�û���Ϣ
extern QSqlDatabase dbCase;//������ݿ�洢�û����
extern QSqlTableModel* modelUser;
extern QSqlTableModel* modelCase;
extern QSqlDatabase db;
extern QVector<TreePatient*> listTreePatient;