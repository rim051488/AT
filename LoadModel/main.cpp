#include <DxLib.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return 0;
	}
	//int model = MV1LoadModel(L"Model/model.mv1");
	int model = MV1LoadModel(L"pbrmodel/sphere.mv1");
	//int sphere = MV1LoadModel(L"Model/sphere.mqo");
	int rough = LoadGraph(L"pbrmodel/roughness.png");
	int rough = LoadGraph(L"pbrmodel/sph.png");
	int ps = LoadPixelShader(L"ps.pso");
	int vs = LoadVertexShader(L"vs.vso");
	auto tlNum = MV1GetTriangleListNum(model);
	int tlVertType = -1;
	for (int i = 0; i < tlNum; ++i)
	{
		tlVertType = MV1GetTriangleListVertexType(model, i);
		break;
	}
	float amplitude = 0.0f;
	int frame = 0;
	int rt = MakeScreen(640, 480);
	//MV1SetPosition(model, VGet(0, 0, 0));
	//MV1SetScale(model, VGet(2.0, 2.0, 2.0));
	//MV1SetPosition(model, VGet(0, -50, 0));

	float angle = 0.0f;
	while (ProcessMessage() != -1) {
		angle += 0.01f;
		SetDrawScreen(rt);
		//SetDrawScreen(DX_SCREEN_BACK);
		SetCameraNearFar(1.0, 500.0f);
		SetCameraPositionAndTargetAndUpVec(VGet(0, 0, -400), VGet(0, 0, 0), VGet(0, 1, 0));
		ClsDrawScreen();
		if (tlVertType == DX_MV1_VERTEX_TYPE_1FRAME) {
			DrawString(0,0,L"not normal not skinning",0xffffff);
		}
		else if (tlVertType == DX_MV1_VERTEX_TYPE_4FRAME) {
			DrawString(0,0,L"not normal use skinning",0xffffff);
		}
		else if (tlVertType == DX_MV1_VERTEX_TYPE_NMAP_1FRAME) {
			DrawString(0, 0, L"use normal not skinning", 0xffffff);
		}
		else if (tlVertType == DX_MV1_VERTEX_TYPE_NMAP_4FRAME) {
			DrawString(0, 0, L"use normal use skinning", 0xffffff);
		}
		// シェーダを使わない
		//MV1SetUseOrigShader(false);
		//MV1DrawModel(sphere);
		if (CheckHitKey(KEY_INPUT_Z))
		{
			amplitude = 10.0;
		}
		// シェーダを使う
		MV1SetUseOrigShader(true);
		SetUseZBuffer3D(true);
		SetWriteZBuffer3D(true);
		MV1SetUseZBuffer(model, true);
		MV1SetWriteZBuffer(model, true);

		SetUseVertexShader(vs);
		SetUsePixelShader(ps);
		//SetCameraPositionAndTargetAndUpVec(VGet(0, 0, -50), VGet(0, 0, 0), VGet(0, 1, 0));
		MV1SetRotationXYZ(model, VGet(0, angle, 0));
		MV1DrawModel(model);
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		int dx = 0, dy = 0;
		if (amplitude > 0.0f) {
			dx = ((frame % 3) - 1) * amplitude;
		}
		DrawGraph(dx, dy, rt, false);
		amplitude *= 0.9;
		if (amplitude < 0.1f)
		{
			amplitude = 0.0f;
		}
		frame++;
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}