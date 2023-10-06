from random import randint

class Matr(object):
    def __new__(cls, *args, **kwargs):
        for i in args:
            if type(i) != int:
                return
        return super().__new__(cls)

    def __init__(self, nums:int, numc:int):
        if self.__check_data(nums, numc):
            return
        self.num_strings = nums
        self.num_columns = numc
        self.elements = []
        for i in range(nums):
            self.elements.append([0] * numc)

    def __del__(self):
        print("матрица была удалена")

    def __add__(self, other):
        if self.num_strings != other.num_strings or self.num_columns != other.num_columns:
            print("размерности матриц не совпадают")
            return
        for i in range(self.num_strings):
            for j in range(self.num_columns):
                self.elements[i][j]+=other.elements[i][j]

    def __check_data(self, a, b):
        if type(a) != int or type(b) != int:
            print("в качестве одного из параметров передано не число")
            return True
        return False

    def new_nubmers_for_matrix(self, start, end):
        if self.__check_data(start, end):
            return
        for i in range(self.num_strings):
            for j in range(self.num_columns):
                aa = randint(start, end)
                self.elements[i][j] = aa

    def print_matrix(self):
        print("новая матрица: ")
        for i in range(self.num_strings):
            print(self.elements[i])

    def multiplication_matrix(self, matrA, matrB):
        if type(matrA) != Matr or type(matrB) != Matr:
            print("один или более переданных аргументов не матрицы")
            return
        if matrA.num_columns != matrB.num_strings:
            print("Nizя, переделывай: необходимые размерности у матриц не совпадают")
            return
        self.num_strings = matrA.num_strings
        self.num_columns = matrB.num_columns
        self.elements = []
        for i in range(self.num_strings):
            self.elements.append([0] * self.num_columns)
        print(f'new string num = {self.num_strings}')
        print(f'new col num = {self.num_columns}')
        for k in range(matrA.num_strings):
            for i in range(matrB.num_columns):
                sum_elements = 0
                for j in range(matrA.num_columns):
                    sum_elements += matrA.elements[k][j] * matrB.elements[j][i]
                self.elements[k][i] = sum_elements

    def multiplication_matrix_constant(self, constant):
        for i in range(self.num_strings):
            for j in range(self.num_columns):
                self.elements[i][j]*=constant




import time
start = time.time()
print(start)
'''a = Matr(2, 5)
a.new_nubmers_for_matrix(2, 9)
a.print_matrix()
b = Matr(5, 3)
b.new_nubmers_for_matrix(5, 9)
b.print_matrix()
aa = Matr(3, 3)
aa.multiplication_matrix(a, b)
aa.print_matrix()'''

'''y, x = Matr(2, 2), Matr(2, 2)
y.new_nubmers_for_matrix(4, 6)
x.new_nubmers_for_matrix(7, 9)
y.print_matrix()
x.print_matrix()
x.__add__(y)
x.print_matrix()
y.print_matrix()'''








'''print(a.elements[0][0])
print(a.elements[1][0])
print(a.elements[2][0])
print(a.elements[3][0])'''