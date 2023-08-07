//
// Created by 赵润朔 on 2023/8/7.
//

#ifndef RASEL_TIMESTEP_H
#define RASEL_TIMESTEP_H

namespace Rasel {
    class Timestep {
    public:
        Timestep(float time = 0.0f) : m_Time(time) {}
        
        operator float() const {return m_Time;}
        
        [[nodiscard]] float GetSeconds() const {return m_Time;}
        [[nodiscard]] float GetMilliseconds() const {return m_Time * 1000.0f;}
    private:
        float m_Time;
    };
}

#endif //RASEL_TIMESTEP_H
