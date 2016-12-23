#include "Utilities.hpp"
#include "GameEngine/GameEngine.h"



namespace ASSB
{
	// Static initialization
	Utilities *Utilities::Instance = nullptr;

	// Constructor
	Utilities::Utilities()
		: EventSystem::ObjectEventManager(Globals::EventSystemInstance)
		, activeIterpolators_()
		, lastTime_(0)
	{
		if (Instance == nullptr)
			Instance = this;
		else
			throw std::exception("Only one instance of utilities may exist.");

		Connect(this, &Utilities::onUpdate);
	}

	void Utilities::InterpolatePos(Globals::ObjectID id, Graphics::Vector4 desto, double ms)
	{
		ComponentHandle<TransformComponent> comp = GameEngine::Instance->GetComponent<TransformComponent>(id);
		activeIterpolators_.push_back({ id, comp->GetPosition(), desto, ms / 1000.0, lastTime_});
	}

	void Utilities::onUpdate(UpdateEvent *e)
	{
		lastTime_ = e->Time.RunTime;
		// For all actively interpolating objects, update positon.
		for (size_t i = 0; i < activeIterpolators_.size();)
		{
			InterpObj &obj = activeIterpolators_[i];
			ComponentHandle<TransformComponent> comp = GameEngine::Instance->GetComponent<TransformComponent>(obj.ID);
			float pos0to1 = static_cast<float>((e->Time.RunTime - obj.StartTime) / obj.Length);

			if (pos0to1 >= 1)
			{
				comp->SetPosition(obj.Desto);
				activeIterpolators_.erase(activeIterpolators_.begin() + static_cast<int>(i));
				continue;
			}

			comp->SetPosition(obj.Desto * (pos0to1 * pos0to1 ) + obj.Start * (1 - pos0to1 * pos0to1));
			++i;
		}
	}
}
