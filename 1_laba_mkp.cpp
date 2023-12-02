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

	//��������������� ������:

	double epsilon = 0.00001; 

	//��������� �������:

	//����� ������� ������� ��� ������ ����� - 1 ��� 32 ������ � 53 �������. ��������� � �������:
	//5573 ���. 
	double T = 5573.0; //������ ��������� ���
	double Rp = 415.0 + 6371.0; //������-������ �� ���������� ���: ������� + ������ �����
	double Ra = 422.0 + 6371.0; //������-������ �� ��������� ���: ������ + ������ ����� 
	double e, n, �, E; //��������������, ������� ������� ��������, ������� �������� � ����. �������� ���
	
	e = (Ra - Rp) / (Ra + Rp); //������ ��������������� ��� 

	n = (2 * M_PI) / T; //������ �������� �������� �������� ��C

	ofstream out; //����� ��� ������
	out.open("values.txt"); //��������� ���� ��� ������

	//���������� � ����:
	out << "t -  arbitrary time, [c]\t";
	out << "M - mean anomaly, [rad]\t";
	out << "E - eccentric anonaly, [rad]\t";
	out << "Theta - true anomaly, [rad]\n";

	double Theta; //�������� ��������

	for (int t = 0; t <= T; t++) { //������ ������� �������� � ����������� �� t (0 <= t <= T) ��� ��� = 0
		� = n * t;
		E = FixedPointIterations(e, �, epsilon);
		Theta = 2 * atan(sqrt(((1 + e) / 1 - e)) * tan(E / 2));

		if (Theta < 0) { //� ������, ���� ���. �������� ������ 0, ���������� ������, ������ ��� ��.
			Theta += 2 * M_PI;
		}

		//��������� � ����:
		out << t << "\t";
		out << � << "\t";
		out << E << "\t";
		out << Theta << "\n";
	}

	out.close(); //��������� ����

	return 0;
}

//����� ��������
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

//����� ����������� �������
double BisectionMethod(double e, double M, double epsilon) {

	double a = M - 3; //��������� ������� �������
	double b = M + 3; //��������� ������� ������� 

	double c; //��� ������������� �������, ����������� ������� 

	if ((a - e * sin(a) - M) * (b - e * sin(b) - M) < 0) { //�������� ��� ������� ��������

		for (int i = 0; i <= 100; i++) {

			c = (b + a) / 2;

			if ((abs(c - e * sin(c) - M) < epsilon) || ((abs(b-a)) < 2*epsilon)) { //�������� ����������

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

//����� �������� �������
double GoldenSectionMethod(double e, double M, double epsilon) {

	double a = M - 3; //��������� ������� �������
	double b = M + 3; //��������� ������� ������� 
	double c; //��������� �������� �������
	double k = (sqrt(5) + 1) / 2; //��������� ��� �������� �������

	if ((a - e * sin(a) - M) * (b - e * sin(b) - M) < 0) { //�������� ��� ������� ��������

		for (int i = 0; i <= 100; i++) {

			c = a + (b - a) / k;

			if ((abs(c - e * sin(c) - M) < epsilon) || ((abs(b - a)) < 2 * epsilon)) { //�����c�� ����������

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


//����� �������
double NewtonMethod(double e, double M, double epsilon) {

	double Ek = M;
	double Ek1, fk1, fk, val_Ek, val_Ek1;

	for (int i = 0; i < 100; i++) {

		val_Ek = Ek; //��������� �������� Ek (�.�. ����� ��������)

		if (i == 0) {

			//����������� ��� ������� �������� ��������� ��������������:
			Ek1 = Ek - ((Ek - e * sin(Ek) - M) / (1 - e * cos(Ek)));

		}
		else { //���� �� ������� ��������, ����������� �������������� �������������:

			Ek1 = Ek - ((Ek - e * sin(Ek) - M) / ((fk1 - fk) / (Ek1 - val_Ek)));

		}

		if (abs(Ek1 - Ek) < epsilon) { //�������� ����������

			return Ek1;

		}

		fk = (Ek - e * sin(Ek) - M); //��� ���������� �����������
		fk1 = Ek1 - e * sin(Ek1) - M; //��� ���������� �����������
		val_Ek = Ek;
		Ek = Ek1;

	}

	return 0;

}