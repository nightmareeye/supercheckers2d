#include <SFML/Graphics.hpp>
using namespace sf;

class Checker {
public:
	CircleShape& get_checker() { 
		return this->checker;
	}
	Vector2f check_position() { 
		return this->checker.getPosition();
	}
	float get_x() { 
		return (this->check_position().x - 87) / 80;
	}
	float get_y() { 
		return (this->check_position().y - 87) / 80;
	}
	bool get_color() { 
		return this->checker_color;
	}
	bool check_select() { 
		return this->choice;
	}
	bool check_superior() { 
		return this->superior;
	}

	void make_superior() { 
		this->superior = 1;
	}
	void set_position(float x_position, float y_position) { // задает координаты х, у шашке
		this->checker.setPosition(x_position, y_position);
	}
	void set_color(Color color) { 
		this->checker.setFillColor(color);
	}
	void select_checker() {
		this->choice = 1;
	}
	void unselect() {
		this->choice = 0;
	}

	Checker(float x_position, float y_position, bool color) {
		this->checker.setOutlineThickness(3);
		this->checker.setOutlineColor(Color(0, 0, 0));
		this->checker_color = color;
		if (color == 0) {		
			this->set_color(Color(159, 133, 103));
		}
		else if (color == 1) {		
			this->set_color(Color(37, 25, 13));
		}
		this->set_position(x_position, y_position); 
		this->choice = 0; 
	}
private:
	CircleShape checker = CircleShape(35);
	bool checker_color;
	bool choice = 0;
	bool superior = 0;
	Texture checker_texture;
	Sprite sprite;
}