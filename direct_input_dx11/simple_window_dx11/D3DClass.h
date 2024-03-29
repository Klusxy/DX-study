#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <iostream>
using namespace DirectX;

class D3DClass
{
public:
	D3DClass();
	~D3DClass();
	bool init(int, int, bool, HWND, bool, float, float);
	void stop();
	void beginScene(float, float, float, float);
	void endScene();

	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

	void getProjectionMatrix(XMMATRIX&);
	void getWorldMatrix(XMMATRIX&);
	void getOrthoMatrix(XMMATRIX&);

	void turnZBufferOn();
	void turnZBufferOff();

	void turnOnAlphaBlending();
	void turnOffAlphaBlending();

private:
	void printInfo(int, int);

private:
	bool m_vsync_enabled;
	IDXGISwapChain *m_swapChain;
	ID3D11Device *m_device;
	ID3D11DeviceContext *m_deviceContext;
	ID3D11RenderTargetView *m_renderTargetView;
	ID3D11Texture2D *m_depthStencilBuffer;
	ID3D11DepthStencilState *m_depthStencilState;
	ID3D11DepthStencilState *m_depthDisabledStencilState;
	ID3D11BlendState *m_alphaEnableBlendState;
	ID3D11BlendState *m_alphaDisableBlendState;
	ID3D11DepthStencilView *m_depthStencilView;
	ID3D11RasterizerState *m_rasterState;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;
};