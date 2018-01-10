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
	  //ȥ��ֵ
   void remean(cv::Mat input,cv::Mat & output);
   //�׻�
	   void whiten(cv::Mat input,cv::Mat &output);

	  void whiten(cv::Mat input,cv::Mat &output,cv::Mat &E,cv::Mat &D);
	 //ICA
	  void runICA(cv::Mat input, cv::Mat &output,cv::Mat &W,int snum); 
	 //�õ����ϵ��
	  double getColrelationNum(QList<double> arrayOne,QList<double> arrayTwo);
	   //DFS��ʱ��תƵ��
	 QList<double> timeToFrequency(QList<double>  containOneICA);
	 //ʱ��תƵ����غ���
	 QList<double> bandPassFilter(QList<double> &FFRresult,double radius,double radius2);
	 //�õ�����Ƶ��
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
	//�����ĵ���ֵ
	QVector<int> widthVector,lengthVector;
	//�泤����ֵ
	QVector<int> widthToVector,heightVector;
	 float* samples;//��ŷ�ֵ����
     float* fft;
	  int SIZE;//��ǵ�ĸ���
	   QList<double> FFRresult;//���ʱ��תƵ����
	 	
 //��ͼƬROI����������ɫͨ���������Ӧ������
   QList<double>  containBlue,containRed,containGreen;
	   //���ICA�������ͨ��
  QList<double>  containOneICA,containTwoICA,containThreeICA;


     //��Ѫ�����Ͷ�
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
