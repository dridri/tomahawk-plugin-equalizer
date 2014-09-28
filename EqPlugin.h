#ifndef EQPLUGIN_H
#define EQPLUGIN_H

#include <ViewPagePlugin.h>
#include <ViewPageLazyLoader.h>
#include <ViewPage.h>
#include <utils/Logger.h>

#include "EqWidget.h"

namespace Tomahawk
{

namespace Widgets
{

class EqPlugin : public ViewPageLazyLoader<EqWidget>
{
	Q_PLUGIN_METADATA( IID "org.tomahawk-player.Player.ViewPagePlugin" )
	Q_OBJECT
	Q_INTERFACES( Tomahawk::ViewPagePlugin )

public:
	EqPlugin();
	virtual ~EqPlugin();

	int bandCount() { return bandcount / 4; /* divide by 4 only with logarithmic */ }
	float* getBands() { return bands; }
	void setBand(int b, float v);
	void setPreamp(float v);
	static EqPlugin* instance();

	static void DSPEntry(signed short* samples, int nb_channels, int nb_samples);

	virtual const QString defaultName();
	virtual QString title() const;
	virtual QString description() const;
	virtual const QString pixmapPath() const;

signals:
	void updateChannelCount(int);
	void updateChannelSpectrum(int, float*, float*, int);
/*
private slots:
	void addViewPageLoader();
*/
private:
	void DSP(signed short* samples, int nb_channels, int nb_samples);
	float preamp;
	float* bands;
	int bandcount;
};

}

}

#endif // EQPLUGIN_H
