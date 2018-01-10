#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <Phonon>
//#include "ui_VideoPlayer.h"
#include "ALLSPACE_VARIABLES.h"
#include <qlabel.h>
#include <qevent.h>


class QMenu;
class QAction;

class VideoPlayer : public QWidget
{
	Q_OBJECT
public:
	VideoPlayer(QWidget *parent = 0);
	~VideoPlayer();
public slots:
	void createContextMenu();
	void showContextMenu(const QPoint &pos);
	void aspectChanged(QAction* action);
	void scaleChanged(QAction* action);

	void onHorizontalSliderLightValueChanged(int value);
	void onHorizontalSliderSaturationValueChanged(int value);
	void onHorizontalSliderTingeValueChanged(int value);
	void onHorizontalSliderContractValueChanged(int value);
	void onScreenShot();
	//打开文件S
	void onOpenFileButtonClicked();

private:
	//Ui::VideoPlayer ui;
	Phonon::VideoWidget* videoWidget;
	QMenu* mainMenu;
	Phonon::MediaObject*  mediaObject;
	void closeEvent(QCloseEvent* ev);
};

#endif // VIDEOPLAYER_H
