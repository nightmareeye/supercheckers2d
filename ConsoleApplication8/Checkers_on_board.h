#include <SFML/Graphics.hpp>
#include <vector>
#include "Checker.h"
#include "Board.h"
using namespace sf;

class Checkers_on_board {
public:
	Board& get_board() {
		return this->board;
	}

	Checker& get_checker(int i) { 
		return this->checkers[i];
	}

	int get_size() { 
		return this->checkers.size();
	}
	void delete_checker() { 
		checkers.pop_back();
	}

	Checkers_on_board() {
		start_game(); 
	};

	void draw_checkers(RenderWindow& window) { 
		board.draw_board(window); 
		for (int i = 0; i < checkers.size(); i++) {
			checkers[i].draw_checker(window); 
		}
	}
	void delete_backlight() { 
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				this->board.get_all_squares(i, j).off_fon_active();
			}
		}
	}
private:
	vector <Checker> checkers;
	Board board;
};