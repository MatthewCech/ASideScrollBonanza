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
		Graphics(window),
		Transform(Graphics, Graphics::ShaderType::Vertex, 1),
		Camera(Graphics),
		PixelShader(Graphics, "SpritePixel.cso", Graphics::ShaderType::Pixel),
		VertexShader(Graphics, "SpriteVertex.cso", Graphics::ShaderType::Vertex),
		ParticleVertexShader(Graphics, "ParticleVertex.cso", Graphics::ShaderType::Vertex),
		ParticleGeoShader(Graphics, "ParticleGeo.cso", Graphics::ShaderType::Geometry),
		testParticle(Graphics)
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
		ParticleVertexShader.Create();
		ParticleGeoShader.Create();
		testParticle.Create(ParticleVertexShader);

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

		float screenXOffset = -0.5f * (Mouse::Current.ScreenXPos/ static_cast<float>(Window.Width) - 0.5f); 
		float screenYOffset = 0.5f * (Mouse::Current.ScreenYPos / static_cast<float>(Window.Height) - 0.5f);

		Camera.SetLook(Graphics::Vector4(screenXOffset, screenYOffset, -1));

		Camera.Use();

		for (auto iterator : GameObjects)
		{
			Globals::ObjectID id = iterator.second;
			ComponentHandle<SpriteComponent> sprite = GetComponent<SpriteComponent>(id);
			if (sprite)
			{
				PixelShader.Use();
				VertexShader.Use();
				ComponentHandle<TransformComponent> trans = GetComponent<TransformComponent>(id);
				auto position = trans->GetPosition();
				Transform.GetDataForWrite() = DirectX::XMMatrixAffineTransformation2D({ trans->GetScaleX(), -trans->GetScaleY(),1 }, { 0,0 }, trans->GetRotation(), { position.X, position.Y, position.Z });

				Transform.Use();
				GetTexture(sprite->Path).Use();

				Graphics.Draw(*Square);
			}

		}

		for (int i = 0; i < 1; ++i)
		{
			auto& part = testParticle.Add();

			if (part.Position[1] == 0)
			{
				part.Position[0] = (rand() / static_cast<float>(RAND_MAX)) * 20 - 10;
				part.Position[1] = 10;
				part.Position[2] = (rand() / static_cast<float>(RAND_MAX)) * 20 - 10;

				part.Scale = (rand() / static_cast<float>(RAND_MAX)) + 0.5f;
				part.Rotation = (rand() / static_cast<float>(RAND_MAX)) * 3.1415926f * 2;

				part.Color[0] = (rand() / static_cast<float>(RAND_MAX));
				part.Color[1] = (rand() / static_cast<float>(RAND_MAX));
				part.Color[2] = (rand() / static_cast<float>(RAND_MAX));
				part.Color[3] = (rand() / static_cast<float>(RAND_MAX));

				part.life = (rand() / static_cast<float>(RAND_MAX)) * 20;
			}
		}
		

		for (size_t i = 0; i < testParticle.size(); ++i)
		{
			auto& part = testParticle[i];
			part.Position[1] -= 0.04f;
			part.life -= static_cast<float>(Time.DT);

			if (part.life < 0)
			{
				testParticle.Remove(i);
				--i;
			}
		}

		GetTexture(L"../../../Assets/None.png").Use();
		ParticleGeoShader.Use();
		ParticleVertexShader.Use();
		testParticle.Use();
		Graphics.SetBlendMode(Graphics::GraphicsEngine::BlendMode::Additive);
		Graphics.DeviceContext->Draw(static_cast<UINT>(testParticle.size()), 0);
		Graphics.SetBlendMode(Graphics::GraphicsEngine::BlendMode::Multiply);
		ParticleGeoShader.UnUse();

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
