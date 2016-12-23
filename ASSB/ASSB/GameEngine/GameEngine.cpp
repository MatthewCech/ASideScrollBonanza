#include "GameEngine.h"
#include "Graphics/Vector4.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Events/UpdateEvent.hpp"

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
		VertexShader(Graphics, "LambertVertex.cso", Graphics::ShaderType::Vertex)
	{
		// Singleton enforcement
		if (Instance == nullptr)
			Instance = this;
		else
			throw "Gee user, why does your mom let you have TWO game engines?";

		//setup input

		window.OnKeyDown = Keyboard::KeyDown;
		window.OnKeyUp = Keyboard::KeyUp;
		window.OnSystemKeyDown = Keyboard::SysKeyDown;
		window.OnSystemKeyUp = Keyboard::SysKeyUp;
		window.OnMouseButton = Mouse::MouseButtonChange;
		window.OnMouseScroll = Mouse::Scroll;
		window.OnMouseMove = Mouse::MouseMove;

		//set up graphics
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

		Camera.SetPosition(Graphics::Vector4(0, 0, 5));
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
		AddComponent<SpriteComponent>(NextID - 1);

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
		Keyboard::Update();
		Mouse::Update();

		Time.Tick();
		Globals::EventSystemInstance.Dispatch(new UpdateEvent(Time));

		// Physics
		Physics.Update(RigidBodies, Time);

		//draw
		Graphics.ClearScreen();

		static float woo = 0;

		PixelShader.Use();
		VertexShader.Use();
		Camera.Use();

		for (auto iterator : GameObjects)
		{
			Globals::ObjectID id = iterator.second;
			ComponentHandle<SpriteComponent> sprite = GetComponent<SpriteComponent>(id);
			if (!sprite)
				continue;
			ComponentHandle<TransformComponent> trans = GetComponent<TransformComponent>(id);
			auto position = trans->GetPosition();
			Transform.GetDataForWrite() = DirectX::XMMatrixAffineTransformation2D({ trans->GetScaleX(), -trans->GetScaleY(),1 }, { 0,0 }, trans->GetRotation(), { position.X, position.Y, position.Z });

			Transform.Use();
			GetTexture(sprite->Path).Use();

			Graphics.Draw(*Square);
		}

		Graphics.Present();
		Mouse::PrepairForNextFrame();
		Keyboard::PrepairForNextFrame();
	}

	Graphics::Texture & GameEngine::GetTexture(const std::wstring path)
	{
		auto it = Textures.find(path);

		if (it == Textures.end())
		{
			Textures.emplace(path, std::shared_ptr<Graphics::Texture>(new Graphics::Texture(Graphics, path)));
			Textures[path]->Create();
			return *Textures[path];
		}
		return *(it->second);
	}
}
