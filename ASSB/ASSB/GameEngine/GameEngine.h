#pragma once
#include <unordered_map>
#include "Graphics/GraphicsEngine.h"
#include "TransformComponent.h"


namespace ASSB
{
	typedef unsigned long long ObjectID;

	class GameEngine
	{
	public:
		GameEngine(Graphics::Window& window);

		ObjectID GetIdOf(const std::string name);

		void Loop();
	private:
		ObjectID NextID;
		bool Running;
		Graphics::GraphicsEngine Graphics;
		Graphics::Window& Window;
		Graphics::ConstantBuffer<DirectX::XMMATRIX> Transform;
		std::unordered_map<std::string, ObjectID> GameObjects;
		std::unordered_map<ObjectID, TransformComponent> Transforms;
		

		GameEngine(const ASSB::GameEngine& other) = delete;

		GameEngine& operator=(const GameEngine& other) = delete;

	};
}
