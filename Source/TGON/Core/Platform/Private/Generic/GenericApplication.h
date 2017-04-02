/**
 * filename GenericApplication.h
 * author   ggomdyu
 * since    03/20/2016
 */

#pragma once
#include "../../TConfig.h"

namespace tgon
{

template <typename PlatformApplicationTy>
class TGON_API GenericApplication
{
public:
	GenericApplication() = delete;
	~GenericApplication() = delete;
};

} /* namespace tgon */