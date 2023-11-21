#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

struct Point {
    double x;
    double y;

    Point(double _x, double _y) : x(_x), y(_y) {}
};

double manhattanLength(Point p1, Point p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

void displayParetoGraph(std::vector<Point>& paretoSet, Point utopyPoint, std::vector<std::string> alternative) {
    sf::RenderWindow window(sf::VideoMode(850, 850), "Pareto Set");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        
        window.clear(sf::Color::White);


        sf::Font font;
        font.loadFromFile("D:/Labs/MO4/ArialRegular.ttf");
        sf::Vertex xAxis[] =
        {
            sf::Vertex(sf::Vector2f(50, 810), sf::Color::Black),
            sf::Vertex(sf::Vector2f(700, 810), sf::Color::Black)
        };

        sf::Vertex yAxis[] =
        {
            sf::Vertex(sf::Vector2f(50, 810), sf::Color::Black),
            sf::Vertex(sf::Vector2f(50, 250), sf::Color::Black)
        };
        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);

        sf::Text axisXText;
        axisXText.setFont(font);
        axisXText.setCharacterSize(16);
        axisXText.setFillColor(sf::Color::Black);
        axisXText.setString("Appearance");
        axisXText.setPosition(600, 800 - axisXText.getLocalBounds().height);

        sf::Text axisYText;
        axisYText.setFont(font);
        axisYText.setCharacterSize(16);
        axisYText.setFillColor(sf::Color::Black);
        axisYText.setString("Character");
        axisYText.setRotation(0);
        axisYText.setPosition(0, 200);

        window.draw(axisXText);
        window.draw(axisYText);

        for (int i = 0; i < paretoSet.size(); ++i) {
            sf::CircleShape pointCircle(8.f);
            pointCircle.setFillColor(sf::Color::Blue);
            pointCircle.setPosition(paretoSet[i].x, paretoSet[i].y);
            window.draw(pointCircle);

            sf::Text pointLabel;
            pointLabel.setFont(font);
            pointLabel.setCharacterSize(12);
            pointLabel.setFillColor(sf::Color::Black);
            pointLabel.setString(alternative[i]);
            pointLabel.setPosition(paretoSet[i].x, paretoSet[i].y - 20);
            window.draw(pointLabel);
        }

        sf::CircleShape utopyCircle(8.f);
        utopyCircle.setFillColor(sf::Color::Red);
        utopyCircle.setPosition(utopyPoint.x, utopyPoint.y);
        window.draw(utopyCircle);
        sf::Text text;
        text.setFont(font);
        text.setString("Utopia");
        text.setCharacterSize(12);
        text.setFillColor(sf::Color::Black);
        text.setPosition(utopyPoint.x + 10, utopyPoint.y - 10);
        window.draw(text);


        for (const auto& point : paretoSet) {
            sf::CircleShape pointCircle(8.f);
            pointCircle.setFillColor(sf::Color::Blue);
            pointCircle.setPosition(point.x, point.y);
            window.draw(pointCircle);
        }

        window.display();
    }
}

std::string runPareto(std::vector<std::vector<double>>& A,
    std::vector<std::string>& alternative, int ind1, int ind2) {
    Point utopyPoint(500, 300);
    

    std::vector<Point> paretoSet;
    for (const auto& row : A) {
        Point P(row[ind1], row[ind2]);
        paretoSet.push_back(P);
    }
    std::cout << "Множество Парето: ";
    for (const auto& p : paretoSet) {
        std::cout << "(" << p.x << ", " << p.y << ") ";
    }
    std::cout << std::endl;

    displayParetoGraph(paretoSet, utopyPoint, alternative);

    Point bestPoint = paretoSet[0];
    for (const auto& point : paretoSet) {
        if (manhattanLength(utopyPoint, point) < manhattanLength(utopyPoint, bestPoint)) {
            bestPoint = point;
        }
    }

    int index = 0;
    for (int i = 0; i < A.size(); i++) {
        if (A[i][ind1] == bestPoint.x && A[i][ind2] == bestPoint.y) {
            index = i;
        }
    }

    return alternative[index];
}
int main() {
    std::vector<std::string> alternative = { "Tatyana", "Larisa", "Natalya", "Olga" };

    std::vector<std::vector<double>> A = {
    {400.f, 500.f},
    {500.f, 400.f},
    {300.f, 500.f},
    {300.f, 600.f}
    };
    
    std::string result = runPareto(A, alternative, 0, 1);
    std::cout << "Result: " << result;
    return 0;
}

