// Game and running
#include "Graphics/Window.h"
#include "GameEngine/GameEngine.h"

// Static classes and singletons
#include "FileSystem/AudioPreloadingMapper.hpp"
#include "FileSystem/ImagePreloadingMapper.hpp"
#include "FileSystem/LevelPreloadingMapper.hpp"
#include "GameEngine/MenuManager.hpp"
#include "GameEngine/Utilities.hpp"
#include "GameEngine/LevelQueue.hpp"

// Tersting
#include "Globals.hpp"
#include "Components/PlayerManagerComponent.hpp"
#include "Events/ShutdownEvent.hpp"



int main()
{
	// Seed random
	//!TODO: Seed properly
	srand(9001);

	// Window and engine creation
	Graphics::Window window(L"OWO");
	ASSB::GameEngine Engine(window);
	ASSB::LevelQueue LevelGenerator;

	// Preloading
	FileSystem::ImagePreloadingMapper::LoadFromFile("../../../Assets/ImageList.txt");
	FileSystem::AudioPreloadingMapper::LoadFromFile("../../../Assets/AudioList.txt");
	FileSystem::LevelPreloadingMapper::LoadFromFile("../../../Assets/LevelList.txt");
	LevelGenerator.BulkPopulate(FileSystem::LevelPreloadingMapper::DumpTags());
	//LevelGenerator.LoadDefault();
	//FileSystem::LevelPreloadingMapper::LevelFromFile(FileSystem::LevelPreloadingMapper::Retrieve("default"));
	//FileSystem::LevelPreloadingMapper::LevelFromFile(FileSystem::LevelPreloadingMapper::Retrieve("default"));

	// Post-preloading
	ASSB::Utilities Utils;
	ASSB::MenuManager Menus;

	// Player
	ASSB::Globals::ObjectID player = Engine.CreateGameObject("player");
	DEBUG_PRINT_VAR(player);
	Engine.AddComponent<ASSB::PlayerManagerComponent>(player);
	Engine.AddComponent<ASSB::RigidBodyComponent>(player);
	ASSB::ComponentHandle<ASSB::PlayerManagerComponent> pmComp = Engine.GetComponent<ASSB::PlayerManagerComponent>(player);
	pmComp->SetImage("icon", { .5f, 1, 0 });
	pmComp->SetActive(false);
	Engine.GetComponent<ASSB::TransformComponent>(player)->SetPosition({ 0, 3, 0 });
	Engine.GetComponent<ASSB::RigidBodyComponent>(player)->SetStatic(false);
	//Engine.GetComponent<ASSB::RigidBodyComponent>(player)->AddDispatchOnCollision(new ASSB::ShutdownEvent());

	//LevelGenerator.loadRandom();
	
	// Start the game.
	Engine.Run();
	return 0;
}