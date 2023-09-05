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
        LayerStack() = default;
        ~LayerStack();
        
        void PushLayer(Scope<Layer> layer);
        void PushOverlay(Scope<Layer> overlay);
        void PopLayer(Scope<Layer> layer);
        void PopOverlay(Scope<Layer> overlay);
        
        LayerVectorIter begin() {return m_Layers.begin();}
        LayerVectorIter end() {return m_Layers.end();}
        std::vector<Scope<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin();}
        std::vector<Scope<Layer>>::reverse_iterator rend() {return m_Layers.rend();}

        [[nodiscard]] std::vector<Scope<Layer>>::const_iterator begin() const {return m_Layers.begin();}
        [[nodiscard]] std::vector<Scope<Layer>>::const_iterator end() const {return m_Layers.end();}
        [[nodiscard]] std::vector<Scope<Layer>>::const_reverse_iterator rbegin() const { return m_Layers.rbegin();}
        [[nodiscard]] std::vector<Scope<Layer>>::const_reverse_iterator rend() const {return m_Layers.rend();}
        [[nodiscard]] int size() const {return static_cast<int>(m_Layers.size());}
    private:
        std::vector<Scope<Layer>> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };

} // Rasel

#endif //RASEL_LAYERSTACK_H
