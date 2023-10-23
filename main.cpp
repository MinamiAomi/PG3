#include <iostream>
#include <numbers>


class Shape {
public:
    Shape() {}
    virtual ~Shape() {}

    virtual void PrintInfo();

protected:
    // 面積
    float m_area;
};

class Circle :
    public Shape {
public:
    Circle(float radius);
    void PrintInfo() override;
    
private:
    // 半径
    float m_radius;
};

class Triangle :
    public Shape {
public:
    Triangle(float base, float height);
    void PrintInfo() override;

private:
    // 底辺
    float m_base;
    // 高さ
    float m_height;
};

class Rectangle :
    public Shape {
public:
    Rectangle(float width, float height);
    void PrintInfo() override;

private:
    // 幅
    float m_width;
    // 高さ
    float m_height;

};

int main() {
    // 図形
    Shape* shapes[]{
        new Circle(5.0f),
        new Triangle(5.0f, 3.0f),
        new Rectangle(5.0f, 2.0f)
    };

    for (Shape* shape : shapes) {
        shape->PrintInfo();
        std::cout << std::endl;
    }

    for (Shape*& shape : shapes) {
        delete shape;
        shape = nullptr;
    }


    std::cout << std::endl << "このプログラムは終了しました。" << std::endl;

    (void)std::getchar();
    return 0;
}

void Shape::PrintInfo() {
    std::cout << "面積 : " << m_area << std::endl;
}

Circle::Circle(float radius) {
    m_radius = radius;
    m_area = radius * radius * std::numbers::pi_v<float>;
}

void Circle::PrintInfo() {
    std::cout << "円" << std::endl;
    std::cout << "半径 : " << m_radius << std::endl;
    Shape::PrintInfo();
}

Triangle::Triangle(float base, float height) {
    m_base = base;
    m_height = height;
    m_area = base * height * 0.5f;
}

void Triangle::PrintInfo() {
    std::cout << "三角形" << std::endl;
    std::cout << "底辺 : " << m_base << std::endl;
    std::cout << "高さ : " << m_height << std::endl;
    Shape::PrintInfo();
}

Rectangle::Rectangle(float width, float height) {
    m_width = width;
    m_height = height;
    m_area = width * height;
}

void Rectangle::PrintInfo() {
    std::cout << "長方形" << std::endl;
    std::cout << "横　 : " << m_width << std::endl;
    std::cout << "高さ : " << m_height << std::endl;
    Shape::PrintInfo();
}
