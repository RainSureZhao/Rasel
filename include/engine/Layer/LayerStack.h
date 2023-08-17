//
// Created by 赵润朔 on 2023/7/23.
//

#ifndef RASEL_LAYERSTACK_H
#define RASEL_LAYERSTACK_H

#include "Layer.h"
#include "stdafx.h"
#include "Core.h"
namespace Rasel {
    using LayerVectorIter = std::vector<Scope<Layer>>::iterator;
    class LayerStack {
    public:
        LayerStack();
        ~LayerStack() = default;
        
        void PushLayer(Scope<Layer> layer);
        void PushOverlay(Scope<Layer> overlay);
        void PopLayer(Scope<Layer> layer);
        void PopOverlay(Scope<Layer> overlay);
        
        LayerVectorIter begin() {return m_Layers.begin();}
        LayerVectorIter end() {return m_Layers.end();}
        
        [[nodiscard]] int size() const {return static_cast<int>(m_Layers.size());}
    private:
        std::vector<Scope<Layer>> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };

} // Rasel

#endif //RASEL_LAYERSTACK_H
