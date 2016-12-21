#include "GameEngine.h"
#include "Graphics/Vector4.h"

namespace ASSB
{
	GameEngine::GameEngine(Graphics::Window & window) 
		: NextID(1),
		Window(window),
		Graphics(window),
		Transform(Graphics, Graphics::ShaderType::Vertex, 1)
	{
		Graphics.VSync = Graphics::GraphicsEngine::VSyncType::On;
	}

	ObjectID GameEngine::GetIdOf(const std::string name)
	{
		//check if it exists
		if (GameObjects.find(name) == GameObjects.end())
			return NULL;
		else
			return GameObjects[name];
	}

	void GameEngine::Loop()
	{
		Graphics.ClearScreen();

		for (auto iterator : GameObjects)
		{
			ObjectID id = iterator.second;
			TransformComponent& trans = Transforms[id];
			auto position = trans.GetPosition();
			Transform.GetDataForWrite() = DirectX::XMMatrixAffineTransformation2D({ 1,1,1 }, { 0,0 }, trans.GetRotation(), { position.X, position.Y, position.Z });

			Transform.Use();
		}

		Graphics.Present();
	}
}
