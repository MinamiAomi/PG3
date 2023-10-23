#include <iostream>
#include <numbers>

class IShape {
public:
    virtual ~IShape() {}
    virtual void Size() = 0;
    virtual void Draw() = 0;
};

class Circle :
    public IShape {
public:
    Circle(float radius);

    void Size() override;
    void Draw() override;

private:
    float m_size;
    float m_radius;
};

class Rectangle :
    public IShape {
public:
    Rectangle(float width, float height);

    void Size() override;
    void Draw() override;

private:
    float m_size;
    float m_width;
    float m_height;
};

int main() {

    IShape* shapes[]{
        new Circle(10.0f),
        new Rectangle(5.0f, 3.0f)
    };

    for (IShape* shape : shapes) {
        shape->Size();
        shape->Draw();
        std::cout << std::endl;
    }

    for (IShape*& shape : shapes) {
        delete shape;
        shape = nullptr;
    }

    std::cout << std::endl << "このプログラムは終了しました。" << std::endl;

    (void)std::getchar();
    return 0;
}

Circle::Circle(float radius) {
    m_radius = radius;
}

void Circle::Size() {
    m_size = m_radius * m_radius * std::numbers::pi_v<float>;
}

void Circle::Draw() {
    std::cout << "円" << std::endl;
    std::cout << "半径 : " << m_radius << std::endl;
    std::cout << "面積 : " << m_size << std::endl;
}

Rectangle::Rectangle(float width, float height) {
    m_width = width;
    m_height = height;
}

void Rectangle::Size() {
    m_size = m_width * m_height;
}

void Rectangle::Draw() {
    std::cout << "矩形" << std::endl;
    std::cout << "幅　 : " << m_width << std::endl;
    std::cout << "高さ : " << m_height << std::endl;
    std::cout << "面積 : " << m_size << std::endl;
}
