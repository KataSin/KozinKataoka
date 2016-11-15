#ifndef NUMBER_TEXTURE_H_
#define NUMBER_TEXTURE_H_

#include<DxLib.h>
#include "../../math/Vector2.h"
#include "../../math/Vector4.h"
#include <string>

class NumberTexture {
public:
	// コンストラクタ
	NumberTexture(int texture, int width, int height);
	// 描画
	void draw(const Vector2& position, int num, int digit, Vector4 color, char fill = '0') const;
	// 描画
	void draw(const Vector2& position, int num, Vector4 color) const;
	// 描画
	void draw(const Vector2& position, const std::string& num, Vector4 color = Vector4(255, 255, 255, 1)) const;

private:
	// テクスチャ
	int	mTextureIndex;
	// 幅
	int		mWidth;
	// 高さ
	int		mHeight;
};

#endif
