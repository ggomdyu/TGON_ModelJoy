#include "PrecompiledHeader.h"

#include <algorithm>

#include "GameObject.h"

namespace tgon
{

GameObject::GameObject(const FixedHashString32& name) :
    m_name(name)
{
}

void GameObject::Update()
{
    if (m_isActivated == false)
    {
        return;
    }

    m_transform.Update();

    for (auto& component : m_components)
    {
        component->Update();
    }
}
    
void GameObject::SetName(const FixedHashString32& name)
{
    m_name = name;
}

const FixedHashString32& GameObject::GetName() const noexcept
{
    return m_name;
}

void GameObject::AddComponent(Component* component)
{
    component->SetOwner(this);

    auto predicate = [&](const std::unique_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), component->GetRTTI()->GetHashCode(), predicate);

    m_components.emplace(iter, component);
}
    
bool GameObject::RemoveComponent(size_t componentId)
{
    auto predicate = [&](const std::unique_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), componentId, predicate);
    if (iter != m_components.end())
    {
        m_components.erase(iter);
        return true;
    }
    else
    {
        return false;
    }
}

Component* GameObject::GetComponent(size_t componentId)
{
    auto predicate = [&](const std::unique_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), componentId, predicate);
    if (iter != m_components.end())
    {
        return iter->get();
    }
    else
    {
        return nullptr;
    }
}

Transform& GameObject::GetTransform() noexcept
{
    return m_transform;
}

const Transform& GameObject::GetTransform() const noexcept
{
    return m_transform;
}

void GameObject::SetActivate(bool isActivate)
{
    m_isActivated = isActivate;
}

bool GameObject::IsActivated() const noexcept
{
    return m_isActivated;
}

} /*namespace tgon*/
