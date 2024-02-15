#include "wind.h"
#include "DxLib.h"

Wind::Wind(int type, int image) :image(image), type(type), speed(0.0f),
location(0.0f), box_size(0.0f)
{
}

Wind::~Wind()
{
}

void Wind::Initialize()
{
}

void Wind::Update(float speed)
{
	//ˆÊ’uî•ñ‚ÉˆÚ“®—Ê‚ð‰ÁŽZ‚·‚é
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void Wind::Draw() const
{
	DrawGraphF(location.x, location.y, image, TRUE);
}

void Wind::Finalize()
{
}

Vector2D Wind::GetLocation() const
{
	return location;
}

Vector2D Wind::GetBoxSize() const
{
	return box_size;
}