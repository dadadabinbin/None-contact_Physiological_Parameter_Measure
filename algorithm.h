//	#include <opencv2/highgui/highgui.hpp>
//	#include <opencv2/imgproc/imgproc.hpp>
//	#include <opencv2/core/core.hpp>
//	#include <opencv2/objdetect/objdetect.hpp>
//	#include <qpainter.h>
//	#include <qtimer.h>
//	#include "Drawer.h"
//	using namespace cv;
//
//    static int faceSizeFuncControl=0;
//	static int faceSizeCount=0;
//	static int sumWidth=0;
//	static int sumHight=0;
//	static int sumRectx=0;
//	static int sumRecty=0;
//	static vector<Mat> roi_list;
//
//		//����Ƶת��������ͼƬ
//	static int VideoToImage() //char* videoName,char* outDir,char* imgExt,int maxFrameCount
//	{
//			//ɾ��Ŀ¼��������Ƭ
//			QDir d("D:\\programtext\\opencv\\4-20demo1\\PictureSequence");
//			d.setFilter(QDir::Files);
//			int fileNum,fileSumNum=d.count()-1;
//			for (fileNum=0;fileNum<=fileSumNum;fileNum++)
//				d.remove(d[fileNum]);
//			//��Ƶ���֡����
//			int framesCount=1500;//������Ƭ��Ŀ
//			char* videoName="2.avi";
//			char* outDir="D:\\programtext\\opencv\\4-20demo1\\PictureSequence\\";
//
//			 CvCapture *cap= cvCaptureFromFile(videoName);
//			 if (cap==NULL)
//			 {
//
//
//			  qDebug()<<"open fail!"<<endl;
//			 }
//			 else
//			 {
//			   qDebug()<<"open success!"<<endl;
//			 }
//			 char cur_fn[255];//���浱ǰ֡����ͼƬ���ļ���
//			 IplImage* pImg=NULL;
//			 int frame=0;
//			 while((pImg=cvQueryFrame(cap))!=NULL&&(frame<framesCount))
//			 {               
//			  frame++;
//			  qDebug()<<"frame="<<frame<<endl;
//			  strcpy_s(cur_fn,"");
//			  sprintf_s(cur_fn,"%s%d%s",outDir,frame,".jpg");//����������ʺ����� 123.jpg 124.jpg��ͼƬ����
//			  cvSaveImage(cur_fn,pImg,NULL);
//			  //cvReleaseImage(&pImg);
//			 }
//
//			 cvReleaseCapture(&cap);
//			 return frame;
//	}
//
//
//	Mat detectAndDraw( Mat& img, CascadeClassifier& cascade,double scale, bool tryflip)
//	{
//		faceSizeFuncControl++;
//		int i = 0;
//		double t = 0;
//		//�������ڴ����������������
//		vector<Rect> faces, faces2;
//		//����һЩ��ɫ��������ʾ��ͬ������
//		const static Scalar colors[] =  { CV_RGB(0,0,255),
//			CV_RGB(0,128,255),
//			CV_RGB(0,255,255),
//			CV_RGB(0,255,0),
//			CV_RGB(255,128,0),
//			CV_RGB(255,255,0),
//			CV_RGB(255,0,0),
//			CV_RGB(255,0,255)} ;
//		//������С��ͼƬ���ӿ����ٶ�
//		//nt cvRound (double value) ��һ��double�͵��������������룬������һ����������
//		Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );
//		//ת�ɻҶ�ͼ��Harr�������ڻҶ�ͼ
//		cvtColor( img, gray, CV_BGR2GRAY );
//		//�ı�ͼ���С��ʹ��˫���Բ�ֵ
//		cv::resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
//		//�任���ͼ�����ֱ��ͼ��ֵ������
//		equalizeHist( smallImg, smallImg );
//
//		//����ʼ�ͽ�������˺�����ȡʱ�䣬������������㷨ִ��ʱ��
//		t = (double)cvGetTickCount();
//		//�������
//		//detectMultiScale������smallImg��ʾ����Ҫ��������ͼ��ΪsmallImg��faces��ʾ��⵽������Ŀ�����У�1.1��ʾ
//		//ÿ��ͼ��ߴ��С�ı���Ϊ1.1��2��ʾÿһ��Ŀ������Ҫ����⵽3�β��������Ŀ��(��Ϊ��Χ�����غͲ�ͬ�Ĵ��ڴ�
//		//С�����Լ�⵽����),CV_HAAR_SCALE_IMAGE��ʾ�������ŷ���������⣬��������ͼ��Size(30, 30)ΪĿ���
//		//��С���ߴ�
//		cascade.detectMultiScale( smallImg, faces,
//			1.1, 2, 0
//			//|CV_HAAR_FIND_BIGGEST_OBJECT
//			//|CV_HAAR_DO_ROUGH_SEARCH
//			|CV_HAAR_SCALE_IMAGE
//			,
//			Size(30, 30));
//		//���ʹ�ܣ���תͼ��������
//		if( tryflip )
//		{
//			flip(smallImg, smallImg, 1);
//			cascade.detectMultiScale( smallImg, faces2,
//									 1.1, 2, 0
//									 //|CV_HAAR_FIND_BIGGEST_OBJECT
//									 //|CV_HAAR_DO_ROUGH_SEARCH
//									 |CV_HAAR_SCALE_IMAGE
//									 ,
//									 Size(30, 30) );
//			for( vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); r++ )
//			{
//				faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
//			}
//		}
//		t = (double)cvGetTickCount() - t;
//	 //   qDebug( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
//		for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
//		{
//			Mat smallImgROI;
//			vector<Rect> nestedObjects;
//			Point center;
//			Scalar color = colors[i%8];
//			int radius;
//
//			double aspect_ratio = (double)r->width/r->height;
//			if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
//			{
//				//��ʾ����ʱ����С֮ǰ��ͼ���ϱ�ʾ����������������ű��������ȥ
//				center.x = cvRound((r->x + r->width*0.5)*scale);
//				center.y = cvRound((r->y + r->height*0.5)*scale);
//				radius = cvRound((r->width + r->height)*0.25*scale);
//				circle( img, center, radius, color, 3, 8, 0 );
//
//				Mat initial_img=img.clone();
//				Rect rect;
//				rect.x=cvRound((r->x+r->width*0.2)*scale);
//				rect.y=cvRound((r->y+r->height*0.5)*scale);
//				if(faceSizeFuncControl>0&&faceSizeFuncControl<faceSizeCount-1)
//				{
//					 rect.width=cvRound((r->width + r->height)*0.32*scale);
//					 rect.height=cvRound((r->width + r->height)*0.125*scale);
//
//					 sumWidth+=rect.width;
//					 sumHight+=rect.height;
//
//					  sumRectx+=rect.x;
//					  sumRecty+=rect.y;
//				}
//				else if(faceSizeFuncControl>=faceSizeCount-1)
//				{
//					rect.x=sumRectx/(faceSizeCount-2);
//					rect.y=sumRecty/(faceSizeCount-2);
//
//					rect.width=sumWidth/(faceSizeCount-2);
//					rect.height=sumHight/(faceSizeCount-2);
//
//				}			
//				rectangle( img, Point(rect.x,rect.y),Point(rect.x+rect.width,rect.y+rect.height),Scalar( 0, 255, 255 ), 3, 8 );
//
//				Mat image_roi = initial_img(rect);  
//				cv::imshow( "result", img );
//
//				return image_roi;
//			
//			}
//			else
//				rectangle( img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
//						   cvPoint(cvRound((r->x + r->width-1)*scale), cvRound((r->y + r->height-1)*scale)),
//						   color, 3, 8, 0);
//			smallImgROI = smallImg(*r);;
//	
//		}
//
//		return img;
//	}
//
//vector<Mat> findROI() //Mat& img, CascadeClassifier& cascade, double scale, bool tryflip
//	{
//			bool stop = false;
//			CascadeClassifier cascade, nestedCascade;
//			//ѵ���õ��ļ����ƣ������ڿ�ִ���ļ�ͬĿ¼��
//			cascade.load("D:\\opencv3.2\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt2.xml");
//
//			QDir dir("D:\\programtext\\opencv\\4-20demo1\\PictureSequence\\");
//			QFileInfoList list=dir.entryInfoList();
//
//	
//			//�õ�ͼƬROI
//			int i=2;
//			roi_list.clear();
//			faceSizeCount=7;
//			//�̶���ɫ����
//			for(;i<faceSizeCount;i++)  
//			{
//				QFileInfo fileInfo=list.at(i);
//				QString filename=fileInfo.path()+"/"+fileInfo.fileName();
//				//qDebug()<<"filename="<<filename<<endl;
//				string filenamestd=filename.toStdString();
//				Mat img=imread(filenamestd,1);
//				detectAndDraw( img, cascade,2,0 );	
//				if(waitKey(30) >=0)
//					 stop = true;
//			}
//			//�õ�ͼƬROI
//			for(;i<list.size();i++)  
//			{
//				QFileInfo fileInfo=list.at(i);
//				QString filename=fileInfo.path()+"/"+fileInfo.fileName();
//				//qDebug()<<"filename="<<filename<<endl;
//				string filenamestd=filename.toStdString();
//				Mat img=imread(filenamestd,1);
//				Mat ROI_img=detectAndDraw( img, cascade,2,0 );
//				roi_list.push_back(ROI_img);
//	
//				if(waitKey(30) >=0)
//					 stop = true;
//			}
//			return roi_list;
//	}
