#include <iostream>

// Абстрактний базовий клас
class Figure {
protected:
    double centerX, centerY; // Координати центра
    double rotationAngle;    // Кут повороту (в градусах)
    double scaleFactor;      // Масштабний фактор

public:
    Figure(double x, double y, double angle, double scale)
        : centerX(x), centerY(y), rotationAngle(angle), scaleFactor(scale) {}

    // Віртуальний деструктор для коректного очищення пам'яті похідних класів
    virtual ~Figure() = default;

    // Чисто віртуальні функції (роблять клас абстрактним)
    virtual void draw() = 0;
    virtual void hide() = 0;

    // Конкретні методи для зміни стану фігури
    void rotate(double degrees) {
        rotationAngle += degrees;
    }

    void move(double dx, double dy) {
        centerX += dx;
        centerY += dy;
    }
};

// Похідний клас: Трикутник
class Triangle : public Figure {
public:
    using Figure::Figure; // Успадкування конструктора базового класу

    void draw() override {
        std::cout << "[Екран] Відображено ТРИКУТНИК. Центр: (" << centerX << ", " << centerY 
                  << "), Кут: " << rotationAngle << "°, Масштаб: " << scaleFactor << "\n";
    }

    void hide() override {
        std::cout << "[Екран] Трикутник сховано (став невидимим).\n";
    }
};

// Похідний клас: Чотирикутник
class Quadrilateral : public Figure {
public:
    using Figure::Figure;

    void draw() override {
        std::cout << "[Екран] Відображено ЧОТИРИКУТНИК. Центр: (" << centerX << ", " << centerY 
                  << "), Кут: " << rotationAngle << "°, Масштаб: " << scaleFactor << "\n";
    }

    void hide() override {
        std::cout << "[Екран] Чотирикутник сховано.\n";
    }
};

// Похідний клас: Многокутник
class Polygon : public Figure {
public:
    using Figure::Figure;

    void draw() override {
        std::cout << "[Екран] Відображено МНОГОКУТНИК. Центр: (" << centerX << ", " << centerY 
                  << "), Кут: " << rotationAngle << "°, Масштаб: " << scaleFactor << "\n";
    }

    void hide() override {
        std::cout << "[Екран] Многокутник сховано.\n";
    }
};

int main() {
    const int size = 3;
    // Масив вказівників на абстрактний базовий клас
    Figure* shapes[size];

    // Ініціалізація об'єктами похідних класів
    shapes[0] = new Triangle(0.0, 0.0, 0.0, 1.0);
    shapes[1] = new Quadrilateral(10.5, -5.0, 45.0, 1.5);
    shapes[2] = new Polygon(-3.2, 4.8, 90.0, 2.0);

    std::cout << "=== Демонстрація пізнього зв'язування ===\n\n";

    for (int i = 0; i < size; ++i) {
        // Виклик віртуальних методів через вказівник базового класу
        shapes[i]->draw();       
        shapes[i]->move(5.0, 5.0);   // Зміна координат
        shapes[i]->rotate(15.0);     // Зміна кута повороту
        shapes[i]->draw();           // Повторне відображення зміненого об'єкта
        shapes[i]->hide();       
        std::cout << "---------------------------------------\n";
    }

    // Очищення виділеної динамічної пам'яті
    for (int i = 0; i < size; ++i) {
        delete shapes[i];
    }

    return 0;
}
