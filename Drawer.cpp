#include "Drawer.h"
#include <qgridlayout.h>
#include <qwt_plot_grid.h>


Drawer::Drawer(const QList<double> contain,QString title,double interval,QWidget *parent)
	: QWidget(parent)
{
	carveTitle=title;
	drawerInterval=interval;
	//QGridLayout* main=new QGridLayout(this);
	qwtPlot=new QwtPlot(this);
	this->resize(1400,300);
	//this->showMaximized();
	//main->addWidget(qwtPlot,1,1);
	//main->setRowStretch(0,1);
	//main->setRowStretch(1,10);
	//main->setRowStretch(2,1);
	//main->setColumnStretch(0,1);
	//main->setColumnStretch(1,10);
	//main->setColumnStretch(2,1);

	for(int i=0;i<contain.size();i++)
	{
		containBlue.push_back(contain.at(i));
	}
     qwtPlotTest();
}
void Drawer::qwtPlotTest()
{
	(new QwtPlotPanner(qwtPlot->canvas()))->setMouseButton(Qt::RightButton);
	(new QwtPlotMagnifier(qwtPlot->canvas()))->setAxisEnabled(QwtPlot::yLeft,false);
	picker=new QwtPlotPicker(QwtPlot::xBottom,QwtPlot::yLeft,QwtPlotPicker::CrossRubberBand,QwtPicker::AlwaysOn,qwtPlot->canvas());
	picker->setStateMachine(new QwtPickerDragPointMachine());
	picker->setRubberBandPen(QPen(QColor(Qt::white)));
	picker->setTrackerPen(QColor(Qt::yellow));

	//qwtPlot->canvas()->setPalette(QPalette(QColor(QColor(Qt::darkGray))));

	int width=this->width()*0.9;
	int height=this->height()*0.9;
	//左上角移位
	qwtPlot->move(this->width()*0.03,this->height()*0.03);
	qwtPlot->resize(width,height);

	QwtText t;
	QString title=carveTitle;
	qDebug()<<"title="<<title<<endl;
	title+=tr("图像");
	t.setText(title);
	QFont font(	"宋体",12);
	//font.setBold(true);
	//font.setItalic(true);
	font.setWeight(10);
	font.setWordSpacing(100.0);
	t.textSize(font);
	t.setFont(font);
	t.setColor(QColor(0,255,0));
	//QBrush brush(QColor(0,0,255));
	//t.setBackgroundBrush(brush);

	qwtPlot->setTitle(t);
	double min=256.0;
	double max=-256.0;
	for(int i=0;i<containBlue.size();i++)
	{

		if(containBlue.at(i)<min)
		    min=containBlue.at(i);
		else if(containBlue.at(i)>max)
			max=containBlue.at(i);
	}
	qDebug()<<"min="<<min<<endl;
	qDebug()<<"max="<<max<<endl;
   //设置坐标轴
	if(drawerInterval==0.0)
	   qwtPlot->setAxisScale(QwtPlot::xBottom,0,containBlue.size(),containBlue.size()/10);
	else
	{
		qwtPlot->setAxisScale(QwtPlot::xBottom,0,containBlue.size(),containBlue.size()/10);
		/*qwtPlot->setAxisScale(QwtPlot::xBottom,0,drawerInterval*containBlue.size(),(drawerInterval*containBlue.size())/10);
		qwtPlot->setAxisAutoScale(QwtPlot::xBottom, true);
		qwtPlot->setAxisScale(QwtPlot::xBottom,0,containBlue.size(),containBlue.size()/10);*/
	}
	   
	double averageSize;
	if((max-min)>=3.0)
		averageSize=1.0;
	else if((max-min)<=1.0)
		averageSize=0.01;
	qwtPlot->setAxisScale(QwtPlot::yLeft,min,max,averageSize);
	qwtPlot->setAxisScale(QwtPlot::yLeft,min,max,(int)((max-min)/2));
	if(drawerInterval==0.0)
	   qwtPlot->setAxisTitle(QwtPlot::xBottom,tr("照片数目/张"));
	else
	   qwtPlot->setAxisTitle(QwtPlot::xBottom,tr("频率/hz"));
	
	qwtPlot->setAxisTitle(QwtPlot::yLeft,tr("结果数值"));
	qwtPlot->setAxisLabelRotation(QwtPlot::yLeft,90.0);
	QFont f("宋体",12);
	qwtPlot->setAxisFont(QwtPlot::xBottom,f);
	qwtPlot->setAxisFont(QwtPlot::yLeft,f);
	QVector<QPointF> vector;
	for(int i=0;i<containBlue.size();i++)
	{
		QPointF point;
		point.setX(i);
		point.setY(containBlue.at(i));
		vector.append(point);
	}

	QwtPointSeriesData* series=new QwtPointSeriesData(vector);

	qDebug()<<"curve title="<<title<<endl;
	QwtPlotCurve* curve=new QwtPlotCurve(title);
	curve->setData(series);
	QPen curvePen(QColor(255,0,0));
	curvePen.setWidth(3);
	curve->setPen(curvePen);
	//QBrush brush2(QColor(128,128,128));
   //curve->setBrush(brush2);
	curve->setCurveAttribute(QwtPlotCurve::Fitted,true);
	curve->setRenderHint(QwtPlotItem::RenderAntialiased,true);
	 //这个会改变曲线在QwtLegend显示的样式，可以是线，矩形，符号，  
	curve->setLegendAttribute(QwtPlotCurve::LegendShowLine);
	curve->attach(qwtPlot);

	 //这个会根据画板中的图在RightLegend显示一个图例  
    qwtPlot->insertLegend(new QwtLegend(),QwtPlot::RightLegend);  
	

	//加入网格
	QwtPlotGrid* grid=new QwtPlotGrid();
	//QPen gridPen(QColor(222,222,222));
	//gridPen.setWidth(2);
	//grid->setPen(gridPen);
	//grid->enableX(true);  
	grid->enableXMin(true);
	//grid->enableY(true);
	grid->enableYMin(true);
    grid->setMajPen(QPen(Qt::white, 0, Qt::DotLine));//大格子  
    grid->setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));//大格子里的小格子 

	grid->attach(qwtPlot);
	qwtPlot->replot();
	qwtPlot->show();

}

Drawer::~Drawer()
{

}
