#include "pch.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <random>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <ctime>
#include <Windows.h>
#include <iomanip>
#include <time.h>
#include <chrono>
#include <cstdlib>


using namespace std;
using namespace std::chrono;
// 9 вариант
double big_num_2 = 3157.75229;


double FunctionValue(double x) {
	return sqrt(x*(3 - x)) / (x + 1);
}
double ErrorRunge(double In, double I2n, double Thetta) {
	return Thetta * abs(In - I2n);
}

//--------------------------------------------------------------------------
//0.137628

double MethodRectangleL(double a, double b) {
	double summ = 0;
	double h = (b - a) / 2000000;
	for (int i = 0; i <= 1999999; i++) {
		summ += FunctionValue(a + h * i) * h;
	}
	return summ;
}
double MethodRectangleL2(double a, double b) {
	double summ = 0;
	double h = (b - a) / 4000000;
	for (int i = 0; i <= 3999999; i++) {
		summ += FunctionValue(a + h * i) * h;
	}
	return summ;
}
double MethodRectangleLParallel(double a, double b) {
	double summ = 0;
	double h = (b - a) / 2000000;
#pragma omp parallel for
	for (int i = 0; i <= 1999999; i++) {
		summ += FunctionValue(a + h * i) * h;
	}
	return summ;
}
void AllRectangleL(double a, double b, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double MetRecLResult = MethodRectangleL(a, b);
	e = chrono::steady_clock::now();

	double MetRecLResult2 = MethodRectangleL(a, b);

	sp = chrono::steady_clock::now();
	double MetRecLResultParallel = MethodRectangleLParallel(a, b);
	ep = chrono::steady_clock::now();

	double ErrRuMetRecL = ErrorRunge(MetRecLResult, MetRecLResult2, Thetta);
	cout << "result" << MetRecLResult << endl;

	cout << "Method RectangleL" << endl;
	cout << "Error Runge = " << ErrRuMetRecL << setprecision(16) << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}

//--------------------------------------------------------------------------
//0.137628

double MethodRectangleR(double a, double b) {
	double summ = 0;
	double h = (b - a) / 2000000;
	for (int i = 1; i <= 2000000; i++) {
		summ += FunctionValue(a + h * i) * h;
	}
	return summ;
}
double MethodRectangleR2(double a, double b) {
	double summ = 0;
	double h = (b - a) / 4000000;
	for (int i = 1; i <= 4000000; i++) {
		summ += FunctionValue(a + h * i) * h;
	}
	return summ;
}
double MethodRectangleRParallel(double a, double b) {
	double summ = 0;
	double h = (b - a) / 2000000;
#pragma omp parallel for
	for (int i = 1; i <= 2000000; i++) {
		summ += FunctionValue(a + h * i) * h;
	}
	return summ;
}
void AllRectangleR(double a, double b, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double MetRecRResult = MethodRectangleR(a, b);
	e = chrono::steady_clock::now();

	double MetRecRResult2 = MethodRectangleR(a, b);

	sp = chrono::steady_clock::now();
	double MetRecRResultParallel = MethodRectangleRParallel(a, b);
	ep = chrono::steady_clock::now();

	double ErrRuMetRecR = ErrorRunge(MetRecRResult, MetRecRResult2, Thetta);

	cout << "Method RectangleR" << endl;
	cout << "Error Runge = " << ErrRuMetRecR << setprecision(16) << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}

//--------------------------------------------------------------------------

double MethodTrapezoid(double a, double b) {
	double summ = 0;
	double h = (b - a) / 2000000;
	for (int i = 0; i <= 2000000; i++) {
		if (i == 0 ^ i == 2000000) {
			summ += (FunctionValue(a + h * i) / 2);
			continue;
		}
		summ += FunctionValue(a + h * i);
	}
	return summ * h;
}
double MethodTrapezoid2(double a, double b) {
	double summ = 0;
	double h = (b - a) / 4000000;
	for (int i = 0; i <= 4000000; i++) {
		if (i == 0 ^ i == 4000000) {
			summ += (FunctionValue(a + h * i) / 2);
			continue;
		}
		summ += FunctionValue(a + h * i);
	}
	return summ * h;
}
double MethodTrapezoidParallel(double a, double b) {
	double summ = 0;
	double h = (b - a) / 2000000;
#pragma omp parallel for
	for (int i = 0; i <= 2000000; i++) {
		if (i == 0 ^ i == 2000000) {
			summ += (FunctionValue(a + h * i) / 2);
			continue;
		}
		summ += FunctionValue(a + h * i);
	}
	return summ * h;
}
void AllTrapezioid(double a, double b, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double MetTrapResult = MethodTrapezoid(a, b);
	e = chrono::steady_clock::now();

	double MetTrapResult2 = MethodTrapezoid2(a, b);

	sp = chrono::steady_clock::now();
	double MetTrapResultParallel = MethodTrapezoidParallel(a, b);
	ep = chrono::steady_clock::now();

	double ErrRuMetTrap = ErrorRunge(MetTrapResult, MetTrapResult2, Thetta);

	cout << "Method Trapezoid" << endl;
	cout << "Error Runge = " << ErrRuMetTrap << setprecision(16) << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}

//--------------------------------------------------------------------------

double MethodQudratureSimpson(double a, double b) {
	double summ = 0;
	summ += FunctionValue(a);
	summ += FunctionValue(b);
	double h = (b - a) / 2000000;
	double chet = 0;
	double nechet = 0;
	for (int i = 0; i < 1000000; i++) {
		nechet += FunctionValue(a + (h * ((2 * i) + 1)));
		if (a + (h * (2 * (i + 1))) == 1.2) {
			break;
		}
		chet += FunctionValue(a + (h * (2 * (i + 1))));
	}
	summ += nechet * 4;
	summ += chet * 2;
	summ *= (h / 3);
	return summ;
}
double MethodQudratureSimpson2(double a, double b) {
	double summ = 0;
	summ += FunctionValue(a);
	summ += FunctionValue(b);
	double h = (b - a) / 4000000;
	double chet = 0;
	double nechet = 0;
	for (int i = 0; i < 2000000; i++) {
		nechet += FunctionValue(a + (h * ((2 * i) + 1)));
		if (a + (h * (2 * (i + 1))) == 1.2) {
			break;
		}
		chet += FunctionValue(a + (h * (2 * (i + 1))));
	}
	summ += nechet * 4;
	summ += chet * 2;
	summ *= (h / 3);
	return summ;
}
double MethodQudratureSimpsonParallel(double a, double b) {
	double summ = 0;
	summ += FunctionValue(a);
	summ += FunctionValue(b);
	double h = (b - a) / 2000000;
	double chet = 0;
	double nechet = 0;
#pragma omp parallel for
	for (int i = 0; i < 1000000; i++) {
		nechet += FunctionValue(a + (h * ((2 * i) + 1)));
		if (a + (h * (2 * (i + 1))) == 1.2) {
			break;
		}
		chet += FunctionValue(a + (h * (2 * (i + 1))));
	}
	summ += nechet * 4;
	summ += chet * 2;
	summ *= (h / 3);
	return summ;
}
void AllSimpson(double a, double b, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double MetQuadSimpResult = MethodQudratureSimpson(a, b);
	e = chrono::steady_clock::now();

	double MetQuadSimpResult2 = MethodQudratureSimpson2(a, b);

	sp = chrono::steady_clock::now();
	double MetQuadSimpResultParallel = MethodQudratureSimpsonParallel(a, b);
	ep = chrono::steady_clock::now();

	double ErrRuMetSimp = ErrorRunge(MetQuadSimpResult, MetQuadSimpResult2, Thetta);

	cout << "Method Quadrature Simpson" << endl;
	cout << "Error Runge = " << ErrRuMetSimp << setprecision(16) << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}

//--------------------------------------------------------------------------
double MethodThreeEight(double a, double b){
	double summ = 0;
	double h = (b - a) / 2000000;
	for (int i = 0; i < 2000000; i++) {
		double localA = a + i * h;
		double localB = a + (i + 1) * h;
		
		double localCons = (localB - localA) / 8;
		double localFunc = FunctionValue(localA);

		localFunc += 3 * FunctionValue(localA + ((1 / 3) * h));
		localFunc += 3 * FunctionValue(localA + ((2 / 3) * h));
		localFunc += FunctionValue(localB);
		localFunc *= localCons;
		summ += localFunc;
		//double hop = a + i * h;
	}

	return summ;
}
double MethodThreeEight2(double a, double b) {
	double summ = 0;
	double h = (b - a) / 4000000;
	for (int i = 0; i < 4000000; i++) {
		double localA = a + i * h;
		double localB = a + (i + 1) * h;

		double localCons = (localB - localA) / 8;
		double localFunc = FunctionValue(localA);

		localFunc += 3 * FunctionValue(localA + ((1 / 3) * h));
		localFunc += 3 * FunctionValue(localA + ((2 / 3) * h));
		localFunc += FunctionValue(localB);
		localFunc *= localCons;
		summ += localFunc;
		//double hop = a + i * h;
	}
	return summ;
}
double MethodThreeEightParallel(double a, double b) {
	double summ = 0;
	double h = (b - a) / 2000000;
#pragma omp parallel for
	for (int i = 0; i < 2000000; i++) {
		double localA = a + i * h;
		double localB = a + (i + 1) * h;

		double localCons = (localB - localA) / 8;
		double localFunc = FunctionValue(localA);

		localFunc += 3 * FunctionValue(localA + ((1 / 3) * h));
		localFunc += 3 * FunctionValue(localA + ((2 / 3) * h));
		localFunc += FunctionValue(localB);
		localFunc *= localCons;
		summ += localFunc;
		//double hop = a + i * h;
	}
	return summ;
}
void AllThreeEight(double a, double b, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double MetThrEighResult = MethodThreeEight(a, b);
	e = chrono::steady_clock::now();

	double MetThrEighResult2 = MethodThreeEight2(a, b);

	sp = chrono::steady_clock::now();
	double MetThrEighResultParallel = MethodThreeEightParallel(a, b);
	ep = chrono::steady_clock::now();

	double ErrRuMetThrEigh = ErrorRunge(MetThrEighResult, MetThrEighResult2, Thetta);

	cout << "Method Three Eight" << endl;
	cout << "Error Runge = " << ErrRuMetThrEigh << setprecision(16) << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}

//--------------------------------------------------------------------------
double MethodMonte(double a, double b) {
	srand(time(NULL));
	int big_num = 20000000;
	double summ = 0;
	for (int i = 0; i < big_num; i++) {
		long double ran = (1.0 / (rand() % big_num + 1));
		long double xi = a + ran * (b - a);
		summ += FunctionValue(xi);
	}
	summ /= big_num;
	summ *= (b - a);
	//cout << summ << " MMMMMMMMM " << endl;
	return summ;
}
double MethodMonte2(double a, double b) {
	srand(time(NULL));
	int big_num = 4000000;
	double summ = 0;
	for (int i = 0; i < big_num; i++) {
		long double ran = (1.0 / (rand() % big_num + 1));
		long double xi = a + ran * (b - a);
		summ += FunctionValue(xi);
	}
	summ /= big_num;
	summ *= (b - a);
	//cout << "double monte " << summ << endl;
	return summ;
}
double MethodMonteParallel(double a, double b) {
	srand(time(NULL));
	int big_num = 2000000;
	double summ = 0;
#pragma omp parallel for
	for (int i = 0; i < big_num; i++) {
		long double ran = (1.0 / (rand() % big_num + 1));
		long double xi = a + ran * (b - a);
		summ += FunctionValue(xi);
	}
	summ /= big_num;
	summ *= (b - a);
	//cout << "parallel" << summ << endl;
	return summ;
}
void AllMonte(double a, double b, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double MetMonteResult = MethodMonte(a, b);
	e = chrono::steady_clock::now();

	double MetMonteResult2 = MethodMonte2(a, b);

	sp = chrono::steady_clock::now();
	double MetMonteResultParallel = MethodMonteParallel(a, b);
	ep = chrono::steady_clock::now();

	double ErrRuMetMonte = ErrorRunge(MetMonteResult, MetMonteResult2, Thetta);

	cout << "Method Monte" << endl;
	cout << "Error Runge = " << ErrRuMetMonte << setprecision(16) << endl;
	//cout << "result Monte parallel" << MetMonteResultParallel << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}
// Двойные интегралы
double FunctionValue2(double x, double y) {
	const double e = 2.7182818284;
	return pow(e, (x - y));
}

double DMethodRectangleL(double x1, double x2, double y1, double y2) {
	int big_num = 2000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
	for (int i = 0; i < big_num; i++) {
		for (int j = 0; j < big_num; j++) {
			double xnow = x1 + hx * i;
			double ynow = y1 + hy * j;
			double qi = 1;
			double qj = 1;
			if (i == 0 || i == big_num) {
				qi = 1.0 / 2;
			}
			if (j == 0 || j == big_num) {
				qj = 1.0 / 2;
			}
			summ += (qi * qj * FunctionValue2(xnow, ynow));
			
		}
	}
	summ *= hx;
	summ *= hy;
	return summ;
}
double DMethodRectangleL2(double x1, double x2, double y1, double y2) {
	int big_num = 4000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
	for (int i = 0; i < big_num; i++) {
		for (int j = 0; j < big_num; j++) {
			double xnow = x1 + hx * i;
			double ynow = y1 + hy * j;
			double qi = 1;
			double qj = 1;
			if (i == 0 || i == big_num) {
				qi = 1.0 / 2;
			}
			if (j == 0 || j == big_num) {
				qj = 1.0 / 2;
			}
			summ += (qi * qj * FunctionValue2(xnow, ynow));

		}
	}
	summ *= hx;
	summ *= hy;
	return summ;
}
double DMethodRectangleLParallel(double x1, double x2, double y1, double y2) {
	int big_num = 2000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
#pragma omp parallel for reduction(+:summ)
	for (int i = 0; i < big_num; i++) {
		for (int j = 0; j < big_num; j++) {
			double xnow = x1 + hx * i;
			double ynow = y1 + hy * j;
			double qi = 1;
			double qj = 1;
			if (i == 0 || i == big_num) {
				qi = 1.0 / 2;
			}
			if (j == 0 || j == big_num) {
				qj = 1.0 / 2;
			}
			summ += (qi * qj * FunctionValue2(xnow, ynow));

		}
	}
	summ *= hx;
	summ *= hy;
	return summ;
}
void DAllRectangleL(double x1, double x2, double y1, double y2, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double DMetRecLResult = DMethodRectangleL(x1, x2, y1, y2);
	e = chrono::steady_clock::now();

	double DMetRecLResult2 = DMethodRectangleL2(x1, x2, y1, y2);

	sp = chrono::steady_clock::now();
	double DMetRecLParallelResult = DMethodRectangleL(x1, x2, y1, y2);
	ep = chrono::steady_clock::now();

	double DErrRuMethRecL = ErrorRunge(DMetRecLResult, DMetRecLResult2, Thetta);

	cout << "Method Double Rectangle L" << endl;
	cout << "Error Runge = " << DErrRuMethRecL << setprecision(16) << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}
//---------------------------------------------------------------------------------------------------

double DMethodRectangleR(double x1, double x2, double y1, double y2) {
	int big_num = 2000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
	for (int i = 1; i < big_num-1; i++) {
		for (int j = 1; j < big_num-1; j++) {
			double xnow = x1 + hx * i;
			double ynow = y1 + hy * j;
			double qi = 1;
			double qj = 1;
			if (i == 0 || i == big_num) {
				qi = 1.0 / 2;
			}
			if (j == 0 || j == big_num) {
				qj = 1.0 / 2;
			}
			summ += (qi * qj * FunctionValue2(xnow, ynow));

		}
	}
	summ *= hx;
	summ *= hy;
	//cout << summ << endl;
	return summ;
}
double DMethodRectangleR2(double x1, double x2, double y1, double y2) {
	int big_num = 4000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
	for (int i = 1; i < big_num-1; i++) {
		for (int j = 1; j < big_num-1; j++) {
			double xnow = x1 + hx * i;
			double ynow = y1 + hy * j;
			double qi = 1;
			double qj = 1;
			if (i == 0 || i == big_num) {
				qi = 1.0 / 2;
			}
			if (j == 0 || j == big_num) {
				qj = 1.0 / 2;
			}
			summ += (qi * qj * FunctionValue2(xnow, ynow));

		}
	}
	summ *= hx;
	summ *= hy;
	return summ;
}
double DMethodRectangleRParallel(double x1, double x2, double y1, double y2) {
	int big_num = 2000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
#pragma omp parallel for reduction(+:summ)
	for (int i = 1; i < big_num-1; i++) {
		for (int j = 0; j < big_num; j++) {
			double xnow = x1 + hx * i;
			double ynow = y1 + hy * j;
			double qi = 1;
			double qj = 1;
			if (i == 0 || i == big_num) {
				qi = 1.0 / 2;
			}
			if (j == 0 || j == big_num) {
				qj = 1.0 / 2;
			}
			summ += (qi * qj * FunctionValue2(xnow, ynow));

		}
	}
	summ *= hx;
	summ *= hy;
	return summ;
}
void DAllRectangleR(double x1, double x2, double y1, double y2, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double DMetRecRResult = DMethodRectangleR(x1, x2, y1, y2);
	e = chrono::steady_clock::now();

	double DMetRecRResult2 = DMethodRectangleR2(x1, x2, y1, y2);

	sp = chrono::steady_clock::now();
	double DMetRecRParallelResult = DMethodRectangleRParallel(x1, x2, y1, y2);
	ep = chrono::steady_clock::now();

	double DErrRuMethRecR = ErrorRunge(DMetRecRResult, DMetRecRResult2, Thetta);

	cout << "Method Double Rectangle R" << endl;
	cout << "Error Runge = " << DErrRuMethRecR << setprecision(16) << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}
//---------------------------------------------------------------------------------------------------
double DMethodTrapezioid(double x1, double x2, double y1, double y2) {
	int big_num = 2000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
	for (int i = 1; i < big_num - 1; i++) {
		double xi = x1 + hx * i;
		for (int j = 1; j < big_num - 1; j++) {
			double yi = y1 + (hy * j);
			summ += FunctionValue2(xi, yi);
		}
	}
	summ += FunctionValue2(x1, y1) / 2;
	summ += FunctionValue2(x1, y2) / 2;
	summ += FunctionValue2(x2, y1) / 2;
	summ += FunctionValue2(x2, y2) / 2;
	summ *= hx * hy;
	cout << summ << endl;
	return summ;
}
double DMethodTrapezioid2(double x1, double x2, double y1, double y2) {
	int big_num = 4000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
	for (int i = 1; i < big_num - 1; i++) {
		double xi = x1 + hx * i;
		for (int j = 1; j < big_num - 1; j++) {
			double yi = y1 + (hy * j);
			summ += FunctionValue2(xi, yi);
		}
	}
	summ += FunctionValue2(x1, y1) / 2;
	summ += FunctionValue2(x1, y2) / 2;
	summ += FunctionValue2(x2, y1) / 2;
	summ += FunctionValue2(x2, y2) / 2;
	summ *= hx * hy;
	cout << summ << endl;
	return summ;
}
double DMethodTrapezioidParallel(double x1, double x2, double y1, double y2) {
	int big_num = 2000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;

#pragma omp parallel for reduction(+:summ)
	for (int i = 1; i < big_num - 1; i++) {
		double xi = x1 + hx * i;
		for (int j = 1; j < big_num - 1; j++) {
			double yi = y1 + (hy * j);
			summ += FunctionValue2(xi, yi);
		}
	}
	summ += FunctionValue2(x1, y1) / 2;
	summ += FunctionValue2(x1, y2) / 2;
	summ += FunctionValue2(x2, y1) / 2;
	summ += FunctionValue2(x2, y2) / 2;
	summ *= hx * hy;
	cout << summ << endl;
	return summ;
}
void DAllTrapezioid(double x1, double x2, double y1, double y2, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double DMetTrapezResult = DMethodTrapezioid(x1, x2, y1, y2);
	e = chrono::steady_clock::now();

	double DMetTrapezResult2 = DMethodTrapezioid2(x1, x2, y1, y2);

	sp = chrono::steady_clock::now();
	double DMetTrapezParallelResult = DMethodTrapezioidParallel(x1, x2, y1, y2);
	ep = chrono::steady_clock::now();

	double DErrRuMethTrapez = ErrorRunge(DMetTrapezResult, DMetTrapezResult2, Thetta);

	cout << "Method Trapezioid double" << endl;
	cout << "Error Runge = " << DErrRuMethTrapez << setprecision(16) << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}
//----------------------------------------------------------------------------------
double DMethodSimpson(double x1, double x2, double y1, double y2) {
	int big_num = 2000;
	double summ = 0.0;
	double chet = 0.0;
	double nechet = 0.0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
	for (int i = 0; i < big_num/2; i++) {
		double xi = x1 + (hx * i);
		for (int j = 0; j < big_num/2; j++) {
			double yi = y1 + (hy * j);
			nechet += FunctionValue2(xi, y1 + (hy * ((2 * j) + 1)));
			if (y1 + (hy * ((2 * j) + 1)) == 1.0) {
				break;
			}
			chet += FunctionValue2(xi, y1 + (hy * (2 * (j + 1))));
		}
		summ += nechet * 4;
		summ += chet * 2;
		summ *= (hx / 3.0);
		nechet = 0.0;
		chet = 0.0;
	}
	//cout << summ << endl;
	return summ;
}
double DMethodSimpson2(double x1, double x2, double y1, double y2) {
	int big_num = 4000;
	double summ = 0.0;
	double chet = 0.0;
	double nechet = 0.0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
	for (int i = 0; i < big_num / 2; i++) {
		double xi = x1 + (hx * i);
		for (int j = 0; j < big_num / 2; j++) {
			double yi = y1 + (hy * j);
			nechet += FunctionValue2(xi, y1 + (hy * ((2 * j) + 1)));
			if (y1 + (hy * ((2 * j) + 1)) == 1.0) {
				break;
			}
			chet += FunctionValue2(xi, y1 + (hy * (2 * (j + 1))));
		}
		summ += nechet * 4;
		summ += chet * 2;
		summ *= (hx / 3.0);
		nechet = 0.0;
		chet = 0.0;
	}
	//cout << summ << endl;
	return summ;
}
double DMethodSimpsonParallel(double x1, double x2, double y1, double y2) {
	int big_num = 2000;
	double summ = 0.0;
	double chet = 0.0;
	double nechet = 0.0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
#pragma omp parallel for reduction(+:summ)
	for (int i = 0; i < big_num / 2; i++) {
		double xi = x1 + (hx * i);
		for (int j = 0; j < big_num / 2; j++) {
			double yi = y1 + (hy * j);
			nechet += FunctionValue2(xi, y1 + (hy * ((2 * j) + 1)));
			if (y1 + (hy * ((2 * j) + 1)) == 1.0) {
				break;
			}
			chet += FunctionValue2(xi, y1 + (hy * (2 * (j + 1))));
		}
		summ += nechet * 4;
		summ += chet * 2;
		summ *= (hx / 3.0);
		nechet = 0.0;
		chet = 0.0;
	}
	//cout << summ << endl;
	return summ;
}
void DAllSimpson(double x1, double x2, double y1, double y2, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double DMetSimpResult = DMethodSimpson(x1, x2, y1, y2);
	e = chrono::steady_clock::now();

	double DMetSimpResult2 = DMethodSimpson2(x1, x2, y1, y2);

	sp = chrono::steady_clock::now();
	double DMetSimpParallelResult = DMethodSimpsonParallel(x1, x2, y1, y2);
	ep = chrono::steady_clock::now();

	double DErrRuMethSimp = ErrorRunge(DMetSimpResult, DMetSimpResult2, Thetta);

	cout << "Method Simpson double" << endl;
	cout << "Error Runge = " << DErrRuMethSimp << setprecision(16) << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}
//--------------------------------------------------------------------------------------
double DMethodThreeEight(double x1, double x2, double y1, double y2) {
	double summ = 0;
	int bg = 2000;
	double hx = (x2 - x1) / bg;
	double hy = (y2 - y1) / bg;
	for (int i = 0; i < bg; i++) {
		double xi = x1 + (hx * i);
		for (int j = 0; j < bg; j++) {
			double localA = y1 + j * hy;
			double localB = y1 + (j + 1) * hy;
			double localCons = (localB - localA) / 8;
			double localFunc = FunctionValue2(xi, localA);
			localFunc += 3 * FunctionValue2(xi, localA + ((1 / 3) * hy));
			localFunc += 3 * FunctionValue2(xi, localA + ((2 / 3) * hy));
			localFunc += FunctionValue2(xi, localB);
			localFunc *= localCons;
			summ += localFunc;
		}
	}
	summ *= hx;
	//cout << summ << endl;
	return summ;
}
double DMethodThreeEight2(double x1, double x2, double y1, double y2) {
	double summ = 0;
	int bg = 4000;
	double hx = (x2 - x1) / bg;
	double hy = (y2 - y1) / bg;
	for (int i = 0; i < bg; i++) {
		double xi = x1 + (hx * i);
		for (int j = 0; j < bg; j++) {
			double localA = y1 + j * hy;
			double localB = y1 + (j + 1) * hy;
			double localCons = (localB - localA) / 8;
			double localFunc = FunctionValue2(xi, localA);
			localFunc += 3 * FunctionValue2(xi, localA + ((1 / 3) * hy));
			localFunc += 3 * FunctionValue2(xi, localA + ((2 / 3) * hy));
			localFunc += FunctionValue2(xi, localB);
			localFunc *= localCons;
			summ += localFunc;
		}
	}
	summ *= hx;
	//cout << summ << endl;
	return summ;
}
double DMethodThreeEightParallel(double x1, double x2, double y1, double y2) {
	double summ = 0;
	int bg = 2000;
	double hx = (x2 - x1) / bg;
	double hy = (y2 - y1) / bg;
#pragma omp parallel for reduction(+:summ)
	for (int i = 0; i < bg; i++) {
		double xi = x1 + (hx * i);
		for (int j = 0; j < bg; j++) {
			double localA = y1 + j * hy;
			double localB = y1 + (j + 1) * hy;
			double localCons = (localB - localA) / 8;
			double localFunc = FunctionValue2(xi, localA);
			localFunc += 3 * FunctionValue2(xi, localA + ((1 / 3) * hy));
			localFunc += 3 * FunctionValue2(xi, localA + ((2 / 3) * hy));
			localFunc += FunctionValue2(xi, localB);
			localFunc *= localCons;
			summ += localFunc;
		}
	}
	summ *= hx;
	//cout << summ << endl;
	return summ;
}
void DAllThreeEight(double x1, double x2, double y1, double y2, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double DMetThEiResult = DMethodThreeEight(x1, x2, y1, y2);
	e = chrono::steady_clock::now();

	double DMetThEiResult2 = DMethodThreeEight2(x1, x2, y1, y2);

	sp = chrono::steady_clock::now();
	double DMetThEiParallelResult = DMethodThreeEightParallel(x1, x2, y1, y2);
	ep = chrono::steady_clock::now();

	double DErrRuMethThEi = ErrorRunge(DMetThEiResult, DMetThEiResult2, Thetta);

	cout << "Method Three Eight double" << endl;
	cout << "Error Runge = " << DErrRuMethThEi << setprecision(16) << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}
//-------------------------------------------------------------------------------------------------------

double DMethodMonte(double x1, double x2, double y1, double y2) {
	srand(time(NULL));
	int big_num = 2000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
	for (int i = 0; i < big_num; i++) {
		double xi = x1 + (hx * i);
		for (int j = 0; j < big_num; j++) {
			long double ran = (1.0 / (rand() % big_num + 1));	
			long double yi = ran;
			
			
			summ += FunctionValue2(xi, yi);
		}
	}
	summ /= big_num;
	summ /= big_num_2;
	//cout << summ << "-----" << endl;
	return summ;
}
double DMethodMonte2(double x1, double x2, double y1, double y2) {
	srand(time(NULL));
	int big_num = 4000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
	for (int i = 0; i < big_num; i++) {
		double xi = x1 + (hx * i);
		for (int j = 0; j < big_num; j++) {
			long double ran = (1.0 / (rand() % big_num + 1));
			long double yi = ran;


			summ += FunctionValue2(xi, yi);
		}
	}
	summ /= big_num;
	summ /= (big_num_2*2);
	//cout << summ << "-----" << endl;
	return summ;
}
double DMethodMonteParallel(double x1, double x2, double y1, double y2) {
	srand(time(NULL));
	int big_num = 2000;
	double summ = 0;
	double hx = (x2 - x1) / big_num;
	double hy = (y2 - y1) / big_num;
#pragma omp parallel for reduction(+:summ)
	for (int i = 0; i < big_num; i++) {
		double xi = x1 + (hx * i);
		for (int j = 0; j < big_num; j++) {
			long double ran = (1.0 / (rand() % big_num + 1));
			long double yi = ran;


			summ += FunctionValue2(xi, yi);
		}
	}
	summ /= big_num;
	summ /= big_num_2;
	//cout << summ << "-----" << endl;
	return summ;
}
void DAllMonte(double x1, double x2, double y1, double y2, double Thetta) {
	steady_clock::time_point s, sp, e, ep;
	duration<double, milli> t, tp;

	s = chrono::steady_clock::now();
	double DMetMonResult = DMethodMonte(x1, x2, y1, y2);
	e = chrono::steady_clock::now();

	double DMetMonResult2 = DMethodMonte2(x1, x2, y1, y2);

	sp = chrono::steady_clock::now();
	double DMetMonParallelResult = DMethodMonteParallel(x1, x2, y1, y2);
	ep = chrono::steady_clock::now();

	double DErrRuMethMon = ErrorRunge(DMetMonResult, DMetMonResult2, Thetta);

	cout << "Method Monte double" << endl;
	cout << "Error Runge = " << DErrRuMethMon << setprecision(16) << endl;

	t = e - s;
	tp = ep - sp;

	cout << "Work default = " << to_string(t.count()) << endl;
	cout << "Work parallel = " << to_string(tp.count()) << endl;
}






int main()
{
	//Интегралы
	double Thetta1 = 1.0 / 3;
	double Thetta2 = 1.0 / 15;
	double a = 1;
	double b = 1.2;

	/*double MetTrapResult = MethodTrapezoid(a, b);
	double MetTrapResult2 = MethodTrapezoid2(a, b);
	double MetTrapResultParallel = MethodTrapezoidParallel(a, b);
	double ErrRuMetTrap = ErrorRunge(MetTrapResult, MetTrapResult2, Thetta1);

	cout << "Method Trapezoid" << endl;
	cout << "Error Runge = " << ErrRuMetTrap << setprecision(16) << endl;

	cout << MetTrapResult << setprecision(16) << endl;
	cout << MetTrapResult2 << setprecision(16) << endl;
*/

	AllRectangleL(a, b, Thetta1);
	AllRectangleR(a, b, Thetta1);
	AllTrapezioid(a, b, Thetta1);
	AllSimpson(a, b, Thetta2);
	AllThreeEight(a, b, Thetta2);
	AllMonte(a, b, Thetta2);

	/*
	double MetQuadSimpResult = MethodQudratureSimpson(a, b);
	double MetThreeEightResult = MethodThreeEight(a, b);

	
	cout << MetQuadSimpResult << setprecision(10) << endl;
	cout << MetThreeEightResult << setprecision(10) << endl;
	*/

	// Двойные интегралы
	
	double x1 = -1;
	double x2 = 0;
	double y1 = 0;
	double y2 = 1;
	
	
	

	//DAllRectangleL(x1, x2, y1, y2, Thetta2);
	//DAllRectangleR(x1, x2, y1, y2, Thetta2);
	//DAllTrapezioid(x1, x2, y1, y2, Thetta2);
	//DAllSimpson(x1, x2, y1, y2, Thetta2);
	//DAllThreeEight(x1, x2, y1, y2, Thetta2);

	//DAllMonte(x1, x2, y1, y2, Thetta2);

	return 0;
}


























//двойной монте карло сделать

















