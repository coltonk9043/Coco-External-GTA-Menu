#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <dwmapi.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

class Graphics
{
	ID2D1Factory* pD2DFactory;
	ID2D1HwndRenderTarget* pD2DRenderTarget;
	ID2D1SolidColorBrush* pBrush;
	IDWriteFactory* pDWriteFactory;
	IDWriteTextFormat* pTextFormat;

public:
	Graphics();
	~Graphics();

	bool Init(HWND hWnd);

	void BeginDraw() { pD2DRenderTarget->BeginDraw(); }
	void EndDraw() { pD2DRenderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b, float alpha);

	void DrawCircle(int x, int y, float radius, float r, float g, float b, float a);
	void DrawRectangle(int x, int y, int width, int height, float r, float g, float b, float a);
	void DrawFilledRectangle(int x, int y, int width, int height, float r, float g, float b, float a);
	void DrawOutlinedRectangle(int x, int y, int width, int height, float r, float g, float b, float a);

	void DrawString(const wchar_t*, float x, float y, float r, float g, float b, float a);
};

