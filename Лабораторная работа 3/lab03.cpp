#include <iostream>
#include <cmath>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Point {
public:
    virtual void draw() const = 0;
    virtual void move(double x, double y) = 0;
    virtual void rotate(double angle, double cx, double cy) = 0;
    virtual ~Point() {}
};

class ConcretePoint : public Point {
private:
    double x;
    double y;
public:
    ConcretePoint(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}
    double getX() const { return x; }
    double getY() const { return y; }
    void draw() const {
        std::cout << "(" << x << ", " << y << ")";
    }
    void move(double xNew, double yNew) {
        x += xNew;
        y += yNew;
    }
    void rotate(double angle, double cx, double cy) {
        double radians = angle * M_PI / 180.0;
        double newX = cos(radians) * (x - cx) - sin(radians) * (y - cy) + cx;
        double newY = sin(radians) * (x - cx) + cos(radians) * (y - cy) + cy;
        x = newX;
        y = newY;
    }
};

class Square : public Point {
private:
    std::vector<ConcretePoint*> corners;
public:
    Square(ConcretePoint* tl, double length) {
        double x = tl->getX();
        double y = tl->getY();
        corners.push_back(new ConcretePoint(x, y));  // Верхний левый угол
        corners.push_back(new ConcretePoint(x + length, y)); // Верхний правый угол
        corners.push_back(new ConcretePoint(x + length, y - length)); // Нижний правый угол
        corners.push_back(new ConcretePoint(x, y - length)); // Нижний левый угол
    }
    void draw() const {
        std::cout << "Квадрат с вершинами: ";
        for (const auto& corner : corners) {
            corner->draw();
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    void move(double x, double y) {
        for (auto& corner : corners) {
            corner->move(x, y);
        }
    }
    void rotate(double angle, double cx, double cy) {
        for (auto& corner : corners) {
            corner->rotate(angle, cx, cy);
        }
    }
};

class Rhombus : public Square {
public:
    Rhombus(ConcretePoint* tl, double length) : Square(tl, length) {}
};

class Parallelogram : public Point {
private:
    ConcretePoint* topLeft;
    ConcretePoint* topRight;
    ConcretePoint* bottomLeft;
    ConcretePoint* bottomRight;
public:
    Parallelogram(ConcretePoint* tl, ConcretePoint* tr, ConcretePoint* bl, ConcretePoint* br)
        : topLeft(tl), topRight(tr), bottomLeft(bl), bottomRight(br) {}
    void draw() const {
        std::cout << "Параллелограмм с вершинами: ";
        topLeft->draw();
        std::cout << " ";
        topRight->draw();
        std::cout << " ";
        bottomRight->draw();
        std::cout << " ";
        bottomLeft->draw();
        std::cout << std::endl;
    }
    void move(double x, double y) {
        topLeft->move(x, y);
        topRight->move(x, y);
        bottomLeft->move(x, y);
        bottomRight->move(x, y);
    }
    void rotate(double angle, double cx, double cy) {
        topLeft->rotate(angle, cx, cy);
        topRight->rotate(angle, cx, cy);
        bottomLeft->rotate(angle, cx, cy);
        bottomRight->rotate(angle, cx, cy);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    ConcretePoint* p1 = new ConcretePoint(1, 1);

    
    Square* square = new Square(p1, 4);
    std::cout << "Square:" << std::endl;
    square->draw();
    square->move(0, 0);
    square->draw();
    square->rotate(45, p1->getX(), p1->getY());
    square->draw();
    std::cout << std::endl;

   
    Rhombus* rhombus = new Rhombus(p1, 4);
    std::cout << "Rhombus:" << std::endl;
    rhombus->draw();
    rhombus->move(2, 2);
    rhombus->draw();
    rhombus->rotate(45, p1->getX(), p1->getY());
    rhombus->draw();
    std::cout << std::endl;

 
    ConcretePoint* p11 = new ConcretePoint(2, 3);
    ConcretePoint* p2 = new ConcretePoint(6, 3);
    ConcretePoint* p3 = new ConcretePoint(1, 1);
    ConcretePoint* p4 = new ConcretePoint(5, 1);
    Parallelogram* parallelogram = new Parallelogram(p11, p2, p3, p4);
    std::cout << "Parallelogram:" << std::endl;
    parallelogram->draw();
    parallelogram->move(0, 0);
    parallelogram->draw();
    parallelogram->rotate(90, p11->getX(), p11->getY());
    parallelogram->draw();
    std::cout << std::endl;

 
    delete p1;
    delete square;
    delete rhombus;
    delete parallelogram;

    return 0;
}
