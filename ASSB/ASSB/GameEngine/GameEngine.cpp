#include "GameEngine.h"
#include "Graphics/Vector4.h"

namespace ASSB
{
	// Static Init
	GameEngine *GameEngine::Instance = nullptr;


	// Constructor
	GameEngine::GameEngine(Graphics::Window & window)
		: NextID(1),
		Window(window),
		Graphics(window, true),//todo don't debug graphics
		Transform(Graphics, Graphics::ShaderType::Vertex, 1),
		Camera(Graphics),
		PixelShader(Graphics, "LambertPixel.cso", Graphics::ShaderType::Pixel),
		VertexShader(Graphics, "LambertVertex.cso", Graphics::ShaderType::Vertex),
		TestTexture(Graphics, L"../../../Assets/wow.png")
	{
		// Singleton enforcement
		if (Instance == nullptr)
			Instance = this;
		else
			throw "Gee user, why does your mom let you have TWO game engines?";

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

		GameObjects.emplace(std::pair<std::string, Globals::ObjectID>("wowzers", NextID++));
		Transforms.emplace(NextID -1, TransformComponent());

		GameObjects.emplace(std::pair<std::string, Globals::ObjectID>("wowzer", NextID++));
		Transforms.emplace(NextID - 1, TransformComponent());

		Transforms[2].SetPosition(Graphics::Vector4(1, 2, 0));

		Camera.SetPosition(Graphics::Vector4(0, 0, 10));
	}


	// Gets the ID of the name
	Globals::ObjectID GameEngine::GetIdOf(const std::string name)
	{
		//check if it exists
		if (GameObjects.find(name) == GameObjects.end())
			return NULL;
		else
			return GameObjects[name];
	}


	// Creates a game object with the specified name.
	// Names must be more than just numbers, as unspecified names 
	// are assigned their ID.
	Globals::ObjectID GameEngine::CreateGameObject(std::string name)
	{
		if (name.size() == 0)
			name = std::to_string(NextID + 1);

		GameObjects.emplace(std::pair<std::string, Globals::ObjectID>(name, NextID++));
		Transforms.emplace(NextID - 1, TransformComponent());

		return NextID - 1;
	}


	// Updates the size of the camera object
	void GameEngine::UpdateCamera()
	{
		Camera.UpdateSize();
	}


	// Primary game loop
	void GameEngine::Loop()
	{
		// Physics
		Physics.Update(*this, RigidBodies);

		//draw
		Graphics.ClearScreen();

		static float woo = 0;

		PixelShader.Use();
		VertexShader.Use();
		Camera.Use();

		for (auto iterator : GameObjects)
		{
			Globals::ObjectID id = iterator.second;
			ComponentHandle<TransformComponent> comp = GetComponent<TransformComponent>(id);
			auto position = comp->GetPosition();
			Transform.GetDataForWrite() = DirectX::XMMatrixAffineTransformation2D({ 1,1,1 }, { 0,0 }, comp->GetRotation(), { position.X, position.Y, position.Z });

			Transform.Use();

			Graphics.Draw(*Square);
		}

		Graphics.Present();
	}
}
