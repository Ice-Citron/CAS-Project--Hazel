#include "hzpch.h"
#include "LayerStack.h"


namespace Hazel {

	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {

		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {

		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {

		// Adds a new element to the end of the vector.
		// CONSTRUCTS an element in-place at the back of the vector, eliminating the need for a copy or move of the element.
		m_Layers.emplace_back(overlay); 
	}

	void LayerStack::PopLayer(Layer* layer) {

		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	// About how the m_LayerInsert iterator works
	/*
	-- Emplace returns an iterator pointing to the newly emplaced element. m_LayerInsert is then updated to this
	   new iterator.

	-- Because emplace inserts the new element before the position of the iterator it is given, after the insertion,
	   m_LayerInsert still points to the position just after the newly inserted layer. This means that if PushLayer is
	   called again, the next layer will be inserted at the correct position, maintaining the order of layers.

	-- When PopLayer is called, and a layer is removed, m_LayerInsert is decremented to ensure it still points to the 
	   correct insertion point. This works because layers are always inserted before m_LayerInsert, so removing a layer
	   would move m_LayerInsert back one position in the vector.

	-- In contrast, overlays are simply added to the end of the vector with emplace_back, and they do not affect the 
	   m_LayerInsert iterator.
	*/

	void LayerStack::PopOverlay(Layer* overlay) {

		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
		}
	}
}