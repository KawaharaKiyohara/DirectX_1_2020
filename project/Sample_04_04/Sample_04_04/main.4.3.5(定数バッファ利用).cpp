#include "stdafx.h"
#include "system/system.h"

/// <summary>
/// �f�B���N�V�������C�g�\���́B
/// </summary>
struct DirectionLight {
	Vector3 direction;	//���C�g�̕����B	
	float pad0;				
	Vector3 color;			//���C�g�̃J���[�B
	float pad1;
};
/// <summary>
/// ���C�g�\���́B
/// </summary>
struct Light {
	DirectionLight directionLight;		//�f�B���N�V�������C�g�B
	Vector3 eyePos;						//���_�̈ʒu�B
	float pad1;
	Vector3 ambientLight;				//�A���r�G���g���C�g�B
};
///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	//////////////////////////////////////
	// �������珉�������s���R�[�h���L�q����B
	//////////////////////////////////////

	g_camera3D->SetPosition({ 0.0f, 0.0f, 100.0f });
	g_camera3D->SetTarget({ 0.0f, 0.0f, 0.0f });

	//���C�g�̃f�[�^���쐬����B
	Light light;
	//���C�g�͉E�����瓖�����Ă���B
	light.directionLight.direction.x = 1.0f;
	light.directionLight.direction.y = -1.0f;
	light.directionLight.direction.z = -1.0f;
	light.directionLight.direction.Normalize();
	//���C�g�̃J���[�͔��B
	light.directionLight.color.x = 0.5f;
	light.directionLight.color.y = 0.5f;
	light.directionLight.color.z = 0.5f;

	//step-2 ���_�̈ʒu��ݒ肷��B
	light.eyePos = g_camera3D->GetPosition();

	light.ambientLight.x = 0.3f;
	light.ambientLight.y = 0.3f;
	light.ambientLight.z = 0.3f;

	//���f��������������B
	//���f�������������邽�߂̏����\�z����B
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/teapot.tkm";
	//�g�p����V�F�[�_�[�t�@�C���p�X��ݒ肷��B
	modelInitData.m_fxFilePath = "Assets/shader/sample.fx";
	//�f�B���N�V�������C�g�̏���萔�o�b�t�@�Ƃ��ăf�B�X�N���v�^�q�[�v�ɓo�^���邽�߂�
	//���f���̏��������Ƃ��ēn���B
	modelInitData.m_expandConstantBuffer = &light;
	modelInitData.m_expandConstantBufferSize = sizeof(light);
	//�����������g���ă��f��������������B
	Model model;
	model.Init(modelInitData);

	//////////////////////////////////////
	// ���������s���R�[�h�������̂͂����܂ŁI�I�I
	//////////////////////////////////////
	auto& renderContext = g_graphicsEngine->GetRenderContext();

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		//�����_�����O�J�n�B
		g_engine->BeginFrame();		
		//////////////////////////////////////
		//��������G��`���R�[�h���L�q����B
		//////////////////////////////////////
		
		Quaternion qRot;
		qRot.SetRotationDegY(g_pad[0]->GetLStickXF());
		qRot.Apply(light.directionLight.direction);
		qRot.SetRotationDegX(g_pad[0]->GetLStickYF());
		qRot.Apply(light.directionLight.direction);

		//�e�B�[�|�b�g���h���[�B
		model.Draw(renderContext);
		
		//////////////////////////////////////
		//�G��`���R�[�h�������̂͂����܂ŁI�I�I
		//////////////////////////////////////
		//�����_�����O�I���B
		g_engine->EndFrame();
	}
	return 0;
}


