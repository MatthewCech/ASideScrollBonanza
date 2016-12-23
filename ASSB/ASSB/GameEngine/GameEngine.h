#pragma once
// General
#include <unordered_map>
#include <memory>
#include "Globals.hpp"
#include "GameTime.h"

// Graphics
#include "Graphics/GraphicsEngine.h"
#include "Graphics/Mesh.h"
#include "Graphics/Camera.h"
#include "Graphics/Shaders/Shader.h"
#include "Graphics/Texture.h"
#include "Particles/ParticleBuffer.h"

// Physics
#include "PhsyicsSystem/PhysicsSystem.hpp"

// Components
#include "ComponentHandle.h"
#include "Components/TransformComponent.h"
#include "Components/SoundEmitterComponent.hpp"
#include "Components/RigidBodyComponent.hpp"
#include "Components/SpriteComponent.hpp"



namespace ASSB
{
	class GameEngine
	{
	public:
		// Connstructor
		GameEngine(Graphics::Window& window);

		// Member functions
		Globals::ObjectID GetIdOf(const std::string name);
		Globals::ObjectID CreateGameObject(const std::string name = "");
		void UpdateCamera();
		void Loop();
		Graphics::Texture& GetTexture(const std::wstring path);

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
		Graphics::GraphicsEngine Graphics;
		Graphics::Window& Window;
		Graphics::ConstantBuffer<DirectX::XMMATRIX> Transform;
		std::unique_ptr<Graphics::Mesh> Square;
		Graphics::Camera Camera;
		Graphics::Shader PixelShader;
		Graphics::Shader VertexShader;
		Graphics::Shader ParticleVertexShader;
		Graphics::Shader ParticleGeoShader;
		ParticleBuffer testParticle;


		//Physics
		PhysicsSystem Physics;

		// Add components here
		std::unordered_map<std::string, Globals::ObjectID> GameObjects;
		std::unordered_map<Globals::ObjectID, TransformComponent> Transforms;
		std::unordered_map<Globals::ObjectID, SoundEmitterComponent> SoundEmitters;
		std::unordered_map<Globals::ObjectID, RigidBodyComponent> RigidBodies;
		std::unordered_map<Globals::ObjectID, SpriteComponent> Sprites;
		std::unordered_map<std::wstring, std::shared_ptr<Graphics::Texture>> Textures;

		GameEngine(const ASSB::GameEngine& other) = delete;

		GameEngine& operator=(const GameEngine& other) = delete;
	};
}

#include "GameEngine.tpp"
