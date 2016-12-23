#include "MenuManager.hpp"
#include "Globals.hpp"
#include <exception>
#include "GameEngine/GameEngine.h"
#include "Events/UIChangeEvent.hpp"
#include "Events/UISelectEvent.hpp"
#include "Events/ShutdownEvent.hpp"
#include "Events/QuitRequestEvent.hpp"
#include "Events/GameStartEvent.hpp"



namespace ASSB
{
	// Static initialization
	MenuManager *MenuManager::Instance = nullptr;


	// Constructor
	MenuManager::MenuManager() 
		: EventSystem::ObjectEventManager(Globals::EventSystemInstance)
	{
		// Singleton enforcement
		if (Instance == nullptr)
			Instance = this;
		else
			throw std::exception("One set of menus is enough, don't you think?");

		// Menu System
		ASSB::Globals::ObjectID obj = GameEngine::Instance->CreateGameObject("mainMenu");
		GameEngine::Instance->AddComponent<MenuComponent>(obj);
		ASSB::ComponentHandle<MenuComponent> comp = GameEngine::Instance->GetComponent<MenuComponent>(obj);
		comp->SetSpacing({ 0, -.4f, 0 });
		comp->SetPosition({ 0, 3.0f, 0 });
		comp->SetIndicatorTag("selectImage", { 1.75f, .4f, 0 });
		comp->AddInteractable("start", { 1.5f,.3f,0 }, new GameStartEvent());
		//comp->AddInteractable("options", { 1.5f,.3f,0 }, new QuitRequestEvent());
		comp->AddInteractable("credits", { 1.5f,.3f,0 }, new QuitRequestEvent());
		comp->AddInteractable("quit", { 1.5f,.3f,0 }, new QuitRequestEvent());
		
		// Audio
		initializeSFX();

		// Event connection
		Connect(this, &MenuManager::quitRequest);
		Connect(this, &MenuManager::shutdownRequest);
		Connect(this, &MenuManager::shutdownRequest);
		Connect(this, &MenuManager::gameStart);
	}

	// Creates necessary SFX Objects
	void MenuManager::initializeSFX()
	{
		// Select
		Globals::ObjectID id = GameEngine::Instance->CreateGameObject();
		GameEngine::Instance->AddComponent<SoundEmitterComponent>(id);
		ComponentHandle<SoundEmitterComponent> se = GameEngine::Instance->GetComponent<SoundEmitterComponent>(id);
		se->SetSource("Select1");
		se->PlayOnEvent<UIChangeEvent>();

		// Confirm
		Globals::ObjectID id2 = GameEngine::Instance->CreateGameObject();
		GameEngine::Instance->AddComponent<SoundEmitterComponent>(id2);
		ComponentHandle<SoundEmitterComponent> se2 = GameEngine::Instance->GetComponent<SoundEmitterComponent>(id2);
		se2->SetSource("Confirm1");
		se2->PlayOnEvent<UISelectEvent>();
	}

	// Game will prompt for confirmation of action;
	void MenuManager::quitRequest(QuitRequestEvent *e)
	{
		// confirm?
		UNUSED(e);
	}

	// Game window will be terminated.
	void MenuManager::shutdownRequest(ShutdownEvent *e)
	{
		GameEngine::Instance->Shutdown();
		UNUSED(e);
	}

	// Start the game
	void MenuManager::gameStart(GameStartEvent *e)
	{
		Globals::ObjectID id = GameEngine::Instance->GetIdOf("player");
		Globals::ObjectID id2 = GameEngine::Instance->GetIdOf("mainMenu");
		GameEngine::Instance->GetComponent<PlayerManagerComponent>(id)->SetActive(true);
		GameEngine::Instance->GetComponent<MenuComponent>(id2)->SetActive(false);
		UNUSED(e);
	}
}
