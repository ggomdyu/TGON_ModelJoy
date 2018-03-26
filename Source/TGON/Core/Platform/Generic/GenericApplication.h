/**
 * @filename    GenericApplication.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       The abstracted application class which is Plaform-agnostic.
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>
#include <type_traits>

#include "Core/Object/Object.h"

#include "../Config.h"

#include "GenericApplicationFwd.h"

#define TGON_DECLARE_APPLICATION(className)\
    namespace tgon\
    {\
    std::shared_ptr<GenericApplication> MakeApplication()\
    {\
        static_assert(std::is_convertible<className*, GenericApplication*>::value, "TGON_DECLARE_APPLICATION accepts only class that inherited from GenericApplication.");\
        return std::make_shared<className>();\
    }\
    } /* namespace tgon */

namespace tgon
{

class TGON_API GenericApplication :
    private boost::noncopyable,
    public Object
{
public:
    TGON_RUNTIME_OBJECT(GenericApplication)

/* @section Public constructor */
public:
    GenericApplication() = default;
    GenericApplication(const std::shared_ptr<GenericWindow>& window);

/* @section Public destructor */
public:
    virtual ~GenericApplication() override = default;

/* @section Public method */
public:
    virtual void MessageLoop() = 0;
    virtual void Terminate() = 0;
    virtual void ShowMessageBox(const char* message) const;
    virtual void ShowMessageBox(const char* message, MessageBoxIconType iconType) const;
    virtual void ShowMessageBox(const char* title, const char* message) const;
    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxIconType iconType) const = 0;

    const std::shared_ptr<GenericWindow>& GetRootWindow() const noexcept;

/* @section Public event handler */
public:
    virtual void OnWillLaunch() {}
    virtual void OnDidLaunch() {}
    virtual void OnWillTerminate() {}
    virtual void OnWillCloseWindow(const std::shared_ptr<GenericWindow>&) {}
    virtual void OnDidCloseWindow(const std::shared_ptr<GenericWindow>&) {}
    virtual void OnUpdate() {}

/* @section Protected variable */
protected:
    std::shared_ptr<GenericWindow> m_rootWindow;
};

} /* namespace tgon */