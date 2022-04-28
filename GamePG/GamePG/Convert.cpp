#include <DxLib.h>
#include "Convert.h"

// マルチバイト文字からワイド文字に変換
wstring Convert::ConvertToWstring(const std::string& str)
{
	int cnt = MultiByteToWideChar(// 1回目はいくついるのかがわからないから文字数を取得する
		CP_UTF8,
		0,
		str.c_str(),			// 元の文字
		str.length(),			// 元の文字数
		nullptr,				// 変換後のアドレス
		0);						// 変換後の文字数 (変換後の文字数がわからないので0とする)
	wstring wstr;				// ユニコードが入れられる(ワイド文字)
	wstr.resize(cnt);
	MultiByteToWideChar(		// 必要な文字数がわかったので変換する
		CP_UTF8,
		0,
		str.c_str(),
		str.length(),
		&wstr[0],				// 受け取るアドレス
		wstr.length()			// 受け取る文字数
	);
	return wstr;
}
