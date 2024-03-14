#ifndef SOGE_RENDERER_THROW_MACROSES_HPP
#define SOGE_RENDERER_THROW_MACROSES_HPP

#include "SOGE/Graphics/DebugSystem/GraphicsException.hpp"

#define CHWND_EXCEPT( hr ) HrException( __LINE__,__FILE__,(hr) )
#define CHWND_LAST_EXCEPT() HrException( __LINE__,__FILE__,GetLastError() )
//#define CHWND_NOGFX_EXCEPT() NoGfxException( __LINE__,__FILE__ )

#endif // !SOGE_RENDERER_THROW_MACROSES_HPP
