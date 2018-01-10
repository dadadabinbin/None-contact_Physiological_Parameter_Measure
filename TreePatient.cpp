#include "TreePatient.h"



TreePatient::TreePatient()
	{
	}
TreePatient::~TreePatient()
	{
	}

void TreePatient::print()
{
	   qDebug()<<"date="<<date<<endl;
	   for(int i=0;i<name.size();i++)
	   {
		   qDebug()<<"name "<<i<<"="<<name.at(i)<<endl;
	   }
	   qDebug()<<endl;

}

