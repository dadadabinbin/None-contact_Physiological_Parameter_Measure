
//������������ȫ�ֱ���
#include "ALLSPACE_VARIABLES.h"
#include <QSqlDatabase>
#include <qsqltablemodel.h>
#include <qsqlrecord.h>
#include <qsqlrelationaltablemodel.h>
#include <QSqlQuery>
#include <qvector.h>
#include "TreePatient.h"

QSqlDatabase dbUser;//������ݿ�洢�û���Ϣ
QSqlDatabase dbCase;//������ݿ�洢�û����
QSqlTableModel* modelUser;
QSqlTableModel* modelCase;
QSqlDatabase db;
QVector<TreePatient*> listTreePatient;
