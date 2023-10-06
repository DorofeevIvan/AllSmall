#include "pch.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <omp.h>
#include <random>
#include <sstream>
//new
#include <memory>
#include <stdexcept>

using namespace std;
using Vec = vector<double>;

Vec &operator+= (Vec &a, const Vec &b) {
	if (a.size() != b.size()) {
		throw std::invalid_argument("Different vector sizes");
	}
	for (size_t i = 0; i < a.size(); ++i) {
		a[i] += b[i];
	}
	return a;
}


string toStrV(const Vec &vec) {
	stringstream SS;
	SS << "[";
	for (size_t i = 0; i < size(vec); i++) {
		SS << vec.at(i);
		SS << ((i != size(vec) - 1) ? ", " : "");
	}
	SS << "]";
	return SS.str();
}


// from lab 1----------------------------------------

vector<double> getRandomVector(unsigned size) {
	vector<double> xs(size);
	random_device rd;
#pragma omp parallel
	{
		unsigned int seed;
	#pragma omp critical
		{
			seed = rd();
		}
		mt19937 gen(seed);
		uniform_real_distribution<double> dist(0.0, 1.0);
	#pragma omp for
		for (int i = 0; i < size; ++i) {
			xs[i] = dist(gen);
		}
	}
	
	return xs;
}


//from home work----------------------------------------



class Matrix {
private:
	size_t row;
	size_t col;
	vector<double> data;
	//-----конструкторы
public:
	Matrix(size_t R, size_t C)
		:row(R), col(C), data(R*C) {}

	//
	/*Vec get_data() const {
		return data;
	}*/

	size_t get_row() const {
		return row;
	}
	size_t get_col() const {
		return col;
	}
	//-----перегрузки
	double &operator() (size_t	r, size_t c) {
		return data[r*col + c];
	}
	const double &operator() (size_t r, size_t c) const {
		return data[r * col + c];
	}
	//-------
	static Matrix MatrOne(size_t n) {
		Matrix A(n, n);
		for (size_t i = 0; i < n; i++) {
			A(i, i) = 1;
		}
		return A;
	}
	
	//new
	
	Matrix(size_t rows, size_t cols, const vector<double> &v_data)// удалил const
		: row(rows)
		, col(cols)
		, data()
	{
		if (v_data.size() != rows * cols) {
			throw invalid_argument("Wrong data size in Matrix constructor");
		}
		data = v_data;
	}

	Matrix(size_t rows, size_t cols, vector<double> &&v_data)
		: row(rows)
		, col(cols)
		, data()
	{
		if (v_data.size() != rows * cols) {
			throw invalid_argument("Wrong data size in Matrix constructor");
		}
		data = move(v_data);
	}

	static Matrix Random(size_t rows, size_t cols) {
		return Matrix(rows, cols, move(getRandomVector(rows * cols)));
	}


};

//function for matrix
string toJsStr(const Matrix &matr) {
	stringstream SS;
	SS << "[";
	for (size_t i = 0; i < matr.get_row(); i++) {
		SS << ((i != 0) ? ", [" : "[");
		if (matr.get_col() > 0) SS << matr(i, 0);
		for (size_t j = 1; j < matr.get_col(); j++) {
			SS << ", " << matr(i, j);
		}
		SS << "]" << "\n";
	}
	SS << "]";
	return SS.str();
}


Matrix toStrM(Matrix &matr) {
	for (size_t i = 0; i < matr.get_row(); i++) {
		for (size_t j = 0; j < matr.get_col(); j++) {
			matr(i, j) = i * 10 + j;
		}
	}
	return matr;
}

Matrix SerAd(double x, Matrix &matr) {
	for (size_t i = 0; i < matr.get_row(); i++) {
		for (size_t j = 0; j < matr.get_col(); j++) {
			matr(i, j) += x;
		}
	}
	return matr;
}

Matrix SerSum(Matrix &m1, Matrix &m2) {
	if (m1.get_col() != m2.get_col() || m1.get_row() != m2.get_row()) return m1;
	Matrix Rez(m1.get_row(), m1.get_col());
	for (size_t i = 0; i < m1.get_row(); i++) {
		for (size_t j = 0; j < m1.get_col(); j++) {
			Rez(i, j) = m1(i, j) + m2(i, j);
		}
	}
	return Rez;
}

Matrix SerMulX(double x, Matrix &matr) {
	for (size_t i = 0; i < matr.get_row(); i++) {
		for (size_t j = 0; j < matr.get_col(); j++) {
			matr(i, j) *= x;
		}
	}
	return matr;
}

Matrix SerMulV(Vec &v, Matrix &matr) {
	if (matr.get_col() != size(v)) return matr;
	Matrix NewMatr(matr.get_row(), 1);
	for (size_t i = 0; i < matr.get_row(); i++) {
		double S = 0;
		for (size_t j = 0; j < matr.get_col(); j++) {
			S += matr(i, j)*v.at(j);
		}
		NewMatr(i, 0) = S;
	}
	return NewMatr;
}

Matrix SerMulM(Matrix &matr0, Matrix &matr1) {
	if (matr0.get_col() != matr1.get_row()) return matr0;
	Matrix NewMatr(matr0.get_row(), matr1.get_col());
	cout << toJsStr(NewMatr) << endl;
	for (size_t i = 0; i < matr0.get_row(); i++) {

		for (size_t j = 0; j < matr1.get_col(); j++) {

			double S = 0;
			for (size_t t = 0; t < matr1.get_row(); t++) {
				S += matr0(i, t)*matr1(t, j);
			}
			NewMatr(i, j) = S;

		}
	}
	return NewMatr;
}

//functoin for vector

void FiV(Vec &vec, double x) {
	vec.assign(vec.size(), x);
	return;

}

// new

Vec ParallelMulByRow(const Matrix &A, const Vec &b) {
	Vec c(A.get_row()); 
#pragma omp for
	for (size_t i = 0; i < A.get_row(); ++i) {
		for (size_t j = 0; j < A.get_col(); ++j) {
			c[i] += A(i, j) * b[j];
		}
	}
	return c;
}

Vec ParallelMulByColumn(const Matrix &A, const Vec &b) {
	Vec c(A.get_row());
	Vec t(A.get_row());
#pragma omp parallel for firstprivate(t) shared(c)
	for (size_t j = 0; j < b.size(); ++j) {
		int id = omp_get_thread_num();
//#pragma omp critical(std_cout)
//		{
//			cout << id << ": start j=" << j << " t=" << toStrV(t) << std::endl;
//			cout << id << ": start j=" << j << " c=" << toStrV(c) << std::endl;
//		}
		for (size_t i = 0; i < A.get_row(); ++i) {
			t[i] = A(i, j) * b[j];
		}
#pragma omp critical (par_mul_col_sum)
		{
			c += t;
		}
//#pragma omp critical(std_cout)
//		{
//			cout << id << ": end j=" << j << " t=" << toStrV(t) << std::endl;
//			cout << id << ": end j=" << j << " c=" << toStrV(c) << std::endl;
//		}
	}
	return c;
}

#pragma omp declare reduction(VecAdd: Vec: omp_out += omp_in)\
initializer(omp_priv=Vec(omp_orig.size()))
Vec ParallelMulByColumn1(const Matrix &A, const Vec &b) {
	Vec c(A.get_row());
	Vec t(A.get_row());
#pragma omp parallel for firstprivate(t) reduction(VectorAdd:c)
	for (size_t j = 0; j < b.size(); ++j) {
		int id = omp_get_thread_num();
//#pragma omp critical(std_cout)
//		{
//			cout << id << ": start j=" << j << " t=" << toStrV(t) << std::endl;
//			cout << id << ": start j=" << j << " c=" << toStrV(c) << std::endl;
//		}
		for (size_t i = 0; i < A.get_row(); ++i) {
			t[i] = A(i, j) * b[j];
		}
		c += t;
//#pragma omp critical(std_cout)
//		{
//			cout << id << ": end j=" << j << " t=" << toStrV(t) << std::endl;
//			cout << id << ": end j=" << j << " c=" << toStrV(c) << std::endl;
//		}
	}
	return c;
}

Vec ParallelMulByColumn2(const Matrix &A, const Vec &b) {
	Vec c(A.get_row());
#pragma omp parallel for reduction(VecAdd:c)
	for (size_t j = 0; j < b.size(); ++j) {
		//1
		for (size_t i = 0; i < A.get_row(); ++i) {
			c[i] += A(i, j) * b[j];
		}
		//2
	}
	return c;
}


//int id = omp_get_thread_num();
//#pragma omp critical(std_cout)
//		{
//			cout << id << ": start j=" << j << " c=" << toStrV(c) << std::endl;
//		}

//#pragma omp critical(std_cout)
//		{
//			cout << id << ": end j=" << j << " c=" << toStrV(c) << std::endl;
//		}


Vec ParallelMulByBlocks(const Matrix &A, const Vec &b) {
	size_t Row = A.get_row() / 2;
	size_t Col = A.get_col() / 2;
	size_t HV = b.size() / 2;
	
	Matrix V(A.get_row() / 2, A.get_col() / 2);
	Vec c(b.size() / 2);
	Vec Itog(A.get_row());

	for (size_t i = 0; i < 2; ++i) {
		for (size_t j = 0; j < 2; ++j) {
			for (size_t k = 0; k < Row; ++k) {
				for (size_t t = 0; t < Col; ++t) {
					c[t] = b[t + HV*i];
					V(k, t) = A(k + Row*j, t + Col*i);
					Itog[k+ j*Row] += V(k, t) * c[t];
				}
			}
		
		}
	}
	return Itog;
}





//
//Vec ParallelMulByBlocks(const Matrix &A, const Vec &b) {
//	size_t Row = A.get_row() / 2;
//	size_t Col = A.get_col() / 2;
//	size_t HV = b.size() / 2;
//
//	Matrix V(A.get_row() / 2, A.get_col() / 2);
//	Vec c(b.size() / 2);
//	Vec S(A.get_row() / 2);
//#pragma omp for
//	for (size_t i = 0; i < A.get_row() / 2; ++i) {
//
//		c[i] = b[i + HV];
//		for (size_t j = 0; j < A.get_col() / 2; ++j) {
//			V(i, j) = A(i + Row, j + Col);
//		}
//
//	}
//	cout << "Matr in function = \n " << toJsStr(V) << endl;
//	cout << "Vec in function = \n " << toStrV(c) << endl;
//#pragma omp for reduction(VecAdd:c)
//	for (size_t i = 0; i < V.get_row(); ++i) {
//		for (size_t j = 0; j < V.get_col(); ++j) {
//			S[i] += V(i, j) * c[j];
//		}
//	}
//	cout << "Vec after mul = \n " << toStrV(S) << endl;
//
//	return b;
//}
int main()
{
	//from 1 lab
	const unsigned N = 10000000;
	const unsigned SEED = 13131313;
	srand(SEED);


	cout<< "maxt"<<omp_get_num_threads()<<endl;
	Matrix A = Matrix::Random(4, 4);

	Vec vA = getRandomVector(4);

	cout <<"Matr A = \n " << toJsStr(A) << endl;
	cout <<"Vec A = " << toStrV(vA) << endl;

	//double t1 = omp_get_wtime();

	//cout << "Itog: " << toStrV(ParallelMulByColumn(A, vA)) << endl;
	//cout << "Itog: " << toStrV(ParallelMulByColumn1(A, vA)) << endl;


	cout << "Itog: " << toStrV(ParallelMulByBlocks(A, vA))<<endl;
	cout << "Itog: " << toStrV(ParallelMulByColumn2(A, vA)) << endl;


	//double t2 = omp_get_wtime();
	//cout << "Worked time: " << (t2 - t1) << endl;
	//cout << "Threads: " << omp_get_max_threads() << endl;





	return 0;
}