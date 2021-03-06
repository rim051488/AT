#pragma once

enum class InputID
{
	Up,					// 上移動
	Down,				// 下移動
	Left,				// 左移動
	Right,				// 右移動
	Dash,				// ダッシュトリガー
	Crouch,				// しゃがみトリガー
	ItemLeft,			// アイテム選択左カーソル
	ItemRight,			// アイテム選択右カーソル
	Attack,				// アイテム使用、攻撃（長押しで溜め攻撃）
	btn1,				// 空きのボタン配置
	Max
};
