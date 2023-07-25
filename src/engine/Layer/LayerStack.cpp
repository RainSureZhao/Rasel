//
// Created by 赵润朔 on 2023/7/23.
//

#include "LayerStack.h"

namespace Rasel {
    LayerStack::LayerStack() {
        m_LayerInsert = m_Layers.begin();
    }
    
    void LayerStack::PushLayer(std::unique_ptr<Layer> layer) {
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, std::move(layer));
    }
    void LayerStack::PushOverlay(std::unique_ptr<Layer> overlay) {
        m_Layers.emplace_back(std::move(overlay));
    }
    void LayerStack::PopLayer(std::unique_ptr<Layer> layer) {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if(it != m_Layers.end()) {
            m_Layers.erase(it);
            m_LayerInsert --;
        }
    }
    void LayerStack::PopOverlay(std::unique_ptr<Layer> overlay) {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if(it != m_Layers.end()) {
            m_Layers.erase(it);
        }
    }
} // Rasel