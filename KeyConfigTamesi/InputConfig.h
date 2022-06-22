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
	/// �L�[�{�[�h�p�̃R�[�h���擾
	/// </summary>
	/// <returns>�L�[�{�[�h�p�̃R�[�h�̎Q��</returns>
	const InputCode& GetKeyInputCode(void);
	void SetKeyInputCode(InputID id, int code);

	/// <summary>
	/// �p�b�h�p�̃R�[�h�擾
	/// </summary>
	/// <returns>�p�b�h�p�̃R�[�h�̎Q��</returns>
	const InputCode& GetJoypadInputCode(void);
	void SetJoypadInputCode(InputID id, int code);
	/// <summary>
	/// �ړ��p
	/// </summary>
	const InputCode& GetJoypadInputMove(void);

	/// <summary>
	/// �p�b�h�R�[�h�����ׂăf�t�H���g���̂ɂ���
	/// </summary>
	void SetDefalutPadCode(void);

	/// <summary>
	/// �L�[�{�[�h�̃R�[�h�����ׂăf�t�H���g�Ƃ���
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

