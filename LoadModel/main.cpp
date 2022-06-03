#include <DxLib.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return 0;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	DxLib::SetCameraPositionAndTargetAndUpVec(VGet(0, 0, -400), VGet(0, 0, 0), VGet(0, 1, 0));
	int model = MV1LoadModel(L"Model/model.mv1");
	int sphere = MV1LoadModel(L"Model/sphere.mqo");
	int ps = LoadPixelShader(L"ps.pso");
	int vs = LoadVertexShader(L"vs.vso");
	auto tlNum = MV1GetTriangleListNum(model);
	int tlVertType = -1;
	for (int i = 0; i < tlNum; ++i)
	{
		tlVertType = MV1GetTriangleListVertexType(model, i);
		break;
	}
	MV1SetPosition(model, VGet(0, 0, 0));
	float angle = 0.0f;
	while (ProcessMessage() != -1) {
		ClsDrawScreen();
		if (tlVertType == DX_MV1_VERTEX_TYPE_1FRAME) {
			DrawString(0,0,L"not normal not skinning",0xffffff);
		}
		angle += 0.01f;
		// シェーダを使わない
		//MV1SetUseOrigShader(false);
		//MV1DrawModel(sphere);
	
		// シェーダを使う
		MV1SetUseOrigShader(true);
		DxLib::SetUseZBuffer3D(true);
		DxLib::SetWriteZBuffer3D(true);
		DxLib::SetWriteZBufferFlag(true);
		DxLib::SetUseVertexShader(vs);
		DxLib::SetUsePixelShader(ps);
		MV1SetRotationXYZ(model, VGet(0, angle, 0));
		MV1DrawModel(model);
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}