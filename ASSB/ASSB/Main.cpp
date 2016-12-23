// Game and running
#include "Graphics/Window.h"
#include "GameEngine/GameEngine.h"

// Static classes and singletons
#include "FileSystem/AudioPreloadingMapper.hpp"
#include "FileSystem/ImagePreloadingMapper.hpp"
#include "FileSystem/LevelPreloader.hpp"
#include "GameEngine/MenuManager.hpp"

// Tersting
#include "Globals.hpp"
#include "Components/PlayerManagerComponent.hpp"




int main()
{
	// Window and engine creation
	Graphics::Window window(L"OWO");
	ASSB::GameEngine Engine(window);

	// Preloading
	FileSystem::ImagePreloadingMapper::LoadFromFile("../../../Assets/ImageList.txt");
	FileSystem::AudioPreloadingMapper::LoadFromFile("../../../Assets/AudioList.txt");
	FileSystem::LevelPreloader::LoadFromFile("../../../Assets/Levels/LevelTest.txt");
	FileSystem::LevelPreloader::LoadFromFile("../../../Assets/Levels/SandboxLevel.txt");

	// Post-preloading
	ASSB::MenuManager Menus;

	// Player
	ASSB::Globals::ObjectID player = Engine.CreateGameObject("player");
	Engine.AddComponent<ASSB::PlayerManagerComponent>(player);
	Engine.AddComponent<ASSB::RigidBodyComponent>(player);
	ASSB::ComponentHandle<ASSB::PlayerManagerComponent> pmComp = Engine.GetComponent<ASSB::PlayerManagerComponent>(player);
	pmComp->SetImage("icon", { .5f, .5f, 0 });
	pmComp->SetActive(true);
	
	// Start the game.
	Engine.Run();
	return 0;
}