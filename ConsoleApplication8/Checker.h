#include <SFML/Graphics.hpp>
using namespace sf;

class Checker {
public:

private:
	CircleShape checker = CircleShape(35);
	bool checker_color;
	bool choice = 0;
	bool superior = 0;
	Texture checker_texture;
	Sprite sprite;
}