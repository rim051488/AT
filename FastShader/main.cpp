#include <DxLib.h>
#include <array>

using namespace std;

void MyDrawGraph(int x, int y, int imghandle,int secondImg,int thirdIng,int pshandle) {
	int width, haight;
	GetGraphSize(imghandle,&width,&haight);
	array<VERTEX2DSHADER, 4> verts;
	for (auto& v : verts) {
		v.rhw = 1.0;
		v.dif = GetColorU8(0xff, 0xff, 0xff, 0xff); // ディフューズ
		v.spc = GetColorU8(255, 255, 255, 255);		// スペキュラ
		v.su = 0.0f;
		v.sv = 0.0f;
		v.pos.z = 0.0f;
	}
	// 左上
	verts[0].pos.x = x;
	verts[0].pos.y = y;
	verts[0].u = 0.0f;
	verts[0].v = 0.0f;
// 右上
	verts[1].pos.x = x+width;
	verts[1].pos.y = y;
	verts[1].u = 1.0f;
	verts[1].v = 0.0f;
	// 左下
	verts[2].pos.x = x;
	verts[2].pos.y = y+haight;
	verts[2].u = 0.0f;
	verts[2].v = 1.0f;
	// 右下
	verts[3].pos.x = x+width;
	verts[3].pos.y = y+haight;
	verts[3].u = 1.0f;
	verts[3].v = 1.0f;
	int alphamode, alphaparam;
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255);
	GetDrawAlphaTest(&alphamode,&alphaparam);
	SetDrawAlphaTest(DX_CMP_GREATER, 0);
	SetUseAlphaTestFlag(true);
	SetUsePixelShader(pshandle);
	SetUseTextureToShader(0, imghandle);
	SetUseTextureToShader(1, secondImg);
	SetUseTextureToShader(2, thirdIng);
	DrawPrimitive2DToShader(verts.data(), verts.size(), DX_PRIMTYPE_TRIANGLESTRIP);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(true);
	DxLib_Init();
	int img = LoadGraph(L"zinbutu.png");
	//int ptn = LoadGraph(L"ptn2.png");
	//int ptn = LoadGraph(L"ptn13.png");
	int ptn = LoadGraph(L"carbon_pattern.png");
	int noimg = LoadGraph(L"zinbutu_n.png");
	int bg = LoadGraph(L"huukei.png");
	//int pps = LoadPixelShader(L"PixelShader.pso");
	int pps = LoadPixelShader(L"test.pso");
	int psPP = LoadPixelShader(L"PostProcess.pso");
	int imgPP = LoadGraph(L"CrackNormalMap.png");

	// 定数バッファの確保(VRAM上)
	int cbuff = DxLib::CreateShaderConstantBuffer(sizeof(float) * 4);
	// グラボのメモリは直接いじれない
	// RAM上のメモリでシュミレートする
	float* threshold = static_cast<float*>(DxLib::GetBufferShaderConstantBuffer(cbuff));
	float t = 0.0f;
	float angle = 0.0f;
	char keystate[256];
	int sw, sh;
	GetDrawScreenSize(&sw,&sh);
	int handleForPP = MakeScreen(sw, sh);
	int shakeTime = 0;
	while (ProcessMessage() != -1) {
		SetDrawScreen(handleForPP);
		angle += 0.05f;
		GetHitKeyStateAll(keystate);
		if (keystate[KEY_INPUT_UP]){
			t -= 0.01f;
		}
		if (keystate[KEY_INPUT_DOWN]){
			t += 0.01f;
		}
		if (keystate[KEY_INPUT_SPACE]) {
			shakeTime = 60;
		}
		if (shakeTime > 0) {
			--shakeTime;
		}
		//SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		//DrawGraph(70, 0, bg, true);
		threshold[0] = t;
		threshold[1] = angle;
		UpdateShaderConstantBuffer(cbuff);
		SetShaderConstantBuffer(cbuff, DX_SHADERTYPE_PIXEL, 0);
		MyDrawGraph(20, 0, img,ptn,noimg ,pps);

		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();
		// モノトーンとなる
		//GraphFilter(handleForPP, DX_GRAPH_FILTER_MONO,-60,7);
		// ガウスフィルターだと（ぼかし）
		//GraphFilter(handleForPP, DX_GRAPH_FILTER_GAUSS, 32, 1000);
		//DrawRotaGraph(320, 240,1,0, handleForPP, false);
		MyDrawGraph(0, 0, handleForPP, imgPP, -1, psPP);
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}