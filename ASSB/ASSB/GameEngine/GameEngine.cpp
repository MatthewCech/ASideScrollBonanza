#include "GameEngine.h"
#include "Graphics/Vector4.h"

namespace ASSB
{
	GameEngine::GameEngine(Graphics::Window & window)
		: NextID(1),
		Window(window),
		Graphics(window, true),
		Transform(Graphics, Graphics::ShaderType::Vertex, 1),
		Camera(Graphics),
		PixelShader(Graphics, "LambertPixel.cso", Graphics::ShaderType::Pixel),
		VertexShader(Graphics, "LambertVertex.cso", Graphics::ShaderType::Vertex)
	{
		Graphics.VSync = Graphics::GraphicsEngine::VSyncType::On;

		PixelShader.Create();
		VertexShader.Create();

		std::vector<Graphics::Mesh::Vertex> verts;
		std::vector<unsigned short> inds;

		verts.push_back(Graphics::Mesh::Vertex{ { 0.5f, 0.5f, 0 },{ 1, 1, 1, 1} });
		verts.push_back(Graphics::Mesh::Vertex{ { 0.5f, -0.5f, 0 },{ 1, 1, 1, 1 } });
		verts.push_back(Graphics::Mesh::Vertex{ { -0.5f, 0.5f, 0 },{ 1, 1, 1, 1 } });
		verts.push_back(Graphics::Mesh::Vertex{ { -0.5f, -0.5f, 0 },{ 1, 1, 1, 1 } });

		inds.push_back(0); inds.push_back(3); inds.push_back(1);
		inds.push_back(0); inds.push_back(2); inds.push_back(3);

		Square = std::unique_ptr<Graphics::Mesh>(new Graphics::Mesh(Graphics, verts, inds));
		Square->Create(VertexShader);
	}

	ObjectID GameEngine::GetIdOf(const std::string name)
	{
		//check if it exists
		if (GameObjects.find(name) == GameObjects.end())
			return NULL;
		else
			return GameObjects[name];
	}

	void GameEngine::UpdateCamera()
	{
		Camera.UpdateSize();
	}

	void GameEngine::Loop()
	{

		//draw
		Graphics.ClearScreen();

		PixelShader.Use();
		VertexShader.Use();
		Camera.Use();

		for (auto iterator : GameObjects)
		{
			ObjectID id = iterator.second;
			TransformComponent& trans = Transforms[id];
			auto position = trans.GetPosition();
			Transform.GetDataForWrite() = DirectX::XMMatrixAffineTransformation2D({ 1,1,1 }, { 0,0 }, trans.GetRotation(), { position.X, position.Y, position.Z });

			Transform.Use();

			Graphics.Draw(*Square);
		}

		Graphics.Present();
	}
}
