#include "cRenderer.h"

cRenderer::cRenderer()
    : m_device(nullptr), m_sprite(nullptr)
{
    
}

cRenderer::~cRenderer()
{
    if (m_sprite)
        m_sprite->Release();
    if (m_device)
        m_device->Release();
}

bool cRenderer::Init(HWND _hWnd)
{
    auto d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
    if (nullptr == d3d9)
        return false;

    D3DPRESENT_PARAMETERS d3dpp;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferWidth = 0;
    d3dpp.BackBufferHeight = 0;
    d3dpp.EnableAutoDepthStencil = true;
    d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
    d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    d3dpp.hDeviceWindow = _hWnd;
    d3dpp.MultiSampleQuality = 0;
    d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.Windowed = true;

    auto result = d3d9->CreateDevice(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        _hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp,
        &m_device);

    d3d9->Release();
    if (FAILED(result))
        return false;

    result = D3DXCreateSprite(m_device, &m_sprite);
    if (FAILED(result))
        return false;

    return true;
}

bool cRenderer::Begin()
{
    m_device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

    if (FAILED(m_device->BeginScene()))
        return false;

    if (FAILED(m_sprite->Begin(D3DXSPRITE_ALPHABLEND)))
    {
        m_device->EndScene();
        return false;
    }

    return true;
}

bool cRenderer::End()
{
    m_sprite->End();
    m_device->EndScene();

    return SUCCEEDED(m_device->Present(nullptr, nullptr, nullptr, nullptr));
}
