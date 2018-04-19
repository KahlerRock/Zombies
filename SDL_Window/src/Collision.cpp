#include "Collision.hpp"
#include "ECS\ColliderComponent.hpp"
bool  Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB)
{
	if
	(
		rectA.x + rectA.w > rectB.x &&
		rectB.x + rectB.w > rectA.x &&
		rectA.y + rectA.h > rectB.y &&
		rectB.y + rectB.h > rectA.y
	) return true;

	else return false;
	}


bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB)
{
	if (AABB(colA.collider, colB.collider))
	{
		//std::cout << colrectA.tag << " hit: " << colB.tag << std::endl;
		return true;
	} else return false;
}