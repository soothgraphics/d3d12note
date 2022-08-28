// need to add Common/d3dx12.h to the include path in visual studio before running, only tested on windows 11
#include <d3dx12.h>
#include <DirectXCollision.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <Windows.h>
#include <algorithm>
#include <array>
#include <comdef.h>
#include <cstdint>
#include <d3d12.h>
#include <d3dcompiler.h>
#include <dxgi1_4.h>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <windowsx.h>
#include <wrl.h>

using namespace Microsoft::WRL;

HWND mhMainWnd = 0;
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine,
                   int nShowCmd) {
#if defined(DEBUG) | defined(_DEBUG)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = MainWndProc;
  wc.cbClsExtra =
      0; 
  wc.cbWndExtra =
      0; 
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(0, IDC_ARROW); 
  wc.hCursor = LoadCursor(0, IDC_ARROW);
  wc.hbrBackground =
      (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = 0;
  wc.lpszClassName = L"MainWnd";
  if (!RegisterClass(&wc)) {
    MessageBox(0, L"RegisterClass Failed", 0, 0);
    return 0;
  }

  RECT R;
  R.left = 0;
  R.top = 0;
  R.right = 1280;
  R.bottom = 720;
  AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW,
                   false);
  int width = R.right - R.left;
  int hight = R.bottom - R.top;

  mhMainWnd = CreateWindow(L"MainWnd", L"DX12Initialize", WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, width, hight, 0, 0,
                           hInstance, 0);
  if (!mhMainWnd) {
    MessageBox(0, L"CreatWindow Failed", 0, 0);
    return 0;
  }
  ShowWindow(mhMainWnd, nShowCmd);
  UpdateWindow(mhMainWnd);

  MSG msg = {0};
  BOOL bRet = 0;
  while (bRet = GetMessage(&msg, 0, 0, 0) != 0) {
    if (bRet == -1) {
      MessageBox(0, L"GetMessage Failed", L"Errow", MB_OK);
    }
    else {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  return (int)msg.wParam;
}


LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam,
                             LPARAM lParam) {
  switch (msg) {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  default:
    break;
  }
  return DefWindowProc(hwnd, msg, wParam, lParam);
}
