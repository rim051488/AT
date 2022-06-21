#include <string>
#include "KeyConfig.h"

KeyConfig::KeyConfig()
{
}

KeyConfig::~KeyConfig()
{
}

void KeyConfig::Init(void)
{
    int i;
    int PadNum;

    // パッドの数を取得する
    PadNum = GetJoypadNum();

    // パッドの数がプログラムがが対応している数より多い場合は、対応している数に制限する
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // パッドの初期状態をDirectInputから取得する
    for (i = 0; i < PadNum; i++)
    {
        GetJoypadDirectInputState(PadIDTable[i], &keyConfSys.NeutralDirectInputState[i]);
    }
    // キー入力の初期応対を取得する
    GetHitKeyStateAll(keyConfSys.NeutralKeyInput);
}

// InputProcess用の軸入力タイプの処理を行う補助関数
// InputState   処理結果を代入する変数アドレス
// SubInfo      軸入力タイプのサブ情報(1:InputValueがプラスの値の場合に入力ありとする -1:InputValueがマイナスの値の場合に入力ありとする)
// InputValue   軸入力の値
static void InputProcessAssist(int* InputState, int SubInfo, int InputValue)
{
    switch (SubInfo)
    {
    case 1:
        if (InputValue > 0)
        {
            *InputState = InputValue;
        }
        break;
    case -1:
        if (InputValue < 0)
        {
            *InputState = -InputValue;
        }
        break;
    }
}

void KeyConfig::InputProcess(void)
{
    int i;
    KEYCONFIGINFO* KCInfo;
    int InputState[KEYCONFIG_INPUT_NUM];
    int PadNum;
    DINPUT_JOYSTATE* DIJState;
    int ButtonPrevInput;
    int Total;
    // パッドの数を取得する
    PadNum = GetJoypadNum();
    // パッドの入力情報をDirectInputから取得する
    for (i = 0; i < PadNum; i++)
    {
        GetJoypadDirectInputState(PadIDTable[i], &keyConfSys.DirectiInputState[i]);
    }
    // 現在のキーの入力状態を取得する
    GetHitKeyStateAll(keyConfSys.KeyInput);
    // ゲームで使用する入力情報を構築する
    KCInfo = keyConfSys.keyConfigInfo;
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++, KCInfo++)
    {
        // 「入力なし」状態にしておく
        InputState[i] = 0;
        // 対応するDirectInputの情報タイプによって処理を分岐
        DIJState = KCInfo->PadNo < 0 ? NULL : &keyConfSys.DirectiInputState[KCInfo->PadNo];
        switch (KCInfo->DirectInputType)
        {
        case DIRECTINPUT_TYPE_X:        // 方向入力のX軸の場合
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->X);
            break;

        case DIRECTINPUT_TYPE_Y:        // 方向入力のY軸の場合
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->Y);
            break;

        case DIRECTINPUT_TYPE_Z:        // 方向入力のZ軸の場合
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->Z);
            break;

        case DIRECTINPUT_TYPE_RX:        // 方向入力のX軸回転の場合
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->Rx);
            break;

        case DIRECTINPUT_TYPE_RY:        // 方向入力のY軸回転の場合
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->Ry);
            break;

        case DIRECTINPUT_TYPE_RZ:        // 方向入力のZ軸回転の場合
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->Rz);
            break;
        case DIRECTINPUT_TYPE_POV:       // 方向コントローラの場合
            // 設定されている方向に入力されていたら「入力あり」にする
            if (DIJState->POV[KCInfo->SubInfo[0]] == KCInfo->SubInfo[1])
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;
        case DIRECTINPUT_TYPE_BUTTON:    // ボタンの場合
            // 設定されているボタンが押されていたら「入力あり」にする
            if (DIJState->Buttons[KCInfo->SubInfo[0]] == 128)
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;
        case DIRECTINPUT_TYPE_KEY:       // キーボードのキーの場合
            // 設定されているキーが押されていたら「入力あり」にする
            if (keyConfSys.KeyInput[KCInfo->SubInfo[0]])
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;
        }
    }
    // 1フレーム前の入力応対をとっておく
    ButtonPrevInput = keyConfSys.ButtonInput;
    // 入力状態の初期化
    keyConfSys.ButtonInput = 0;
    // 各入力に対応するビットを「入力あり」の場合は立てる
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++)
    {
        if (InputState[i] > 0)
        {
            keyConfSys.ButtonInput |= 1 << i;
        }
    }
    // 今回のフレームで「入力あり」になり始めたビットを算出する
    keyConfSys.ButtonEdgeInput = keyConfSys.ButtonInput & ~ButtonPrevInput;
    
}

int KeyConfig::GetInput(void)
{
    return keyConfSys.ButtonInput;
}

int KeyConfig::GetEdgeInput(void)
{
    return keyConfSys.ButtonEdgeInput;
}

VECTOR KeyConfig::GetCameraInput(void)
{
    return VECTOR();
}

int KeyConfig::Save(const char* FilePath)
{
    FILE* fp;
    KEYCONFIGINFO* KCInfo;
    int i;
    // 対応情報を保存するファイルを開く
    auto f = fopen_s(&fp, FilePath, "wt");
    if (fp == NULL)
    {
        // 失敗終了
        return false;
    }
    // ゲームの各入力とキーやパddなどの入力との対応情報をファイルに書き出す
    KCInfo = keyConfSys.keyConfigInfo;
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++, KCInfo++)
    {
        fprintf(fp, "PadNo = %d  DirectInputType = %d  SubInfo0 = %d  SubInfo1 = %d \n",
            KCInfo->PadNo, KCInfo->DirectInputType,
            KCInfo->SubInfo[0], KCInfo->SubInfo[1]);
    }
    // ファイルを閉じる
    fclose(fp);
    // 成功終了
    return true;
}

int KeyConfig::Load(const char* FilePath)
{
    FILE* fp;
    KEYCONFIGINFO* KCInfo;
    int i;
    // 対応情報を保存したファイルを開く
    fopen_s(&fp, FilePath, "rt");
    if (fp == NULL)
    {
        return false;
    }
    // ゲームの各入力とキーやパッドなどの入力との対応情報をファイルから読み込む
    KCInfo = keyConfSys.keyConfigInfo;
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++, KCInfo++)
    {
        fscanf_s(fp, "PadNo = % d  DirectInputType = % d  SubInfo0 = % d  SubInfo1 = % d \n",
            &KCInfo->PadNo, &KCInfo->DirectInputType,
            &KCInfo->SubInfo[0], &KCInfo->SubInfo[1]);
    }
    // ファイルを閉じる
    fclose(fp);
    return true;
}

void KeyConfig::SetDefault(void)
{
    int i;
    // デフォルト設定の情報をコピーする
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++)
    {
        keyConfSys.keyConfigInfo[i] = DefaultInputTypeInfo[i];
    }
}

static void UpdateAssist(KEYCONFIGINFO* KCInfo, int* ValidMaxDInput, int* MaxDInput,
    int PadNo, int DirectInputType, int DirectInputValue, int NeutralDirectInputValue)
{
    // 初期状態と同じ値が同じ場合は何もしない
    if (DirectInputValue == NeutralDirectInputValue)
    {
        return;
    }
    // DirectInputの入力値がマイナスかプラスかで処理を分岐
    if (DirectInputValue < 0)
    {
        // MaxDirectInputValue にまだ有効な値が入っていないか
        // 又は MaxDirectInputValue の値よりも DirectInputValue の値が大きいかをチェック
        if (*ValidMaxDInput == FALSE || *MaxDInput < -DirectInputValue)
        {
            // 情報を保存する
            KCInfo->PadNo = PadNo;
            KCInfo->DirectInputType = DirectInputType;
            KCInfo->SubInfo[0] = -1;
            KCInfo->SubInfo[1] = 0;

            *ValidMaxDInput = TRUE;
            *MaxDInput = -DirectInputValue;
        }
    }
    else if (DirectInputValue > 0)
    {
        // MaxDirectInputValue にまだ有効な値が入っていないか
        // 又は MaxDirectInputValue の値よりも DirectInputValue の値が大きいかをチェック
        if (*ValidMaxDInput == FALSE || *MaxDInput < DirectInputValue)
        {
            // 情報を保存する
            KCInfo->PadNo = PadNo;
            KCInfo->DirectInputType = DirectInputType;
            KCInfo->SubInfo[0] = 1;
            KCInfo->SubInfo[1] = 0;

            *ValidMaxDInput = TRUE;
            *MaxDInput = DirectInputValue;
        }
    }
}

int KeyConfig::UpdateInputTypeInfo(int UpdateInputType)
{
    int              i;
    int              j;
    int              ValidMaxDInput;
    int              MaxDInput;
    int              PadNum;
    DINPUT_JOYSTATE* DIJState;
    DINPUT_JOYSTATE* NDIJState;
    KEYCONFIGINFO* KCInfo = &keyConfSys.keyConfigInfo[UpdateInputType];
    int              Result;

    // 戻り値は『入力が無かった』にしておく
    Result = FALSE;

    // 接続されているパッドの数を取得する
    PadNum = GetJoypadNum();

    // パッドの数がプログラムが対応している数より多い場合は、対応している数に制限する
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // 『MaxDInput に有効な値が入っているかどうか』のフラグを倒し、
    // MaxDInput の値も初期化しておく
    ValidMaxDInput = FALSE;
    MaxDInput = 0;

    // 全てのパッドの入力状態をチェック
    DIJState = keyConfSys.DirectiInputState;
    NDIJState = keyConfSys.NeutralDirectInputState;
    for (i = 0; i < PadNum; i++, DIJState++, NDIJState++)
    {
        // 方向入力状態をチェック
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_X, DIJState->X, NDIJState->X);
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_Y, DIJState->Y, NDIJState->Y);
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_Z, DIJState->Z, NDIJState->Z);
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RX, DIJState->Rx, NDIJState->Rx);
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RY, DIJState->Ry, NDIJState->Ry);
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RZ, DIJState->Rz, NDIJState->Rz);

        // 方向コントローラの入力状態をチェック
        for (j = 0; j < 4; j++)
        {
            // POV が有効な値( -1 以外の値 )で、且つ初期状態と異なるかをチェック
            if (DIJState->POV[j] != -1 &&
                DIJState->POV[j] != NDIJState->POV[j])
            {
                // 情報を保存する
                KCInfo->PadNo = i;
                KCInfo->DirectInputType = DIRECTINPUT_TYPE_POV;
                KCInfo->SubInfo[0] = j;
                KCInfo->SubInfo[1] = DIJState->POV[j];

                // 戻り値を『入力があった』にする
                Result = TRUE;
            }
        }

        // ボタンの入力状態をチェック
        for (j = 0; j < 32; j++)
        {
            // ボタンが押されていて、且つ初期状態と異なるかをチェック
            if (DIJState->Buttons[j] == 128 &&
                DIJState->Buttons[j] != NDIJState->Buttons[j])
            {
                // 情報を保存する
                KCInfo->PadNo = i;
                KCInfo->DirectInputType = DIRECTINPUT_TYPE_BUTTON;
                KCInfo->SubInfo[0] = j;
                KCInfo->SubInfo[1] = 0;

                // 戻り値を『入力があった』にする
                Result = TRUE;
            }
        }
    }

    // ValidMaxDirectInputValue が true の場合は、有効な入力があったということなので戻り値を『入力があった』にする
    if (ValidMaxDInput)
    {
        Result = TRUE;
    }

    // キーの入力状態をチェック
    for (i = 0; i < KEY_STATE_BUFFER_SIZE; i++)
    {
        // 入力が初期状態と異なるかをチェック
        if (keyConfSys.KeyInput[i] != keyConfSys.NeutralKeyInput[i])
        {
            // 情報を保存する
            KCInfo->PadNo = -1;
            KCInfo->DirectInputType = DIRECTINPUT_TYPE_KEY;
            KCInfo->SubInfo[0] = i;

            // 戻り値を『入力があった』にする
            Result = TRUE;
        }
    }

    // 入力があったかどうかを返す
    return Result;
}

int KeyConfig::CheckInput(void)
{
    int              i;
    int              PadNum;

    // 接続されているパッドの数を取得する
    PadNum = GetJoypadNum();

    // パッドの数がプログラムが対応している数より多い場合は、対応している数に制限する
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // 全てのパッドの入力状態をチェック
    for (i = 0; i < PadNum; i++)
    {
        // 初期状態と情報が異なる場合は何かしら入力があるということなので、TRUE を返す
        if (memcmp(&keyConfSys.DirectiInputState[i],
            &keyConfSys.NeutralDirectInputState[i], sizeof(DINPUT_JOYSTATE)) != 0)
        {
            return TRUE;
        }
    }

    // キーの入力状態が初期状態と異なる場合はキーの入力があるということなので TRUE を返す
    if (memcmp(keyConfSys.NeutralKeyInput, keyConfSys.KeyInput, sizeof(keyConfSys.NeutralKeyInput)) != 0)
    {
        return TRUE;
    }

    // ここに来たということは何も入力が無かったということなので FALSE を返す
    return FALSE;
}

void KeyConfig::GetInputTypeString(int InputType, char* InputString)
{
    KEYCONFIGINFO* KCInfo = &keyConfSys.keyConfigInfo[InputType];
    KEYINFO* KInfo;
    char           String[256];

    // キーボード入力かどうかで処理を分岐
    if (KCInfo->DirectInputType == DIRECTINPUT_TYPE_KEY)
    {
        // キーコードの情報テーブルに無いキーコードである場合に備えて、最初は UNKNOWN を代入しておく
        strcpy_s(InputString, 256, "Key UNKNOWN");

        // 一致するキーコード情報をテーブルから探す
        for (KInfo = keyInputTable; KInfo->Name != NULL; KInfo++)
        {
            if (KInfo->keyInput == KCInfo->SubInfo[0])
            {
                sprintf_s(InputString,10,"Key %s", KInfo->Name);
                break;
            }
        }
    }
    else
    {
        // パッドの入力名は先頭にパッドの番号を付ける
        sprintf_s(String, "Pad No.%d", KCInfo->PadNo);

        // 対応しているパッドの DirectInput の情報タイプによって分岐
        switch (KCInfo->DirectInputType)
        {
        case DIRECTINPUT_TYPE_X:        // X軸入力の場合はプラスの場合は RIGHT、マイナスの場合は LEFT を付ける
            sprintf_s(InputString, 20,"%s %s", String, KCInfo->SubInfo[0] > 0 ? "RIGHT" : "LEFT");
            break;

        case DIRECTINPUT_TYPE_Y:        // Y軸入力の場合はプラスの場合は DOWN、マイナスの場合は UP を付ける
            sprintf_s(InputString, 20,"%s %s", String, KCInfo->SubInfo[0] > 0 ? "DOWN" : "UP");
            break;

        case DIRECTINPUT_TYPE_Z:        // Z軸入力の場合はプラスの場合は +、マイナスの場合は - を付ける
            sprintf_s(InputString,20, "%s %sZ", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RX:       // X軸回転入力の場合はプラスの場合は +、マイナスの場合は - を付ける
            sprintf_s(InputString, 20,"%s %sRx", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RY:       // Y軸回転入力の場合はプラスの場合は +、マイナスの場合は - を付ける
            sprintf_s(InputString, 20,"%s %sRy", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RZ:       // Z軸回転入力の場合はプラスの場合は +、マイナスの場合は - を付ける
            sprintf_s(InputString,20, "%s %sRz", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_POV:      // 方向コントローラ入力の場合は POV であることと、POVの情報番号と入力角度を付ける
            sprintf_s(InputString,20, "%s POV %d Angle %d°", String, KCInfo->SubInfo[0], KCInfo->SubInfo[1] / 100);
            break;

        case DIRECTINPUT_TYPE_BUTTON:   // ボタン入力の場合は BUTTON とボタン番号を付ける
            sprintf_s(InputString,20, "%s BUTTON %d", String, KCInfo->SubInfo[0]);
            break;
        }
    }
}
