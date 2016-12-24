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

// Testing
#include "Globals.hpp"
#include "Components/PlayerManagerComponent.hpp"
#include "Events/ShutdownEvent.hpp"
#include <time.h>

//particles
#include "Particles/EmitConstant.hpp"
#include "Particles/InitializeSizeRandom.hpp"
#include "Particles/InitializePositionRandom.hpp"
#include "Particles/InitializePositionRandomCam.hpp"
#include "Particles/UpdatePosition.hpp"
#include "Particles/InitializeLifeRandom.hpp"
#include "Particles/TerminateInstant.hpp"


int main()
{
	// Seed random
	srand(static_cast<unsigned int>(time(0)));

	// Window and engine creation
	Graphics::Window window(L"Partial Shift");
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


	// Player
	ASSB::Globals::ObjectID player = Engine.CreateGameObject("player");
	DEBUG_PRINT_VAR(player);
	Engine.AddComponent<ASSB::PlayerManagerComponent>(player);
	Engine.AddComponent<ASSB::RigidBodyComponent>(player);
	ASSB::ComponentHandle<ASSB::PlayerManagerComponent> pmComp = Engine.GetComponent<ASSB::PlayerManagerComponent>(player);
	pmComp->SetImage("player1L", "player1D", { .5f,1,0 });
	pmComp->SetActive(false);
	Engine.GetComponent<ASSB::TransformComponent>(player)->SetPosition({ 0, 1, 0 });
	Engine.GetComponent<ASSB::RigidBodyComponent>(player)->SetStatic(false);
	//Engine.GetComponent<ASSB::RigidBodyComponent>(player)->AddDispatchOnCollision(new ASSB::ShutdownEvent());

	//particle rain/snow
	ASSB::Globals::ObjectID ParticleObject = Engine.CreateGameObject("Snow System");
	Engine.AddComponent<ASSB::ParticleComponent>(ParticleObject);
	Engine.GetComponent<ASSB::SpriteComponent>(ParticleObject)->Visible = false;
	auto ParticleComp = Engine.GetComponent<ASSB::ParticleComponent>(ParticleObject);

	ParticleComp->Path = L"../../../Assets/Images/snow.png";
	ParticleComp->Visible = false;
	ParticleComp->BlendMode = Graphics::GraphicsEngine::BlendMode::Multiply;
	ParticleComp->Emitter = std::unique_ptr<ASSB::Emitter>(new ASSB::EmitConstant(ParticleObject, 40));
	ParticleComp->Initializers.emplace_back(new ASSB::InitializeSizeRandom(ParticleObject, 0.05f, 0.2f));
	ParticleComp->Initializers.emplace_back(new ASSB::InitializeLifeRandom(ParticleObject, 15, 20));
	ParticleComp->Initializers.emplace_back(new ASSB::InitializePositionRandomCam(ParticleObject, Graphics::Vector4(-10, 15, -15), Graphics::Vector4(80, 15, 5)));
	ParticleComp->Updaters.emplace_back(new ASSB::UpdatePosition(ParticleObject, Graphics::Vector4(-1, -2, 0)));
	ParticleComp->Terminator = std::unique_ptr<ASSB::Terminator>(new ASSB::TerminateInstant(ParticleObject));

	ParticleObject = Engine.CreateGameObject("Rain System");
	Engine.AddComponent<ASSB::ParticleComponent>(ParticleObject);
	Engine.GetComponent<ASSB::SpriteComponent>(ParticleObject)->Visible = false;
	ParticleComp = Engine.GetComponent<ASSB::ParticleComponent>(ParticleObject);

	ParticleComp->Path = L"../../../Assets/Images/rain.png";
	ParticleComp->BlendMode = Graphics::GraphicsEngine::BlendMode::Multiply;
	ParticleComp->Emitter = std::unique_ptr<ASSB::Emitter>(new ASSB::EmitConstant(ParticleObject, 560));
	ParticleComp->Initializers.emplace_back(new ASSB::InitializeSizeRandom(ParticleObject, 0.3f, 0.3f));
	ParticleComp->Initializers.emplace_back(new ASSB::InitializeLifeRandom(ParticleObject, 2, 2));
	ParticleComp->Initializers.emplace_back(new ASSB::InitializePositionRandomCam(ParticleObject, Graphics::Vector4(-10, 15, -15), Graphics::Vector4(50, 15, 5)));
	ParticleComp->Updaters.emplace_back(new ASSB::UpdatePosition(ParticleObject, Graphics::Vector4(-20, -55, 0)));
	ParticleComp->Terminator = std::unique_ptr<ASSB::Terminator>(new ASSB::TerminateInstant(ParticleObject));

	//player killer

	ASSB::Globals::ObjectID PK = Engine.CreateGameObject("PK");
	Engine.AddComponent<ASSB::RigidBodyComponent>(PK);
	auto RigidComp = Engine.GetComponent<ASSB::RigidBodyComponent>(PK);
	RigidComp->SetCollisionType(ASSB::CollisionType::GHOSTING);
	RigidComp->SetStatic(false);
	RigidComp->SetVelocity(Graphics::Vector4(4.75f, 0, 0));

	auto TransComp = Engine.GetComponent<ASSB::TransformComponent>(PK);
	TransComp->SetPosition(Graphics::Vector4(-16, 0, 0.06f));
	TransComp->SetScale(10, 25);
	
	auto SpriteComp = Engine.GetComponent<ASSB::SpriteComponent>(PK);
	std::string pkpath = FileSystem::ImagePreloadingMapper::Retrieve("death");
	SpriteComp->AddPath(std::wstring(pkpath.begin(), pkpath.end()));

	// Post-everything Menu init
	ASSB::MenuManager Menus;
	Engine.Camera.SetPosition({ 2.25f, 1.75f, 5.5f });

	// Start the game.
	Engine.Run();
	return 0;
}