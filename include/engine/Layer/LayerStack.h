//
// Created by 赵润朔 on 2023/7/23.
//

#ifndef RASEL_LAYERSTACK_H
#define RASEL_LAYERSTACK_H

#include "Layer.h"
#include "stdafx.h"
namespace Rasel {
    using LayerVectorIter = std::vector<std::unique_ptr<Layer>>::iterator;
    class LayerStack {
    public:
        LayerStack();
        ~LayerStack() = default;
        
        void PushLayer(std::unique_ptr<Layer> layer);
        void PushOverlay(std::unique_ptr<Layer> overlay);
        void PopLayer(std::unique_ptr<Layer> layer);
        void PopOverlay(std::unique_ptr<Layer> overlay);
        
        LayerVectorIter begin() {return m_Layers.begin();}
        LayerVectorIter end() {return m_Layers.end();}
        
        [[nodiscard]] int size() const {return m_Layers.size();}
    private:
        std::vector<std::unique_ptr<Layer>> m_Layers;
        LayerVectorIter m_LayerInsert;
    };

} // Rasel

#endif //RASEL_LAYERSTACK_H
