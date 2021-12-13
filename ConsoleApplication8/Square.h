#include <SFML/Graphics.hpp>
using namespace sf;

class Square {
public:

	RectangleShape& get_cell() { // �������� ������
		return this->cell;
	}
	bool get_fon_active() { // �������� ���� �� ���������
		return this->fon_active;
	}
	bool get_free() { // �������� �� ������
		return this->free;
	}
	bool get_checker_color() { // �������� ���� ������
		return this->checker_color;
	}
	void off_fon_active() { // ������ ���������
		this->fon_active = 0;
	}
	void on_fon_active() { // �������� ���������
		this->fon_active = 1;
	}
private:
	bool fon_active = 0; // 1 ��������� ����, 0 = ��� ��������� 
	bool free = 0; // 1 = ������ ������, 0 = ��������� ������
	bool checker_color; // 1 = ������ �����, 0 = ����� �����
	RectangleShape cell = RectangleShape(Vector2f(80, 80)); // ������ �������� 80�80
};
