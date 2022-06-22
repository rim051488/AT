#include <DxLib.h>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "KeyConfig.h"

#define KEY_CON			"keyconfig.txt"			// キーコンフィグデータのファイル名
#define INFO_X			(10)					// 情報の描画開始X座標
#define INFO_Y			(10)					// 情報の描画開始Y座標
#define INFO_SPACE		(24)					// 一行あたりに開けるスペース
#define INFO_NAME_X		(140)					// 入力名を描画するX座標

std::unique_ptr<KeyConfig> controller_;		// コントローラ情報

// キーコンフィグ対象の項目
int TargetIndex;

// キーコンフィグ各項目の名前
static const char* KeyConfigMenu[KEYCONFIG_INPUT_NUM] =
{
	"左",
	"右",
	"上",
	"下",
	"ダッシュ",
	"しゃがみ",
	"アイテム選択カーソル(左)",
	"アイテム選択カーソル(右)",
	"攻撃",
	"空きボタン",
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
	// キーコンフィグ処理の初期化
	controller_ = std::make_unique<KeyConfig>();
	controller_->Init();
	// キーコンフィグファイルの読み込み
	if (controller_->Load("keyconfig.txt") == false)
	{
		// コンフィグファイルが読み込めなかったらデフォルトに設定にする
		controller_->SetDefault();
	}
	// 何か入力があったら何もしないのフラグ
	InputWait = false;
	while (ProcessMessage() == 0)
	{

		ClsDrawScreen();
		//std::ifstream file("keyconfig.txt");  // 読み込むファイルのパスを指定
		//std::string line;

		//while (std::getline(file, line)) {  // 1行ずつ読み込む
		//	DrawFormatString(0, 0, 0xffffff, "%s", line);
		//}

		controller_->InputProcess();
		// フラグが立っているかどうか
		if (InputWait)
		{
			if (!controller_->CheckInput())
			// 何も入力がなかったら「何か入力があったら何もしない」のフラグを変える
			InputWait = false;
		}
		else
		{
			// キーやパッドの押したかどうかをチェックして、押していたらキーコンフィグ設定に反映させる
			if (controller_->UpdateInputTypeInfo(TargetIndex))
			{
				// 何かボタンが押されたら次の項目に移動する
				TargetIndex++;
				// 「何か入力があったら何もしない」フラグを立てる
				InputWait = true;
			}
		}
		// 項目の数だけ繰り返し
		DrawY = INFO_Y;
		for (i = 0; i < KEYCONFIG_INPUT_NUM; i++)
		{
			int DrawColor;
			char InputString[256];
			// 変更対象の項目かどうかで描画色を変える
			DrawColor = TargetIndex == i ? GetColor(255, 0, 0) : GetColor(255, 255, 255);
			// 項目名の描画
			DrawString(INFO_X, DrawY, KeyConfigMenu[i], DrawColor);
			// 入力に割り当てられている入力名を取得する
			controller_->GetInputTypeString(i, InputString);
			// 割り当てられている入力名を描画する
			DrawString(INFO_NAME_X, DrawY, InputString, DrawColor);
			// 項目の描画Y座標を１項目分下に移動する
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