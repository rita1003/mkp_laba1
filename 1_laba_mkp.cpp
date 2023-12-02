#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double FixedPointIterations(double e, double M, double epsilon);
double BisectionMethod(double e, double M, double epsilon);
double GoldenSectionMethod(double e, double M, double epsilon);
double NewtonMethod(double e, double M, double epsilon);


int main() {

	//Вспомогательные данные:

	double epsilon = 0.00001; 

	//Начальные условия:

	//Время полного оборота МКС вокруг Земли - 1 час 32 минуты и 53 секунды. Переводим в секунды:
	//5573 сек. 
	double T = 5573.0; //период обращения МКС
	double Rp = 415.0 + 6371.0; //радиус-вектор до перицентра МКС: перигей + радиус Земли
	double Ra = 422.0 + 6371.0; //радиус-вектор до апоцентра МКС: апогей + радиус Земли 
	double e, n, М, E; //эксцентриситет, среднее угловое движение, средняя аномалия и эксц. аномалия МКС
	
	e = (Ra - Rp) / (Ra + Rp); //расчёт эксцентриситета МКС 

	n = (2 * M_PI) / T; //расчёт среднего углового движения МКC

	ofstream out; //поток для записи
	out.open("values.txt"); //открываем файл для записи

	//записываем в файл:
	out << "t -  arbitrary time, [c]\t";
	out << "M - mean anomaly, [rad]\t";
	out << "E - eccentric anonaly, [rad]\t";
	out << "Theta - true anomaly, [rad]\n";

	double Theta; //истинная аномалия

	for (int t = 0; t <= T; t++) { //расчёт средней аномалии в зависимости от t (0 <= t <= T) при тау = 0
		М = n * t;
		E = FixedPointIterations(e, М, epsilon);
		Theta = 2 * atan(sqrt(((1 + e) / 1 - e)) * tan(E / 2));

		if (Theta < 0) { //в случае, если ист. аномалия меньше 0, прибавляем период, равный два Пи.
			Theta += 2 * M_PI;
		}

		//записывем в файл:
		out << t << "\t";
		out << М << "\t";
		out << E << "\t";
		out << Theta << "\n";
	}

	out.close(); //закрываем файл

	return 0;
}

//метод итераций
double FixedPointIterations(double e, double M, double epsilon) {

	double Ek = M;
	double Ek1;

	for (int i = 0; i <= 100; i++) {

		Ek1 = e * sin(Ek) + M;

		if (abs(Ek1 - Ek) < epsilon) {
			return Ek1;
		}
		
		Ek = Ek1;

	}

	return 0;

}

//метод половинного деления
double BisectionMethod(double e, double M, double epsilon) {

	double a = M - 3; //выбранная граница отрезка
	double b = M + 3; //выбранная граница отрезка 

	double c; //для произвольного отрезка, поделенного пополам 

	if ((a - e * sin(a) - M) * (b - e * sin(b) - M) < 0) { //проверка для нулевой итерации

		for (int i = 0; i <= 100; i++) {

			c = (b + a) / 2;

			if ((abs(c - e * sin(c) - M) < epsilon) || ((abs(b-a)) < 2*epsilon)) { //точность вычисления

				return c;

			}

			if ((a - e * sin(a) - M) * (c - e * sin(c) - M) < 0) {

				b = c;
			}
			else {
				a = c;
			}
		}
	}

	return 0;
}

//метод золотого сечения
double GoldenSectionMethod(double e, double M, double epsilon) {

	double a = M - 3; //выбранная граница отрезка
	double b = M + 3; //выбранная граница отрезка 
	double c; //отношение золотого сечения
	double k = (sqrt(5) + 1) / 2; //константа для золотого сечения

	if ((a - e * sin(a) - M) * (b - e * sin(b) - M) < 0) { //проверка для нулевой итерации

		for (int i = 0; i <= 100; i++) {

			c = a + (b - a) / k;

			if ((abs(c - e * sin(c) - M) < epsilon) || ((abs(b - a)) < 2 * epsilon)) { //точноcть вычисления

				return c;

			}

			if ((a - e * sin(a) - M) * (c - e * sin(c) - M) < 0) {

				b = c;

			}
			else {
				
				a = c;

			}

		}

	}

	return 0;
}


//метод Ньютона
double NewtonMethod(double e, double M, double epsilon) {

	double Ek = M;
	double Ek1, fk1, fk, val_Ek, val_Ek1;

	for (int i = 0; i < 100; i++) {

		val_Ek = Ek; //сохранить значение Ek (т.к. потом меняется)

		if (i == 0) {

			//производную для нулевой итерации посчитаем самостоятельно:
			Ek1 = Ek - ((Ek - e * sin(Ek) - M) / (1 - e * cos(Ek)));

		}
		else { //если не нулевая итерация, производная подсчитывается автоматически:

			Ek1 = Ek - ((Ek - e * sin(Ek) - M) / ((fk1 - fk) / (Ek1 - val_Ek)));

		}

		if (abs(Ek1 - Ek) < epsilon) { //точность вычисления

			return Ek1;

		}

		fk = (Ek - e * sin(Ek) - M); //для вычисления производной
		fk1 = Ek1 - e * sin(Ek1) - M; //для вычисления производной
		val_Ek = Ek;
		Ek = Ek1;

	}

	return 0;

}