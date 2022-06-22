#pragma once
#include <map>
#include <string>
#include "InputID.h"

#define lpInputConfigMng (InputConfig::GetInstance())

using InputCodeTbl = std::map<std::string, int>;
using InputCode = std::map<InputID, int>;

class InputConfig
{
public:
	static void Create(void);
	static void Destroy(void);
	static InputConfig& GetInstance(void);

	/// <summary>
	/// キーボード用のコードを取得
	/// </summary>
	/// <returns>キーボード用のコードの参照</returns>
	const InputCode& GetKeyInputCode(void);
	void SetKeyInputCode(InputID id, int code);

	/// <summary>
	/// パッド用のコード取得
	/// </summary>
	/// <returns>パッド用のコードの参照</returns>
	const InputCode& GetJoypadInputCode(void);
	void SetJoypadInputCode(InputID id, int code);
	/// <summary>
	/// 移動用
	/// </summary>
	const InputCode& GetJoypadInputMove(void);

	/// <summary>
	/// パッドコードをすべてデフォルトものにする
	/// </summary>
	void SetDefalutPadCode(void);

	/// <summary>
	/// キーボードのコードをすべてデフォルトとする
	/// </summary>
	void SetDefalutKeyCode(void);

	void SwapKeyInputCode(InputID id, int code);
	void SwapPadInputCode(InputID id, int code);
private:
	InputConfig();
	~InputConfig();
	InputConfig(const InputConfig&) = delete;
	void operator=(const InputConfig&) = delete;

	bool Load(const std::string& fname, InputCode& in);
	bool Save(const std::string& fname, InputCode& in);

	static InputConfig* sInstance_;
	InputCode keyInputCode_;
	InputCode joypadInputCode_;
	InputCode joypadInputMove_;
};

