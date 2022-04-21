#include <iostream>
#include <string>

using namespace std;

struct Test {
	int a;
	int b;
	int strlen;
};

int main() {
	FILE* fp = nullptr;			// *ポインター型ポインターのメモリしか確保されない実体なし
	fopen_s(&fp, "./ObjectLocation.dat", "r");
	if (fp == nullptr) {
		cout << "not found" << endl;
		return 0;
	}
	Test header;				// 実体を作る
	fread_s(&header,			// アドレスを渡す
		sizeof(header),			// 受け取り可能サイズ
		sizeof(header),			// 受け取るデータサイズ
		1, fp);
	cout << "a=" << header.a << endl;
	cout << "b=" << header.b << endl;
	cout << "TextLen=" << header.strlen << endl;
	string str;
	str.resize(header.strlen);	// resizeをしてメモリを確保する
	fread_s(&str[0],			// 受け取りアドレス
		str.size(),				// 受け取りサイズ
		header.strlen,			// データサイズ
		1,						// データ個数
		fp);
	fclose(fp);
	cout << str << endl;
	//string str = "abc";
	//str += "def.dat";
	//auto itx = str.rfind(".") + 1; // def.datの.の位置を取り出す/一番後ろの.を取り出す
	////auto itx = str.find(".") + 1; // def.datの.の位置を取り出す/先頭の.を取り出す
	//cout << str.substr(itx,str.length() - itx) << endl;

	//char str[7];
	//strcpy_s(str, "abcdef");
	//if (strcmp("abcdef",str))
	//{
	//	cout << "一致！" << endl;
	//}
	//else          
	//{
	//	cout << "不一致！" << endl;
	//}

	//if ("abcdef" == str)
	//{
	//	cout << "一致！" << endl;
	//}
	//else
	//{
	//	cout << "不一致！" << endl;
	//}
	//fread_s(,
	//	sizeof(header),
	//	sizeof(header), 1, fp);
}

//int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
//{
//
//}