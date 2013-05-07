//*============================================================================
//Particle.h
//*============================================================================
//[history]
//	08/06/07 作成
//[author]
//	Taka
//============================================================================
#pragma once

//=============================================================================
//include
//=============================================================================
#include "c3dobject.h"

//=============================================================================
//define
//=============================================================================
const int PARTS_DIVIDE = 8;
const int BOMB_MAX = 8;
const int PERTICLE_MAX = (PARTS_DIVIDE * PARTS_DIVIDE) * BOMB_MAX;
const int BOMB_ALIVE_TIME = 60;

//=============================================================================
//class
//=============================================================================
//[Desc]
//	パーティクル描画用オブジェクト
//=============================================================================
class CParticle :	public CDraw3DObject
{
	protected:
	
		Selene::Renderer::ITexture *m_pTex;//テクスチャ用ハンドル
		Selene::Renderer::Object::IParticle *m_pParticle;//パーティクル用ハンドル
		Selene::Scene::IParticleActor *m_pActorParticle[S_MAX];//パーティクルアクター
		Renderer::IRender *m_pRender;//レンダラー用デバイス
		
	protected:
	
		Sint32 m_Width;//幅
		Sint32 m_Height;//高さ
		
		Math::Point3D<Uint8> m_Alpha;//アルファ値
	
	public:
	
		CParticle(){};
		CParticle( string name );//コンストラクタ
		CParticle( string name, Math::Vector3D vPos );//コンストラクタ
		~CParticle(void);//デストラクタ
		
		virtual void Load( Renderer::IRender *pRender );//ファイル読み込み
		void CreateActor( int index, Scene::ISceneManager *pSceneMgr );//アクターの生成

		void Init(){};//初期化
		void Exec();//処理
		void Rendering( int index );//レンダリング
		
	/*Set系*/
	public:
	
		/*レンダリングデバイスの設定*/
		void SetRenderDevice( Renderer::IRender *pRender )
		{
			m_pRender = pRender;
			pRender->AddRef();
		}
		
		/*アルファ値の設定*/
		void SetAlpha( Math::Point3D<Uint8> Alpha)
		{
			m_Alpha = Alpha;
		}
		
	/*Get系*/
	public:

		//テクスチャ用ハンドルの取得
		Selene::Renderer::ITexture *GetTexture() const
		{
			return m_pTex;
		}
		
		//パーティクル用ハンドルの取得
		Selene::Renderer::Object::IParticle *GetParticle() const
		{
			return m_pParticle;
		}
		
};
