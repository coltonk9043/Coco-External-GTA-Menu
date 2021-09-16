#include "Graphics.h"

Graphics::Graphics() {
	pD2DFactory = NULL;
	pD2DRenderTarget = NULL;
	pBrush = NULL;
	pDWriteFactory = NULL;
	pTextFormat = NULL;
}

Graphics::~Graphics() {
	if (pD2DFactory) pD2DFactory->Release();
	if (pD2DRenderTarget) pD2DRenderTarget->Release();
	if (pBrush) pBrush->Release();
	if (pDWriteFactory) pDWriteFactory->Release();
}

bool Graphics::Init(HWND windowHandle) {
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	if (res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&pD2DRenderTarget);
	if (res != S_OK) return false;
	res = pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &pBrush);
	if (res != S_OK) return false;
	res = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(&pDWriteFactory));
	if (res != S_OK) return false;
	res = pDWriteFactory->CreateTextFormat(
		L"Ariel",								// Font family name
		NULL,									// Font collection(NULL sets it to the system font collection)
		DWRITE_FONT_WEIGHT_DEMI_BOLD,			// Weight
		DWRITE_FONT_STYLE_NORMAL,				// Style
		DWRITE_FONT_STRETCH_NORMAL,				// Stretch
		18.0f,									// Size    
		L"en-us",								// Local
		&pTextFormat							// Pointer to recieve the created object
	);
	if (res != S_OK) return false;

	return true;
}

void Graphics::ClearScreen(float r, float g, float b, float alpha) {
	pD2DRenderTarget->Clear(D2D1::ColorF(r, g, b, alpha));
}
void Graphics::DrawCircle(int x, int y, float radius, float r, float g, float b, float a) {
	pBrush->SetColor(D2D1::ColorF(r, g, b, a));
	pD2DRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), pBrush, 3.0f);
}


void Graphics::DrawRectangle(int x, int y, int width, int height, float r, float g, float b, float a) {
	pBrush->SetColor(D2D1::ColorF(r, g, b, a));
	D2D1_RECT_F rect = D2D1::RectF(
		x,
		y,
		x + width,
		y + height
	);
	pD2DRenderTarget->DrawRectangle(rect, pBrush);
}

void Graphics::DrawFilledRectangle(int x, int y, int width, int height, float r, float g, float b, float a) {
	pBrush->SetColor(D2D1::ColorF(r, g, b, a));
	D2D1_RECT_F rect = D2D1::RectF(
		x,
		y,
		x + width,
		y + height
	);
	pD2DRenderTarget->FillRectangle(rect, pBrush);
}

void Graphics::DrawOutlinedRectangle(int x, int y, int width, int height, float r, float g, float b, float a) {
	pBrush->SetColor(D2D1::ColorF(r, g, b, a));
	D2D1_RECT_F rect = D2D1::RectF(
		x,
		y,
		x + width,
		y + height
	);
	pD2DRenderTarget->FillRectangle(rect, pBrush);
	pBrush->SetColor(D2D1::ColorF(0.1f, 0.1f, 0.1f, 1.0f));
	pD2DRenderTarget->DrawRectangle(rect, pBrush, 2.0f);
}

void Graphics::DrawString(const wchar_t* str, float x, float y, float r, float g, float b, float a) {
	int length = wcslen(str);
	pBrush->SetColor(D2D1::ColorF(r, g, b, a));
	D2D1_RECT_F rect = D2D1::RectF(
		x,
		y,
		1920,
		1080
	);
	pD2DRenderTarget->DrawTextW(str, length, pTextFormat, rect, pBrush);
}


