#include <iostream>

class Rectangle {
private:
	int square;
protected:
	int a;
	int b;
public:

	Rectangle() {
		printf("Вызвался конструктор по умолчанию класса Rectangle\n");
		a = 1;
		b = 1;
	}

	Rectangle(int a, int b) {
		printf("Вызвался конструктор с параметрами класса Rectangle\n");
		this->a = a;
		this->b = b;
	}

	Rectangle(Rectangle &rtg) {
		printf("Вызвался конструктор копирования класса Rectangle\n");
		a = rtg.a;
		b = rtg.b;
	}

	int FindRectangle() {
		square = a * b;
		return square;
	}

	void ResetRectangle();

	~Rectangle() {
		printf("Вызвался деструктор класса Rectangle\n");
		printf("Стороны прямоугольника = %d %d\n\n", a, b);
	}

	virtual void PrintName() {
		printf("\nRectangle\n");
	}
};

void Rectangle::ResetRectangle() {
	a = 1;
	b = 1;
}

class Parallelepiped : public Rectangle {
protected:
	int c;
public:

	Parallelepiped() : Rectangle() {
		printf("Вызвался конструктор по умолчанию класса Parallelepiped\n");
		c = 1;
	}

	Parallelepiped(int a, int b, int c) : Rectangle(a, b) {
		printf("Вызвался конструктор с параметрами класса Parallelepiped\n");
		this->c = c;
	}

	Parallelepiped(Parallelepiped& parallelepiped) {
		printf("Вызвался конструктор копирования класса Parallelepiped\n");
		c = parallelepiped.c;
		a = parallelepiped.a;
		b = parallelepiped.b;
	}

	int FindParallelepiped() {
		return FindRectangle() * c;
	}

	~Parallelepiped() {
		printf("Вызвался деструктор класса Parallelepiped\n");
		printf("Стороны параллелепипеда = %d %d %d\n\n", a, b, c);
	}

	void PrintName() {
		printf("\nParallelepiped\n");
	}
};

class RectangleWork {
protected:
	Rectangle* rtg1;
	Rectangle* rtg2;
public:
	RectangleWork() {
		printf("Вызвался конструктор по умолчанию класса RectangleWork\n");
		rtg1 = new Rectangle;
		rtg2 = new Rectangle;
	}
	RectangleWork(int a1, int b1, int a2, int b2) {
		printf("Вызвался конструктор с параметрами класса RectangleWork\n");
		rtg1 = new Rectangle(a1, b1);
		rtg2 = new Rectangle(a2, b2);
	}
	RectangleWork(RectangleWork& rtgWorker) {
		printf("Вызвался конструктор копирования класса RectangleWork\n");
		rtg1 = new Rectangle(*(rtgWorker.rtg1));
		rtg2 = new Rectangle(*(rtgWorker.rtg2));
	}
	~RectangleWork() {
		printf("Вызвался деструктор класса RectangleWork\n");
		delete rtg1;
		delete rtg2;
	}

	void CompareRectangles() {
		if (rtg1->FindRectangle() > rtg2->FindRectangle()) {
			printf("Первый прямоугольник больше второго\n");
		}
		else if (rtg2->FindRectangle() > rtg1->FindRectangle()) {
			printf("Второй прямоугольник больше первого\n");
		}
		else {
			printf("Прямоугольники равны\n");
		}
	}
};

int main()
{
	setlocale(LC_ALL, "rus");

	//создание статических объектов
	printf("Создание статических объектов\n\n");
	Rectangle rtg1;
	Rectangle rtg2(2, 4);
	Rectangle rtg3(rtg2);

	printf("---------------------------\n");

	//создание динамических объектов
	printf("Создание динамических объектов\n\n");
	Rectangle* rtg4 = new Rectangle();
	Rectangle* rtg5 = new Rectangle(4, 7);
	Rectangle* rtg6 = new Rectangle(*rtg4);

	printf("---------------------------\n");

	//вызов методов объекта
	printf("Вызов методов объекта\n\n");
	rtg5->ResetRectangle();
	printf("Площадь прямоугольника 5 = %d\n", rtg5->FindRectangle());

	printf("---------------------------\n");

	//вызов объекта класса наследника
	printf("Вызов объекта класса наследника\n\n");
	Parallelepiped* prl1 = new Parallelepiped(6, 4, 5);

	delete prl1;

	printf("---------------------------\n"); 
	
	//вызов объекта класса наследника с переменной-указателем типа предка
	printf("Вызов объекта класса наследника с переменной-указателем типа предка\n\n");
	Rectangle* figure = new Parallelepiped(6, 4, 5);
	figure->PrintName();

	delete figure;

	printf("---------------------------\n");
	
	//создание объекта класса с композицией
	printf("Создание объекта класса с композицией\n\n");
	RectangleWork* rtgWorker1 = new RectangleWork;
	RectangleWork* rtgWorker2 = new RectangleWork(*rtgWorker1);

	rtgWorker1->CompareRectangles();

	delete rtgWorker1;
	delete rtgWorker2;

	printf("---------------------------\n");

	printf("Удаление динамических объектов класса\n\n");
	delete rtg4;
	delete rtg5;
	delete rtg6;

	printf("---------------------------\n");
	printf("Удаление статических объектов класса\n\n");
}