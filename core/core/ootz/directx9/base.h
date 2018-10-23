#pragma once

#include <d3dx9.h>

namespace ootz
{

namespace directx9
{

using EffectPtr = std::unique_ptr<ID3DXEffect>;
using TexturePtr = std::unique_ptr<IDirect3DTexture9>;
using SurfacePtr = std::unique_ptr<IDirect3DSurface9>;

} // namespace directx9

} // namespace ootz