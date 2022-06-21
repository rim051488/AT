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

    // �p�b�h�̐����擾����
    PadNum = GetJoypadNum();

    // �p�b�h�̐����v���O���������Ή����Ă��鐔��葽���ꍇ�́A�Ή����Ă��鐔�ɐ�������
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // �p�b�h�̏�����Ԃ�DirectInput����擾����
    for (i = 0; i < PadNum; i++)
    {
        GetJoypadDirectInputState(PadIDTable[i], &keyConfSys.NeutralDirectInputState[i]);
    }
    // �L�[���͂̏������΂��擾����
    GetHitKeyStateAll(keyConfSys.NeutralKeyInput);
}

// InputProcess�p�̎����̓^�C�v�̏������s���⏕�֐�
// InputState   �������ʂ�������ϐ��A�h���X
// SubInfo      �����̓^�C�v�̃T�u���(1:InputValue���v���X�̒l�̏ꍇ�ɓ��͂���Ƃ��� -1:InputValue���}�C�i�X�̒l�̏ꍇ�ɓ��͂���Ƃ���)
// InputValue   �����͂̒l
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
    // �p�b�h�̐����擾����
    PadNum = GetJoypadNum();
    // �p�b�h�̓��͏���DirectInput����擾����
    for (i = 0; i < PadNum; i++)
    {
        GetJoypadDirectInputState(PadIDTable[i], &keyConfSys.DirectiInputState[i]);
    }
    // ���݂̃L�[�̓��͏�Ԃ��擾����
    GetHitKeyStateAll(keyConfSys.KeyInput);
    // �Q�[���Ŏg�p������͏����\�z����
    KCInfo = keyConfSys.keyConfigInfo;
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++, KCInfo++)
    {
        // �u���͂Ȃ��v��Ԃɂ��Ă���
        InputState[i] = 0;
        // �Ή�����DirectInput�̏��^�C�v�ɂ���ď����𕪊�
        DIJState = KCInfo->PadNo < 0 ? NULL : &keyConfSys.DirectiInputState[KCInfo->PadNo];
        switch (KCInfo->DirectInputType)
        {
        case DIRECTINPUT_TYPE_X:        // �������͂�X���̏ꍇ
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->X);
            break;

        case DIRECTINPUT_TYPE_Y:        // �������͂�Y���̏ꍇ
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->Y);
            break;

        case DIRECTINPUT_TYPE_Z:        // �������͂�Z���̏ꍇ
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->Z);
            break;

        case DIRECTINPUT_TYPE_RX:        // �������͂�X����]�̏ꍇ
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->Rx);
            break;

        case DIRECTINPUT_TYPE_RY:        // �������͂�Y����]�̏ꍇ
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->Ry);
            break;

        case DIRECTINPUT_TYPE_RZ:        // �������͂�Z����]�̏ꍇ
            InputProcessAssist(&InputState[i], KCInfo->SubInfo[0], DIJState->Rz);
            break;
        case DIRECTINPUT_TYPE_POV:       // �����R���g���[���̏ꍇ
            // �ݒ肳��Ă�������ɓ��͂���Ă�����u���͂���v�ɂ���
            if (DIJState->POV[KCInfo->SubInfo[0]] == KCInfo->SubInfo[1])
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;
        case DIRECTINPUT_TYPE_BUTTON:    // �{�^���̏ꍇ
            // �ݒ肳��Ă���{�^����������Ă�����u���͂���v�ɂ���
            if (DIJState->Buttons[KCInfo->SubInfo[0]] == 128)
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;
        case DIRECTINPUT_TYPE_KEY:       // �L�[�{�[�h�̃L�[�̏ꍇ
            // �ݒ肳��Ă���L�[��������Ă�����u���͂���v�ɂ���
            if (keyConfSys.KeyInput[KCInfo->SubInfo[0]])
            {
                InputState[i] = DIRECTINPUT_MAX_VALUE;
            }
            break;
        }
    }
    // 1�t���[���O�̓��͉��΂��Ƃ��Ă���
    ButtonPrevInput = keyConfSys.ButtonInput;
    // ���͏�Ԃ̏�����
    keyConfSys.ButtonInput = 0;
    // �e���͂ɑΉ�����r�b�g���u���͂���v�̏ꍇ�͗��Ă�
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++)
    {
        if (InputState[i] > 0)
        {
            keyConfSys.ButtonInput |= 1 << i;
        }
    }
    // ����̃t���[���Łu���͂���v�ɂȂ�n�߂��r�b�g���Z�o����
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
    // �Ή�����ۑ�����t�@�C�����J��
    auto f = fopen_s(&fp, FilePath, "wt");
    if (fp == NULL)
    {
        // ���s�I��
        return false;
    }
    // �Q�[���̊e���͂ƃL�[��pdd�Ȃǂ̓��͂Ƃ̑Ή������t�@�C���ɏ����o��
    KCInfo = keyConfSys.keyConfigInfo;
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++, KCInfo++)
    {
        fprintf(fp, "PadNo = %d  DirectInputType = %d  SubInfo0 = %d  SubInfo1 = %d \n",
            KCInfo->PadNo, KCInfo->DirectInputType,
            KCInfo->SubInfo[0], KCInfo->SubInfo[1]);
    }
    // �t�@�C�������
    fclose(fp);
    // �����I��
    return true;
}

int KeyConfig::Load(const char* FilePath)
{
    FILE* fp;
    KEYCONFIGINFO* KCInfo;
    int i;
    // �Ή�����ۑ������t�@�C�����J��
    fopen_s(&fp, FilePath, "rt");
    if (fp == NULL)
    {
        return false;
    }
    // �Q�[���̊e���͂ƃL�[��p�b�h�Ȃǂ̓��͂Ƃ̑Ή������t�@�C������ǂݍ���
    KCInfo = keyConfSys.keyConfigInfo;
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++, KCInfo++)
    {
        fscanf_s(fp, "PadNo = % d  DirectInputType = % d  SubInfo0 = % d  SubInfo1 = % d \n",
            &KCInfo->PadNo, &KCInfo->DirectInputType,
            &KCInfo->SubInfo[0], &KCInfo->SubInfo[1]);
    }
    // �t�@�C�������
    fclose(fp);
    return true;
}

void KeyConfig::SetDefault(void)
{
    int i;
    // �f�t�H���g�ݒ�̏����R�s�[����
    for (i = 0; i < KEYCONFIG_INPUT_NUM; i++)
    {
        keyConfSys.keyConfigInfo[i] = DefaultInputTypeInfo[i];
    }
}

static void UpdateAssist(KEYCONFIGINFO* KCInfo, int* ValidMaxDInput, int* MaxDInput,
    int PadNo, int DirectInputType, int DirectInputValue, int NeutralDirectInputValue)
{
    // ������ԂƓ����l�������ꍇ�͉������Ȃ�
    if (DirectInputValue == NeutralDirectInputValue)
    {
        return;
    }
    // DirectInput�̓��͒l���}�C�i�X���v���X���ŏ����𕪊�
    if (DirectInputValue < 0)
    {
        // MaxDirectInputValue �ɂ܂��L���Ȓl�������Ă��Ȃ���
        // ���� MaxDirectInputValue �̒l���� DirectInputValue �̒l���傫�������`�F�b�N
        if (*ValidMaxDInput == FALSE || *MaxDInput < -DirectInputValue)
        {
            // ����ۑ�����
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
        // MaxDirectInputValue �ɂ܂��L���Ȓl�������Ă��Ȃ���
        // ���� MaxDirectInputValue �̒l���� DirectInputValue �̒l���傫�������`�F�b�N
        if (*ValidMaxDInput == FALSE || *MaxDInput < DirectInputValue)
        {
            // ����ۑ�����
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

    // �߂�l�́w���͂����������x�ɂ��Ă���
    Result = FALSE;

    // �ڑ�����Ă���p�b�h�̐����擾����
    PadNum = GetJoypadNum();

    // �p�b�h�̐����v���O�������Ή����Ă��鐔��葽���ꍇ�́A�Ή����Ă��鐔�ɐ�������
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // �wMaxDInput �ɗL���Ȓl�������Ă��邩�ǂ����x�̃t���O��|���A
    // MaxDInput �̒l�����������Ă���
    ValidMaxDInput = FALSE;
    MaxDInput = 0;

    // �S�Ẵp�b�h�̓��͏�Ԃ��`�F�b�N
    DIJState = keyConfSys.DirectiInputState;
    NDIJState = keyConfSys.NeutralDirectInputState;
    for (i = 0; i < PadNum; i++, DIJState++, NDIJState++)
    {
        // �������͏�Ԃ��`�F�b�N
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_X, DIJState->X, NDIJState->X);
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_Y, DIJState->Y, NDIJState->Y);
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_Z, DIJState->Z, NDIJState->Z);
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RX, DIJState->Rx, NDIJState->Rx);
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RY, DIJState->Ry, NDIJState->Ry);
        UpdateAssist(KCInfo, &ValidMaxDInput, &MaxDInput, i, DIRECTINPUT_TYPE_RZ, DIJState->Rz, NDIJState->Rz);

        // �����R���g���[���̓��͏�Ԃ��`�F�b�N
        for (j = 0; j < 4; j++)
        {
            // POV ���L���Ȓl( -1 �ȊO�̒l )�ŁA��������ԂƈقȂ邩���`�F�b�N
            if (DIJState->POV[j] != -1 &&
                DIJState->POV[j] != NDIJState->POV[j])
            {
                // ����ۑ�����
                KCInfo->PadNo = i;
                KCInfo->DirectInputType = DIRECTINPUT_TYPE_POV;
                KCInfo->SubInfo[0] = j;
                KCInfo->SubInfo[1] = DIJState->POV[j];

                // �߂�l���w���͂��������x�ɂ���
                Result = TRUE;
            }
        }

        // �{�^���̓��͏�Ԃ��`�F�b�N
        for (j = 0; j < 32; j++)
        {
            // �{�^����������Ă��āA��������ԂƈقȂ邩���`�F�b�N
            if (DIJState->Buttons[j] == 128 &&
                DIJState->Buttons[j] != NDIJState->Buttons[j])
            {
                // ����ۑ�����
                KCInfo->PadNo = i;
                KCInfo->DirectInputType = DIRECTINPUT_TYPE_BUTTON;
                KCInfo->SubInfo[0] = j;
                KCInfo->SubInfo[1] = 0;

                // �߂�l���w���͂��������x�ɂ���
                Result = TRUE;
            }
        }
    }

    // ValidMaxDirectInputValue �� true �̏ꍇ�́A�L���ȓ��͂��������Ƃ������ƂȂ̂Ŗ߂�l���w���͂��������x�ɂ���
    if (ValidMaxDInput)
    {
        Result = TRUE;
    }

    // �L�[�̓��͏�Ԃ��`�F�b�N
    for (i = 0; i < KEY_STATE_BUFFER_SIZE; i++)
    {
        // ���͂�������ԂƈقȂ邩���`�F�b�N
        if (keyConfSys.KeyInput[i] != keyConfSys.NeutralKeyInput[i])
        {
            // ����ۑ�����
            KCInfo->PadNo = -1;
            KCInfo->DirectInputType = DIRECTINPUT_TYPE_KEY;
            KCInfo->SubInfo[0] = i;

            // �߂�l���w���͂��������x�ɂ���
            Result = TRUE;
        }
    }

    // ���͂����������ǂ�����Ԃ�
    return Result;
}

int KeyConfig::CheckInput(void)
{
    int              i;
    int              PadNum;

    // �ڑ�����Ă���p�b�h�̐����擾����
    PadNum = GetJoypadNum();

    // �p�b�h�̐����v���O�������Ή����Ă��鐔��葽���ꍇ�́A�Ή����Ă��鐔�ɐ�������
    if (PadNum > MAX_GAMEPAD_NUM)
    {
        PadNum = MAX_GAMEPAD_NUM;
    }

    // �S�Ẵp�b�h�̓��͏�Ԃ��`�F�b�N
    for (i = 0; i < PadNum; i++)
    {
        // ������ԂƏ�񂪈قȂ�ꍇ�͉���������͂�����Ƃ������ƂȂ̂ŁATRUE ��Ԃ�
        if (memcmp(&keyConfSys.DirectiInputState[i],
            &keyConfSys.NeutralDirectInputState[i], sizeof(DINPUT_JOYSTATE)) != 0)
        {
            return TRUE;
        }
    }

    // �L�[�̓��͏�Ԃ�������ԂƈقȂ�ꍇ�̓L�[�̓��͂�����Ƃ������ƂȂ̂� TRUE ��Ԃ�
    if (memcmp(keyConfSys.NeutralKeyInput, keyConfSys.KeyInput, sizeof(keyConfSys.NeutralKeyInput)) != 0)
    {
        return TRUE;
    }

    // �����ɗ����Ƃ������Ƃ͉������͂����������Ƃ������ƂȂ̂� FALSE ��Ԃ�
    return FALSE;
}

void KeyConfig::GetInputTypeString(int InputType, char* InputString)
{
    KEYCONFIGINFO* KCInfo = &keyConfSys.keyConfigInfo[InputType];
    KEYINFO* KInfo;
    char           String[256];

    // �L�[�{�[�h���͂��ǂ����ŏ����𕪊�
    if (KCInfo->DirectInputType == DIRECTINPUT_TYPE_KEY)
    {
        // �L�[�R�[�h�̏��e�[�u���ɖ����L�[�R�[�h�ł���ꍇ�ɔ����āA�ŏ��� UNKNOWN �������Ă���
        strcpy_s(InputString, 256, "Key UNKNOWN");

        // ��v����L�[�R�[�h�����e�[�u������T��
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
        // �p�b�h�̓��͖��͐擪�Ƀp�b�h�̔ԍ���t����
        sprintf_s(String, "Pad No.%d", KCInfo->PadNo);

        // �Ή����Ă���p�b�h�� DirectInput �̏��^�C�v�ɂ���ĕ���
        switch (KCInfo->DirectInputType)
        {
        case DIRECTINPUT_TYPE_X:        // X�����͂̏ꍇ�̓v���X�̏ꍇ�� RIGHT�A�}�C�i�X�̏ꍇ�� LEFT ��t����
            sprintf_s(InputString, 20,"%s %s", String, KCInfo->SubInfo[0] > 0 ? "RIGHT" : "LEFT");
            break;

        case DIRECTINPUT_TYPE_Y:        // Y�����͂̏ꍇ�̓v���X�̏ꍇ�� DOWN�A�}�C�i�X�̏ꍇ�� UP ��t����
            sprintf_s(InputString, 20,"%s %s", String, KCInfo->SubInfo[0] > 0 ? "DOWN" : "UP");
            break;

        case DIRECTINPUT_TYPE_Z:        // Z�����͂̏ꍇ�̓v���X�̏ꍇ�� +�A�}�C�i�X�̏ꍇ�� - ��t����
            sprintf_s(InputString,20, "%s %sZ", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RX:       // X����]���͂̏ꍇ�̓v���X�̏ꍇ�� +�A�}�C�i�X�̏ꍇ�� - ��t����
            sprintf_s(InputString, 20,"%s %sRx", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RY:       // Y����]���͂̏ꍇ�̓v���X�̏ꍇ�� +�A�}�C�i�X�̏ꍇ�� - ��t����
            sprintf_s(InputString, 20,"%s %sRy", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_RZ:       // Z����]���͂̏ꍇ�̓v���X�̏ꍇ�� +�A�}�C�i�X�̏ꍇ�� - ��t����
            sprintf_s(InputString,20, "%s %sRz", String, KCInfo->SubInfo[0] > 0 ? "+" : "-");
            break;

        case DIRECTINPUT_TYPE_POV:      // �����R���g���[�����͂̏ꍇ�� POV �ł��邱�ƂƁAPOV�̏��ԍ��Ɠ��͊p�x��t����
            sprintf_s(InputString,20, "%s POV %d Angle %d��", String, KCInfo->SubInfo[0], KCInfo->SubInfo[1] / 100);
            break;

        case DIRECTINPUT_TYPE_BUTTON:   // �{�^�����͂̏ꍇ�� BUTTON �ƃ{�^���ԍ���t����
            sprintf_s(InputString,20, "%s BUTTON %d", String, KCInfo->SubInfo[0]);
            break;
        }
    }
}
