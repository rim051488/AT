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

// SJIS(マルチバイト文字)で得た文字をワイド文字(Unicode)に変換
// str : マルチバイト文字
// 戻り値 : ワイド文字
//wstring ConvertToWstring(const std::string& str)
//{
//	int cnt = MultiByteToWideChar(// 1回目はいくついるのかがわからないから文字数を取得する
//		CP_UTF8,
//		0,
//		str.c_str(),			// 元の文字
//		str.length(),			// 元の文字数
//		nullptr,				// 変換後のアドレス
//		0);						// 変換後の文字数 (変換後の文字数がわからないので0とする)
//	wstring wstr;				// ユニコードが入れられる(ワイド文字)
//	wstr.resize(cnt);
//	MultiByteToWideChar(		// 必要な文字数がわかったので変換する
//		CP_UTF8,
//		0,
//		str.c_str(),
//		str.length(),
//		&wstr[0],				// 受け取るアドレス
//		wstr.length()			// 受け取る文字数
//	);
//	return wstr;
//}

//int main() {
//	FILE* fp = nullptr;			// *ポインター型ポインターのメモリしか確保されない実体なし
//	fopen_s(&fp, "./ObjectLocation.dat", "r");
//	if (fp == nullptr) {
//		cout << "not found" << endl;
//		return 0;
//	}
//	Test header;				// 実体を作る
//	fread_s(&header,			// アドレスを渡す
//		sizeof(header),			// 受け取り可能サイズ
//		sizeof(header),			// 受け取るデータサイズ
//		1, fp);
//	cout << "a=" << header.a << endl;
//	cout << "b=" << header.b << endl;
//	cout << "TextLen=" << header.strlen << endl;
//	string str;
//	wstring wstr;				// ユニコードが入れられる(ワイド文字)
//	str = "abcd";
//	wstr = L"abcd";
//	str.resize(header.strlen);	// resizeをしてメモリを確保する
//	fread_s(&str[0],			// 受け取りアドレス
//		str.size(),				// 受け取りサイズ
//		header.strlen,			// データサイズ
//		1,						// データ個数
//		fp);
//	fclose(fp);
//	cout << str << endl;
//	//string str = "abc";
//	//str += "def.dat";
//	//auto itx = str.rfind(".") + 1; // def.datの.の位置を取り出す/一番後ろの.を取り出す
//	////auto itx = str.find(".") + 1; // def.datの.の位置を取り出す/先頭の.を取り出す
//	//cout << str.substr(itx,str.length() - itx) << endl;
//
//	//char str[7];
//	//strcpy_s(str, "abcdef");
//	//if (strcmp("abcdef",str))
//	//{
//	//	cout << "一致！" << endl;
//	//}
//	//else          
//	//{
//	//	cout << "不一致！" << endl;
//	//}
//
//	//if ("abcdef" == str)
//	//{
//	//	cout << "一致！" << endl;
//	//}
//	//else
//	//{
//	//	cout << "不一致！" << endl;
//	//}
//	//fread_s(,
//	//	sizeof(header),
//	//	sizeof(header), 1, fp);
//}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	FILE* fp = nullptr;			// *ポインター型ポインターのメモリしか確保されない実体なし
	fopen_s(&fp, "./ObjectLocation.dat", "r");
	if (fp == nullptr) {
		return 0;
	}
	Test header;				// 実体を作る
	fread_s(&header,			// アドレスを渡す
		sizeof(header),			// 受け取り可能サイズ
		sizeof(header),			// 受け取るデータサイズ
		1, fp);
	string str;
	str.resize(header.strlen);	// resizeをしてメモリを確保する

	fread_s(&str[0],			// 受け取りアドレス
		str.size(),				// 受け取りサイズ
		header.strlen,			// データサイズ
		1,						// データ個数
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