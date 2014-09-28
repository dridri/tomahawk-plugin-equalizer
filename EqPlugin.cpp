#include <QCoreApplication>
#include <boost/bind.hpp>
#include <ViewManager.h>

#include "EqPlugin.h"
#include "EqWidget.h"

#include <stdint.h>
#include <math.h>

#define min(a, b) ((a) <= (b)) ? (a) : (b)
#define max(a, b) ((a) >= (b)) ? (a) : (b)

#define BANDS_COUNT 1024

extern "C" {
void fft3_forward(short* buf, int len, int N, float* re, float* im, int stride);
void fft3_inverse(float* re, float* im, int len, int N, short* buf, int stride);
}

static Tomahawk::Widgets::EqPlugin* plugin_instance = 0;

Tomahawk::Widgets::EqPlugin* Tomahawk::Widgets::EqPlugin::instance()
{
	return plugin_instance;
}

Tomahawk::Widgets::EqPlugin::EqPlugin()
{
	tDebug() << Q_FUNC_INFO;
	plugin_instance = this;

	bandcount = BANDS_COUNT;
	bands = new float[bandcount];
	for ( int i = 0 ; i < bandcount ; i++ )
	{
		bands[ i ] = 1.0f;
	}

	AudioEngine::instance()->setDspCallback(&Tomahawk::Widgets::EqPlugin::DSPEntry);
}


Tomahawk::Widgets::EqPlugin::~EqPlugin()
{
	tDebug() << Q_FUNC_INFO;
}



const QString Tomahawk::Widgets::EqPlugin::defaultName()
{
	tDebug() << Q_FUNC_INFO;
	return "equalizer";
}

QString Tomahawk::Widgets::EqPlugin::title() const
{
	tDebug() << Q_FUNC_INFO;
	return "256 bands Equalizer";
}

QString Tomahawk::Widgets::EqPlugin::description() const
{
	tDebug() << Q_FUNC_INFO;
	return QString();
}

const QString Tomahawk::Widgets::EqPlugin::pixmapPath() const
{
	tDebug() << Q_FUNC_INFO;
	return ( RESPATH "images/eq_icon.png" );
}

void
Tomahawk::Widgets::EqPlugin::setPreamp(float value)
{
//	tDebug() << Q_FUNC_INFO;
	preamp = value;
}


void
Tomahawk::Widgets::EqPlugin::setBand(int b, float value)
{
//	tDebug() << Q_FUNC_INFO;
	bands[b] = value;
}


void
Tomahawk::Widgets::EqPlugin::DSPEntry(signed short* samples, int nb_channels, int nb_samples)
{
	Tomahawk::Widgets::EqPlugin::instance()->DSP(samples, nb_channels, nb_samples);
}

void
Tomahawk::Widgets::EqPlugin::DSP(signed short* samples, int nb_channels, int nb_samples)
{
	int i;
	uint32_t j;
	uint32_t k;

	static short buffer[2048 * 2 * 4] = { 0 };
	static short last_buffer[2048 * 2 * 4] = { 0 };
	static float re[2048 * 2 * 4] = { 0.0 };
	static float im[2048 * 2 * 4] = { 0.0 };
	static float last_re[2048 * 2 * 4] = { 0.0 };


	memcpy(buffer, &last_buffer[nb_samples*nb_channels], 896*nb_channels*sizeof(short));
	memcpy(&buffer[896*2], samples, nb_samples*nb_channels*sizeof(short));
	memcpy(last_buffer, buffer, 2048*nb_channels*sizeof(short));

	for ( i = 0 ; i < nb_channels ; i++ )
	{
		fft3_forward(&buffer[i], 2048, 12, re, im, nb_channels);
/*
 	// LINEAR EQUALIZER
		for(j=0; j<BANDS_COUNT; j++){
			uint32_t range = 1024 / BANDS_COUNT;
			for(k=0; k<range; k++){
				re[j * range + k] *= bands[j];
				im[j * range + k] *= bands[j];
			}
		}
*/
 	// LOGARITHMIC EQUALIZER
		for(j=0; j<BANDS_COUNT/4; j++){
		//	uint32_t start = (uint32_t)( powf((float)j, 1.4f) - 1.0f );
		//	uint32_t range = (uint32_t)( powf((float)j + 1.0f, 1.4f) - 1.0f );
			uint32_t start = (uint32_t)( 0.75f * ((float)j / 32.0f + 1.0f) * (float)j / 2.0f );
			uint32_t range = (uint32_t)( 0.75f * ((float)(j + 1) / 32.0f + 1.0f) * ((float)j + 1.0f) / 2.0f );
			for(k=start; k < range && k < BANDS_COUNT; k++){
				//re[k] *= max(0.0f, min(2.0f, preamp + bands[j]));
				//im[k] *= max(0.0f, min(2.0f, preamp + bands[j]));
				re[k] *= max(0.0f, min(2.0f, bands[j]));
				im[k] *= max(0.0f, min(2.0f, bands[j]));
			}
		}

		if(m_widget){
		//	m_widget->visualizer()->setChannelCount(nb_channels);
		//	m_widget->visualizer()->setChannelSpectrum(i, last_re, im, 1024);
		}

		memcpy(last_re, re, 2048 * sizeof(float));

		fft3_inverse(re, im, 2048, 12, &buffer[i], nb_channels);
		
	}
	
	memcpy(samples, &buffer[448*nb_channels], sizeof(short) * nb_channels * 1152);
}


Q_EXPORT_PLUGIN2( Tomahawk::ViewPagePlugin, Tomahawk::Widgets::EqPlugin )
