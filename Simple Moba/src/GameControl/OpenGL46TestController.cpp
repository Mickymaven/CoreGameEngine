#include "OpenGL46TestController.h"

OpenGL46TestController::OpenGL46TestController() : TimestepController()
{
	m_gameElapsedTime=0.0f;
	m_gameStartTime = LARGE_INTEGER ();
	m_gameCurrentTime = LARGE_INTEGER();
	m_FrequencyQuadPart=0.0f;
	tLastCount = LARGE_INTEGER();

	//firstQuit = true;

	m_Camera = 0;
	m_Model = 0;
	m_ColorShader = 0;
	m_textureShader = 0;
	m_LightShader = 0;
	m_Light = 0;
}

OpenGL46TestController::~OpenGL46TestController()
{
}

bool OpenGL46TestController::Initialize(OpenGL4Object * object, HWND hwnd)
{
	bool result;

	m_OpenGL = object;

	//initialize
	m_Camera = new CameraClass;
	if (!m_Camera) return false;


	m_Camera->SetPosition(0.0f, 0.0f, -40.0f);

	//m_myCamera.Init(1.0f, g_initWidth, g_initHeight, new D3DXVECTOR3(0.0f, 0.0f, 10.0f), new D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_Model = new ModelClass();
	if (! m_Model) return false;

	result = m_Model->Initialize(object, "Resources/cube.txt", "Resources/maven.tga", 0, true);
	if (!result)
	{
		MessageBoxW(g_hwnd, L"Could not init model", L"Error", MB_OK);
		return false;
	}
	
	/*
	m_ColorShader = new OpenGL4ColorShader();
	
	result = m_ColorShader->Initialize(object, g_hwnd);
	if (!result)
	{
		MessageBoxW(g_hwnd, L"Could not shaders.", L"Error", MB_OK);

		return false;
	}
	
	// Create the texture shader object.
	m_textureShader = new OpenGL4TextureShader;
	if (!m_textureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_textureShader->ShaderInitialize(object, hwnd);
	if (!result)
	{
		MessageBoxW(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}*/

	m_LightShader = new OpenGL4LightShader();

	if (!m_LightShader) return false;

	result = m_LightShader->Initialize(m_OpenGL, hwnd);
	if (!result)
	{
		MessageBoxW(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	m_Light = new LightClass();
	if (!m_Light) return false;

	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, -1.0f, 1.0f);
	m_Light->SetAmbientLight(0.25f, 0.25f, 0.25f, 1.0f);


	return true;
}

INT OpenGL46TestController::Run()
{
	/*

	//run

	QueryPerformanceCounter(&m_gameStartTime);
	QueryPerformanceCounter(&m_gameCurrentTime);
	QueryPerformanceCounter(&tLastCount);


	isDone = false;

	g_msg.message = 0;

	while (!isDone)
	{
		if (!ProcessMessages())
		{
			QueryPerformanceCounter(&tCurrentCount);

			timeElapsed = (tCurrentCount.QuadPart - tLastCount.QuadPart) / (float)tFrequency.QuadPart;

			Update(timeElapsed);

			Render();

			Yield();
			tLastCount = tCurrentCount;
		}
	}


	//shutdown

	if (m_ColorShader)
	{
		m_ColorShader->Shutdown(&g_OpenGL4Object, g_hwnd);
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	if (m_Model)
	{
		m_Model->Shutdown(&g_OpenGL4Object);
		delete m_Model;
		m_Model = 0;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	//shutdown finished
	*/
	return (INT)g_msg.wParam;

}

bool OpenGL46TestController::Frame()
{
	bool result;
	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += 0.0174532925f * 1.0f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

void OpenGL46TestController::Update(float deltaTime)
{
}

bool OpenGL46TestController::Render(float rotation)
{
	LMVector3 model_position = LMVector3(0.0f,0.0f,7.0f);
	LMVector3 modelRotationAxis = LMVector3(0.0f, 0.0f, 0.0f);
	LMVector3 modelScale = LMVector3(0.01f, 0.01f, 0.01f);

	

	LMMatrix4 projViewModel;
	LMMatrix4 prevProjViewModel = projViewModel;

	LMMatrix4 worldMatrix;
	LMMatrix4 viewMatrix;
	LMMatrix4 projectionMatrix;


	float lightDirection[3];
	float diffuseLightColor[4];
	float ambientLight[4];

	RenderBegin();

	//m_myCamera.Update();
	m_Camera->Render();

	
	//todo implement these with new system
	//m_OpenGL->GetWorldMatrix((float*)&worldMatrix);
	m_Camera->GetViewMatrix((float*)&viewMatrix);
	m_OpenGL->GetProjectionMatrix((float*)&projectionMatrix);
	
	



	//projectionMatrix = glm::perspective(camera.cameraFOV, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	// glm::mat4 view = camera.GetViewMatrix();


	LMMatrix4 rotationMatrix;
	LMMatrix4 translationMatrix;
	LMMatrix4 scaleMatrix;

	modelScale.set(1.0f, 1.0f, 1.0f);
	//model_position.set(3.5f*sin(0.5f*rotation), 3.5f*-cos(0.5f*rotation), 15.0f);


	worldMatrix = LMMatrix4();
	worldMatrix.identity();

	//local
	modelRotationAxis.set(1.0f, 0.1f, 0.0f);
	worldMatrix.rotate(-360.0f*rotation, modelRotationAxis);


	worldMatrix.translate(model_position);

	worldMatrix.scale(modelScale);


	//parent wrapper
	modelRotationAxis.set(1.0f, 0.0f, 0.0f);
	worldMatrix.rotate(180.0f* rotation, modelRotationAxis);
	
	model_position.set(20.0f*sin(0.5*rotation), 0.0f,0.0f);
	worldMatrix.translate(model_position);



	

	//projViewModel = projectionMatrix * viewMatrix * worldMatrix;


	




	/*
	// Set the rotation value to the matrix.
	D3DXMatrixScaling(&m_scaleMatrix, m_pScale->x, m_pScale->y, m_pScale->z);
	D3DXMatrixRotationYawPitchRoll(&m_rotationMatrix, m_pRotation->y, m_pRotation->x, m_pRotation->z);
	D3DXMatrixTranslation(&m_translationMatrix, m_pPosition->x, m_pPosition->y, m_pPosition->z);

	m_worldMatrix = m_scaleMatrix * m_rotationMatrix * m_translationMatrix;

	WorldTransform();

	// Set the matrix.
	m_D3D_Device->SetTransform(D3DTS_WORLD, &m_worldMatrix);
	*/

	LMVector3 rotatoGenerator = LMVector3(1.0f,-0.5f,0.5f);

	m_Light->GetDirection(lightDirection);
	m_Light->GetDiffuseColor(diffuseLightColor);
	m_Light->GetAmbientLight(ambientLight);

	

	//m_OpenGL->MatrixRotation((float*)&worldMatrix, (float*)&worldMatrix, rotation, (float*)&rotatoGenerator);
	//m_OpenGL->MatrixRotationX((float*)&worldMatrix, rotation);
	//m_OpenGL->MatrixRotation((float*)&viewMatrix, (float*)&viewMatrix, rotation, (float*)&rotatoGenerator);
	
	
	//try//m_OpenGL->MatrixTranslation((float*)&viewMatrix, 3.5f*sin(0.5f*rotation), 3.5f*-cos(0.5f*rotation), 15.0f);

	





	m_LightShader->SetShader(m_OpenGL);
	m_LightShader->SetShaderParameters(m_OpenGL, (float*)&worldMatrix, (float*)&viewMatrix, (float*)&projectionMatrix, 0,
		lightDirection, diffuseLightColor, ambientLight);
	
	m_Model->Render(&g_OpenGL4Object);

	RenderEnd();

	/*
	int tutNo = 7;

	switch(tutNo)
	{
	case 4:
		m_ColorShader->SetShader(&g_OpenGL4Object);
		m_ColorShader->SetShaderParameters(&g_OpenGL4Object,(float*)&worldMatrix, (float*)&viewMatrix, (float*)&projectionMatrix);
		break;
	case 5:
		m_textureShader->SetShader(m_OpenGL);
		m_textureShader->SetShaderParameters(m_OpenGL, (float*)&worldMatrix, (float*)&viewMatrix, (float*)&projectionMatrix, 0);
		break;
	case 7:
		m_Light->GetDirection(lightDirection);
		m_Light->GetDiffuseColor(diffuseLightColor);
		m_Light->GetAmbientLight(ambientLight);

		m_OpenGL->MatrixRotationY((float*)&worldMatrix, rotation);
		//m_OpenGL->MatrixTranslation(viewMatrix, -0.1f*rotation, 0.0f, 10.0f);


		m_LightShader->SetShader(m_OpenGL);
		m_LightShader->SetShaderParameters(m_OpenGL, (float*)&worldMatrix, (float*)&viewMatrix, (float*)&projectionMatrix, 0,
			lightDirection, diffuseLightColor, ambientLight);
		break;
	}
	*/

	return true;
}

void OpenGL46TestController::RenderBegin()
{
	
	m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGL46TestController::RenderEnd()
{
	m_OpenGL->EndScene();
}

bool OpenGL46TestController::ProcessMessages()
{
	if (PeekMessage(&g_msg, NULL, NULL, NULL, PM_REMOVE))
	{
		
		if (g_msg.message == WM_QUIT)
		{
			isDone = true; OutputDebugString("QUIT");
			firstQuit = false;
		}
		

		if (g_msg.message == GAMEEXIT_MENU)
		{
			isDone = true; OutputDebugString("Message found is for 'Game Exit to Menu'.");
		}

		TranslateMessage(&g_msg);
		DispatchMessage(&g_msg);
		return true;
	}
	return false;
}

void OpenGL46TestController::Shutdown()
{
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown(m_OpenGL);
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the texture shader object.
	/*if (m_textureShader)
	{
		m_textureShader->Shutdown(m_OpenGL);
		delete m_textureShader;
		m_textureShader = 0;
	}*/

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown(m_OpenGL);
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the pointer to the OpenGL class object.
	m_OpenGL = 0;

	return;
}
