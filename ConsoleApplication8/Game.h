#include <SFML/Graphics.hpp>
#include "Checkers_on_board.h"
using namespace sf;

class Game {
public:
	Checkers_on_board& get_checkers_on_board() { // шашки на доске
		return this->checkers_on_board;
	}
	void mouse_pos(RenderWindow& window) {  // позиция курсора
		this->pos_of_mouse = Mouse::getPosition(window);
	}
	Vector2i centre_on_square() { // определение центра клетки при наведении курсора
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (pos_of_mouse.x < i * 80 + 160 && pos_of_mouse.x < (i + 1) * 80 + 160 &&
					pos_of_mouse.y < j * 80 + 160 && pos_of_mouse.y < (j + 1) * 80 + 160) {
					return Vector2i(i * 80 + 87, j * 80 + 87);
				}
			}
		}
	}
private:
	bool move_color = 0; 
	bool selection = 0; 
	int checker_num; 
	float x; 
	float y; 
	Vector2i pos_of_mouse; 
	Checkers_on_board checkers_on_board;
	vector <int> eat_checkers; \
};
