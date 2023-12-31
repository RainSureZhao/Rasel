//
// Created by 赵润朔 on 2023/7/23.
//

#include "LayerStack.h"

namespace Rasel {
    
    void LayerStack::PushLayer(Scope<Layer> layer) {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
        m_LayerInsertIndex ++;
    }
    void LayerStack::PushOverlay(Scope<Layer> overlay) {
        m_Layers.emplace_back(std::move(overlay));
    }
    void LayerStack::PopLayer(Scope<Layer> layer) {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if(it != m_Layers.end()) {
            layer->OnDetach();
            m_Layers.erase(it);
            m_LayerInsertIndex --;
        }
    }
    void LayerStack::PopOverlay(Scope<Layer> overlay) {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if(it != m_Layers.end()) {
            overlay->OnDetach();
            m_Layers.erase(it);
        }
    }

    LayerStack::~LayerStack() {
        for(auto &layer : m_Layers)
            layer->OnDetach();
    }
} // Rasel