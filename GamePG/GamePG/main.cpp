#include <iostream>
#include <string>

using namespace std;

struct Test {
	int a;
	int b;
	int strlen;
};

int main() {
	FILE* fp = nullptr;			// *�|�C���^�[�^�|�C���^�[�̃����������m�ۂ���Ȃ����̂Ȃ�
	fopen_s(&fp, "./ObjectLocation.dat", "r");
	if (fp == nullptr) {
		cout << "not found" << endl;
		return 0;
	}
	Test header;				// ���̂����
	fread_s(&header,			// �A�h���X��n��
		sizeof(header),			// �󂯎��\�T�C�Y
		sizeof(header),			// �󂯎��f�[�^�T�C�Y
		1, fp);
	cout << "a=" << header.a << endl;
	cout << "b=" << header.b << endl;
	cout << "TextLen=" << header.strlen << endl;
	string str;
	str.resize(header.strlen);	// resize�����ă��������m�ۂ���
	fread_s(&str[0],			// �󂯎��A�h���X
		str.size(),				// �󂯎��T�C�Y
		header.strlen,			// �f�[�^�T�C�Y
		1,						// �f�[�^��
		fp);
	fclose(fp);
	cout << str << endl;
	//string str = "abc";
	//str += "def.dat";
	//auto itx = str.rfind(".") + 1; // def.dat��.�̈ʒu�����o��/��Ԍ���.�����o��
	////auto itx = str.find(".") + 1; // def.dat��.�̈ʒu�����o��/�擪��.�����o��
	//cout << str.substr(itx,str.length() - itx) << endl;

	//char str[7];
	//strcpy_s(str, "abcdef");
	//if (strcmp("abcdef",str))
	//{
	//	cout << "��v�I" << endl;
	//}
	//else          
	//{
	//	cout << "�s��v�I" << endl;
	//}

	//if ("abcdef" == str)
	//{
	//	cout << "��v�I" << endl;
	//}
	//else
	//{
	//	cout << "�s��v�I" << endl;
	//}
	//fread_s(,
	//	sizeof(header),
	//	sizeof(header), 1, fp);
}

//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
//{
//
//}