#include <SFML/Graphics.hpp>
#include "Checkers_on_board.h"
using namespace sf;

class Game {
public:
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
