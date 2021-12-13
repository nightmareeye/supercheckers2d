#include <SFML/Graphics.hpp>
using namespace sf;

class Square {
private:
	bool fon_active = 0; // 1 подцветки есть, 0 = нет подцветки  
	bool free = 0; // 1 = заняте клетки, 0 = свободные клетки
	bool checker_color; // 1 = черные шашки, 0 = белые шашки
	RectangleShape cell = RectangleShape(Vector2f(80, 80)); // клетка размером 80х80
};
};
