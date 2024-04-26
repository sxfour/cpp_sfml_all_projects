#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>

float clamp(float value, float minn, float maxx) {
    if (value < minn) {
        return minn;
    }
    else if (value > maxx) {
        return maxx;
    }
    else {
        return value;
    }
}

// Функция проверки на столкновение обьектов
int checkCollision(sf::RectangleShape& R1, sf::CircleShape& C1) {
    float closestX = clamp(C1.getPosition().x, R1.getPosition().x, R1.getPosition().x + R1.getSize().x);
    float closestY = clamp(C1.getPosition().y, R1.getPosition().y, R1.getPosition().y + R1.getSize().y);

    float distanceX = C1.getPosition().x - closestX;
    float distanceY = C1.getPosition().y - closestY;

    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
    if (distanceSquared < C1.getRadius() * C1.getRadius() && closestX != C1.getPosition().x && closestY != C1.getPosition().y) {
        return 3;
    }
    else if (distanceSquared < C1.getRadius() * C1.getRadius() && closestX == C1.getPosition().x) {
        return 2;
    }
    else if (distanceSquared < C1.getRadius() * C1.getRadius() && closestY == C1.getPosition().y) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "", sf::Style::Close);

    // Инициализация ImGui.
    ImGui::SFML::Init(window);

    bool circleExists = true, circleExist2 = true;
    float color[3] = { 0.f, 0.f, 0.f };
    char windowTitle[255] = "SFML_Collision_Template";
    float circleRadius = 20.0f;
    int circleSegment = 20;
    float circleColor[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255 };
    float xstep = 0.25;
    float ystep = 0.25;

    // Круг
    sf::CircleShape shape(circleRadius, circleSegment);
    shape.setOrigin(circleRadius, circleRadius);
    shape.setPosition(50, 50);
    shape.setFillColor(sf::Color
    (
        (int)(circleColor[0] * 255),
        (int)(circleColor[1] * 255),
        (int)(circleColor[2] * 255)
    ));

    // Квадрат
    sf::RectangleShape rshape;
    rshape.setSize(sf::Vector2f(100, 100));
    rshape.setPosition(300, 300);
    rshape.setFillColor(sf::Color::Yellow);

    window.setTitle(windowTitle);

    // Цвет заднего фона
    sf::Color bgColor;

    // Инициализация времени для ImGui.
    sf::Clock deltaClock;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            // Создаём событие для ImGui.
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            switch (event.type) {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) { window.close(); }
            }
            
        }

        // Границы игровой области
        if ((shape.getPosition().x > 800 - circleRadius) || (shape.getPosition().x < circleRadius)) {
            xstep = -xstep;
        }
        else if ((shape.getPosition().y > 600 - circleRadius) || (shape.getPosition().y < circleRadius)) {
            ystep = -ystep;
        } 

        // Границы столкновения обьектов
        if (checkCollision(rshape, shape) == 1) {
            xstep = -xstep;
        }
        else if (checkCollision(rshape, shape) == 2) {
            ystep = -ystep;
        }
        else if (checkCollision(rshape, shape) == 3) {
            xstep = -xstep;
            ystep = -ystep;
        }

        // Движение шара
        shape.move(xstep, ystep);

        // Обновляем окно и время ImGui.
        ImGui::SFML::Update(window, deltaClock.restart());
        
        // Создаем окно и параметры ImGui.
        ImGui::Begin("Circle editor");
        ImGui::Text("Editor Tool");
        ImGui::Checkbox("Shape", &circleExists);
        ImGui::SliderFloat("Radius", &circleRadius, 5.0f, 60.0f);
        ImGui::SliderFloat("Speed X", &xstep, 0.25f, 5.0f);
        ImGui::SliderFloat("Speed Y", &ystep, 0.25f, 5.0f);
        ImGui::SliderInt("PointCount", &circleSegment, 4, 100);
        ImGui::ColorEdit3("ColorEdi3", circleColor);
        if (ImGui::Button("Update position")) {
            shape.setPosition(sf::Vector2f(100, 100));
        }
        ImGui::End();

        // Создаем второе окно и параметры.
        ImGui::Begin("Background");
        if (ImGui::ColorEdit3("Color map", color)) {
            bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
        }
        ImGui::InputText("Title", windowTitle, 255);
        if (ImGui::Button("Update window title")) {
            window.setTitle(windowTitle);
        }
        ImGui::End();


        shape.setRadius(circleRadius);
        shape.setOrigin(circleRadius, circleRadius);
        shape.setPointCount(circleSegment);
        shape.setFillColor(sf::Color
        (
            (int)(circleColor[0] * 255),
            (int)(circleColor[1] * 255),
            (int)(circleColor[2] * 255)
        ));
        
        window.clear(bgColor);

        if (circleExists) {
            window.draw(shape);
            window.draw(rshape);
        }

        // Отрисовка ImGui окна.
        ImGui::SFML::Render(window);

        window.display();
    }

    // Закрытие ImGui.
    ImGui::SFML::Shutdown();

    return EXIT_SUCCESS;
}