#include <SFML/Graphics.hpp>
using namespace sf;

class Square {
public:

	RectangleShape& get_cell() { // передает клетку
		return this->cell;
	}
	bool get_fon_active() { // передает есть ли подцветка
		return this->fon_active;
	}
	bool get_free() { // свободна ли клетку
		return this->free;
	}
	bool get_checker_color() { // передает цвет клетки
		return this->checker_color;
	}
	void off_fon_active() { // убрать подцветку
		this->fon_active = 0;
	}
	void on_fon_active() { // добавить подцветку
		this->fon_active = 1;
	}
private:
	bool fon_active = 0; // 1 подцветки есть, 0 = нет подцветки 
	bool free = 0; // 1 = заняте клетки, 0 = свободные клетки
	bool checker_color; // 1 = черные шашки, 0 = белые шашки
	RectangleShape cell = RectangleShape(Vector2f(80, 80)); // клетка размером 80х80
};
