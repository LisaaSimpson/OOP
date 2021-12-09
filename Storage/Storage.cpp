#include <iostream>
#include <ctime>

using namespace std;

//базовый класс
class Object {
public:
	virtual void ShowName() {
		printf("Object\n");
	}
};

class Rectangle : public Object {
protected:
	int a;
	int b;
public:

	Rectangle() {
		a = 1;
		b = 1;
	}

	Rectangle(int a, int b) {
		this->a = a;
		this->b = b;
	}

	void ShowName() {
		printf("Rectangle\n");
	}
};

class Triangle : public Object {
protected:
	int a;
	int b;
	int c;
public:
	Triangle() {
		a = 1;
		b = 1;
		c = 1;
	}
	Triangle(int a, int b, int c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}

	void ShowName() {
		printf("Triangle\n");
	}
};

class Cat : public Object {
protected:
	string sound;
	int color;
public:
	Cat() {
		sound = "Meow";
		color = 1;
	}

	Cat(string sound, int color) {
		this->sound = sound;
		this->color = color;
	}

	void ShowName() {
		printf("Cat\n");
	}
};

class Storage {
private:
	int size;
	Object** storage; //массив указателей
public:
	Storage() {
		size = 0;
	}

	Storage(int size) {
		this->size = size;
		storage = new Object*[size];
	}

	void SetObject(int i, Object* newObject) {
		storage[i] = newObject;
	}

	Object& GetObject(int i) {
		return *storage[i];
	}

	int GetCount() {
		return size;
	}

	void DeleteObject(int i) {
		storage[i] = nullptr;
	}

	void DestroyObject(int i) {
		if (size != 0) {
			DeleteObject(i);
			delete storage[i];
		}
	}

	bool HaveObject(int i) {
		if (storage[i] != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	~Storage() {
		for (int i = 0; i < size; i++) {
			delete storage[i];
		}
		delete[] storage;
	}
};

void Cycle(Storage& storage, int max) {
	unsigned int firstTime = clock();
	srand(time(NULL));
	printf("\n\n");
	for (int j = 0; j < max; j++) {
		int method = rand() % 4;
		int object;

		if (storage.GetCount() != 0) {
			object = rand() % storage.GetCount();
		}

		int numberOfClass = rand() % 3;
		switch (method) {
		case 0:
			if (numberOfClass == 0) {
				storage.SetObject(object, new Rectangle);
			}
			if (numberOfClass == 1) {
				storage.SetObject(object, new Triangle);
			}
			if (numberOfClass == 2) {
				storage.SetObject(object, new Cat);
			}
			printf("SetObject\n");
			break;
		case 1:
			storage.DeleteObject(object);
			printf("DeleteObject\n");
			break;
		case 2:
			storage.DestroyObject(object);
			printf("DestroyObject\n");
			break;
		case 3:
			if(storage.HaveObject(object))
				storage.GetObject(object).ShowName();
			else {
				printf("Нет объекта для вызова его метода\n");
			}
			break;
		}
	}
	unsigned int secondTime = clock();
	unsigned int time = secondTime - firstTime;
	printf("\nВремя работы: %d миллисекунд\n", time);
	printf("Количество объектов: %d\n", storage.GetCount());
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	Storage storage(10);
	for (int i = 0; i < storage.GetCount(); i++) {
		int randomClass = rand() % 3;
		if (randomClass == 0) {
			storage.SetObject(i, new Rectangle());
		}
		if (randomClass == 1) {
			storage.SetObject(i, new Triangle());
		}
		if (randomClass == 2) {
			storage.SetObject(i, new Cat());
		}
	}

	Cycle(storage, 100);
	printf("\n\n");
	system("pause");
	Cycle(storage, 1000);
	printf("\n\n");
	system("pause");
	Cycle(storage, 10000);
}
