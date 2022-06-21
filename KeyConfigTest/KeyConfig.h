#pragma once
#include <DxLib.h>

#define MAX_GAMEPAD_NUM             (2)            // チェックするゲームパッドの数
#define KEY_STATE_BUFFER_SIZE       (256)           // キーボードの入力状態を取得するためのバッファのサイズ
#define DIRECTINPUT_MAX_VALUE       (1000)          // DirectInputから得られる値の最大値

// 入力情報タイプ
#define KEYCONFIG_INPUT_LEFT			(0)			// 方向入力左
#define KEYCONFIG_INPUT_RIGHT			(1)			// 方向入力右
#define KEYCONFIG_INPUT_UP				(2)			// 方向入力上
#define KEYCONFIG_INPUT_DOWN			(3)			// 方向入力下
#define KEYCONFIG_INPUT_DASH			(4)			// ダッシュ
#define KEYCONFIG_INPUT_CROUCH			(5)			// しゃがみ
#define KEYCONFIG_INPUT_ITEM_LEFT		(6)			// アイテム選択左カーソル
#define KEYCONFIG_INPUT_ITEM_RIGHT		(7)			// アイテム選択右カーソル
#define KEYCONFIG_INPUT_ATTACK			(8)			// 攻撃ボタン
#define KEYCONFIG_INPUT_BTN1			(9)			// メニューボタン
#define KEYCONFIG_INPUT_NUM				(10)		// 入力タイプの数

// DirectInput の入力情報タイプ
#define DIRECTINPUT_TYPE_X          (0)             // 方向入力のＸ軸
#define DIRECTINPUT_TYPE_Y          (1)             // 方向入力のＹ軸
#define DIRECTINPUT_TYPE_Z          (2)             // 方向入力のＺ軸
#define DIRECTINPUT_TYPE_RX         (3)             // 方向入力のＸ軸回転
#define DIRECTINPUT_TYPE_RY         (4)             // 方向入力のＹ軸回転
#define DIRECTINPUT_TYPE_RZ         (5)             // 方向入力のＺ軸回転
#define DIRECTINPUT_TYPE_POV        (6)             // 方向コントローラ
#define DIRECTINPUT_TYPE_BUTTON     (7)             // ボタン
#define DIRECTINPUT_TYPE_KEY        (8)             // キーボードのキー

// キーボードの１キー当たりの情報
struct KEYINFO
{
	int keyInput;		// 入力コード(KEY_INPUT_LEFTなど)
	const char* Name;	// キーの名前
};

// ゲームでの入力とキーやパッドなどの入力との対応情報
struct KEYCONFIGINFO
{
	int PadNo;				// パッド番号
	int DirectInputType;	// DirectInputの入力情報タイプ(DIRECTINPUT_TYPE_Xなど)
	int SubInfo[2];			// サブ情報(DirectInputTypeによって意味が変わる)
};

// 入力処理用の情報
struct KEYCONFIGSYSTEMDATA
{
	KEYCONFIGINFO keyConfigInfo[KEYCONFIG_INPUT_NUM];					// ゲーム中の入力とキーやパッドなどの入力との対応情報
	DINPUT_JOYSTATE NeutralDirectInputState[MAX_GAMEPAD_NUM];			// DirectInputのパッドの初期入力状態
	DINPUT_JOYSTATE DirectiInputState[MAX_GAMEPAD_NUM];					// DirectInputのパッドの入力状態
	char NeutralKeyInput[KEY_STATE_BUFFER_SIZE];						// キーの初期入力状態
	char KeyInput[KEY_STATE_BUFFER_SIZE];								// キーの入力状態
	int ButtonInput;													// ボタンの入力状態
	int ButtonEdgeInput;												// ボタンの押された瞬間のみの入力状態
	VECTOR CameraStickInput;											// カメラ操作用の入力状態
};

// 入力処理用の情報
static KEYCONFIGSYSTEMDATA keyConfSys;

// ゲームでの各入力とキーやパッドなどの入力とのデフォルトの対応設定
static KEYCONFIGINFO DefaultInputTypeInfo[KEYCONFIG_INPUT_NUM] =
{
	0, DIRECTINPUT_TYPE_X,      -1, 0,      // KEYCONFIG_INPUT_LEFT
	0, DIRECTINPUT_TYPE_X,       1, 0,      // KEYCONFIG_INPUT_RIGHT
	0, DIRECTINPUT_TYPE_Y,      -1, 0,      // KEYCONFIG_INPUT_UP 
	0, DIRECTINPUT_TYPE_Y,       1, 0,      // KEYCONFIG_INPUT_DOWN 
	0, DIRECTINPUT_TYPE_RX,     -1, 0,      // KEYCONFIG_INPUT_DASH
	0, DIRECTINPUT_TYPE_RX,      1, 0,      // KEYCONFIG_INPUT_CROUCH
	0, DIRECTINPUT_TYPE_RY,     -1, 0,      // KEYCONFIG_INPUT_ITEM_LEFT
	0, DIRECTINPUT_TYPE_RY,      1, 0,      // KEYCONFIG_INPUT_ITEM_RIGHT
	0, DIRECTINPUT_TYPE_BUTTON,  0, 0,      // KEYCONFIG_INPUT_ATTACK
	0, DIRECTINPUT_TYPE_BUTTON,  2, 0,      // KEYCONFIG_INPUT_BTN1
};

// パッドの識別子テーブル
static int PadIDTable[MAX_GAMEPAD_NUM] =
{
	DX_INPUT_PAD1,
	DX_INPUT_PAD2,
};

// キーコードの情報
static KEYINFO keyInputTable[] =
{
    KEY_INPUT_BACK,         "BACK",         // バックスペースキー
    KEY_INPUT_TAB,          "TAB",          // タブキー
    KEY_INPUT_RETURN,       "ENTER",        // エンターキー

    KEY_INPUT_LSHIFT,       "L SHIFT",      // 左シフトキー
    KEY_INPUT_RSHIFT,       "R SHIFT",      // 右シフトキー
    KEY_INPUT_LCONTROL,     "L CONTROL",    // 左コントロールキー
    KEY_INPUT_RCONTROL,     "R CONTROL",    // 右コントロールキー
    KEY_INPUT_ESCAPE,       "ESCAPE",       // エスケープキー
    KEY_INPUT_SPACE,        "SPACE",        // スペースキー
    KEY_INPUT_PGUP,         "PAGE UP",      // ＰａｇｅＵＰキー
    KEY_INPUT_PGDN,         "PAGE DOWN",    // ＰａｇｅＤｏｗｎキー
    KEY_INPUT_END,          "END",          // エンドキー
    KEY_INPUT_HOME,         "HOME",         // ホームキー
    KEY_INPUT_LEFT,         "LEFT",         // 左キー
    KEY_INPUT_UP,           "UP",           // 上キー
    KEY_INPUT_RIGHT,        "RIGHT",        // 右キー
    KEY_INPUT_DOWN,         "DOWN",         // 下キー
    KEY_INPUT_INSERT,       "INSERT",       // インサートキー
    KEY_INPUT_DELETE,       "DELETE",       // デリートキー

    KEY_INPUT_MINUS,        "-",            // －キー
    KEY_INPUT_YEN,          "\\",           // ￥キー
    KEY_INPUT_PREVTRACK,    "^",            // ＾キー
    KEY_INPUT_PERIOD,       ".",            // ．キー
    KEY_INPUT_SLASH,        "/",            // ／キー
    KEY_INPUT_LALT,         "L ALT",        // 左ＡＬＴキー
    KEY_INPUT_RALT,         "R ALT",        // 右ＡＬＴキー
    KEY_INPUT_SCROLL,       "SCROLL LOCK",  // ScrollLockキー
    KEY_INPUT_SEMICOLON,    ";",            // ；キー
    KEY_INPUT_COLON,        ":",            // ：キー
    KEY_INPUT_LBRACKET,     "[",            // ［キー
    KEY_INPUT_RBRACKET,     "]",            // ］キー
    KEY_INPUT_AT,           "@",            // ＠キー
    KEY_INPUT_BACKSLASH,    "BACK SLASH",   // ＼キー
    KEY_INPUT_COMMA,        ",",            // ，キー
    KEY_INPUT_KANJI,        "KANJI",        // 漢字キー
    KEY_INPUT_CONVERT,      "CONVERT",      // 変換キー
    KEY_INPUT_NOCONVERT,    "NO CONVERT",   // 無変換キー
    KEY_INPUT_KANA,         "KANA",         // カナキー
    KEY_INPUT_APPS,         "APPS",         // アプリケーションメニューキー
    KEY_INPUT_CAPSLOCK,     "CAPS LOCK",    // CaspLockキー
    KEY_INPUT_SYSRQ,        "PRINT SCREEN", // PrintScreenキー
    KEY_INPUT_PAUSE,        "PAUSE BREAK",  // PauseBreakキー
    KEY_INPUT_LWIN,         "L WIN",        // 左Ｗｉｎキー
    KEY_INPUT_RWIN,         "R WIN",        // 右Ｗｉｎキー

    KEY_INPUT_NUMLOCK,      "NUM LOCK",     // テンキー０
    KEY_INPUT_NUMPAD0,      "NUMPAD 0",     // テンキー０
    KEY_INPUT_NUMPAD1,      "NUMPAD 1",     // テンキー１
    KEY_INPUT_NUMPAD2,      "NUMPAD 2",     // テンキー２
    KEY_INPUT_NUMPAD3,      "NUMPAD 3",     // テンキー３
    KEY_INPUT_NUMPAD4,      "NUMPAD 4",     // テンキー４
    KEY_INPUT_NUMPAD5,      "NUMPAD 5",     // テンキー５
    KEY_INPUT_NUMPAD6,      "NUMPAD 6",     // テンキー６
    KEY_INPUT_NUMPAD7,      "NUMPAD 7",     // テンキー７
    KEY_INPUT_NUMPAD8,      "NUMPAD 8",     // テンキー８
    KEY_INPUT_NUMPAD9,      "NUMPAD 9",     // テンキー９
    KEY_INPUT_MULTIPLY,     "NUMPAD *",     // テンキー＊キー
    KEY_INPUT_ADD,          "NUMPAD +",     // テンキー＋キー
    KEY_INPUT_SUBTRACT,     "NUMPAD -",     // テンキー－キー
    KEY_INPUT_DECIMAL,      "NUMPAD .",     // テンキー．キー
    KEY_INPUT_DIVIDE,       "NUMPAD /",     // テンキー／キー
    KEY_INPUT_NUMPADENTER,  "NUMPAD ENTER", // テンキーのエンターキー

    KEY_INPUT_F1,           "F1",           // Ｆ１キー
    KEY_INPUT_F2,           "F2",           // Ｆ２キー
    KEY_INPUT_F3,           "F3",           // Ｆ３キー
    KEY_INPUT_F4,           "F4",           // Ｆ４キー
    KEY_INPUT_F5,           "F5",           // Ｆ５キー
    KEY_INPUT_F6,           "F6",           // Ｆ６キー
    KEY_INPUT_F7,           "F7",           // Ｆ７キー
    KEY_INPUT_F8,           "F8",           // Ｆ８キー
    KEY_INPUT_F9,           "F9",           // Ｆ９キー
    KEY_INPUT_F10,          "F10",          // Ｆ１０キー
    KEY_INPUT_F11,          "F11",          // Ｆ１１キー
    KEY_INPUT_F12,          "F12",          // Ｆ１２キー

    KEY_INPUT_A,            "A",            // Ａキー
    KEY_INPUT_B,            "B",            // Ｂキー
    KEY_INPUT_C,            "C",            // Ｃキー
    KEY_INPUT_D,            "D",            // Ｄキー
    KEY_INPUT_E,            "E",            // Ｅキー
    KEY_INPUT_F,            "F",            // Ｆキー
    KEY_INPUT_G,            "G",            // Ｇキー
    KEY_INPUT_H,            "H",            // Ｈキー
    KEY_INPUT_I,            "I",            // Ｉキー
    KEY_INPUT_J,            "J",            // Ｊキー
    KEY_INPUT_K,            "K",            // Ｋキー
    KEY_INPUT_L,            "L",            // Ｌキー
    KEY_INPUT_M,            "M",            // Ｍキー
    KEY_INPUT_N,            "N",            // Ｎキー
    KEY_INPUT_O,            "O",            // Ｏキー
    KEY_INPUT_P,            "P",            // Ｐキー
    KEY_INPUT_Q,            "Q",            // Ｑキー
    KEY_INPUT_R,            "R",            // Ｒキー
    KEY_INPUT_S,            "S",            // Ｓキー
    KEY_INPUT_T,            "T",            // Ｔキー
    KEY_INPUT_U,            "U",            // Ｕキー
    KEY_INPUT_V,            "V",            // Ｖキー
    KEY_INPUT_W,            "W",            // Ｗキー
    KEY_INPUT_X,            "X",            // Ｘキー
    KEY_INPUT_Y,            "Y",            // Ｙキー
    KEY_INPUT_Z,            "Z",            // Ｚキー

    KEY_INPUT_0,            "0",            // ０キー
    KEY_INPUT_1,            "1",            // １キー
    KEY_INPUT_2,            "2",            // ２キー
    KEY_INPUT_3,            "3",            // ３キー
    KEY_INPUT_4,            "4",            // ４キー
    KEY_INPUT_5,            "5",            // ５キー
    KEY_INPUT_6,            "6",            // ６キー
    KEY_INPUT_7,            "7",            // ７キー
    KEY_INPUT_8,            "8",            // ８キー
    KEY_INPUT_9,            "9",            // ９キー

    -1,                     NULL,
};

class KeyConfig
{
public:
	KeyConfig();
	~KeyConfig();
	void Init(void);				// キーコンフィグの初期化を行う
	void InputProcess(void);		// キーコンフィグの入力を行う(毎フレーム実行する)
	int GetInput(void);				// ボタンの入力状態を取得する(戻り値：ボタンの入力状態)
	int GetEdgeInput(void);			// ボタンの押された瞬間のみの入力状態を取得する(戻り値：ボタンの押された瞬間のみの入力状態)
	VECTOR GetCameraInput(void);	// カメラ操作用の入力状態を取得する(戻り値：カメラ操作用の入力状態)
	int Save(const char* FilePath);	// キーコンフィグ設定をファイルに保存する(戻り値：保存成功：True	保存失敗：False)
	int Load(const char* FilePath);	// キーコンフィグ設定をファイルから読み込む(戻り値：読み込み成功：True	読み込み失敗：False)
	void SetDefault(void);			// キーコンフィグ設定をデフォルトにする
	// 現在押されているキーやパッドの入力情報をチェックして、入力があった場合は情報更新する(キーコンフィグ画面用)
	//		戻り値：入力があったかどうか(True：入力があった		False：入力はなかった)
	int UpdateInputTypeInfo(int UpdateInputType);
	// パッドかキーの入力があるかどうかを取得する(キーコンフィグ画面)
	//		戻り値：入力があったかどうか(True：入力があった		False：入力はなかった)
	int CheckInput(void);
	// 指定の入力情報タイプに割り当てられているパッドやキーの入力の名前を取得する(キーコンフィグ画面)
	void GetInputTypeString(int InputType, char* InputString);
};

