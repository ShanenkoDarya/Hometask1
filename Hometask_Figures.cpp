#include "pch.h"
#include <iostream>
#include <math.h>

using namespace std;

struct Points
{
	int x;
	int y;
};

class Figure
{
private:
	Points* points = nullptr; // обнуляем указатели точек
	int* tops = nullptr; // обнуляем указатели вершин
public:
	Figure() {} //вызов автоконструктора

	Figure(int tops)
	{
		try //определения блока стейтментов. Блок try действует как наблюдател; в поисках исключений, которые были выброшены каким-либо из операторов в этом же блоке try.
		{
			if (tops < 3)
				cout << "Tops count error";
			else
			{
				this->tops = new int(tops);
				points = (Points*)malloc(*this->tops * sizeof(Points)); //выделение памяти под вершины
			}
		}
		catch (const char* msg) // определение блока кода, который обрабатывает исключения определённого типа данных
		{
			cout << msg << endl;
		}
	}

	void SetPoints() // получение наших точек с ввода с клавиатуры
	{
		for (int i = 0; i < *tops; i++)
		{
			cin >> points[i].x >> points[i].y;
		}
	}

	virtual void GetName()
	{
		cout << "Фигура" << endl;
	}

	virtual float GetSquare() // перевод точек для площади
	{
		float* Square = new float(0.0);

		for (int i = 0; i < *tops - 1; i++)
		{
			*Square += 0.5 * abs(points[i].x * points[i + 1].y - points[i + 1].x * points[i].y);
		}
		*Square += 0.5 * abs(points[*tops].x * points[0].y - points[0].x * points[*tops].y);

		return *Square;
	}

	virtual float GetPerimeter() //переводс точек для периметра
	{
		float* Perimeter = new float(0.0);

		for (int i = 0; i < *tops - 1; i++)
		{
			*Perimeter += sqrt(pow(points[i + 1].x - points[i].x, 2) + pow(points[i + 1].y - points[i].y, 2));
		}
		*Perimeter += sqrt(pow(points[*tops - 1].x - points[0].x, 2) + pow(points[*tops - 1].y - points[0].y, 2));

		return *Perimeter;
	}

	~Figure() //вызов деконструктора
	{
		delete tops;
		free(points);
	}
};

class Rectangle : public Figure //прямоугольник, наследует от Figure 
{
protected:
	int* Width = nullptr; //обнуляем ширину
		int* Height = nullptr; // обнуляем высоту
	using  Figure::SetPoints;
public:
	Rectangle(int W, int H) // конструктор прямоугольника
	{
		Width = new int(W);
		Height = new int(H);
	}

	void GetName()
	{
		cout << "Прямоугольник" << endl;
	}

	virtual float GetSquare() //выводим на экран площадь прямоугольника
	{
		return *Width * *Height;
	}

	virtual float GetPerimeter() //выводим на экран периметр прямоугольника
	{
		return 2 * (*Width + *Height);
	}

	~Rectangle() //деконструктор прямоугольника
	{
		delete Width;
		delete Height;
	}
};

class Square : public Rectangle //квадрат, наследует от rectangle
{
	public:
		Square(int side) : Rectangle(side, side) {}

		void GetName()
		{
			cout << "Квадрат" << endl;
		}

		float GetSquare()
		{
			return pow(*Width, 2); //возвращает значение экспоненты второй степени 
		}

		float GetPerimeter()  //выводим на экран периметр квадрата
		{
			return 4 * *Width;
		}
};

class Circle : public Figure //круг, наследует от Figure
{
private:
	int* Radius = nullptr; //обнуляем указатель радиуса
public:
	Circle(int Radius)
	{
		this->Radius = new int(Radius);
	}

	void GetName()
	{
		cout << "Круг" << endl;
	}

	float GetSquare() //площадь круга
	{
		return 3.14 * pow(*Radius, 2);
	}

	float GetPerimeter() //периметр круга
	{
		return 2 * 3.14 * *Radius;
	}

	~Circle() // деконструктор круга
	{
		delete Radius;
	}
};

class Ellipse : public Figure // эллипс, наследует от Figure
{
private:
	int* a = nullptr; //меньшая полуось
	int* b = nullptr; // большая полуось
public:
	Ellipse(int a, int b)
	{
		this->a = new int(a);
		this->b = new int(b);
	}

	void GetName()
	{
		cout << "Эллипс" << endl;
	}

	float GetSquare() // площадь эллипса
	{
		return 3.14 * *a * *b;
	}

	float GetPerimeter() //перриметр эллипса
	{
		return 2 * 3.14 * sqrt((pow(*a, 2) * pow(*b, 2)) / 2);
	}

	~Ellipse() // деконструктор эллипса
	{
		delete a;
		delete b;
	}
};

int main()
{
	setlocale(LC_ALL, "");
	const int count = 100;
	Figure* figure[count];

	for (int i = 0; i < count; i++)
	{
		if (i % 2 == 0)
			figure[i] = new Rectangle(i, i * 2);
		else 
				if (i % 3 == 0)
				figure[i] = new Square(i);
		else 
					if (i % 5 == 0)
					figure[i] = new Circle(i / 5);
		else
			figure[i] = new Ellipse(i / 2, i);
	}

	for (int i = 0; i < count; i++)
	{
		figure[i]->GetName();
		cout << "Площадь S = " << figure[i]->GetSquare() << endl;
		cout << "Периметр P = " << figure[i]->GetPerimeter() << endl;
		cout << "" << endl;
	}

	for (int i = 0; i < count; i++)
	{
		delete figure[i];
	}

	return 0;
}