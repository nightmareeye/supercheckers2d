#include <SFML/Graphics.hpp>
#include <vector>
#include "Checker.h"
#include "Board.h"
using namespace sf;

class Checkers_on_board {
public:
	Board &get_board() { // передаем доску
		return this->board;
	}

	Checker &get_checker(int i) {  // передаем шашку с номером i
		return this->checkers[i];
	}

	int get_size() {  // число шашек
		return this->checkers.size();
	}

	void start_game() {
		for (int i = 0; i < 24; i++) {  // белые шашки
			if (i < 4) {
				checkers.push_back(Checker((float)i * 160 + 167, (float)87, 1)); // первый ряд
				board.get_all_squares(i * 2 + 1, 0).cell_free_1(1);
			}
			else if (i >= 4 && i < 8) {
				checkers.push_back(Checker((float)(i - 4) * 160 + 87, (float)167, 1));// второй ряд
				board.get_all_squares((i - 4) * 2, 1).cell_free_1(1);
			}
			else if (i >= 8 && i < 12) {
				checkers.push_back(Checker((float)(i - 8) * 160 + 167, (float)247, 1));  // третий ряд
			}

			else if (i >= 12 && i < 16) { // черные шашки
				checkers.push_back(Checker((float)(i - 12) * 160 + 87, (float)487, 0)); // первый ряд 
				board.get_all_squares((i - 12) * 2, 5).cell_free_1(0);
			}
			else if (i >= 16 && i < 20) {
				checkers.push_back(Checker((float)(i - 16) * 160 + 167, (float)567, 0));  // второй ряд
				board.get_all_squares((i - 16) * 2 + 1, 6).cell_free_1(0);
			}
			else if (i >= 20 && i < 24) {
				checkers.push_back(Checker((float)(i - 20) * 160 + 87, (float)647, 0));  // третий ряд
				board.get_all_squares((i - 20) * 2, 7).cell_free_1(0);
			}
		}
	}

	void delete_checker() {  // удаление шашки
		checkers.pop_back();
	}

	Checkers_on_board() {
		start_game(); // стартовая позиция шашек
	};

	void draw_checkers(RenderWindow& window) { // создание поля с фигурами
		board.draw_board(window); // рисую доску
		for (int i = 0; i < checkers.size(); i++) {
			checkers[i].draw_checker(window); // рисую каждую шашку
		}
	}
	void delete_backlight() { // удаляю все подсвеченные клетки
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				this->board.get_all_squares(i, j).off_fon_active();
			}
		}
	}
private:
	vector <Checker> checkers; // светлые шашки
	Board board;
};