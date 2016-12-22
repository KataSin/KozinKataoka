#ifndef NUMBER_TEXTURE_H_
#define NUMBER_TEXTURE_H_

#include<DxLib.h>
#include "../../math/Vector2.h"
#include "../../math/Vector4.h"
#include "../../actor/ID.h"
#include <string>

class NumberTexture {
public:
	// コンストラクタ
	NumberTexture(SPRITE_ID texture, int width, int height);
	// 描画
	//void draw(const Vector2& position, int num, int digit, Vector4 color, float scale = 1, char fill = '0') const;
	// 描画
	void draw(const Vector2& position, int num, Vector4 color, float scale=1) const;
	// 描画
	void draw(const Vector2& position, const std::string& num, Vector4 color = Vector4(255, 255, 255, 1), float scale = 1) const;

private:
	// テクスチャ
	SPRITE_ID	mTexture;
	// 幅
	int		mWidth;
	// 高さ
	int		mHeight;
};

#endif
