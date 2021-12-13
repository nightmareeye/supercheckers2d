#include <SFML/Graphics.hpp>
#include "Checkers_on_board.h"
using namespace sf;

class Game {
public:
	Checkers_on_board& get_checkers_on_board() {
		return this->checkers_on_board;
	}
	void mouse_pos(RenderWindow& window) { à
		this->pos_of_mouse = Mouse::getPosition(window);
	}
	Vector2i centre_on_square() {
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
};
