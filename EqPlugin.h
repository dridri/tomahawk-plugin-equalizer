#ifndef EQPLUGIN_H
#define EQPLUGIN_H

#include <infosystem/InfoSystem.h>
#include <ViewPage.h>

namespace Tomahawk
{

namespace InfoSystem
{

class EqPlugin : public InfoPlugin
{
	Q_PLUGIN_METADATA( IID "org.tomahawk-player.Player.InfoPlugin" )
	Q_OBJECT
	Q_INTERFACES( Tomahawk::InfoSystem::InfoPlugin )

public:
	EqPlugin();
	virtual ~EqPlugin();

protected slots:
	virtual void init();
	virtual void getInfo( Tomahawk::InfoSystem::InfoRequestData requestData );
	virtual void notInCacheSlot( Tomahawk::InfoSystem::InfoStringHash criteria, Tomahawk::InfoSystem::InfoRequestData requestData );
	virtual void pushInfo( Tomahawk::InfoSystem::InfoPushData pushData );

private slots:
	void addViewPageLoader();

private:
	Tomahawk::ViewPage* viewPageLoader();
};

}

}

#endif // EQPLUGIN_H
