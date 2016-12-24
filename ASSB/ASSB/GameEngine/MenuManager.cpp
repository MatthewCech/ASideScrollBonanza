#include "MenuManager.hpp"
#include "Globals.hpp"
#include <exception>
#include "GameEngine/GameEngine.h"
#include "Events/UIChangeEvent.hpp"
#include "Events/UISelectEvent.hpp"
#include "Events/ShutdownEvent.hpp"
#include "Events/QuitRequestEvent.hpp"
#include "Events/GameStartEvent.hpp"
#include "Events/KeyboardEvent.hpp"
#include "Events/PauseToggleEvent.hpp"
#include "Events/LoseEvent.hpp"
#include "Events/ReturnToMenuEvent.hpp"
#include "Components/SpriteComponent.hpp"


namespace ASSB
{
	// Static initialization
	MenuManager *MenuManager::Instance = nullptr;


	// Constructor
	MenuManager::MenuManager()
		: EventSystem::ObjectEventManager(Globals::EventSystemInstance)
		, onMainMenu_(true)
		, onPauseMenu_(false)
	{
		// Singleton enforcement
		if (Instance == nullptr)
			Instance = this;
		else
			throw std::exception("One set of menus is enough, don't you think?");

		// Main Menu System
		ASSB::Globals::ObjectID obj = GameEngine::Instance->CreateGameObject("mainMenu");
		GameEngine::Instance->AddComponent<MenuComponent>(obj);
		GameEngine::Instance->GetComponent<SpriteComponent>(obj)->Visible = false;
		ASSB::ComponentHandle<MenuComponent> comp = GameEngine::Instance->GetComponent<MenuComponent>(obj);
		comp->SetSpacing({ 0, -.6f, 0 });
		comp->SetPosition({ -0.75f, 4.0f, 0 });
		comp->SetIndicatorTag("selectImage", { 2.75f, .55f, 0 });
		comp->AddInteractable("start", { 2.5f,.5f,0 }, new GameStartEvent());
		comp->AddInteractable("options", { 2.5f,.5f,0 }, new QuitRequestEvent());
		comp->AddInteractable("credits", { 2.5f,.5f,0 }, new QuitRequestEvent());
		comp->AddInteractable("quit", { 2.5f,.5f,0 }, new ShutdownEvent());
		
		// Pause Menu System
		ASSB::Globals::ObjectID pause = GameEngine::Instance->CreateGameObject("pauseMenu");
		GameEngine::Instance->AddComponent<MenuComponent>(pause);
		GameEngine::Instance->GetComponent<SpriteComponent>(pause)->Visible = false;
		ASSB::ComponentHandle<MenuComponent> pauseComp = GameEngine::Instance->GetComponent<MenuComponent>(pause);
		pauseComp->SetSpacing({ 0, -.6f, 0 });
		pauseComp->SetPosition({ 0, 3.75f, 0 });
		pauseComp->SetIndicatorTag("selectImage", { 2.75f, .55f, 0 });
		pauseComp->AddInteractable("resume", { 2.5f,.5f,0 }, new PauseToggleEvent(false));
		pauseComp->AddInteractable("restart", { 2.5f,.5f,0 }, new LoseEvent(GameTime()));
		pauseComp->AddInteractable("exit", { 2.5f,.5f,0 }, new ReturnToMenuEvent());
		pauseComp->SetActive(false);
		pauseComp->SetVisible(false);

		// Audio
		initializeSFX();

		// Event connection
		Connect(this, &MenuManager::quitRequest);
		Connect(this, &MenuManager::shutdownRequest);
		Connect(this, &MenuManager::shutdownRequest);
		Connect(this, &MenuManager::gameStart);
		Connect(this, &MenuManager::handleKeyboard);
		Connect(this, &MenuManager::pauseToggle);
		Connect(this, &MenuManager::playerLose);
		Connect(this, &MenuManager::menuReturn);

		// Initial paused
		ASSB::Globals::EventSystemInstance.Dispatch(new PauseToggleEvent(true));
	}

	// Creates necessary SFX Objects
	void MenuManager::initializeSFX()
	{
		// Select
		Globals::ObjectID id = GameEngine::Instance->CreateGameObject();
		GameEngine::Instance->AddComponent<SoundEmitterComponent>(id);
		ComponentHandle<SoundEmitterComponent> se = GameEngine::Instance->GetComponent<SoundEmitterComponent>(id);
		GameEngine::Instance->GetComponent<SpriteComponent>(id)->Visible = false;
		se->SetSource("Select1");
		se->PlayOnEvent<UIChangeEvent>();

		// Confirm
		Globals::ObjectID id2 = GameEngine::Instance->CreateGameObject();
		GameEngine::Instance->AddComponent<SoundEmitterComponent>(id2);
		ComponentHandle<SoundEmitterComponent> se2 = GameEngine::Instance->GetComponent<SoundEmitterComponent>(id2);
		GameEngine::Instance->GetComponent<SpriteComponent>(id2)->Visible = false;
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
	void MenuManager::gameStart(GameStartEvent *)
	{
		Globals::ObjectID id = GameEngine::Instance->GetIdOf("player");
		Globals::ObjectID id2 = GameEngine::Instance->GetIdOf("mainMenu");
		GameEngine::Instance->GetComponent<PlayerManagerComponent>(id)->SetActive(true);
		GameEngine::Instance->GetComponent<MenuComponent>(id2)->SetActive(false);
		GameEngine::Instance->GetComponent<MenuComponent>(id2)->SetVisible(false);
		ASSB::Globals::EventSystemInstance.Dispatch(new PauseToggleEvent(false));
		onMainMenu_ = false;
	}

	// Catch relevant keyboard input
	void MenuManager::handleKeyboard(KeyboardEvent *e)
	{
		if (e->Down)
		{
			if (e->Key == Key::P || e->Key == Key::Escape)
			{
				if (!onMainMenu_)
				{
					if (onPauseMenu_)
					{
						ASSB::Globals::EventSystemInstance.Dispatch(new PauseToggleEvent(false));
						onPauseMenu_ = false;
					}
					else
					{
						ASSB::Globals::EventSystemInstance.Dispatch(new PauseToggleEvent(true));
						onPauseMenu_ = true;
					}
				}
			}
		}
	}

	void MenuManager::playerLose(LoseEvent *)
	{
		Globals::ObjectID id2 = GameEngine::Instance->GetIdOf("pauseMenu");
		ComponentHandle<MenuComponent> menuComp = GameEngine::Instance->GetComponent<MenuComponent>(id2);
		menuComp->SetPosition(GameEngine::Instance->Camera.GetPosition() + Graphics::Vector4(0, 2, 0));
	}

	void MenuManager::menuReturn(ReturnToMenuEvent *)
	{
		// Hide pause menu
		Globals::ObjectID id1 = GameEngine::Instance->GetIdOf("pauseMenu");
		GameEngine::Instance->GetComponent<MenuComponent>(id1)->SetActive(false);
		GameEngine::Instance->GetComponent<MenuComponent>(id1)->SetVisible(false);
		Globals::ObjectID id2 = GameEngine::Instance->GetIdOf("mainMenu");
		GameEngine::Instance->GetComponent<MenuComponent>(id2)->SetActive(true);
		GameEngine::Instance->GetComponent<MenuComponent>(id2)->SetVisible(true);
		// Show main menu
		onMainMenu_ = true;
		Globals::EventSystemInstance.Dispatch(new LoseEvent(GameTime()));
	}


	// Pause was hit on or off
	void MenuManager::pauseToggle(PauseToggleEvent *e)
	{
		if (onMainMenu_)
			return;

		Globals::ObjectID id = GameEngine::Instance->GetIdOf("player");
		Globals::ObjectID id2 = GameEngine::Instance->GetIdOf("pauseMenu");
		if(e->Paused)
		{
			// Show menu and stop player
			GameEngine::Instance->GetComponent<PlayerManagerComponent>(id)->SetActive(false);
			ComponentHandle<MenuComponent> menuComp = GameEngine::Instance->GetComponent<MenuComponent>(id2);
			menuComp->SetActive(true);
			menuComp->SetVisible(true);
			menuComp->SetPosition(GameEngine::Instance->Camera.GetPosition() + Graphics::Vector4(0,2,0));
		}
		else
		{
			// enable player and hide menu
			GameEngine::Instance->GetComponent<PlayerManagerComponent>(id)->SetActive(true);
			GameEngine::Instance->GetComponent<MenuComponent>(id2)->SetActive(false);
			GameEngine::Instance->GetComponent<MenuComponent>(id2)->SetVisible(false);
		}
	}
}
