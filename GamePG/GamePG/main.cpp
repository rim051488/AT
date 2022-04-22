//#include <iostream>
#include <string>
#include <DxLib.h>
#include "Convert.h"

using namespace std;

struct Test {
	int a;
	int b;
	int strlen;
};

// SJIS(�}���`�o�C�g����)�œ������������C�h����(Unicode)�ɕϊ�
// str : �}���`�o�C�g����
// �߂�l : ���C�h����
//wstring ConvertToWstring(const std::string& str)
//{
//	int cnt = MultiByteToWideChar(// 1��ڂ͂�������̂����킩��Ȃ����當�������擾����
//		CP_UTF8,
//		0,
//		str.c_str(),			// ���̕���
//		str.length(),			// ���̕�����
//		nullptr,				// �ϊ���̃A�h���X
//		0);						// �ϊ���̕����� (�ϊ���̕��������킩��Ȃ��̂�0�Ƃ���)
//	wstring wstr;				// ���j�R�[�h���������(���C�h����)
//	wstr.resize(cnt);
//	MultiByteToWideChar(		// �K�v�ȕ��������킩�����̂ŕϊ�����
//		CP_UTF8,
//		0,
//		str.c_str(),
//		str.length(),
//		&wstr[0],				// �󂯎��A�h���X
//		wstr.length()			// �󂯎�镶����
//	);
//	return wstr;
//}

//int main() {
//	FILE* fp = nullptr;			// *�|�C���^�[�^�|�C���^�[�̃����������m�ۂ���Ȃ����̂Ȃ�
//	fopen_s(&fp, "./ObjectLocation.dat", "r");
//	if (fp == nullptr) {
//		cout << "not found" << endl;
//		return 0;
//	}
//	Test header;				// ���̂����
//	fread_s(&header,			// �A�h���X��n��
//		sizeof(header),			// �󂯎��\�T�C�Y
//		sizeof(header),			// �󂯎��f�[�^�T�C�Y
//		1, fp);
//	cout << "a=" << header.a << endl;
//	cout << "b=" << header.b << endl;
//	cout << "TextLen=" << header.strlen << endl;
//	string str;
//	wstring wstr;				// ���j�R�[�h���������(���C�h����)
//	str = "abcd";
//	wstr = L"abcd";
//	str.resize(header.strlen);	// resize�����ă��������m�ۂ���
//	fread_s(&str[0],			// �󂯎��A�h���X
//		str.size(),				// �󂯎��T�C�Y
//		header.strlen,			// �f�[�^�T�C�Y
//		1,						// �f�[�^��
//		fp);
//	fclose(fp);
//	cout << str << endl;
//	//string str = "abc";
//	//str += "def.dat";
//	//auto itx = str.rfind(".") + 1; // def.dat��.�̈ʒu�����o��/��Ԍ���.�����o��
//	////auto itx = str.find(".") + 1; // def.dat��.�̈ʒu�����o��/�擪��.�����o��
//	//cout << str.substr(itx,str.length() - itx) << endl;
//
//	//char str[7];
//	//strcpy_s(str, "abcdef");
//	//if (strcmp("abcdef",str))
//	//{
//	//	cout << "��v�I" << endl;
//	//}
//	//else          
//	//{
//	//	cout << "�s��v�I" << endl;
//	//}
//
//	//if ("abcdef" == str)
//	//{
//	//	cout << "��v�I" << endl;
//	//}
//	//else
//	//{
//	//	cout << "�s��v�I" << endl;
//	//}
//	//fread_s(,
//	//	sizeof(header),
//	//	sizeof(header), 1, fp);
//}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	FILE* fp = nullptr;			// *�|�C���^�[�^�|�C���^�[�̃����������m�ۂ���Ȃ����̂Ȃ�
	fopen_s(&fp, "./ObjectLocation.dat", "r");
	if (fp == nullptr) {
		return 0;
	}
	Test header;				// ���̂����
	fread_s(&header,			// �A�h���X��n��
		sizeof(header),			// �󂯎��\�T�C�Y
		sizeof(header),			// �󂯎��f�[�^�T�C�Y
		1, fp);
	string str;
	str.resize(header.strlen);	// resize�����ă��������m�ۂ���

	fread_s(&str[0],			// �󂯎��A�h���X
		str.size(),				// �󂯎��T�C�Y
		header.strlen,			// �f�[�^�T�C�Y
		1,						// �f�[�^��
		fp);
	fclose(fp);

	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	auto wstr = ConvertToWstring(str);
	while (ProcessMessage() == 0 )
	{
		DrawFormatString(10, 10, 0xffffff, L"a=%d", header.a);
		DrawFormatString(10, 25, 0xffffff, L"b=%d", header.b);
		DrawFormatString(10, 40, 0xffffff, L"text=%s", wstr.c_str());

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}