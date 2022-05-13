#include <DxLib.h>
#include <array>

using namespace std;

void MyDrawGraph(int x, int y, int imghandle,int pshandle) {
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
		v.u = 0.0f;
		v.v = 0.0f;
	}
	// 左上
	verts[0].pos.x = x;
	verts[0].pos.y = y;
	// 右上
	verts[1].pos.x = x+width;
	verts[1].pos.y = y;
	verts[1].u = 1.0f;
	// 左下
	verts[2].pos.x = x;
	verts[2].pos.y = y+haight;
	verts[2].v = 1.0f;
	// 右下
	verts[3].pos.x = x+width;
	verts[3].pos.y = y+haight;
	verts[3].u = 1.0f;
	verts[3].v = 1.0f;
	int alphamode, alphaparam;
	GetDrawAlphaTest(&alphamode,&alphaparam);
	SetUsePixelShader(pshandle);
	SetUseTextureToShader(0, imghandle);
	DrawPrimitive2DToShader(verts.data(), verts.size(), DX_PRIMTYPE_TRIANGLESTRIP);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	int img = LoadGraph(L"bg_takeyabu.jpg");
	int pps = LoadPixelShader(L"PixelShader.pso");
	//int ps = LoadPixelShader(L"test.pso");
	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		//DrawGraph(0, 0, img, true);
		//MyDrawGraph(0, 0, img, ps);
		MyDrawGraph(0, 0, img, pps);
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}