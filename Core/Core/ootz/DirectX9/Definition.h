#pragma once

/* std::unique_ptr */
#include <memory>

#include <d3dx9.h>

namespace ootz
{

namespace DirectX9
{

using EffectPtr = std::unique_ptr<ID3DXEffect>;
using TexturePtr = std::unique_ptr<IDirect3DTexture9>;
using SurfacePtr = std::unique_ptr<IDirect3DSurface9>;

} // namespace directx9

} // namespace ootz