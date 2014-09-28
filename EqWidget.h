#ifndef EQWIDGET_H
#define EQWIDGET_H

#include <ViewPage.h>
#include <utils/ImageRegistry.h>
#include <audio/AudioEngine.h>
#include <phonon/Path>
#include <phonon/Effect>

#include <QWidget>
#include <QPixmap>
#include <QResizeEvent>
#include <QShowEvent>
#include <QHideEvent>

#include "ui_equalizer.h"

class ViWidget;
/*
namespace Ui {
class Equalizer;
};
*/

class EqWidget : public QWidget, public Tomahawk::ViewPage
{
	Q_OBJECT

public:
	EqWidget( QWidget *parent = 0 );
	~EqWidget();

	bool jumpToCurrentTrack() { return false; }
	QString description() const { return QString("256-bands Equalizer"); }
	QString title() const{ return QString("Equalizer"); }
	QPixmap pixmap() const { return ImageRegistry::instance()->pixmap( RESPATH "images/eq_icon.png", QSize( 0, 0 ) ); }
	Tomahawk::playlistinterface_ptr playlistInterface() const { return Tomahawk::playlistinterface_ptr(); }
	QWidget* widget(){ printf("EqWidget::widget()\n"); fflush(stdout); return this; }
	//TODO: Add the activate and deactivate methods, which can be called from  ViewManager.cpp
	//when some other page is being activated, to save the CPU cycles.
	static bool canRun(){
	  return true;
	}
	ViWidget* visualizer() { return m_visualizer; }

public slots:
	void enable(bool en);
	void reset();
	void setPreamp(int value);

protected:
	void resizeEvent(QResizeEvent* event);
	void paintEvent(QPaintEvent* ){;}//Will be taken Care by the Rendering thread
	void hideEvent(QHideEvent* ){;}
	void showEvent(QShowEvent* ){;}

private:
	Ui::Equalizer* m_equalizerUi;
	ViWidget* m_visualizer;
};
#endif // EQWIDGET_H
