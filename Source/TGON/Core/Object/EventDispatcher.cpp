#include "PrecompiledHeader.h"

#include "EventDispatcher.h"

namespace tgon
{

void EventDispatcher::SubscribeEvent(const HashStringView& eventName, const EventHandler& eventHandler)
{
    m_eventHandlers[eventName.GetHashCode()][reinterpret_cast<uintptr_t>(&eventHandler)] = eventHandler;
}
    
void EventDispatcher::SubscribeEvent(const HashStringView& eventName, EventHandler&& eventHandler)
{
    m_eventHandlers[eventName.GetHashCode()][reinterpret_cast<uintptr_t>(&eventHandler)] = std::move(eventHandler);
}
    
bool EventDispatcher::UnsubscribeEvent(const HashStringView& eventName, const EventHandler& eventHandler)
{
    auto iter = m_eventHandlers.find(eventName.GetHashCode());
    if (iter == m_eventHandlers.end())
    {
        return false;
    }
    
    iter->second.erase(reinterpret_cast<uintptr_t>(&eventHandler));
    
    return true;
}
    
void EventDispatcher::DispatchEvent(const HashStringView& eventName)
{
    auto iter = m_eventHandlers.find(eventName.GetHashCode());
    if (iter == m_eventHandlers.end())
    {
        return;
    }
    
    for (auto& handler : iter->second)
    {
        handler.second();
    }
}
    
} /* namespace tgon */