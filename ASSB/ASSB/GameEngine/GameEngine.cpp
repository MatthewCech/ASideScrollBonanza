#include "GameEngine.h"
#include "Graphics/Vector4.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Events/UpdateEvent.hpp"

#include <cstdlib>

namespace ASSB
{
	// Static Init
	GameEngine *GameEngine::Instance = nullptr;


	// Constructor
	GameEngine::GameEngine(Graphics::Window & window)
		: NextID(1),
		Running(true),
		Window(window),
		Graphics(window),
		Transform(Graphics, Graphics::ShaderType::Vertex, 1),
		Camera(Graphics),
		PixelShader(Graphics, "SpritePixel.cso", Graphics::ShaderType::Pixel),
		VertexShader(Graphics, "SpriteVertex.cso", Graphics::ShaderType::Vertex),
		ParticleVertexShader(Graphics, "ParticleVertex.cso", Graphics::ShaderType::Vertex),
		ParticleGeoShader(Graphics, "ParticleGeo.cso", Graphics::ShaderType::Geometry),
		ClearColor(1, 1, 1)
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
		Globals::EventSystemInstance.Register(this, &GameEngine::OnSwitch);
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
		AddComponent<TransformComponent>(NextID - 1);
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

		//////////////////
		//
		//        Graphics
		//              //
		//////////////////
		std::vector<Globals::ObjectID> drawOrder;
		std::vector<Globals::ObjectID> particles;
		Graphics.ClearScreen(ClearColor);

		/*float screenXOffset = -0.5f * (Mouse::Current.ScreenXPos / static_cast<float>(Window.Width) - 0.5f);
		float screenYOffset = 0.5f * (Mouse::Current.ScreenYPos / static_cast<float>(Window.Height) - 0.5f);

		Camera.SetLook(Graphics::Vector4(screenXOffset, screenYOffset, -1));*/

		Camera.Use();

		//get the objects
		for (auto iterator : GameObjects)
		{
			Globals::ObjectID id = iterator.second;
			auto sprite = GetComponent<SpriteComponent>(id);
			if (sprite && sprite->Visible)
				drawOrder.push_back(id);
			if (GetComponent<ParticleComponent>(id))
				particles.push_back(id);
		}

		//sort them
		std::qsort(&drawOrder[0], drawOrder.size(), sizeof(Globals::ObjectID),
			[](const void* p1, const void* p2)
		{
			Globals::ObjectID id1 = *reinterpret_cast<const Globals::ObjectID*>(p1);
			Globals::ObjectID id2 = *reinterpret_cast<const Globals::ObjectID*>(p2);

			ComponentHandle<TransformComponent> trans1 = Instance->GetComponent<TransformComponent>(id1);
			ComponentHandle<TransformComponent> trans2 = Instance->GetComponent<TransformComponent>(id2);

			float val = trans1->GetPosition().Z - trans2->GetPosition().Z;

			if (val < 0)
				return -1;
			else if (val == 0)
				return 0;
			else
				return 1;
		});
		
		PixelShader.Use();
		VertexShader.Use();
		for (Globals::ObjectID id : drawOrder)
		{
			ComponentHandle<SpriteComponent> sprite = GetComponent<SpriteComponent>(id);
			
			ComponentHandle<TransformComponent> trans = GetComponent<TransformComponent>(id);
			auto position = trans->GetPosition();
			Transform.GetDataForWrite() = DirectX::XMMatrixAffineTransformation2D({ trans->GetScaleX(), -trans->GetScaleY(),1 }, { 0,0 }, trans->GetRotation(), { position.X, position.Y, position.Z });
			Transform.Use();
			GetTexture(sprite->Path).Use();

			Graphics.Draw(*Square);
		}

		/*for (int i = 0; i < 1; ++i)
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
		}*/


		/*for (size_t i = 0; i < testParticle.size(); ++i)
		{
			auto& part = testParticle[i];
			part.Position[1] -= 0.04f;
			part.life -= static_cast<float>(Time.DT);

			if (part.life < 0)
			{
				testParticle.Remove(i);
				--i;
			}
		}*/

		//particles
		ParticleVertexShader.Use();
		ParticleGeoShader.Use();
		for (Globals::ObjectID id : particles)
		{
			auto partComp = GetComponent<ParticleComponent>(id);

			Graphics.SetBlendMode(partComp->BlendMode);
			GetTexture(partComp->Path).Use();
			partComp->Buffer.Use();
			Graphics.DeviceContext->Draw(static_cast<UINT>(partComp->Buffer.size()), 0);
		}
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


	// Message handling infinite game loop.
	// Most logic in loop.
	void GameEngine::Run()
	{
		MSG msg;
		while (Running)
		{
			while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				if (msg.message == WM_QUIT)
					Running = false;
			}

			UpdateCamera();
			Loop();
		}
	}


	void GameEngine::Shutdown()
	{
		PostQuitMessage(0);
	}

	void GameEngine::OnSwitch(SwitchEvent * e)
	{
		if (e->White)
		{
			ClearColor = Graphics::Color(0, 0, 0);
		}
		else
		{
			ClearColor = Graphics::Color(1, 1, 1);
		}
	}
}
