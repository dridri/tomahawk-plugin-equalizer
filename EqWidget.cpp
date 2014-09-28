#include <utils/Logger.h>

#include <phonon/BackendCapabilities>
#include <phonon/Effect>
#include <phonon/EffectParameter>

#include "EqPlugin.h"
#include "EqWidget.h"
#include "GraphicEq.h"
#include "ui_equalizer.h"


EqWidget::EqWidget(QWidget* parent)
	: QWidget(parent)
	, m_equalizerUi( new Ui::Equalizer )
{
	tDebug() << Q_FUNC_INFO;
	m_equalizerUi->setupUi( this );

	m_visualizer = 0;

	connect( m_equalizerUi->enabled, SIGNAL( toggled(bool) ), this, SLOT( enable(bool) ) );
	connect( m_equalizerUi->reset, SIGNAL( clicked() ), this, SLOT( reset() ) );
	connect( m_equalizerUi->preamp, SIGNAL( valueChanged( int ) ), this, SLOT( setPreamp( int ) ) );

	reset();
}

void EqWidget::resizeEvent(QResizeEvent* event)
{
//	tDebug() << Q_FUNC_INFO;
}

EqWidget::~EqWidget()
{
	tDebug() << Q_FUNC_INFO;
}

void EqWidget::enable(bool en)
{
	tDebug() << Q_FUNC_INFO;
}

void EqWidget::reset()
{
	tDebug() << Q_FUNC_INFO;

	Tomahawk::Widgets::EqPlugin::instance()->setPreamp(0.0f);

	for(int i=0; i<Tomahawk::Widgets::EqPlugin::instance()->bandCount(); i++){
		Tomahawk::Widgets::EqPlugin::instance()->setBand(i, 1.0f);
	}

	m_equalizerUi->preamp->setValue(-4);
	m_equalizerUi->eq->repaint();
}

void EqWidget::setPreamp(int value)
{
	tDebug() << Q_FUNC_INFO;

	float v = 0.0;
	if(value >= 0){
		v = ((float)value + 128.0) / 128.0;
	}else{
		v = 1.0 + (((float)value) / 128.0);
	}
	Tomahawk::Widgets::EqPlugin::instance()->setPreamp(v);
}

