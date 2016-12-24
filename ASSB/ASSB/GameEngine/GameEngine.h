#pragma once
// General
#include <unordered_map>
#include <memory>
#include "Globals.hpp"
#include "GameTime.h"
#include "Events/SwitchEvent.hpp"

// Graphics
#include "Graphics/GraphicsEngine.h"
#include "Graphics/Mesh.h"
#include "Graphics/Camera.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Texture.h"
#include "Particles/ParticleBuffer.h"

// Systems
#include "PhsyicsSystem/PhysicsSystem.hpp"

// Components
#include "ComponentHandle.h"
#include "Components/TransformComponent.h"
#include "Components/SoundEmitterComponent.hpp"
#include "Components/RigidBodyComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/MenuComponent.hpp"
#include "Components/PlayerManagerComponent.hpp"
#include "Components/ParticleComponent.hpp"



namespace ASSB
{
	class GameEngine
	{
		friend class ParticleComponent;
		//no variables above this!
		Graphics::GraphicsEngine Graphics;
	public:
		Graphics::Camera Camera;

		// Constructor
		GameEngine(Graphics::Window& window);

		// Member functions
		Globals::ObjectID GetIdOf(const std::string name);
		Globals::ObjectID CreateGameObject(const std::string name = "");
		Graphics::Texture& GetTexture(const std::wstring path);
		void RemoveID(Globals::ObjectID id);
		void UpdateCamera();
		void Loop();
		void Run();
		void Shutdown();


		// Templatized Member Function
		template <typename T>
		ComponentHandle<T> GetComponent(Globals::ObjectID id);
		template <typename T>
		void AddComponent(Globals::ObjectID id);

		// Static instance of the game engine
		static GameEngine *Instance;

		
	private:
		// Variables
		Globals::ObjectID NextID;
		GameTime Time;
		bool Running;

		// Graphics
		Graphics::Color ClearColor;
		Graphics::Color ColorTo;
		Graphics::Window& Window;
		Graphics::ConstantBuffer<DirectX::XMMATRIX> Transform;
		std::unique_ptr<Graphics::Mesh> Square;
		Graphics::Shader PixelShader;
		Graphics::Shader VertexShader;
		Graphics::Shader ParticleVertexShader;
		Graphics::Shader ParticleGeoShader;

		//Physics
		PhysicsSystem Physics;

		// Add components here
		std::unordered_map<std::string, Globals::ObjectID> GameObjects;
		std::unordered_map<Globals::ObjectID, std::string> GameObjectNames;
		std::unordered_map<Globals::ObjectID, std::unique_ptr<TransformComponent>> Transforms;
		std::unordered_map<Globals::ObjectID, std::unique_ptr<SoundEmitterComponent>> SoundEmitters;
		std::unordered_map<Globals::ObjectID, std::unique_ptr<RigidBodyComponent>> RigidBodies;
		std::unordered_map<Globals::ObjectID, std::unique_ptr<SpriteComponent>> Sprites;
		std::unordered_map<Globals::ObjectID, std::unique_ptr<MenuComponent>> Menus;
		std::unordered_map<Globals::ObjectID, std::unique_ptr<PlayerManagerComponent>> PlayerManagers;
		std::unordered_map<Globals::ObjectID, std::unique_ptr<ParticleComponent>> ParticleSystems;
		std::unordered_map<std::wstring, std::shared_ptr<Graphics::Texture>> Textures;
		GameEngine(const ASSB::GameEngine& other) = delete;

		GameEngine& operator=(const GameEngine& other) = delete;

		void OnSwitch(SwitchEvent* e);
	};
}

#include "GameEngine.tpp"
