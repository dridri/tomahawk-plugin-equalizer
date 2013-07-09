#include <QCoreApplication>
#include <boost/bind.hpp>
#include <utils/Logger.h>
#include <ViewManager.h>

#include "EqPlugin.h"
#include "EqWidget.h"
#include "EqEffect.h"

Tomahawk::InfoSystem::EqPlugin::EqPlugin()
{
	tDebug() << Q_FUNC_INFO;
	m_effect = NULL;
}


Tomahawk::InfoSystem::EqPlugin::~EqPlugin()
{
	tDebug() << Q_FUNC_INFO;
}


void
Tomahawk::InfoSystem::EqPlugin::init()
{
	tDebug() << Q_FUNC_INFO;

	// HACK: we wait for Tomahawk (the MainWindow with the ViewManager to be ready) and use the DirectConnection to make addViewPage be called from the GUI thread
	connect(QCoreApplication::instance(), SIGNAL( tomahawkLoaded() ), SLOT( addViewPageLoader() ), Qt::DirectConnection );
	m_effect = new EqEffect();
}


void
Tomahawk::InfoSystem::EqPlugin::addViewPageLoader()
{
	tLog() << Q_FUNC_INFO;

	// don't add this twice, for some reason tomahawkLoaded() is fired more than once
	disconnect(QCoreApplication::instance(), SIGNAL( tomahawkLoaded() ), this, SLOT( addViewPageLoader() ) );

	


	ViewManager::instance()->addDynamicPage("Equalizer",
											"Equalizer",
											QIcon(),
											boost::bind( &EqPlugin::viewPageLoader, this) );
}


Tomahawk::ViewPage* Tomahawk::InfoSystem::EqPlugin::viewPageLoader()
{
	tDebug() << Q_FUNC_INFO;
	return new EqWidget(m_effect, NULL);
}


void
Tomahawk::InfoSystem::EqPlugin::getInfo( Tomahawk::InfoSystem::InfoRequestData requestData )
{
	tDebug() << Q_FUNC_INFO;
}


void
Tomahawk::InfoSystem::EqPlugin::notInCacheSlot( Tomahawk::InfoSystem::InfoStringHash criteria, Tomahawk::InfoSystem::InfoRequestData requestData )
{
	tDebug() << Q_FUNC_INFO;
}


void
Tomahawk::InfoSystem::EqPlugin::pushInfo( Tomahawk::InfoSystem::InfoPushData pushData )
{
	tDebug() << Q_FUNC_INFO;
}


Q_EXPORT_PLUGIN2( Tomahawk::InfoSystem::InfoPlugin, Tomahawk::InfoSystem::EqPlugin )
