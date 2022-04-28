#include <DxLib.h>
#include "Convert.h"

// �}���`�o�C�g�������烏�C�h�����ɕϊ�
wstring Convert::ConvertToWstring(const std::string& str)
{
	int cnt = MultiByteToWideChar(// 1��ڂ͂�������̂����킩��Ȃ����當�������擾����
		CP_UTF8,
		0,
		str.c_str(),			// ���̕���
		str.length(),			// ���̕�����
		nullptr,				// �ϊ���̃A�h���X
		0);						// �ϊ���̕����� (�ϊ���̕��������킩��Ȃ��̂�0�Ƃ���)
	wstring wstr;				// ���j�R�[�h���������(���C�h����)
	wstr.resize(cnt);
	MultiByteToWideChar(		// �K�v�ȕ��������킩�����̂ŕϊ�����
		CP_UTF8,
		0,
		str.c_str(),
		str.length(),
		&wstr[0],				// �󂯎��A�h���X
		wstr.length()			// �󂯎�镶����
	);
	return wstr;
}
