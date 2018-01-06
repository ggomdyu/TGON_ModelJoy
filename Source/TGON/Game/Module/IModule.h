/**
 * @filename    IModule.h
 * @author      ggomdyu
 * @since       07/13/2016
 */

#pragma once
#include "Core/Object/Object.h"

#include <boost/noncopyable.hpp>

namespace tgon
{
namespace game
{

class TGON_API IModule :
    public core::Object
{
public:
    TGON_RUNTIME_OBJECT(IModule)

/* @section Public constructor */
public:
    IModule() = default;
    virtual ~IModule() = 0;

/* @section Public method */
public:
    virtual void Update() = 0;
};

} /* namespace game */
} /* namespace tgon */