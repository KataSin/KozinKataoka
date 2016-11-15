#ifndef NUMBER_TEXTURE_H_
#define NUMBER_TEXTURE_H_

#include<DxLib.h>
#include "../../math/Vector2.h"
#include "../../math/Vector4.h"
#include <string>

class NumberTexture {
public:
	// �R���X�g���N�^
	NumberTexture(int texture, int width, int height);
	// �`��
	void draw(const Vector2& position, int num, int digit, Vector4 color, char fill = '0') const;
	// �`��
	void draw(const Vector2& position, int num, Vector4 color) const;
	// �`��
	void draw(const Vector2& position, const std::string& num, Vector4 color = Vector4(255, 255, 255, 1)) const;

private:
	// �e�N�X�`��
	int	mTextureIndex;
	// ��
	int		mWidth;
	// ����
	int		mHeight;
};

#endif
