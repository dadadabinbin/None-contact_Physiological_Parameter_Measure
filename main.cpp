//#include "MyUi.h"
#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <qsqldatabase.h>
#include <qstringlist.h>
#include <qdebug.h>
#include <qsqlerror.h>
#include "ALLSPACE_VARIABLES.h"
#include <qmessagebox.h>
#include "connection.h"
#include "Login.h"
#include "PatientMessage.h"


int main(int argc,char* argv[])
{

	QApplication a(argc, argv);
	QTextCodec* pCodec=QTextCodec::codecForName("System");//获取系统字体编码
	QTextCodec::setCodecForLocale(pCodec);
	QTextCodec::setCodecForCStrings(pCodec);
	QTextCodec::setCodecForTr(pCodec);
	//QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	//连接数据库
	if (!createConnection()) return 1;

	Login w;
	w.show();

	//MyUi w;
	//w.show();
	return a.exec();
}


