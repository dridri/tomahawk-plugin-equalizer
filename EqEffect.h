#ifndef EQEFFECT_H
#define EQEFFECT_H

#include <ViewPage.h>
#include <audio/AudioEngine.h>
#include <phonon/Path>
#include <phonon/Effect>

#include <QObject>

namespace Ui {
class Equalizer;
};

class EqEffect : public QObject
{
	Q_OBJECT

public:
	EqEffect();
	~EqEffect();
	void setEqualizer(int band, int value);

private:
	Phonon::Path* m_audioPath;
	Phonon::Effect* m_effect;
};
#endif // EQEFFECT_H
