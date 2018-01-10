#ifndef MYUI_H
#define MYUI_H

#include <QtGui/QMainWindow>
#include <QMessageBox>
#include "ShortcutText.h"
#include "SystemMessage.h"
#include "VideoPlayer.h"
#include "AddUserData.h"
#include "ALLSPACE_VARIABLES.h"
#include "mainwindow.h"
#include "SpecialMessage.h"
#include "queue.h"
#include "HistoryUserData.h"
#include "HistoryLog.h"
#include "HistoryReport.h"
#include "RegisterAccount.h"
#include "VideoPlayer.h"
#include "PatientMessage.h"
#include "algorithm.h"

#include <QMouseEvent>
#include <QProcess>
#include <qtimer.h>
#include <qmovie.h>
#include <TextLog.h>
#include <TextReport.h>
#include <QHBoxLayout>
#include <qgroupbox.h>
#include <QVBoxLayout>
#include <cmath>
#include <fstream>
#include <QFileDialog>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <qpainter.h>
#include <qtimer.h>
#include <vector>
#include "qfouriertransformer.h"
#include "qwindowfunction.h"
#include "Drawer.h"

using namespace cv;
using namespace std;



class MyUi : public QMainWindow
{
	Q_OBJECT

public:
	MyUi(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MyUi();
public slots:
	void onAction_shortcutText();
	void onAction_systemMessage();
	void onAction_exit();
	void onAction_videoPlayer();
	void onAction_browser();
	void onAction_calc();
	void onAction_addUserData();
	void onAction_carema();
	void onAction_selectedcarema();
	void onAction_measure();
	void onAction_platform();
	void onAction_paitentManegent();
	void onAction_special();
	void onAction_queue();
	void processError (QProcess::ProcessError error);
	void onAction_test();
	void onAction_testReport();
	void onAction_historyUserData();
	void onAction_historyLog();
	void onAction_historyReport();
	void onAction_RegisterAccount();

	void onTimeOut();
	
	void videoToImage();
	void FindROI();
	void GetThreeChannel();
	void videoToImageButton();
	void FindROIButton();
	void ICA();
	void bandPass();

	void smooth();
	void getServalMax();
	void getR();
	void getBloodResult();
private:
	void mouseDoubleClickEvent(QMouseEvent *ev);
	Mat detectAndDraw( Mat& img, CascadeClassifier& cascade,double scale, bool tryflip);
	  //去均值
   void remean(cv::Mat input,cv::Mat & output);
   //白化
	   void whiten(cv::Mat input,cv::Mat &output);

	  void whiten(cv::Mat input,cv::Mat &output,cv::Mat &E,cv::Mat &D);
	 //ICA
	  void runICA(cv::Mat input, cv::Mat &output,cv::Mat &W,int snum); 
	 //得到相关系数
	  double getColrelationNum(QList<double> arrayOne,QList<double> arrayTwo);
	   //DFS将时域转频域
	 QList<double> timeToFrequency(QList<double>  containOneICA);
	 //时域转频域相关函数
	 QList<double> bandPassFilter(QList<double> &FFRresult,double radius,double radius2);
	 //得到呼吸频率
	 double getBreathe(QList<double> &FFRresult,double radius,double radius2);

    string videoName;
	vector<Mat> roi_list;
	QLabel* label;
	QWidget* paintWidget;
	int framesCount;
	int faceSizeFuncControl;
	int faceSizeCount;
	int sumWidth;
	int sumHight;
	int sumRectx;
	int sumRecty;
	void Image_to_video();
	int myframeH;
	int myframeW;
	int myfps;
	int mynumFrames;
	//存中心点数值
	QVector<int> widthVector,lengthVector;
	//存长宽数值
	QVector<int> widthToVector,heightVector;
	 float* samples;//存放幅值数据
     float* fft;
	  int SIZE;//标记点的个数
	   QList<double> FFRresult;//存放时域转频域结果
	 	
 //将图片ROI分离三个彩色通道，加入对应序列中
   QList<double>  containBlue,containRed,containGreen;
	   //存放ICA后的三个通道
  QList<double>  containOneICA,containTwoICA,containThreeICA;


     //求血氧饱和度
  	 QList<double> containBlueLater;
	 QList<double> containRedLater;

	 double IdcRed;
	 double IdcBlue;
	 QList<double> blueMaxArray;
	 QList<double> redMaxArray;
	 double blueMaxArrayAverage;
	 double redMaxArrayAverage;
	 double R;
	 double result;

	 QList<double>  smoothFilter(QList<double> list);
	 double  getAverage(QList<double> list);
	 QList<double>  getMaxArray(QList<double> list);

private:

	QProcess browserProcess;
	QProcess* caremaProcess;
	QTimer* timeClock;
	QMovie* movie;
	QMovie* background;
	QLabel* labeltime;

	QPushButton* button1;
	QPushButton* button2;
	QPushButton* button3;
	QPushButton* button4;
	QPushButton* button5;
	QPushButton* button6;
	QPushButton* button7;
	QPushButton* button8;
	QPushButton* button9;

	QPushButton* button21;
	QPushButton* button22;
	QPushButton* button23;

	QLineEdit* heartResult;
	QLineEdit* breathe;
	QLineEdit* bloodResult;

};

#endif // MYUI_H
