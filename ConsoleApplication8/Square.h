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
private:
	bool fon_active = 0; // 1 ��������� ����, 0 = ��� ��������� 
};
