#pragma once
#pragma warning (disable : 26495)
#include <d3dx9.h>
#pragma warning (default : 26495)

class cRenderer
{
private:
    LPDIRECT3DDEVICE9 m_device;
    LPD3DXSPRITE m_sprite;
public:
    cRenderer();
    ~cRenderer();

    bool Init(HWND _hWnd);

    bool Begin();
    bool End();
};

