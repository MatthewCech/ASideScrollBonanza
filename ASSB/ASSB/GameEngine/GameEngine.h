#pragma once
// General
#include <unordered_map>
#include <memory>
#include "Globals.hpp"

// Graphics
#include "Graphics/GraphicsEngine.h"
#include "Graphics/Mesh.h"
#include "Graphics/Camera.h"
#include "Graphics/Shaders/Shader.h"

// Components
#include "ComponentHandle.h"
#include "TransformComponent.h"
#include "SoundEmitterComponent.hpp"



namespace ASSB
{

	class GameEngine
	{
	public:
		GameEngine(Graphics::Window& window);

		Globals::ObjectID GetIdOf(const std::string name);
		void UpdateCamera();

		template <typename T>
		ComponentHandle<T> GetComponent(Globals::ObjectID id);

		void Loop();
	private:
		Globals::ObjectID NextID;
		bool Running;
		Graphics::GraphicsEngine Graphics;
		Graphics::Window& Window;
		Graphics::ConstantBuffer<DirectX::XMMATRIX> Transform;
		std::unique_ptr<Graphics::Mesh> Square;
		Graphics::Camera Camera;
		Graphics::Shader PixelShader;
		Graphics::Shader VertexShader;

		// Add components here
		std::unordered_map<std::string, Globals::ObjectID> GameObjects;
		std::unordered_map<Globals::ObjectID, TransformComponent> Transforms;
		std::unordered_map<Globals::ObjectID, SoundEmitterComponent> SoundEmitters;

		GameEngine(const ASSB::GameEngine& other) = delete;

		GameEngine& operator=(const GameEngine& other) = delete;
	};
}

#include "GameEngine.tpp"
