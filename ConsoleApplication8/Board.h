#include <SFML/Graphics.hpp>
#include "Square.h"
#include <iostream>
using namespace sf; 
using namespace std; 

class Board {
private:
public:
	Square &get_all_squares(int i, int j) { // ��������� ������ � ������� i, j
		return this->all_squares[i][j];
	}
	void draw_board(RenderWindow& window) { // ���������
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				all_squares[i - 1][j - 1].set_position(i * 80.0, j * 80); // ���������� ��������� ������
				if ((i + j) % 2 == 1) all_squares[i - 1][j - 1].set_color(Color(115, 95, 74)); // ���������� �������� ����� ������
				else all_squares[i - 1][j - 1].set_color(Color(51, 37, 22)); // ���������� ������� ����� ������
				window.draw(all_squares[i - 1][j - 1].get_cell()); // ��������� �����
			}
		}
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (all_squares[i - 1][j - 1].get_fon_active() == 1) { // ���� ������ ����������
					RectangleShape square_light(Vector2f(80, 80)); // ���������� �������
					square_light.setPosition(i * 80, j * 80); // ���������� ���������
					all_squares[i - 1][j - 1].set_color(Color(150, 120, 90)); // ��������� �������� ������
				}
				window.draw(all_squares[i - 1][j - 1].get_cell()); // ���������
			}
		}
	}
private:
	Square all_squares[8][8]; //���������� �����
};