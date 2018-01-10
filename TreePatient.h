#pragma once

#include <qlist.h>
#include <qstring.h>
#include <QDebug>

class TreePatient
{
public:
	TreePatient();
	~TreePatient();
     QString date;
	 QList<QString> name;
	 void print();
	 
};
