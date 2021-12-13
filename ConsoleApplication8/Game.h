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
	void choise_of_checker(RenderWindow& window, Event event) { 
		if (event.type == Event::MouseButtonPressed) {
			if (event.key.code == Mouse::Left) {
				mouse_pos(window);
				if (event.type == Event::MouseButtonPressed) { 
					if (event.key.code == Mouse::Left) {
						if (checkers_on_board.get_checker(checker_num).check_select() == 1 && selection == 1) { 
							checkers_on_board.get_checker(checker_num).unselect(); 
							selection = 0;
							checkers_on_board.delete_backlight(); 
							return;
						}
					}
				}
				for (int i = 0; i < checkers_on_board.get_size(); i++) {
					if (this->pos_of_mouse.x >= checkers_on_board.get_checker(i).check_position().x - 7 &&
						this->pos_of_mouse.x <= checkers_on_board.get_checker(i).check_position().x + 73 &&
						this->pos_of_mouse.y >= checkers_on_board.get_checker(i).check_position().y - 7 &&
						this->pos_of_mouse.y <= checkers_on_board.get_checker(i).check_position().y + 73) {
						if (checkers_on_board.get_checker(i).check_select() == 0 && selection == 0) { 
							if (checkers_on_board.get_checker(i).get_color() == move_color) {
								if (if_you_can_eat_you_must_eat(checkers_on_board.get_checker(i).get_color())) {
									int s = 0;
									for (int f : eat_checkers) {
										if (f == i) {
											s++;
										}
									}
									if (s == 0) {
										checkers_on_board.delete_backlight();
										return;
									}
								}
								checker_num = i;
								selection = 1;
								checkers_on_board.get_checker(checker_num).select_checker();
								x = checkers_on_board.get_checker(checker_num).get_x();
								y = checkers_on_board.get_checker(checker_num).get_y();
								if (checkers_on_board.get_checker(checker_num).check_superior()) { 
									queen_square_for_move(checkers_on_board.get_checker(checker_num).get_color(), 1, 1, 1, 1);
								}
								else {
									square_for_move();а
								}
								return;
							}
						}
					}
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
