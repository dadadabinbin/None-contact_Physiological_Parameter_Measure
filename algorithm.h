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
//		//将视频转化成序列图片
//	static int VideoToImage() //char* videoName,char* outDir,char* imgExt,int maxFrameCount
//	{
//			//删除目录下所有照片
//			QDir d("D:\\programtext\\opencv\\4-20demo1\\PictureSequence");
//			d.setFilter(QDir::Files);
//			int fileNum,fileSumNum=d.count()-1;
//			for (fileNum=0;fileNum<=fileSumNum;fileNum++)
//				d.remove(d[fileNum]);
//			//视频变成帧序列
//			int framesCount=1500;//设置照片数目
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
//			 char cur_fn[255];//保存当前帧所得图片的文件名
//			 IplImage* pImg=NULL;
//			 int frame=0;
//			 while((pImg=cvQueryFrame(cap))!=NULL&&(frame<framesCount))
//			 {               
//			  frame++;
//			  qDebug()<<"frame="<<frame<<endl;
//			  strcpy_s(cur_fn,"");
//			  sprintf_s(cur_fn,"%s%d%s",outDir,frame,".jpg");//这里的设置适合形如 123.jpg 124.jpg的图片序列
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
//		//建立用于存放人脸的向量容器
//		vector<Rect> faces, faces2;
//		//定义一些颜色，用来标示不同的人脸
//		const static Scalar colors[] =  { CV_RGB(0,0,255),
//			CV_RGB(0,128,255),
//			CV_RGB(0,255,255),
//			CV_RGB(0,255,0),
//			CV_RGB(255,128,0),
//			CV_RGB(255,255,0),
//			CV_RGB(255,0,0),
//			CV_RGB(255,0,255)} ;
//		//建立缩小的图片，加快检测速度
//		//nt cvRound (double value) 对一个double型的数进行四舍五入，并返回一个整型数！
//		Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );
//		//转成灰度图像，Harr特征基于灰度图
//		cvtColor( img, gray, CV_BGR2GRAY );
//		//改变图像大小，使用双线性差值
//		cv::resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
//		//变换后的图像进行直方图均值化处理
//		equalizeHist( smallImg, smallImg );
//
//		//程序开始和结束插入此函数获取时间，经过计算求得算法执行时间
//		t = (double)cvGetTickCount();
//		//检测人脸
//		//detectMultiScale函数中smallImg表示的是要检测的输入图像为smallImg，faces表示检测到的人脸目标序列，1.1表示
//		//每次图像尺寸减小的比例为1.1，2表示每一个目标至少要被检测到3次才算是真的目标(因为周围的像素和不同的窗口大
//		//小都可以检测到人脸),CV_HAAR_SCALE_IMAGE表示不是缩放分类器来检测，而是缩放图像，Size(30, 30)为目标的
//		//最小最大尺寸
//		cascade.detectMultiScale( smallImg, faces,
//			1.1, 2, 0
//			//|CV_HAAR_FIND_BIGGEST_OBJECT
//			//|CV_HAAR_DO_ROUGH_SEARCH
//			|CV_HAAR_SCALE_IMAGE
//			,
//			Size(30, 30));
//		//如果使能，翻转图像继续检测
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
//				//标示人脸时在缩小之前的图像上标示，所以这里根据缩放比例换算回去
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
//			//训练好的文件名称，放置在可执行文件同目录下
//			cascade.load("D:\\opencv3.2\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt2.xml");
//
//			QDir dir("D:\\programtext\\opencv\\4-20demo1\\PictureSequence\\");
//			QFileInfoList list=dir.entryInfoList();
//
//	
//			//得到图片ROI
//			int i=2;
//			roi_list.clear();
//			faceSizeCount=7;
//			//固定黄色区域
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
//			//得到图片ROI
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
