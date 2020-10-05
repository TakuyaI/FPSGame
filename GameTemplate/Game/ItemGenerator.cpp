#include "stdafx.h"
#include "ItemGenerator.h"

const CVector2 ITEM_SPRITE_SIZE = { 320.0f, 180.0f }; //アイテムのスプライトのサイズ。
const int MOVE_RIGHT_TIME = 10;                       //タイムが10になるまで、アイテムゲットのフォントが右に動く。
const int MOVE_LEFT_TIME = 30;                        //タイムが30を超えたら、アイテムゲットのフォントが左に動く。
const float EXP_CAL_NUM = 1.7f;                       //指数計算で使う値。
const int MOVE_UP_TIME = 2;                           //タイムが2になるまで、アイテムゲットのフォントが上に動く。
const float UP_MOVE_SPEED = 20.0f;                    //アイテムゲットのフォントが上に動くスピード。
ItemGenerator::ItemGenerator()
{
	//テクスチャをロード。
	m_itemTex.Init(L"Resource/sprite/item2.dds", ITEM_SPRITE_SIZE.x, ITEM_SPRITE_SIZE.y);
	m_danyakuTex.Init(L"Resource/sprite/item_danyaku.dds", ITEM_SPRITE_SIZE.x, ITEM_SPRITE_SIZE.y);
	m_kaihukuyakuTex.Init(L"Resource/sprite/item_kaihuku.dds", ITEM_SPRITE_SIZE.x, ITEM_SPRITE_SIZE.y);
	//アイテムのインスタンスを作成。
	m_kaihuku = g_goMgr.NewGameObject<Kaihuku>(kaihuku);
	m_danyaku = g_goMgr.NewGameObject<Danyaku>(danyaku);

	for (int i = 0; i < m_maxFontItemNum; i++) {
		m_fontPos[i].x = m_initFontPos.x;
		m_fontPos[i].y = m_initFontPos.y;
		m_timerX[i] = 0;
		m_timerY[i] = 0;
		m_itemName[i] = nullptr;
	}
}
ItemGenerator::~ItemGenerator()
{
	//アイテムのインスタンスを削除する。
	g_goMgr.DeleteGameObject(m_kaihuku);
	g_goMgr.DeleteGameObject(m_danyaku);
}
void ItemGenerator::GetItem(bool* flug, IItemObject* item, wchar_t* name)
{
	if (*flug != false) {
		//アイテムを拾った。
		if(item->GetHaveFlug() != true) {
			//拾ったアイテムと同じものをまだ持っていない。
			for (int i = 0; i < m_maxHaveNum; i++) {
				//配列の0番から探して、空いているところに入れる。
				if (m_getItemList[i] == nullptr) {
					//空いていた。
					m_getItemList[i] = item;
					//アイテムを所持している状態になったので、
					//フラグをtrueにする。
					item->SetHaveFlug(true);
					//アイテムの番号に配列の番号を入れる。
					m_getItemList[i]->SetItemNumber(i);
					m_stateNumber = i;
					//入れ終わったので、for文を終了する。
					break;
				}
			}
		}
		//アイテムの所持数を加算する。
		int itemNum = item->GetHaveNum();
		item->SetHaveNum(++itemNum);

		//アイテムゲットのフォントを1個追加。
		m_DisplayingNum++;
		for (int i = 0; i < m_DisplayingNum; i++) {
			//配列にnullptrが入っていたら、
			//ゲットしたアイテムの名前を入れる。
			if (m_itemName[i] == nullptr) {
				m_itemName[i] = name;
				break;
			}
		}
		int arrayNum = m_DisplayingNum - 2;
		//arrayNumは配列の番号なので、
		//m_DisplayingNumの番号と一番新しいアイテムゲットのフォントの番号は外すので、
		//2引く。
		//一番新しいアイテムゲットのフォント以外のフォントを上に移動させるため、
		//タイマーをリセットする。
		for (int i = 0; i < arrayNum; i++) {
			m_timerY[i] = 0;
		}
	}
	*flug = false;
}
void ItemGenerator::SelectItem()
{
	//LB2ボタン。
	if (g_pad->IsTrigger(enButtonLB2)) {
		//LB2ボタンを押した。
		if (m_pushLB2Flug != true) {
			//1回押したら、1度離して押さないと反応しないようにする。
			m_stateNumber--;
			if (m_stateNumber < 0) {
				//m_stateNumberがマイナスになったら、
				//m_maxHaveNumを代入する。
				int num = m_maxHaveNum;
				//配列の関係上、１引く。
				m_stateNumber = --num;
			}
			for (int i = 0; i < m_maxHaveNum; i++) {
				if (m_getItemList[m_stateNumber] != nullptr) {
					//m_getItemListの中にアイテムが入っていたので、
					//表示する。
					m_stateNumber = m_getItemList[m_stateNumber]->GetmItemNumber();
					break;
				}
				else {
					m_stateNumber--;
					if (m_stateNumber < 0) {
						int num = m_maxHaveNum;
						m_stateNumber = --num;
					}
				}
			}
			//LB2ボタンを押しているので、フラグをtrueにする。
			m_pushLB2Flug = true;
		}
	}
	else {
		//LB2ボタンを離しているので、フラグをfalseにする。
		m_pushLB2Flug = false;
	}
	//RB2ボタン。
	if (g_pad->IsTrigger(enButtonRB2)) {
		//RB2ボタンを押した。
		if (m_pushRB2Flug != true) {
			//1回押したら、1度離して押さないと反応しないようにする。
			m_stateNumber++;
			if (m_stateNumber >= m_maxHaveNum) {
				//m_stateNumberがm_maxHaveNum以上になったら、
				//0を代入する。
				m_stateNumber = 0;
			}
			for (int i = 0; i < m_maxHaveNum; i++) {
				if (m_getItemList[m_stateNumber] != nullptr) {
					//m_getItemListの中にアイテムが入っていたので、
					//表示する。
					m_stateNumber = m_getItemList[m_stateNumber]->GetmItemNumber();
					break;
				}
				else {
					m_stateNumber++;
					if (m_stateNumber >= m_maxHaveNum) {
						m_stateNumber = 0;
					}
				}
			}
			//RB2ボタンを押しているので、フラグをtrueにする。
			m_pushRB2Flug = true;
		}
	}
	else {
		//RB2ボタンを離しているので、フラグをfalseにする。
		m_pushRB2Flug = false;
	}


}
void ItemGenerator::UseItem()
{
	if (g_pad->IsTrigger(enButtonA)) {
		//Aボタンを押した。
			if (m_getItemList[m_stateNumber] != nullptr) {
				//m_getItemList[m_stateNumber]にアイテムが入っている。
				//アイテム効果。
				m_getItemList[m_stateNumber]->ItemEffects();
				//使ったので、個数を減らす。
				int num = m_getItemList[m_stateNumber]->GetHaveNum();
				m_getItemList[m_stateNumber]->SetHaveNum(--num);
				if (m_getItemList[m_stateNumber]->GetHaveNum() <= 0) {
					//アイテムの個数が0個になった。
					//アイテムの所持フラグをfalseにする。
					m_getItemList[m_stateNumber]->SetHaveFlug(false);
					//番号をリセット。
					m_getItemList[m_stateNumber]->SetItemNumber(1000);
					//m_getItemList[m_stateNumber]にnullptrを入れる。
					m_getItemList[m_stateNumber] = nullptr;
				}
			}
	}
}
void ItemGenerator::FontItem(Sprite& sprite, IItemObject* item)
{
	sprite.Update(
		m_position,
		CQuaternion::Identity(),
		CVector3::One()
	);
	m_stateNum = item->GetHaveNum();
	sprite.Draw();
	//表示されているアイテムの個数を表示する。
	wchar_t text[256];
	swprintf_s(text, L"%d", m_stateNum);
	m_itemNumFont.Draw(text, m_itemNumFontPos, m_fontColor, m_fontSize);
}
void ItemGenerator::Update()
{
	//弾薬を取得したかどうか。
	GetItem(&m_getDanyakuFlug, m_danyaku ,L"弾薬");
	//回復薬を取得したかどうか。
	GetItem(&m_getKaihukuyakuFlug, m_kaihuku, L"回復薬");
	//アイテムを選ぶ。
	SelectItem();
	//アイテムを使用使用するかどうか。
	UseItem();
}
void ItemGenerator::PostRender()
{
		{//アイテムの一番下のテクスチャ。
			m_itemTex.Update(
				m_position,
				CQuaternion::Identity(),
				CVector3::One()
			);
			m_itemTex.Draw();
		}
		if (m_stateNumber == m_danyaku->GetmItemNumber()) {
			//弾薬を表示。
			FontItem(m_danyakuTex, m_danyaku);
		}
		else if (m_stateNumber == m_kaihuku->GetmItemNumber()) {
			//回復薬を表示。
			FontItem(m_kaihukuyakuTex, m_kaihuku);
		}
		if (m_DisplayingNum > 0) {
			//アイテムゲットのフォントを表示中。

			//displayingNumは配列の番号なので、
			//m_DisplayingNumの番号は外すので、1引く。
			int displayingNum = m_DisplayingNum;
			--displayingNum;
			for (int i = 0; i < m_DisplayingNum; i++) {
				m_timerX[i]++;
				//指数。
				float sisu = MOVE_RIGHT_TIME;
				if (m_timerX[i] <= MOVE_RIGHT_TIME) {
					//タイマーが10以下
					//右に移動
					//指数からタイマー分引く。フレーム毎に指数が減っていく。
					sisu -= m_timerX[i];
					m_fontPos[i].x += powf(EXP_CAL_NUM, sisu);
				}
				else if (m_timerX[i] >= MOVE_LEFT_TIME) {
					//タイマーが30以上になった
					//左に移動
					//指数からタイマーからMOVE_LEFT_TIMEを引いた分引く。フレーム毎に指数が減っていく。
					sisu -= m_timerX[i] - MOVE_LEFT_TIME;
					m_fontPos[i].x -= powf(EXP_CAL_NUM, sisu);

					if (m_fontPos[i].x <= m_initFontPos.x) {
						//フォントのX座標が初期値以下になった。
						//初期値に固定。
						m_fontPos[i].x = m_initFontPos.x;
						m_fontPos[i].y = m_initFontPos.y;
						if (i == displayingNum) {
							//最後のフォントのX座標が初期値以下になった。
							for (int j = 0; j < m_DisplayingNum; j++) {
								//タイマーとアイテムの名前を初期化。
								m_timerX[j] = 0;
								m_timerY[j] = 0;
								m_itemName[j] = nullptr;
							}
							//m_DisplayingNumを0にして、表示しないようにする。
							m_DisplayingNum = 0;
						}
					}
				}
				if (i < displayingNum) {
					//一番新しいアイテムゲットのフォントの番号未満の配列。
					if (m_timerY[i] <= MOVE_UP_TIME) {
						//上に移動。
						m_fontPos[i].y -= UP_MOVE_SPEED;
						m_timerY[i]++;
					}
				}
				wchar_t text[256];
				swprintf_s(text, L"%sを獲得した", m_itemName[i]);
				m_getFontItem[i].Draw(text, m_fontPos[i], m_getItemaFontColor, m_getItemaFontScale);
			}
		}
}