#pragma once

#include <stdlib.h>
#include <unordered_set>
#include <chroma/events/Event.h>

//from: https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Layer.h
namespace Chroma
{
    class Layer
    {
    public:
        Layer(const std::string& name = "New Layer")
            : m_layer_name(name) 
        {}
        virtual ~Layer() = default;

        inline std::string GetLayerName() { return m_layer_name; }

        inline std::string SetLayerName(const std::string& name) { m_layer_name = name; }

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

    private:
        std::string m_layer_name;
    };
}