#ifndef SOGE_GRAPHICS_THROW_MACROSES_HPP
#define SOGE_GRAPHICS_THROW_MACROSES_HPP

#include "SOGE/Graphics/DebugSystem/GraphicsException.hpp"
#include "SOGE/Graphics/DebugSystem/DXGIInfoManager.hpp"

// HRESULT hr should exist in the local scope for these macros to work

#define GFX_EXCEPT_NOINFO(hr) HrException( __LINE__,__FILE__,(hr) )
#define GFX_THROW_NOINFO(hrcall) if( FAILED( hr = (hrcall) ) ) throw HrException( __LINE__,__FILE__,hr )

#ifndef _NDEBUG
#define GFX_EXCEPT(hr) HrException( __LINE__,__FILE__,(hr), DXGIInfoManager::GetInstance()->GetMessages() )
#define GFX_THROW_INFO(hrcall) DXGIInfoManager::GetInstance()->Set(); if( FAILED( hr = (hrcall) ) ) throw GFX_EXCEPT(hr)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) DeviceRemovedException( __LINE__,__FILE__,(hr), DXGIInfoManager::GetInstance()->GetMessages() )
#define GFX_THROW_INFO_ONLY(call) DXGIInfoManager::GetInstance()->Set(); (call); {auto v = DXGIInfoManager::GetInstance()->GetMessages(); if(!v.empty()) {throw InfoException( __LINE__,__FILE__,v);}}
#else
#define GFX_EXCEPT(hr) HrException( __LINE__,__FILE__,(hr) )
#define GFX_THROW_INFO(hrcall) GFX_THROW_NOINFO(hrcall)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) DeviceRemovedException( __LINE__,__FILE__,(hr) )
#define GFX_THROW_INFO_ONLY(call) (call)
#endif

// macro for importing infomanager into local scope
// this.GetInfoManager(Graphics& gfx) must exist
#ifdef _NDEBUG
#define INFOMAN(gfx) HRESULT hr
#else
#define INFOMAN(gfx) HRESULT hr; DXGIInfoManager* infoManager = GetInfoManager((gfx))
#endif

#ifdef _NDEBUG
#define INFOMAN_NOHR(gfx)
#else
#define INFOMAN_NOHR(gfx) DxgiInfoManager& infoManager = GetInfoManager((gfx))
#endif

#endif // !SOGE_GRAPHICS_THROW_MACROSES_HPP
