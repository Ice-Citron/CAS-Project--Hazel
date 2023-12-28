#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"


namespace Hazel {

	class HAZEL_API Layer {
	// This is essentially an interface, and most methods will be overrided to tailor to the needs of the specific Layer subclasses. 
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		
		// Each layer subclass' OnEvent function, overriden to tune to subclass' specific needs
		virtual void OnEvent(Event& event) {} 

		inline const std::string& GetName() const { return m_DebugName; }

	protected:

		std::string m_DebugName;
	};
}

/*
-- Layer lifecycle: Each layer can react to being attached/detached from the layer stack, update each frame, and handle events.

-- Beyond Graphics: Layers are not just for graphics. They are crucial for handling events and update logic. Each layer in the layer stack 
   can be updated in each iteration of the game loop.

-- Layer Class: This class represents a single layer. It includes methods for lifecycle events (attach, detach), updating, and event handling. 
   Developers can subclass this to create specific layers like a game layer or UI layer.

*/