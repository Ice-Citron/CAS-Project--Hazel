#pragma once

#include "Hazel/Core.h"
#include "Layer.h"

#include <vector>


namespace Hazel {

	class HAZEL_API LayerStack {

	public:

		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:

		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}

/*
----------------------------------------------------------Notes about LayerStack class----------------------------------------------------------
-- Layer Stack: The engine maintains a stack of layers. Layers can be enabled or disabled, similar to how layers can be shown or hidden in 
   Photoshop. Each layer in the stack is updated according to its order in the stack. It allows adding and removing layers and overlays. 
   Overlays are always rendered last and are useful for UI elements that should be on top of other content.

-- Event Handling: Event handling in layers is inverse to the rendering order. The topmost layer (the last rendered) gets the first chance 
   to handle an event. If an event is handled by a layer, it doesn't propagate to lower layers. This is crucial for UI elements that overlay 
   the game content. Practical Implications:

   ** UI Interaction: Ensures that UI elements receive input first and can prevent game logic from reacting to UI interactions.
   ** Debugging and Tools: Debug layers or tools can intercept events without affecting the game state.
   ** Gameplay Layers: Different gameplay layers can handle events differently, allowing for complex game logic.

-- Application Class Integration: "Application" now includes a LayerStack. It forwards events to layers and calls their update methods.



-- Adding Layers: When a new layer is added to the stack, it's placed below the overlays but above the existing layers. This ensures that 
   overlays always remain on top of regular layers.

-- Overlays: Overlays are a special type of layer that always render last. This is crucial for UI elements that need to be on top of other 
   content, like menus or HUDs.

-- Updating Layers: During each iteration of the game loop, each layer in the stack is updated in order. This means that layers added earlier 
   to the stack are updated before the layers added later. Update Order && Render Order:

   ** Update Order: The layers at the bottom of the stack are updated first. This means their logic, such as input processing or state changes, 
      is handled before the layers above them. This order is important for game logic and ensuring that dependencies between layers are resolved correctly.
   ** Render Order: Typically, the rendering follows the update order. The layers at the bottom are usually rendered first. This is because the visual 
      elements of lower layers need to be drawn before the elements of higher layers can be drawn over them. For example, the game world would be rendered before the UI elements that overlay it.

*/

