#include <SFML/Graphics.hpp>
using namespace sf;

class Checker {
public:
	CircleShape& get_checker() { // передает шашку
		return this->checker;
	}
	Vector2f check_position() { // передает позицию
		return this->checker.getPosition();
	}
	float get_x() {  // передает х
		return (this->check_position().x - 87) / 80;
	}
	float get_y() {  // передает у
		return (this->check_position().y - 87) / 80;
	}
	bool get_color() { // передает цвет шашки 
		return this->checker_color;
	}
	bool check_select() {  // передает выбрана ли шашка
		return this->choice;
	}
	bool check_superior() { // передает дамка ли шашка
		return this->superior;
	}

	void make_superior() {  // делает дамкой шашку
		this->superior = 1;
	}
	void set_position(float x_position, float y_position) { // задает координаты х, у шашке
		this->checker.setPosition(x_position, y_position);
	}
	void set_color(Color color) { //задает цвет шашке
		this->checker.setFillColor(color);
	}
	void select_checker() {// выбор шашки
		this->choice = 1;
	}
	void unselect() {// отмена выбора шашки
		this->choice = 0;
	}

	Checker(float x_position, float y_position, bool color) {
		this->checker.setOutlineThickness(3);
		this->checker.setOutlineColor(Color(0, 0, 0));
		this->checker_color = color;
		if (color == 0) {		// белая шашка	
			this->set_color(Color(159, 133, 103));
		}
		else if (color == 1) {		// черная шашка	
			this->set_color(Color(37, 25, 13));
		}
		this->set_position(x_position, y_position); // устанавливаем позицию шашке
		this->choice = 0; // шашка не выбрана
	}
	void draw_checker(RenderWindow& window) {  // рисуем шашку
		window.draw(this->checker);
		if (superior == 1) { // если дамка
			this->checker_texture.loadFromFile("Images//Queen.png"); // выбираем картинку для текстурки
			this->sprite.setTexture(checker_texture); // текстурка
			this->sprite.setTextureRect(IntRect(-22, -22, 45, 45));// позиция текстурки
			this->sprite.setPosition(this->check_position().x, this->check_position().y);// передаем положение шашки
		}
		window.draw(this->sprite);
	}
private:
	CircleShape checker = CircleShape(35);// радиус шашки
	bool checker_color;// 0 = белые, 1 = черные
	bool choice = 0;// 1 если выбрана, 0 если нет
	bool superior = 0;// 1 если шашка дамка, 0 если нет
	Texture checker_texture;// текстура значка дамки
	Sprite sprite;// спрайт значка дамки
};