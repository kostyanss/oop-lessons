#include <iostream>

class DigitalCounter {
private:
    int minVal;
    int maxVal;
    int currentVal;

public:
    // Конструктор з ініціалізацією меж та початкового значення
    DigitalCounter(int min, int max) : minVal(min), maxVal(max), currentVal(min) {
        if (minVal > maxVal) {
            std::swap(minVal, maxVal);
        }
    }

    // Збільшення значення на 1 із логікою скидання (wrap-around)
    void increment() {
        if (currentVal >= maxVal) {
            currentVal = minVal; // Скидання у початковий мінімум
        } else {
            currentVal++;
        }
    }

    // Повернення поточного значення
    int getValue() const {
        return currentVal;
    }

    // Можливість динамічно змінити межі лічильника
    void setRange(int min, int max) {
        minVal = min;
        maxVal = max;
        if (minVal > maxVal) std::swap(minVal, maxVal);
        
        // Якщо поточне значення вилетіло за нові межі — скидаємо його
        if (currentVal < minVal || currentVal > maxVal) {
            currentVal = minVal;
        }
    }
};

int main() {
    // Створюємо лічильник з діапазоном від 0 до 2 (наприклад, для індексів)
    DigitalCounter counter(0, 2);

    // Демонстрація роботи циклічного переповнення
    for (int i = 0; i < 5; ++i) {
        std::cout << "Значення: " << counter.getValue() << "\n";
        counter.increment();
    }

    return 0;
}
