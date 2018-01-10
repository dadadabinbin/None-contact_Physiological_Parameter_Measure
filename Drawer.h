#ifndef DRAWER_H
#define DRAWER_H

#include <QtGui/QWidget>
#include <qwt_plot.h>
#include <qwt_text.h>
#include <qfont.h>
#include <QPointF>
#include <qdebug.h>
#include <QVector>
#include <qwt_series_data.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_picker_machine.h>
#include <qwt_legend.h>



class Drawer : public QWidget
{
	Q_OBJECT

public:
	Drawer(QList<double> containBlue,QString title,double interval=0.0,QWidget *parent = 0);
	~Drawer();
public slots:
	void  qwtPlotTest();
private:
	 QList<double> containBlue;
	 QwtPlot* qwtPlot;
	 QString carveTitle;
	 QwtPlotPicker* picker;

	 double drawerInterval;

};


#endif // DRAWER_H
