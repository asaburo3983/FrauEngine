#include "EventUI.h"

void EventUI::Setup(ImageObject* _base, ImageObject* _openShopStr, ImageObject* _planterStr, ImageObject* _exitShopStr) {
	base = _base;
	openShopStr = _openShopStr;
	planterStr = _planterStr;
	exitShopStr = _exitShopStr;
}
void EventUI::SetDrawPos() {
	Player* player = Player::GetInstance();
	//イベント座標
	float offsetX = 1920.0 / 15.0;
	DirectX::XMMATRIX tmpMatrix = DirectX::XMMatrixTranslation(1, 1, 1);
	DirectX::XMMATRIX world_matrix = DirectX::XMMatrixTranslation(player->GetPos().X, player->GetPos().Y, player->GetPos().Z);
	DirectX::XMMATRIX screen_matrix = tmpMatrix * world_matrix * Camera::GetInstance()->GetView() * Camera::GetInstance()->GetProjection();
	DirectX::XMFLOAT4X4 wm;
	XMStoreFloat4x4(&wm, XMMatrixTranspose(screen_matrix));
	Vector2 eventBasePos = Vector2((wm._14) * 150, (-wm._24) * 108.0);
	eventBasePos.X = (player->GetPos().X + 7.5) * offsetX;

	switch (player->GetEventNum()) {
	case 1://ショッピング
		eventBasePos.X += 350;
		eventBasePos.Y -= 400;

		exitShopStr->SetAll(eventBasePos, Vector2(1, 1), 0, 1);
		base->SetTurn(true, false);
		base->SetAll(eventBasePos, Vector2(1, 1), 0, 1);
		break;
	case 2://プランター
		eventBasePos.X += 500;
		eventBasePos.Y -= 150;

		planterStr->SetAll(eventBasePos, Vector2(1, 1), 0, 1);
		base->SetTurn(true, false);
		base->SetAll(eventBasePos, Vector2(1, 1), 0, 1);
		break;
	case 3://開店
		eventBasePos.X -= 500;
		eventBasePos.Y -= 100;

		openShopStr->SetAll(eventBasePos, Vector2(1, 1), 0, 1);
		base->SetTurn(false, false);
		base->SetAll(eventBasePos, Vector2(1, 1), 0, 1);
		break;
	}
}

int EventUI::Click() {
	Player* player = Player::GetInstance();
	MouseInput* MOUSE = MouseInput::GetInstance();

	if (player->GetEventNum() && base->Hit(MOUSE->x, MOUSE->y) && MOUSE->left == 1) {
		return player->GetEventNum();
	}
	return 0;
}
void EventUI::Draw() {
	Player* player = Player::GetInstance();
	if (player->GetEventNum()) {
		base->Draw();
	}
	switch (player->GetEventNum()) {
	case 1://ショッピング	
		exitShopStr->Draw();
		break;
	case 2://プランター
		planterStr->Draw();
		break;
	case 3://開店
		openShopStr->Draw();
		break;
	}
}