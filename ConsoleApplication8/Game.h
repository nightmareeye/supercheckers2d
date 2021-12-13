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
	void choise_of_checker(RenderWindow& window, Event event) { // выбор шашки
		if (event.type == Event::MouseButtonPressed) {
			if (event.key.code == Mouse::Left) {
				mouse_pos(window);
				if (event.type == Event::MouseButtonPressed) {  // для отмены взятия фигуры
					if (event.key.code == Mouse::Left) {
						if (checkers_on_board.get_checker(checker_num).check_select() == 1 && selection == 1) {  // шашка выбрана
							checkers_on_board.get_checker(checker_num).unselect();  // отмена выбора шашки
							selection = 0;
							checkers_on_board.delete_backlight();  // убрать подцветку
							return;
						}
					}
				}
				for (int i = 0; i < checkers_on_board.get_size(); i++) {
					if (this->pos_of_mouse.x >= checkers_on_board.get_checker(i).check_position().x - 7 && // проверка позиции курсора на шашке
						this->pos_of_mouse.x <= checkers_on_board.get_checker(i).check_position().x + 73 &&
						this->pos_of_mouse.y >= checkers_on_board.get_checker(i).check_position().y - 7 &&
						this->pos_of_mouse.y <= checkers_on_board.get_checker(i).check_position().y + 73) {
						if (checkers_on_board.get_checker(i).check_select() == 0 && selection == 0) { // если шашка не выбрана
							if (checkers_on_board.get_checker(i).get_color() == move_color) { // определение очереди хода
								if (if_you_can_eat_you_must_eat(checkers_on_board.get_checker(i).get_color())) {  // проверка возможности рубить
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
								if (checkers_on_board.get_checker(checker_num).check_superior()) { // проверка на дамку
									queen_square_for_move(checkers_on_board.get_checker(checker_num).get_color(), 1, 1, 1, 1);
								}
								else {
									square_for_move();// клетка для хода
								}
								return;
							}
						}
					}
				}
			}
		}
	}
	void hod(RenderWindow& window, Event event) { // ход шашки 
		if (event.type == Event::MouseButtonPressed) {
			if (event.key.code == Mouse::Right) {
				if (checkers_on_board.get_checker(checker_num).check_select() == 1 && selection == 1) { // если шашка выбрана
					mouse_pos(window);
					if (checkers_on_board.get_board().get_all_squares((centre_on_square().x - 87) / 80, (centre_on_square().y - 87) / 80).get_fon_active()) {
						checkers_on_board.get_board().get_all_squares(x, y).cell_free_0();
						if (checkers_on_board.get_checker(checker_num).check_superior() == 1) { // если шашка дамка
							checkers_on_board.get_checker(checker_num).set_position(centre_on_square().x, centre_on_square().y);
							if (queen_eat_checker()) {
								x = (centre_on_square().x - 87) / 80;
								y = (centre_on_square().y - 87) / 80;
								checkers_on_board.delete_backlight();
								if (queen_square_for_move(checkers_on_board.get_checker(checker_num).get_color(), 1, 1, 1, 1)) {
									return;
								}
							}
						}
						else {
							checkers_on_board.get_checker(checker_num).set_position(centre_on_square().x, centre_on_square().y);
							make_queen();
							if (eat_checker()) {
								checkers_on_board.delete_backlight();
								x = (centre_on_square().x - 87) / 80;
								y = (centre_on_square().y - 87) / 80;
								if (!chance_eat_checker(checkers_on_board.get_checker(checker_num).get_color())) {
									cout << "loop" << endl;
									return;
								}
							}
						}
						checkers_on_board.get_board().get_all_squares((centre_on_square().x - 87) / 80, (centre_on_square().y - 87) / 80).cell_free_1(checkers_on_board.get_checker(checker_num).get_color());
						move_color = !move_color;
						checkers_on_board.get_checker(checker_num).unselect();
						selection = 0;
						std::cout << "Drop" << endl;
						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								cout << checkers_on_board.get_board().get_all_squares(j, i).get_free();
							}
							cout << endl;
						}
						checkers_on_board.delete_backlight();
						return;
					}
				}
			}
		}
	}
	void make_move(RenderWindow& window, Event event) { // выполнение хода шашки
		choise_of_checker(window, event);
		hod(window, event);
	}
	void square_for_move() { // варианты хода шашки
		if (checkers_on_board.get_checker(checker_num).get_color()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_free() == 0) { // проверка вакантных мест снизу
				if (end_board(x + 1, y + 1)) {
					checkers_on_board.get_board().get_all_squares(x + 1, y + 1).on_fon_active();
				}
			}
			if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_free() == 0) {
				if (end_board(x - 1, y + 1)) {
					checkers_on_board.get_board().get_all_squares(x - 1, y + 1).on_fon_active();
				}
			}
		}
		else { // проверка вакантных мест сверху
			if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_free() == 0) {
				if (end_board(x + 1, y - 1)) {
					checkers_on_board.get_board().get_all_squares(x + 1, y - 1).on_fon_active();
				}
			}
			if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_free() == 0) {
				if (end_board(x - 1, y - 1)) {
					checkers_on_board.get_board().get_all_squares(x - 1, y - 1).on_fon_active();
				}
			}
		}
		if (!chance_eat_checker(checkers_on_board.get_checker(checker_num).get_color())) { // есть ли варианты съесть шашку
			checkers_on_board.delete_backlight();
			chance_eat_checker(checkers_on_board.get_checker(checker_num).get_color());
		}
	}
	bool chance_eat_checker(bool color) {
		bool more = 1;
		if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_free()) { 
			if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != color) {
				if (checkers_on_board.get_board().get_all_squares(x + 2, y + 2).get_free() == 0) {
					if (end_board(x + 2, y + 2)) {
						checkers_on_board.get_board().get_all_squares(x + 2, y + 2).on_fon_active(); 
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_free()) {
			if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != color) {
				if (checkers_on_board.get_board().get_all_squares(x - 2, y + 2).get_free() == 0) {
					if (end_board(x - 2, y + 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y + 2).on_fon_active();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_free()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != color) {
				if (checkers_on_board.get_board().get_all_squares(x + 2, y - 2).get_free() == 0) {
					if (end_board(x + 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x + 2, y - 2).on_fon_active();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_free()) {
			if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != color) {
				if (checkers_on_board.get_board().get_all_squares(x - 2, y - 2).get_free() == 0) {
					if (end_board(x - 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y - 2).on_fon_active();
						more = 0;
					}
				}
			}
		}
		return more;
	}
	bool eat_checker() { // рубление шашки
		if ((centre_on_square().x - 87) / 80 - x == 2 || (centre_on_square().x - 87) / 80 - x == -2 &&
			(centre_on_square().y - 87) / 80 - y == 2 || (centre_on_square().y - 87) / 80 - y == -2) {
			for (int i = 0; i < checkers_on_board.get_size(); i++) {
				if (checkers_on_board.get_checker(i).get_x() == x + (checkers_on_board.get_checker(checker_num).get_x() - x) / 2 &&
					checkers_on_board.get_checker(i).get_y() == y + (checkers_on_board.get_checker(checker_num).get_y() - y) / 2) {
					checkers_on_board.get_board().get_all_squares(checkers_on_board.get_checker(i).get_x(), checkers_on_board.get_checker(i).get_y()).cell_free_0();
					for (int j = i; j < checkers_on_board.get_size() - 1; j++) {
						checkers_on_board.get_checker(j) = checkers_on_board.get_checker(j + 1);
					}
					checkers_on_board.delete_checker();
					if (i < checker_num) {
						checker_num = checker_num - 1;
					}
					return 1;
				}
			}
		}
		return 0;
	}
	void make_queen() { // делаем дамкой
		if (checkers_on_board.get_checker(checker_num).get_color() == 0) { // для белых
			if (checkers_on_board.get_checker(checker_num).get_y() == 0) {
				checkers_on_board.get_checker(checker_num).make_superior();
			}
		}
		if (checkers_on_board.get_checker(checker_num).get_color() == 1) { // для черных
			if (checkers_on_board.get_checker(checker_num).get_y() == 7) {
				checkers_on_board.get_checker(checker_num).make_superior();
			}
		}
	}
	bool queen_square_for_move(bool color, int i1, int i2, int i3, int i4) { // варианты хода дамки
		int must_eat = 0;
		bool can_eat[4] = { i1, i2, i3, i4 };
		checkers_on_board.delete_backlight();
		int x_queen = x;
		int y_queen = y;
		if (can_eat[0]) {
			can_eat[0] = 0;
			while (1) {
				if (end_board(x_queen + 1, y_queen + 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_free() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() == color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() != color) {
							if (end_board(x_queen + 2, y_queen + 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen + 2).get_free() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen + 2).on_fon_active();
									x_queen = x_queen + 2;
									y_queen = y_queen + 2;
									must_eat++;
									can_eat[0] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).on_fon_active();
						x_queen = x_queen + 1;
						y_queen = y_queen + 1;
					}
				}
				else break;
			}
		}
		if (can_eat[1]) {
			can_eat[1] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen - 1, y_queen + 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_free() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() == color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() != color) {
							if (end_board(x_queen - 2, y_queen + 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen + 2).get_free() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen + 2).on_fon_active();
									x_queen = x_queen - 2;
									y_queen = y_queen + 2;
									must_eat++;
									can_eat[1] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).on_fon_active();
						x_queen = x_queen - 1;
						y_queen = y_queen + 1;
					}
				}
				else break;
			}
		}
		if (can_eat[2]) {
			can_eat[2] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen + 1, y_queen - 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_free() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() == color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() != color) {
							if (end_board(x_queen + 2, y_queen - 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen - 2).get_free() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen - 2).on_fon_active();
									x_queen = x_queen + 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[2] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).on_fon_active();
						x_queen = x_queen + 1;
						y_queen = y_queen - 1;
					}
				}
				else break;
			}
		}
		if (can_eat[3]) {
			can_eat[3] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen - 1, y_queen - 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_free() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() == color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() != color) {
							if (end_board(x_queen - 2, y_queen - 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen - 2).get_free() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen - 2).on_fon_active();
									x_queen = x_queen - 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[3] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).on_fon_active();
						x_queen = x_queen - 1;
						y_queen = y_queen - 1;
					}
				}
				else break;
			}
		}
		if (must_eat == 0) {
			return 0;
		}
		else {
			if (i1 == 1 && i2 == 1 && i3 == 1 && i4 == 1) {
				queen_square_for_move(color, can_eat[0], can_eat[1], can_eat[2], can_eat[3]);
			}
			else return 1;
		}
	}
	bool queen_eat_checker() { // дамка рубит шашку
		int x_eat = 0;
		int y_eat = 0;
		if ((centre_on_square().x - 87) / 80 - x >= 2 && (centre_on_square().y - 87) / 80 - y >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 87) / 80 - 1 && j < (centre_on_square().y - 87) / 80 - 1) {
					if (checkers_on_board.get_board().get_all_squares(i + 1, j + 1).get_free() == 1) {
						x_eat = i + 1;
						y_eat = j + 1;
						break;
					}
					else {
						i++;
						j++;
					}
				}
				else break;
			}
		}
		if ((centre_on_square().x - 87) / 80 - x >= 2 && y - (centre_on_square().y - 87) / 80 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 87) / 80 - 1 && j >(centre_on_square().y - 87) / 80 + 1) {
					if (checkers_on_board.get_board().get_all_squares(i + 1, j - 1).get_free() == 1) {
						x_eat = i + 1;
						y_eat = j - 1;
						break;
					}
					else {
						i++;
						j--;
					}
				}
				else break;
			}
		}
		if (x - (centre_on_square().x - 87) / 80 >= 2 && (centre_on_square().y - 87) - y / 80 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 87) / 80 + 1 && j < (centre_on_square().y - 87) / 80 - 1) {
					if (checkers_on_board.get_board().get_all_squares(i - 1, j + 1).get_free() == 1) {
						x_eat = i - 1;
						y_eat = j + 1;
						break;
					}
					else {
						i--;
						j++;
					}
				}
				else break;
			}
		}
		if (x - (centre_on_square().x - 87) / 80 >= 2 && y - (centre_on_square().y - 87) / 80 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 87) / 80 + 1 && j > (centre_on_square().y - 87) / 80 + 1) {
					if (checkers_on_board.get_board().get_all_squares(i - 1, j - 1).get_free() == 1) {
						x_eat = i - 1;
						y_eat = j - 1;
						break;
					}
					else {
						i--;
						j--;
					}
				}
				else break;
			}
		}

		for (int f = 0; f < checkers_on_board.get_size(); f++) {
			if (checkers_on_board.get_checker(f).get_x() == x_eat && checkers_on_board.get_checker(f).get_y() == y_eat) {
				checkers_on_board.get_board().get_all_squares(checkers_on_board.get_checker(f).get_x(), checkers_on_board.get_checker(f).get_y()).cell_free_0();

				for (int c = f; c < checkers_on_board.get_size() - 1; c++) {
					checkers_on_board.get_checker(c) = checkers_on_board.get_checker(c + 1);
				}
				checkers_on_board.delete_checker();
				if (f < checker_num) {
					checker_num = checker_num - 1;
				}
				return 1;
			}
		}
		return 0;
	}
	bool end_board(float x, float y) { // проверка выходы за пределы поля
		if (x >= 0 && x < 8 && y >= 0 && y < 8) {
			return 1;
		}
		return 0;
	}
	bool if_you_can_eat_you_must_eat(bool color) {
		while (eat_checkers.size() != 0) {
			eat_checkers.pop_back();
		}
		for (int i = 0; i < checkers_on_board.get_size(); i++) {
			if (checkers_on_board.get_checker(i).get_color() == color) {
				if (checkers_on_board.get_checker(i).check_superior() == 0) {  // проверка на дамку
					x = checkers_on_board.get_checker(i).get_x();
					y = checkers_on_board.get_checker(i).get_y();
					if (!chance_eat_checker(color)) {
						eat_checkers.push_back(i);
					}
				}
				if (checkers_on_board.get_checker(i).check_superior() == 1) { // проверка на дамку
					x = checkers_on_board.get_checker(i).get_x();
					y = checkers_on_board.get_checker(i).get_y();
					if (queen_square_for_move(color, 1, 1, 1, 1)) {
						eat_checkers.push_back(i);
					}
				}
			}
		}
		checkers_on_board.delete_backlight();
		if (eat_checkers.size() != 0) return 1;
		else return 0;
	}
private:
	bool move_color = 0; // 0 - ход белых, 1 - ход черных
	bool selection = 0; // 0 - фигуры не выбрана, 1 - выбрана
	int checker_num; // номер выбранной для хода шашки
	float x; // номер клетки в которой шашка по оси х
	float y; // номер клетки в которой шашка по оси у
	Vector2i pos_of_mouse; // позиция мыши
	Checkers_on_board checkers_on_board;
	vector <int> eat_checkers; // шашки, которые могут съесть
};
