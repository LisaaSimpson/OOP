#include <iostream>

class Rectangle {
private:
	int square;
protected:
	int coordX;
	int coordY;
public:

	Rectangle() {
		printf("Вызвался конструктор по умолчанию класса Rectangle\n");
		coordX = 1;
		coordY = 1;
	}

	Rectangle(int coordX, int coordY) {
		printf("Вызвался конструктор с параметрами класса Rectangle\n");
		this->coordX = coordX;
		this->coordY = coordY;
	}

	Rectangle(Rectangle &rtg) {
		printf("Вызвался конструктор копирования класса Rectangle\n");
		coordX = rtg.coordX;
		coordY = rtg.coordY;
	}

	int FindRectangle() {
		square = coordX * coordY;
		return square;
	}

	void ResetRectangle();

	~Rectangle() {
		printf("Вызвался деструктор класса Rectangle\n");
		printf("Стороны прямоугольника = %d %d\n\n", coordX, coordY);
	}
};

void Rectangle::ResetRectangle() {
	coordX = 1;
	coordY = 1;
}

class Parallelepiped : public Rectangle {
protected:
	int coordZ;
public:

	Parallelepiped() : Rectangle() {
		printf("Вызвался конструктор по умолчанию класса Parallelepiped\n");
		coordZ = 1;
	}

	Parallelepiped(int coordX, int coordY, int CoordZ) : Rectangle(coordX, coordY) {
		printf("Вызвался конструктор с параметрами класса Parallelepiped\n");
		this->coordZ = CoordZ;
	}

	Parallelepiped(Parallelepiped& parallelepiped) {
		printf("Вызвался конструктор копирования класса Parallelepiped\n");
		coordZ = parallelepiped.coordZ;
		coordX = parallelepiped.coordX;
		coordY = parallelepiped.coordY;
	}

	int FindParallelepiped() {
		return FindRectangle() * coordZ;
	}

	~Parallelepiped() {
		printf("Вызвался деструктор класса Parallelepiped\n");
		printf("Стороны параллелепипеда = %d %d %d\n\n", coordX, coordY, coordZ);
	}
};

int main()
{
	setlocale(LC_ALL, "rus");

	//создание статических объектов
	Rectangle rtg1;
	Rectangle rtg2(2, 4);
	Rectangle rtg3(rtg2);

	//создание динамических объектов
	Rectangle* rtg4 = new Rectangle();
	Rectangle* rtg5 = new Rectangle(4, 7);
	Rectangle* rtg6 = new Rectangle(*rtg4);

	printf("---------------------------\n");

	//вызов методов объекта
	rtg5->ResetRectangle();
	printf("\nПлощадь прямоугольника 5 = %d\n", rtg5->FindRectangle());

	printf("---------------------------\n");

	//вызов объекта класса наследника
	Parallelepiped* prl1 = new Parallelepiped(6, 4, 5);

	delete prl1;

	printf("---------------------------\n"); 
	
	//вызов объекта класса наследника с переменной-указателем типа предка
	Rectangle* figure = new Parallelepiped(6, 4, 5);

	delete figure;

	printf("---------------------------\n");

	delete rtg4;
	delete rtg5;
	delete rtg6;

	printf("---------------------------\n");
}