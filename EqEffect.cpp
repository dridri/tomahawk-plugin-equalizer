#include <utils/Logger.h>

#include <phonon/BackendCapabilities>
#include <phonon/Effect>
#include <phonon/EffectParameter>

#include "EqEffect.h"

EqEffect::EqEffect()
{
	m_audioPath = NULL;
	m_effect = NULL;

	m_audioPath = AudioEngine::instance()->getAudioPath();
	tDebug() << "m_audioPath : " << m_audioPath;
	QList<Phonon::EffectDescription> effectDescriptions = Phonon::BackendCapabilities::availableAudioEffects();
	m_effect = NULL;
	int i=0;
	foreach(Phonon::EffectDescription effectDesc, effectDescriptions)
	{
		tDebug() << "PHONON::Effect : '" << effectDesc.name() << "'";
		if(effectDesc.name().contains("Eq") || effectDesc.name().contains("eq")){
			if(i==0){
				m_effect = new Phonon::Effect(effectDesc);
				tDebug() << "OK";
				break;
			}
		}
	}

	if(m_effect){
		tDebug() << "Effect insertion succeeded : " << m_audioPath->insertEffect(m_effect);
		setEqualizer(0, -4);
		setEqualizer(1, -4);
		setEqualizer(2, -4);
		setEqualizer(3, -4);
		setEqualizer(4, -4);
		setEqualizer(5, -4);
		setEqualizer(6, -4);
		setEqualizer(7, -4);
		setEqualizer(8, -4);
		setEqualizer(9, -4);
	}
}

EqEffect::~EqEffect()
{
}

void EqEffect::setEqualizer(int band, int value)
{
	if (m_effect)
	{
		QList<Phonon::EffectParameter> params = m_effect->parameters();
		if (band < params.size())
		{
			m_effect->setParameterValue(params.at(band), value);
		}
	}
}
