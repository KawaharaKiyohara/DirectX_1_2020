#include "stdafx.h"
#include "system/system.h"

struct DirectionLight {
	Vector3 ligDirection;		//���C�g�̕����B	
	float pad0;				
	Vector3 ligColor;			//���C�g�̃J���[�B
	float pad1;
	//step-1 �\���̂Ɏ��_�̈ʒu��ǉ�����B
	Vector3 eyePos;			//���_�̈ʒu�B
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

	//�f�B���N�V�������C�g�̃f�[�^���쐬����B
	DirectionLight directionLig;
	//���C�g�͉E�����瓖�����Ă���B
	directionLig.ligDirection.x = 1.0f;
	directionLig.ligDirection.y = -1.0f;
	directionLig.ligDirection.z = -1.0f;
	directionLig.ligDirection.Normalize();
	//���C�g�̃J���[�͔��B
	directionLig.ligColor.x = 0.5f;
	directionLig.ligColor.y = 0.5f;
	directionLig.ligColor.z = 0.5f;

	//step-2 ���_�̈ʒu��ݒ肷��B
	directionLig.eyePos = g_camera3D->GetPosition();

	//���f��������������B
	//���f�������������邽�߂̏����\�z����B
	ModelInitData modelInitData;
	modelInitData.m_tkmFilePath = "Assets/modelData/teapot.tkm";
	//�g�p����V�F�[�_�[�t�@�C���p�X��ݒ肷��B
	modelInitData.m_fxFilePath = "Assets/shader/sample.fx";
	//�f�B���N�V�������C�g�̏���萔�o�b�t�@�Ƃ��ăf�B�X�N���v�^�q�[�v�ɓo�^���邽�߂�
	//���f���̏��������Ƃ��ēn���B
	modelInitData.m_expandConstantBuffer = &directionLig;
	modelInitData.m_expandConstantBufferSize = sizeof(directionLig);
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
		qRot.Apply(directionLig.ligDirection);
		qRot.SetRotationDegX(g_pad[0]->GetLStickYF());
		qRot.Apply(directionLig.ligDirection);

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


