#include "GameEngine.h"
#include "Graphics/Vector4.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Events/UpdateEvent.hpp"
#include "FileSystem/LevelPreloadingMapper.hpp"
#include <cstdlib>

namespace ASSB
{
	// Static Init
	GameEngine *GameEngine::Instance = nullptr;


	// Constructor
	GameEngine::GameEngine(Graphics::Window & window)
		: NextID(1),
		Running(true),
		EnvironmentIsLight(true),
		Window(window),
		Graphics(window),
		Transform(Graphics, Graphics::ShaderType::Vertex, 1),
		Camera(Graphics),
		PixelShader(Graphics, "SpritePixel.cso", Graphics::ShaderType::Pixel),
		VertexShader(Graphics, "SpriteVertex.cso", Graphics::ShaderType::Vertex),
		ParticleVertexShader(Graphics, "ParticleVertex.cso", Graphics::ShaderType::Vertex),
		ParticleGeoShader(Graphics, "ParticleGeo.cso", Graphics::ShaderType::Geometry),
		ClearColor(0.8f, 0.9f, 1),
		ColorTo(0.8f, 0.9f, 1)
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

		Camera.SetPosition(Graphics::Vector4(0, 0, 5.5f));
		Globals::EventSystemInstance.Register(this, &GameEngine::OnSwitch);
		Globals::EventSystemInstance.Register(this, &GameEngine::OnDeath);
	}


	void GameEngine::RemoveID(Globals::ObjectID id)
	{
		Transforms.erase(id);
		SoundEmitters.erase(id);
		RigidBodies.erase(id);
		Sprites.erase(id);
		Menus.erase(id);
		PlayerManagers.erase(id);
		ParticleSystems.erase(id);
		GameObjects.erase(GameObjectNames.at(id));
		GameObjectNames.erase(id);
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

	const std::string & GameEngine::GetNameOf(Globals::ObjectID id)
	{
		//check if it exists
		if (GameObjectNames.find(id) == GameObjectNames.end())
			throw std::exception("THAT DOESN'T EXIST");
		else
			return GameObjectNames[id];
	}


	// Creates a game object with the specified name.
	// Names must be more than just numbers, as unspecified names 
	// are assigned their ID.
	Globals::ObjectID GameEngine::CreateGameObject(std::string name)
	{
		if (name.size() == 0)
			name = std::to_string(NextID + 1);

		GameObjects.emplace(std::pair<std::string, Globals::ObjectID>(name, NextID++));
		GameObjectNames.emplace(std::pair<Globals::ObjectID, std::string>(NextID - 1, name));
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

		//////////////////  //////////////////
		//									//
		//        Graphics	//        Graphics
		//              //	//              //
		//////////////////	//////////////////
		std::vector<Globals::ObjectID> drawOrder;
		std::vector<Globals::ObjectID> particles;

		Graphics::Color diff = ColorTo;
		diff.A -= ClearColor.A;
		diff.R -= ClearColor.R;
		diff.G -= ClearColor.G;
		diff.B -= ClearColor.B;

		diff.A /= 10;
		diff.R /= 10;
		diff.G /= 10;
		diff.B /= 10;

		ClearColor.A += diff.A;
		ClearColor.R += diff.R;
		ClearColor.G += diff.G;
		ClearColor.B += diff.B;

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
			auto particle = GetComponent<ParticleComponent>(id);
			if (particle && particle->Visible)
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
			auto& transf = Transform.GetDataForWrite();
			transf = DirectX::XMMatrixAffineTransformation2D({ trans->GetScaleX(), -trans->GetScaleY(),1 }, { 0,0 }, trans->GetRotation(), { 0,0 });
			transf = transf * DirectX::XMMatrixTranslation(position.X, position.Y, position.Z);
			Transform.Use();
			GetTexture(sprite->GetPath(EnvironmentIsLight)).Use();

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

		// Automated Cleanup
		Globals::EventSystemInstance.Upkeep();
		FileSystem::LevelPreloadingMapper::CheckOldestLoaded();
		FileSystem::LevelPreloadingMapper::ResolveNukes();
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
		auto snowSys = GetComponent<ParticleComponent>(GetIdOf("Snow System"));
		auto rainSys = GetComponent<ParticleComponent>(GetIdOf("Rain System"));
		EnvironmentIsLight = !e->White;
		if (e->White)
		{
			ColorTo = Graphics::Color(0, 0, 0);
			snowSys->Visible = true;
			rainSys->Visible = false;
		}
		else
		{
			ColorTo = Graphics::Color(0.8f, 0.9f, 1);
			snowSys->Visible = false;
			rainSys->Visible = true;
		}
	}

	void GameEngine::OnDeath(LoseEvent *)
	{
		FileSystem::LevelPreloadingMapper::NukeObjects();
		ASSB::Globals::ObjectID player = GetIdOf("player");
		GetComponent<ASSB::TransformComponent>(player)->SetPosition({ 0, 1, 0 });

		Camera.SetPosition({ 0,1, 0 });

		ASSB::Globals::ObjectID PK = GetIdOf("PK");
		auto TransComp = GetComponent<ASSB::TransformComponent>(PK);
		TransComp->SetPosition(Graphics::Vector4(-10, 0, 0.001f));
	}
}
