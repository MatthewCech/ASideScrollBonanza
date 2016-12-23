#pragma once
#include "EventSystem/ObjectEventManager.hpp"



namespace ASSB
{
	// Handles menus and some menu-related events.
	class QuitRequestEvent;
	class ShutdownEvent;
	class GameStartEvent;
	class MenuManager : public EventSystem::ObjectEventManager
	{
	public:
		// Constructor
		MenuManager();
		
		// Static instance of Menu Manager
		static MenuManager *Instance;

	private:
		// Variables

		// Member functions
		void initializeSFX();
		void quitRequest(QuitRequestEvent *e);
		void shutdownRequest(ShutdownEvent *e);
		void gameStart(GameStartEvent *e);

		// Omit
		MenuManager &operator=(const MenuManager &rhs) = delete;
		MenuManager(const MenuManager &rhs) = delete;
	};
}
