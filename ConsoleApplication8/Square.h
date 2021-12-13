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
private:
	bool fon_active = 0; // 1 подцветки есть, 0 = нет подцветки 
};
