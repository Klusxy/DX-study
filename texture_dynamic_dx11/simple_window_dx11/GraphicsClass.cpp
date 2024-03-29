#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	m_direct3D = 0;
	//m_colorShader = 0;
	m_model = 0;
	m_camera = 0;
	fileIndex = 0;
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::init(int screenWidth, int screenHeight, HWND hWnd)
{
	bool result;

	m_direct3D = new D3DClass;
	if (!m_direct3D)
	{
		return false;
	}
	result = m_direct3D->init(screenWidth, screenHeight, VSYNC_ENABLED, hWnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hWnd, L"d3d11 init error", L"Error", MB_OK);
		return false;
	}

	m_camera = new CameraClass;
	m_camera->setPosition(0.0f, 0.0f, -10.0f);

	m_model = new ModelClass;
	if (!m_model)
	{
		return false;
	}
	//result = m_model->init(m_direct3D->getDevice(), m_direct3D->getDeviceContext(), "../../image_source/stone01.tga");
	result = m_model->init(m_direct3D->getDevice(), m_direct3D->getDeviceContext(), "../../image_source/video/00.png");
	if (!result)
	{
		MessageBox(hWnd, L"model init error", L"Error", MB_OK);
		return false;
	}

	m_textureShader = new TextureShaderClass;
	if (!m_textureShader)
	{
		return false;
	}
	result = m_textureShader->init(m_direct3D->getDevice(), hWnd);
	if (!result)
	{
		MessageBox(hWnd, L"shader init error", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::stop()
{
	if (m_direct3D)
	{
		m_direct3D->stop();
		delete m_direct3D;
		m_direct3D = 0;
	}

	if (m_model)
	{
		m_model->stop();
		delete m_model;
		m_model = 0;
	}

	if (m_camera)
	{
		delete m_camera;
		m_camera = 0;
	}

	if (m_textureShader)
	{
		m_textureShader->stop();
		delete m_textureShader;
		m_textureShader = 0;
	}
}

bool GraphicsClass::frame()
{
	bool result;
	result = render();
	if (!result)
	{
		return false;
	}
	return true;
}

bool GraphicsClass::render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;
	m_direct3D->beginScene(0.0f, 0.0f, 0.0f, 1.0f);
	m_camera->render();

	m_direct3D->getWorldMatrix(worldMatrix);
	m_camera->getViewMatrix(viewMatrix);
	m_direct3D->getProjectionMatrix(projectionMatrix);
	//m_direct3D->getOrthoMatrix(projectionMatrix);

	m_model->render(m_direct3D->getDeviceContext());
	char filename[40];
	sprintf(filename, "../../image_source/video/%02d.png", fileIndex);
	result = m_model->updateTexture(m_direct3D->getDeviceContext(), filename);
	if (!result)
	{
		return false;
	}
	fileIndex++;
	if (fileIndex == 29)
		fileIndex = 0;
	result = m_textureShader->render(m_direct3D->getDeviceContext(), m_model->getIndexCount(), m_model->getTexture(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	m_direct3D->endScene();
	return true;
}