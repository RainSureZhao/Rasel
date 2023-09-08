//
// Created by 赵润朔 on 2023/7/23.
//

#ifndef RASEL_LAYER_H
#define RASEL_LAYER_H

#include "Event.h"
#include "Timestep.h"

namespace Rasel {
    class Layer {
    public:
        explicit Layer(const std::string &debugName = "Layer");
        virtual ~Layer() = default;
        
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep timestep) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event &event) {}
    
        [[nodiscard]] const std::string& GetName() const {return m_DebugName;}
    protected:
        std::string m_DebugName;
    };
}


#endif //RASEL_LAYER_H
