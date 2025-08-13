#include <SFML/Graphics.hpp>
#include "LinkedList.h"  // core logic

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Linked List Visualization");

    // Initialize font
    sf::Font font("../assets/ARIAL.TTF");

    // Create your LinkedList object
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::White);

        // Draw nodes (visual representation of LinkedList)
        float x = 50;
        for (auto node = list.getHead(); node != nullptr; node = node->next) {
            sf::RectangleShape box(sf::Vector2f(60, 40));
            box.setFillColor(sf::Color::Blue);
            box.setPosition({x, 200});
            window.draw(box);

            sf::Text text(font);
            text.setString(std::to_string(node->data));
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Red);
            text.setPosition({x + 15, 21});
            window.draw(text);

            x += 80;
        }

        window.display();
    }

    return 0;
}
