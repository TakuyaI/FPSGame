#include "stdafx.h"
#include "Game.h"
#include "ItemObject.h"
const int ENEMY_STAY = 0; //待機中
const int ENEMY_TRACKING = 1;  //追跡中
const int ENEMY_ATTACK = 2;    //攻撃
const int ENEMY_PUSH_AWAY = 3; //突き飛ばされた。
const int ENEMY_DEATH = 4; //死亡。
const float TRACKING_DISTANCE = 750.0f; //追跡してくる距離。
const float ATTACK_DISTANCE = 150.0f;  //攻撃してくる距離。
IEnemyObject::IEnemyObject()
{
	//サンプルのエフェクトをロードする。
	m_sampleEffect = Effekseer::Effect::Create(
		g_goMgr.GetEffekseerManager(),
		(const EFK_CHAR*)L"Assets/effect/test03.efk"
	);
	//サウンドをロード。
	m_receiveDamageS.Init(L"Assets/sound/bomb1.wav");
	m_walkS.Init(L"Assets/sound/walkS.wav");
	m_giveDamageS.Init(L"Assets/sound/damageS.wav");
	//プレイヤーのインスタンスを探す。
	m_player = g_goMgr.FindGameObject<Player>(player);
}


IEnemyObject::~IEnemyObject()
{
}
void IEnemyObject::ReceiveDamage(CVector3* position)
{
	//ダメージを受けたら、一定時間怯む。
	m_receiveDamageFlug = false;
	m_animationFlug = enAnimationCrip_hirumu;
	m_receiveDamageS.Stop();
	m_receiveDamageS.Play(false);
	//再生中のエフェクトを止める。
	auto effMgr = g_goMgr.GetEffekseerManager();
	//effMgr->StopEffect(m_playEffectHandle);
	//再生。
	CVector3 effectPos = *position;
	effectPos.y = m_bulletPos.y;
	m_effectVec.Normalize();
	effectPos += m_effectVec;
	m_playEffectHandle = effMgr->Play(
		m_sampleEffect,
		0.0f,
		0.0f,
		0.0f
	);
	//カメラの回転行列を求める。
	CMatrix mCameraRot;
	//カメラ行列の逆行列はカメラのワールド行列。
	mCameraRot.Inverse(g_camera3D.GetViewMatrix());
	
	mCameraRot.m[3][0] = effectPos.x;
	mCameraRot.m[3][1] = effectPos.y;
	mCameraRot.m[3][2] = effectPos.z;

	Effekseer::Matrix43 effMat;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 3; y++) {
			effMat.Value[x][y] = mCameraRot.m[x][y];
		}
	}

	effMgr->SetBaseMatrix(m_playEffectHandle, effMat);
	effMgr->SetScale(m_playEffectHandle, 2.0f, 2.0f, 2.0f);
	m_moveSpeed = CVector3::Zero();
}
void IEnemyObject::Tracking()
{
	//走るアニメーション。
	m_animationFlug = enAnimationCrip_run;
	//ターゲットをプレイヤーにする。
	m_targetPos = m_player->GetPosition();
}
void IEnemyObject::PushAway()
{
	//プレイヤーから敵に向かって伸びるベクトルを求める。
		CVector3 toEenmyVec = m_toPlayerVec * -1.0f;
		toEenmyVec.Normalize();
		//m_moveSpeedに、正規化したm_toPlayerVec×突き放されるスピードを入れる。
		m_moveSpeed = toEenmyVec * m_pushAwaySpeed;
		//突き放されるスピードを徐々に減速させていく。
		m_pushAwaySpeed -= 10.0f;
		if (m_pushAwaySpeed <= 0.0f) {
			//Enemyが突き放し終えた。
			//m_pushAwaySpeedをリセット。
			m_pushAwaySpeed = 100.0f;
			m_player->SetPushAwayFlug(false);
			m_endPushAwayflug = false;
		}
}
void IEnemyObject::Death(CVector3* pos, int* time)
{
	//移動しないようにする。
	m_moveSpeed = CVector3::Zero();
	//ターゲットは死亡する直前に固定する。
	m_targetPos = m_lockTargetPos;
	//タイマーを加算。
	m_deathAnimtimer++;
	//死亡アニメーション。
	m_animationFlug = enAnimationCrip_death;
	if (m_deathAnimtimer >= *time) {
		//タイマーが一定時間になった。
		//Gameのインスタンスを探す。
		m_game = g_goMgr.FindGameObject<Game>(game);
		//倒す敵の残りの数を減らす。
		int num = m_game->GetKnockDownEnemyNum();
		m_game->SetKnockDownEnemyNum(--num);
		//アイテムを出現させる。。
		m_itemObj = g_goMgr.NewGameObject<ItemObject>(itemobject);
		//アイテムの座標を設定する。
		CVector3 Ipos = *pos;
		//Y方向に少しプラスして、地面に埋まらないようにする。
		Ipos.y = 100.0f;
		m_itemObj->SetPosition(Ipos);
		//敵のインスタンスを削除する。
		g_goMgr.DeleteGameObject(this);
	}
}

void IEnemyObject::EnemyUpdate(CVector3* position, CVector3* initPos, CQuaternion* rotation, CharacterController& charaCon, int* deathTime, float* AttackPow, float* speed)
{
	//EnemyからPlayerへ向かうベクトル。
	m_toPlayerVec = m_player->GetPosition() - *position;
	float len = m_toPlayerVec.Length();
	if (len <= TRACKING_DISTANCE) {
		//プレイヤーとの距離が750以内になった。
		if (m_toPlayerVec.Length() <= ATTACK_DISTANCE) {
			//プレイヤーとの距離が70以内になった。
			//攻撃をする。
			m_state = ENEMY_ATTACK;
			if (m_player->GetPushAwayFlug() != false) {
				//プレイヤーに突き飛ばされた。
				m_endPushAwayflug = true;
			}
		}
		else {
			//追跡をする。
			m_state = ENEMY_TRACKING;
		}
	}
	else {
		//留まる。
		m_state = ENEMY_STAY;
	}
	if (m_endPushAwayflug != false) {
		//Enemyを突き放した。
		m_state = ENEMY_PUSH_AWAY;
	}
	if (m_death != false) {
		m_state = ENEMY_DEATH;
		if (m_lockTargetPosFlug != true) {
			//ターゲットの座標を固定する。
			m_lockTargetPos = m_targetPos;
			m_lockTargetPosFlug = false;
		}
	}
	//敵の座標からターゲットに向かって伸びるベクトルを求める。
	m_toTargetVec = m_targetPos - *position;
	//Yの要素を0にする。
	m_toTargetVec.y = 0.0f;
	//正規化。
	m_toTargetVec.Normalize();
	//ムーブスピードを設定する。
	m_moveSpeed = m_toTargetVec * *speed;
	//敵の向く方向を設定する。
	float rot = atan2(m_toTargetVec.x, m_toTargetVec.z);
	rotation->SetRotation(CVector3::AxisY(), rot);
	rotation->Multiply(m_targetPos);
	
	if (m_receiveDamageFlug != false) {
		//ダメージを受ける。
		ReceiveDamage(position);
	}
	if (m_state == ENEMY_STAY) {
		//待機。
		Saty(position, initPos);
	}
	else if (m_state == ENEMY_TRACKING) {
		//追跡。
		Tracking();
	}
	else if (m_state == ENEMY_ATTACK) {
		//攻撃。
		Attack(*AttackPow);
	}
	else if (m_state == ENEMY_PUSH_AWAY) {
		//突き飛ばされた。
		PushAway();
	}
	else if (m_state == ENEMY_DEATH){
		//死亡。
		Death(position, deathTime);
	}
	
	if (m_animationFlug == enAnimationCrip_run) {
		m_walkS.Play(false);
		CVector3 toPlV = m_toPlayerVec;
		//追跡を開始する距離を10としたとき、追跡している今の距離を求める。
		//また、求めた値を10で割る。（1以下の値にするため）
		float len = ((10 * toPlV.Length()) / TRACKING_DISTANCE) / 10.0f;
		float volnme = 1.0f - len;
		m_walkS.SetVolume(powf(volnme, 1.5f));
	}
	else {
		//音を止める。
		m_walkS.Stop();
	}
	//重力を受ける。
	m_moveSpeed.y -= 10.0f;
	//敵の座標を設定。
	*position = charaCon.Execute(1.0f,0, m_moveSpeed);
}