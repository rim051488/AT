#include <DxLib.h>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "KeyConfig.h"

#define KEY_CON			"keyconfig.txt"			// �L�[�R���t�B�O�f�[�^�̃t�@�C����
#define INFO_X			(10)					// ���̕`��J�nX���W
#define INFO_Y			(10)					// ���̕`��J�nY���W
#define INFO_SPACE		(24)					// ��s������ɊJ����X�y�[�X
#define INFO_NAME_X		(140)					// ���͖���`�悷��X���W

std::unique_ptr<KeyConfig> controller_;		// �R���g���[�����

// �L�[�R���t�B�O�Ώۂ̍���
int TargetIndex;

// �L�[�R���t�B�O�e���ڂ̖��O
static const char* KeyConfigMenu[KEYCONFIG_INPUT_NUM] =
{
	"��",
	"�E",
	"��",
	"��",
	"�_�b�V��",
	"���Ⴊ��",
	"�A�C�e���I���J�[�\��(��)",
	"�A�C�e���I���J�[�\��(�E)",
	"�U��",
	"�󂫃{�^��",
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int i;
	int DrawY;
	int InputWait;
	if (DxLib_Init() == -1)
	{ 
		return -1; 
	}
	ChangeWindowMode(true);
	SetDrawScreen(DX_SCREEN_BACK);
	// �L�[�R���t�B�O�����̏�����
	controller_ = std::make_unique<KeyConfig>();
	controller_->Init();
	// �L�[�R���t�B�O�t�@�C���̓ǂݍ���
	if (controller_->Load("keyconfig.txt") == false)
	{
		// �R���t�B�O�t�@�C�����ǂݍ��߂Ȃ�������f�t�H���g�ɐݒ�ɂ���
		controller_->SetDefault();
	}
	// �������͂��������牽�����Ȃ��̃t���O
	InputWait = false;
	while (ProcessMessage() == 0)
	{

		ClsDrawScreen();
		//std::ifstream file("keyconfig.txt");  // �ǂݍ��ރt�@�C���̃p�X���w��
		//std::string line;

		//while (std::getline(file, line)) {  // 1�s���ǂݍ���
		//	DrawFormatString(0, 0, 0xffffff, "%s", line);
		//}

		controller_->InputProcess();
		// �t���O�������Ă��邩�ǂ���
		if (InputWait)
		{
			if (!controller_->CheckInput())
			// �������͂��Ȃ�������u�������͂��������牽�����Ȃ��v�̃t���O��ς���
			InputWait = false;
		}
		else
		{
			// �L�[��p�b�h�̉��������ǂ������`�F�b�N���āA�����Ă�����L�[�R���t�B�O�ݒ�ɔ��f������
			if (controller_->UpdateInputTypeInfo(TargetIndex))
			{
				// �����{�^���������ꂽ�玟�̍��ڂɈړ�����
				TargetIndex++;
				// �u�������͂��������牽�����Ȃ��v�t���O�𗧂Ă�
				InputWait = true;
			}
		}
		// ���ڂ̐������J��Ԃ�
		DrawY = INFO_Y;
		for (i = 0; i < KEYCONFIG_INPUT_NUM; i++)
		{
			int DrawColor;
			char InputString[256];
			// �ύX�Ώۂ̍��ڂ��ǂ����ŕ`��F��ς���
			DrawColor = TargetIndex == i ? GetColor(255, 0, 0) : GetColor(255, 255, 255);
			// ���ږ��̕`��
			DrawString(INFO_X, DrawY, KeyConfigMenu[i], DrawColor);
			// ���͂Ɋ��蓖�Ă��Ă�����͖����擾����
			controller_->GetInputTypeString(i, InputString);
			// ���蓖�Ă��Ă�����͖���`�悷��
			DrawString(INFO_NAME_X, DrawY, InputString, DrawColor);
			// ���ڂ̕`��Y���W���P���ڕ����Ɉړ�����
			DrawY += INFO_SPACE;
		}
		ScreenFlip();

		if (TargetIndex == KEYCONFIG_INPUT_NUM)
		{
			break;
		}
	}
	controller_->Save(KEY_CON);
	DxLib_End();
	return 0;
}