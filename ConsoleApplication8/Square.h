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
private:
	bool fon_active = 0; // 1 ��������� ����, 0 = ��� ��������� 
	bool free = 0; // 1 = ������ ������, 0 = ��������� ������
	bool checker_color; // 1 = ������ �����, 0 = ����� �����
};
