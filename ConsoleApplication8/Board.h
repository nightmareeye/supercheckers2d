#include <SFML/Graphics.hpp>
#include "Square.h"
#include <iostream>
using namespace sf; 
using namespace std; 

class Board {
private:
public:
	Square& get_all_squares(int i, int j) { // получение €чейки с номером i, j
		return this->all_squares[i][j];
	}
	Square all_squares[8][8]; //количество €чеек
};