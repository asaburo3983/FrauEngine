#include "MagicShop.h"

void MagicShop::Initialize(std::string _itemCSVPath, std::string _textCSVPath) {

	auto rc = Resource::GetInstance();
	npc[0].SetResource(rc->Image("Christa_Normal.png"));
	npc[1].SetResource(rc->Image("Christa_Smile.png"));
	npc[2].SetResource(rc->Image("Christa_Surprise.png"));
	npc[3].SetResource(rc->Image("Christa_Trouble.png"));
	for (int i = 0; i < 4; i++) {
		npc[i].SetAll(Vector2(400, 760), Vector2(0.5, 0.5), 0, alpha);
		npc[i].SetTurn(true, false);
	}
	Shop::Initialize(_itemCSVPath, _textCSVPath);

	itemIcon[0].SetResource(rc->Image("MagicPlanter.png"));
	itemIcon[1].SetResource(rc->Image("BugFix.png"));
	itemIcon[2].SetResource(rc->Image("Book0.png"));
	itemIcon[3].SetResource(rc->Image("Book1.png"));
	itemIcon[4].SetResource(rc->Image("Book2.png"));
	itemIcon[5].SetResource(rc->Image("Book3.png"));
	itemIcon[6].SetResource(rc->Image("Book4.png"));

	
}
void MagicShop::Update() {
	Shop::Update();
}
void MagicShop::Draw() {

	//—§‚¿ŠG•`‰æ
	npc[charaEcpression].SetAlpha(alpha);
	npc[charaEcpression].Draw();

	Shop::Draw();

	if (selectNum != -1) {
		itemIcon[selectNum].SetAll(Vector2(1015, 320), Vector2(1, 1), 0, manualAlpha);
		itemIcon[selectNum].Draw();
	}

}