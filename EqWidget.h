#ifndef EQWIDGET_H
#define EQWIDGET_H

#include <ViewPage.h>
#include <audio/AudioEngine.h>
#include <phonon/Path>
#include <phonon/Effect>

#include <QWidget>
#include <QPixmap>
#include <QResizeEvent>
#include <QShowEvent>
#include <QHideEvent>

namespace Ui {
class Equalizer;
};

class EqWidget : public QWidget, public Tomahawk::ViewPage
{
	Q_OBJECT

public:
	EqWidget( QWidget *parent = 0 );
	~EqWidget();

	bool jumpToCurrentTrack() { return false; }
	QString description() const { return QString("10-band Equalizer"); }
	QString title() const{ return QString("Equalizer"); }
	QPixmap pixmap() const { return QPixmap(); }
	Tomahawk::playlistinterface_ptr playlistInterface() const { return Tomahawk::playlistinterface_ptr(); }
	QWidget* widget(){ return this; }
	//TODO: Add the activate and deactivate methods, which can be called from  ViewManager.cpp
	//when some other page is being activated, to save the CPU cycles.
	static bool canRun(){
	  return true;
	}

public slots:
	void enable(bool en);
	void reset();
	void setPreamp(int value);
	void setBand0(int value);
	void setBand1(int value);
	void setBand2(int value);
	void setBand3(int value);
	void setBand4(int value);
	void setBand5(int value);
	void setBand6(int value);
	void setBand7(int value);
	void setBand8(int value);
	void setBand9(int value);

protected:
	void resizeEvent(QResizeEvent* event);
	void paintEvent(QPaintEvent* ){;}//Will be taken Care by the Rendering thread
	void hideEvent(QHideEvent* ){;}
	void showEvent(QShowEvent* ){;}

private:
	Ui::Equalizer* m_equalizerUi;
	int preamp;
	int band[10];
};
#endif // EQWIDGET_H
