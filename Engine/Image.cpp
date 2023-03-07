#include "Global.h"
#include "Image.h"
#include "Input.h"

//3D画像を管理する
namespace Image
{
	//ロード済みの画像データ一覧
	std::vector<ImageData*>	_datas;

	//初期化
	void Initialize()
	{
		AllRelease();
	}

	//画像をロード
	int Load(std::string fileName)
	{
		ImageData* pData = new ImageData;

		//開いたファイル一覧から同じファイル名のものが無いか探す
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//すでに開いている場合
			if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
			{
				pData->pSprite = _datas[i]->pSprite;
				isExist = true;
				break;
			}
		}

		//新たにファイルを開く
		if (isExist == false)
		{
			pData->pSprite = new Sprite;
			if (FAILED(pData->pSprite->Load(fileName)))
			{
				//開けなかった
				SAFE_DELETE(pData->pSprite);
				SAFE_DELETE(pData);
				return -1;
			}

			//無事開けた
			pData->fileName = fileName;
		}


		//使ってない番号が無いか探す
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] == nullptr)
			{
				_datas[i] = pData;
				return i;
			}
		}

		//新たに追加
		_datas.push_back(pData);

		//画像番号割り振り
		int handle = (int)_datas.size() - 1;

		//切り抜き範囲をリセット
		ResetRect(handle);

		return handle;
	}



	//描画
	void Draw(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}
		_datas[handle]->transform.Calclation();
		_datas[handle]->pSprite->Draw(_datas[handle]->transform, _datas[handle]->rect, _datas[handle]->color);
	}



	//任意の画像を開放
	void Release(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		//同じモデルを他でも使っていないか
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//すでに開いている場合
			if (_datas[i] != nullptr && i != handle && _datas[i]->pSprite == _datas[handle]->pSprite)
			{
				isExist = true;
				break;
			}
		}

		//使ってなければモデル解放
		if (isExist == false)
		{
			SAFE_DELETE(_datas[handle]->pSprite);
		}

		SAFE_DELETE(_datas[handle]);
	}



	//全ての画像を解放
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			Release(i);
		}
		_datas.clear();
	}


	//切り抜き範囲の設定
	void SetRect(int handle, int x, int y, int width, int height)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		_datas[handle]->rect.left = x;
		_datas[handle]->rect.top = y;
		_datas[handle]->rect.right = width;
		_datas[handle]->rect.bottom = height;
	}


	//切り抜き範囲をリセット（画像全体を表示する）
	void ResetRect(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		XMFLOAT3 size = _datas[handle]->pSprite->GetTextureSize();

		_datas[handle]->rect.left = 0;
		_datas[handle]->rect.top = 0;
		_datas[handle]->rect.right = (long)size.x;
		_datas[handle]->rect.bottom = (long)size.y;

	}

	//アルファ値設定
	void SetAlpha(int handle, int alpha)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}
		_datas[handle]->color.w = (float)alpha / 255.0f;
	}


	//ワールド行列を設定
	void SetTransform(int handle, Transform& transform)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		_datas[handle]->transform = transform;
	}


	//ワールド行列の取得
	XMMATRIX GetMatrix(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return XMMatrixIdentity();
		}
		return _datas[handle]->transform.GetWorldMatrix();
	}

	//色をセット
	void SetColor(int handle, float r, float g, float b)
	{
		_datas[handle]->color.x = r;
		_datas[handle]->color.y = g;
		_datas[handle]->color.z = b;
	}

	//モデルを点滅させる
	void FlashImage(int handle, int frame)
	{
		_datas[handle]->Alpha.FlashImage(frame);
		SetAlpha(handle, _datas[handle]->Alpha.GetAlpha());
	}

	void FlashImage2(int handle, int frame)
	{
		_datas[handle]->Alpha.FlashImage2(frame);
		SetAlpha(handle, _datas[handle]->Alpha.GetAlpha());
	}

	void FadeInImage(int handle, float frame)
	{
		_datas[handle]->Alpha.FadeInImage(frame);
		SetAlpha(handle, _datas[handle]->Alpha.GetAlpha());
	}

	void FadeoutImage(int handle, float frame)
	{
		_datas[handle]->Alpha.FadeOutImage(frame);
		SetAlpha(handle, _datas[handle]->Alpha.GetAlpha());
	}

	int GetTime(int handle)
	{
		return _datas[handle]->Alpha.GetTime();
	}

	bool IsHitCursor(int hPict)
	{
		UINT wid = (UINT)(_datas[hPict]->pSprite->GetTextureSize().x * _datas[hPict]->transform.scale_.x / 2);
		UINT hgt = (UINT)(_datas[hPict]->pSprite->GetTextureSize().y * _datas[hPict]->transform.scale_.y / 2);
		float Left = (_datas[hPict]->transform.position_.x + 1) * (Direct3D::screenWidth_ / 2) - wid;
		float Right = (_datas[hPict]->transform.position_.x + 1) * (Direct3D::screenWidth_ / 2) + wid;
		float Top = (-_datas[hPict]->transform.position_.y + 1) * (Direct3D::screenHeight_ / 2) - hgt;
		float Bottom = (-_datas[hPict]->transform.position_.y + 1) * (Direct3D::screenHeight_ / 2) + hgt;
		if (Left <= Input::GetMousePosition().x && Input::GetMousePosition().x <= Right &&
			Top <= Input::GetMousePosition().y && Input::GetMousePosition().y <= Bottom)
		{
			return true;
		}
		return false;
	}
}

