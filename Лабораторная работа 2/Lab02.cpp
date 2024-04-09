#include <iostream>

class Vect {
private:
    int dim;
    double* b;
    int num;
    static int count;

public:
    Vect(int dim, double* a);
    ~Vect();
    Vect operator+(const Vect& other);
    Vect operator-(const Vect& other);
    Vect operator*(const Vect& other);
    Vect operator*(double k);
    Vect& operator=(const Vect& other);
    Vect operator-();
    void print() const;
    double* getB() const;
    int getDim() const;
};

class Matr {
private:
    int rows;
    int cols;
    double** values;
    int num;
    static int count;

public:
    Matr(int rows, int cols);
    ~Matr();
    Matr operator+(const Matr& other);
    Matr operator-(const Matr& other);
    Matr operator*(const Matr& other);
    Matr operator*(double k);
    Matr& operator=(const Matr& other);
    Matr operator-();
    Vect operator*(const Vect& v);
    void print() const;
    double** getValues() const;
};

int Vect::count = 0;
int Matr::count = 0;

Vect::Vect(int dim, double* a) : dim(dim), num(++count) {
    std::cout << "Creating Vect object #" << num << std::endl;
    b = new double[dim];
    for (int i = 0; i < dim; ++i)
        b[i] = a[i];
}

Vect::~Vect() {
    std::cout << "Destroying Vect object #" << num << std::endl;
    delete[] b;
}

Vect Vect::operator+(const Vect& other) {
    if (dim != other.dim) {
        throw std::invalid_argument("Dimensions do not match");
    }
    double* result = new double[dim];
    for (int i = 0; i < dim; ++i) {
        result[i] = b[i] + other.b[i];
    }
    return Vect(dim, result);
}

Vect Vect::operator-(const Vect& other) {
    if (dim != other.dim) {
        throw std::invalid_argument("Dimensions do not match");
    }
    double* result = new double[dim];
    for (int i = 0; i < dim; ++i) {
        result[i] = b[i] - other.b[i];
    }
    return Vect(dim, result);
}

Vect Vect::operator*(const Vect& other) {
    if (dim != other.dim) {
        throw std::invalid_argument("Dimensions do not match");
    }
    double* result = new double[dim];
    for (int i = 0; i < dim; ++i) {
        result[i] = b[i] * other.b[i];
    }
    return Vect(dim, result);
}

Vect Vect::operator*(double k) {
    double* result = new double[dim];
    for (int i = 0; i < dim; ++i) {
        result[i] = b[i] * k;
    }
    return Vect(dim, result);
}

Vect& Vect::operator=(const Vect& other) {
    if (this == &other) {
        return *this;
    }
    dim = other.dim;
    delete[] b;
    b = new double[dim];
    for (int i = 0; i < dim; ++i) {
        b[i] = other.b[i];
    }
    return *this;
}

Vect Vect::operator-() {
    double* result = new double[dim];
    for (int i = 0; i < dim; ++i) {
        result[i] = -b[i];
    }
    return Vect(dim, result);
}

void Vect::print() const {
    for (int i = 0; i < dim; ++i) {
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;
}

double* Vect::getB() const {
    return b;
}

int Vect::getDim() const {
    return dim;
}

Matr::Matr(int rows, int cols) : rows(rows), cols(cols), num(++count) {
    std::cout << "Creating Matr object #" << num << std::endl;
    values = new double* [rows];
    for (int i = 0; i < rows; ++i) {
        values[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            values[i][j] = 0.0;
        }
    }
}

Matr::~Matr() {
    std::cout << "Destroying Matr object #" << num << std::endl;
    for (int i = 0; i < rows; ++i) {
        delete[] values[i];
    }
    delete[] values;
}

Matr Matr::operator+(const Matr& other) {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions do not match");
    }
    Matr result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.values[i][j] = values[i][j] + other.values[i][j];
        }
    }
    return result;
}

Matr Matr::operator-(const Matr& other) {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Dimensions do not match");
    }
    Matr result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.values[i][j] = values[i][j] - other.values[i][j];
        }
    }
    return result;
}

Matr Matr::operator*(const Matr& other) {
    if (cols != other.rows) {
        throw std::invalid_argument("Dimensions do not match for matrix multiplication");
    }
    Matr result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.values[i][j] += values[i][k] * other.values[k][j];
            }
        }
    }
    return result;
}

Matr Matr::operator*(double k) {
    Matr result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.values[i][j] = values[i][j] * k;
        }
    }
    return result;
}

Matr& Matr::operator=(const Matr& other) {
    if (this == &other) {
        return *this;
    }
    rows = other.rows;
    cols = other.cols;
    for (int i = 0; i < rows; ++i) {
        delete[] values[i];
    }
    delete[] values;
    values = new double* [rows];
    for (int i = 0; i < rows; ++i) {
        values[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            values[i][j] = other.values[i][j];
        }
    }
    return *this;
}

Matr Matr::operator-() {
    Matr result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.values[i][j] = -values[i][j];
        }
    }
    return result;
}

Vect Matr::operator*(const Vect& v) {
    if (cols != v.getDim()) {
        throw std::invalid_argument("Matrix columns do not match vector dimension for multiplication");
    }
    double* result = new double[rows];
    for (int i = 0; i < rows; ++i) {
        result[i] = 0.0;
        for (int j = 0; j < cols; ++j) {
            result[i] += values[i][j] * v.getB()[j];
        }
    }
    return Vect(rows, result);
}

void Matr::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << values[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

double** Matr::getValues() const {
    return values;
}

int main() {
    double a1[] = { 1, 2, 3 };
    double a2[] = { 4, 5, 6 };
    Vect v1(3, a1);
    Vect v2(3, a2);
    Vect v3 = v1 + v2;
    std::cout << "Result of vector addition: ";
    v3.print();

    Vect v4 = v1 - v2;
    std::cout << "Result of vector subtraction: ";
    v4.print();

    Vect v5 = v1 * v2;
    std::cout << "Result of element-wise vector multiplication: ";
    v5.print();

    Vect v6 = v1 * 2.0;
    std::cout << "Result of vector-scalar multiplication: ";
    v6.print();

    v1 = v2;
    std::cout << "v1 after assignment: ";
    v1.print();

    Vect v7 = -v2;
    std::cout << "Result of unary negation: ";
    v7.print();

    double m1_data[] = { 1, 2, 3, 4 };
    double m2_data[] = { 7, 8, 9, 10 };
    Matr m1(2, 2); // 2 строки, 2 столбца
    Matr m2(2, 2); // 2 строки, 2 столбца
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            m1.getValues()[i][j] = m1_data[i * 2 + j];
            m2.getValues()[i][j] = m2_data[i * 2 + j];
        }
    }

    Matr m3 = m1 + m2;
    std::cout << "Result of matrix addition:" << std::endl;
    m3.print();

    Matr m4 = m1 - m2;
    std::cout << "Result of matrix subtraction:" << std::endl;
    m4.print();

    Matr m5 = m1 * m2;
    std::cout << "Result of matrix multiplication:" << std::endl;
    m5.print();

    Matr m6 = m1 * 2.0;
    std::cout << "Result of scalar-matrix multiplication:" << std::endl;
    m6.print();

    m1 = m2;
    std::cout << "m1 after assignment:" << std::endl;
    m1.print();

    Matr m7 = -m2;
    std::cout << "Result of unary negation:" << std::endl;
    m7.print();

    Vect v8(3, a1);
    Vect v9 = m1 * v8;
    std::cout << "Result of matrix-vector multiplication:" << std::endl;
    v9.print();

    return 0;
}
