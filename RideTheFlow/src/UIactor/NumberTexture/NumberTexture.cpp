#include "NumberTexture.h"
#include <sstream>
#include <iomanip>
#include "../../graphic/Sprite.h"
NumberTexture::NumberTexture(SPRITE_ID texture, int width, int height):
	mTexture(texture),
	mWidth(width),
	mHeight(height)
{
}

void NumberTexture::draw(const Vector2 & position, int num, int digit, Vector4 color, char fill) const
{
	std::stringstream ss;
	ss << std::setw(digit) << std::setfill(fill) << num;
	draw(position, ss.str(), color);
}

void NumberTexture::draw(const Vector2 & position, int num, Vector4 color) const
{
	draw(position, std::to_string(num), color);
}

void NumberTexture::draw(const Vector2 & position, const std::string & num, Vector4 color) const
{
	for (int i = 0; i < (int)num.size(); ++i) {
		if (num[i] == ' ') continue;
		const int n = num[i] - '0';
		const Vector2 pos(position.x + i * mWidth, position.y);
		DrawRectGraph(pos.x, pos.y, n * mWidth, 0.0f, mWidth , mHeight, Sprite::GetInstance().GetIndex(mTexture) , TRUE, FALSE);
	}
}
