#include <utils/Logger.h>

#include <phonon/BackendCapabilities>
#include <phonon/Effect>
#include <phonon/EffectParameter>

#include "EqWidget.h"
#include "EqEffect.h"
#include "ui_equalizer.h"

EqWidget::EqWidget(EqEffect* eqEffect, QWidget* parent)
	: QWidget(parent)
	, m_equalizerUi( new Ui::Equalizer )
{
	m_equalizerUi->setupUi( this );
	m_equalizerUi->tab_2->setEnabled(false);
	m_equalizerUi->tab_2->setVisible(false);

	connect( m_equalizerUi->enabled, SIGNAL( toggled(bool) ), this, SLOT( enable(bool) ) );
	connect( m_equalizerUi->reset, SIGNAL( clicked() ), this, SLOT( reset() ) );
	connect( m_equalizerUi->preamp, SIGNAL( valueChanged( int ) ), this, SLOT( setPreamp( int ) ) );
	connect( m_equalizerUi->eq_0, SIGNAL( valueChanged( int ) ), this, SLOT( setBand0( int ) ) );
	connect( m_equalizerUi->eq_1, SIGNAL( valueChanged( int ) ), this, SLOT( setBand1( int ) ) );
	connect( m_equalizerUi->eq_2, SIGNAL( valueChanged( int ) ), this, SLOT( setBand2( int ) ) );
	connect( m_equalizerUi->eq_3, SIGNAL( valueChanged( int ) ), this, SLOT( setBand3( int ) ) );
	connect( m_equalizerUi->eq_4, SIGNAL( valueChanged( int ) ), this, SLOT( setBand4( int ) ) );
	connect( m_equalizerUi->eq_5, SIGNAL( valueChanged( int ) ), this, SLOT( setBand5( int ) ) );
	connect( m_equalizerUi->eq_6, SIGNAL( valueChanged( int ) ), this, SLOT( setBand6( int ) ) );
	connect( m_equalizerUi->eq_7, SIGNAL( valueChanged( int ) ), this, SLOT( setBand7( int ) ) );
	connect( m_equalizerUi->eq_8, SIGNAL( valueChanged( int ) ), this, SLOT( setBand8( int ) ) );
	connect( m_equalizerUi->eq_9, SIGNAL( valueChanged( int ) ), this, SLOT( setBand9( int ) ) );

	preamp = -4;
	for(int i=0; i<10; i++){
		band[i] = 0;
	}

	m_effect = eqEffect;
}

void EqWidget::resizeEvent(QResizeEvent* event)
{
}

EqWidget::~EqWidget()
{
}

void EqWidget::enable(bool en)
{
	if(en)
	{
		for(int i=0; i<10; i++){
			m_effect->setEqualizer(i, preamp + band[i]);
		}
	}
	else
	{
		for(int i=0; i<10; i++){
			m_effect->setEqualizer(i, 0);
		}
	}
}

void EqWidget::reset()
{
	m_equalizerUi->preamp->setValue(-4);
	m_equalizerUi->eq_0->setValue(0);
	m_equalizerUi->eq_1->setValue(0);
	m_equalizerUi->eq_2->setValue(0);
	m_equalizerUi->eq_3->setValue(0);
	m_equalizerUi->eq_4->setValue(0);
	m_equalizerUi->eq_5->setValue(0);
	m_equalizerUi->eq_6->setValue(0);
	m_equalizerUi->eq_7->setValue(0);
	m_equalizerUi->eq_8->setValue(0);
	m_equalizerUi->eq_9->setValue(0);
	for(int i=0; i<10; i++){
		band[i] = 0;
		m_effect->setEqualizer(i, preamp + band[i]);
	}
}

void EqWidget::setPreamp(int value)
{
	preamp = value;
	for(int i=0; i<10; i++){
		m_effect->setEqualizer(i, preamp + band[i]);
	}
}

void EqWidget::setBand0(int value)
{
	int v = value;
	if(v > 0)
	{
		v /= 2;
	}
	band[0] = v;
	v += preamp;
	m_effect->setEqualizer(0, v);
}

void EqWidget::setBand1(int value)
{
	int v = value;
	if(v > 0)
	{
		v /= 2;
	}
	band[1] = v;
	v += preamp;
	m_effect->setEqualizer(1, v);
}

void EqWidget::setBand2(int value)
{
	int v = value;
	if(v > 0)
	{
		v /= 2;
	}
	band[2] = v;
	v += preamp;
	m_effect->setEqualizer(2, v);
}

void EqWidget::setBand3(int value)
{
	int v = value;
	if(v > 0)
	{
		v /= 2;
	}
	band[3] = v;
	v += preamp;
	m_effect->setEqualizer(3, v);
}

void EqWidget::setBand4(int value)
{
	int v = value;
	if(v > 0)
	{
		v /= 2;
	}
	band[4] = v;
	v += preamp;
	m_effect->setEqualizer(4, v);
}

void EqWidget::setBand5(int value)
{
	int v = value;
	if(v > 0)
	{
		v /= 2;
	}
	band[5] = v;
	v += preamp;
	m_effect->setEqualizer(5, v);
}

void EqWidget::setBand6(int value)
{
	int v = value;
	if(v > 0)
	{
		v /= 2;
	}
	band[6] = v;
	v += preamp;
	m_effect->setEqualizer(6, v);
}

void EqWidget::setBand7(int value)
{
	int v = value;
	if(v > 0)
	{
		v /= 2;
	}
	band[7] = v;
	v += preamp;
	m_effect->setEqualizer(7, v);
}

void EqWidget::setBand8(int value)
{
	int v = value;
	if(v > 0)
	{
		v /= 2;
	}
	band[8] = v;
	v += preamp;
	m_effect->setEqualizer(8, v);
}

void EqWidget::setBand9(int value)
{
	int v = value;
	if(v > 0)
	{
		v /= 2;
	}
	band[9] = v;
	v += preamp;
	m_effect->setEqualizer(9, v);
}
