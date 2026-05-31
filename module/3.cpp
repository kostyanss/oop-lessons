#include <iostream>
#include <algorithm>

template <typename T>
class Matrix {
private:
    T** data;
    int rows;
    int cols;

    void allocate() {
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols]();
        }
    }

    void clear() {
        if (data) {
            for (int i = 0; i < rows; ++i) {
                delete[] data[i];
            }
            delete[] data;
            data = nullptr;
        }
    }

public:
    // Конструктор
    Matrix(int r, int c) : rows(r), cols(c) {
        allocate();
    }

    // Деструктор
    ~Matrix() {
        clear();
    }

    // Копіюючий конструктор (глибоке копіювання)
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        allocate();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Оператор присвоювання
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            clear();
            rows = other.rows;
            cols = other.cols;
            allocate();
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    // 1. Копіювання за рядками (зовнішній цикл по рядках)
    Matrix copyRowWise() const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = this->data[i][j];
            }
        }
        return result;
    }

    // 2. Копіювання за стовпцями (зовнішній цикл по стовпцях)
    Matrix copyColWise() const {
        Matrix result(rows, cols);
        for (int j = 0; j < cols; ++j) {
            for (int i = 0; i < rows; ++i) {
                result.data[i][j] = this->data[i][j];
            }
        }
        return result;
    }

    // 3. Копіювання вибраного рядка (повертає матрицю 1 x cols)
    Matrix copySelectedRow(int r) const {
        if (r < 0 || r >= rows) throw std::out_of_range("Індекс рядка за межами");
        Matrix result(1, cols);
        for (int j = 0; j < cols; ++j) {
            result.data[0][j] = data[r][j];
        }
        return result;
    }

    // 4. Копіювання вибраного стовпчика (повертає матрицю rows x 1)
    Matrix copySelectedCol(int c) const {
        if (c < 0 || c >= cols) throw std::out_of_range("Індекс стовпця за межами");
        Matrix result(rows, 1);
        for (int i = 0; i < rows; ++i) {
            result.data[i][0] = data[i][c];
        }
        return result;
    }

    // 5. Копіювання головної діагоналі (повертає матрицю 1 x min(rows,cols))
    Matrix copyMainDiagonal() const {
        int size = std::min(rows, cols);
        Matrix result(1, size);
        for (int i = 0; i < size; ++i) {
            result.data[0][i] = data[i][i];
        }
        return result;
    }

    // Потокове виведення
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j) {
                os << m.data[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }

    // Потокове введення
    friend std::istream& operator>>(std::istream& is, Matrix& m) {
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j) {
                is >> m.data[i][j];
            }
        }
        return is;
    }
};

int main() {
    int r = 3, c = 3;
    Matrix<int> mat(r, c);

    std::cout << "Введіть елементи матриці 3х3:\n";
    std::cin >> mat;

    std::cout << "\nОригінальна матриця:\n" << mat;

    // Демонстрація операцій копіювання
    Matrix<int> rowWiseCopy = mat.copyRowWise();
    Matrix<int> colWiseCopy = mat.copyColWise();
    Matrix<int> singleRow = mat.copySelectedRow(1); // Другий рядок (індекс 1)
    Matrix<int> singleCol = mat.copySelectedCol(2); // Третій стовпець (індекс 2)
    Matrix<int> diagonal = mat.copyMainDiagonal();

    std::cout << "\nКопія за рядками:\n" << rowWiseCopy;
    std::cout << "\nКопія за стовпцями:\n" << colWiseCopy;
    std::cout << "\nКопія 2-го рядка (індекс 1):\n" << singleRow;
    std::cout << "\nКопія 3-го стовпця (індекс 2):\n" << singleCol;
    std::cout << "\nКопія головної діагоналі:\n" << diagonal;

    return 0;
}
