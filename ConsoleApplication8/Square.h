#include <SFML/Graphics.hpp>
using namespace sf;

class Square {
private:
	bool fon_active = 0; // 1 ��������� ����, 0 = ��� ���������  
	bool free = 0; // 1 = ������ ������, 0 = ��������� ������
	bool checker_color; // 1 = ������ �����, 0 = ����� �����
	RectangleShape cell = RectangleShape(Vector2f(80, 80)); // ������ �������� 80�80
};
};
