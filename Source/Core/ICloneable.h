#pragma once

#include <memory>

namespace tg
{

class ICloneable
{
/**@section Constructor */
public:
    ICloneable() = default;
    ICloneable(const ICloneable&) = delete;
    ICloneable(ICloneable&&) = delete;

/**@section Destructor */
public:
    virtual ~ICloneable() = default;

/**@section Operator */
public:
    ICloneable& operator=(const ICloneable& rhs) noexcept = delete;
    ICloneable& operator=(ICloneable&& rhs) noexcept = delete;

/**@section Method */
public:
    [[nodiscard]] virtual std::shared_ptr<ICloneable> Clone() = 0;
    [[nodiscard]] std::shared_ptr<const ICloneable> Clone() const;
};
    
inline std::shared_ptr<const ICloneable> ICloneable::Clone() const
{
    return const_cast<ICloneable*>(this)->Clone();
}

}
