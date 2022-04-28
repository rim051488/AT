#include<iostream>
#include<string>

using namespace std;

struct Test {
	int a;
	int b;
	int strlen;
};

int main() {
	FILE* fp = nullptr;
	fopen_s(&fp, "./ObjectLocation.dat", "r");
	if (fp == nullptr) {
		cout << "not found" << endl;
		return 0;
	}
	Test header;
	fread_s(&header, 
		sizeof(header),//�󂯎��\�T�C�Y
		sizeof(header),//�󂯎��f�[�^�T�C�Y
		1, fp);
	cout << "a=" << header.a << endl;
	cout << "b=" << header.b << endl;
	cout << "textLength=" << header.strlen << endl;
	string str;
	str.resize(header.strlen);
	fread_s(
		&str[0],//�󂯎��A�h���X
		str.size(),//�󂯎��T�C�Y
		header.strlen, //�f�[�^�T�C�Y
		1,//�f�[�^�� 
		fp);
	fclose(fp);
	cout << str << endl;

	//string str = "abc";
	//str += "def.test.dat";
	//auto idx=str.rfind('.')+1;
	//cout << str.substr(idx, str.length()-idx) << endl;

}