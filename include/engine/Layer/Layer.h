//
// Created by 赵润朔 on 2023/7/23.
//

#ifndef RASEL_LAYER_H
#define RASEL_LAYER_H

#include "Event.h"

namespace Rasel {
    class Layer {
    public:
        explicit Layer(const std::string &name = "Layer");
        virtual ~Layer();
        
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event &event) {}
    
        [[nodiscard]] inline const std::string& GetName() const {return m_DebugName;}
    protected:
        std::string m_DebugName;
    };
}


#endif //RASEL_LAYER_H
