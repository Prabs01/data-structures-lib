#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");

    sf::Texture texture("../assets/grass.jpg");

    sf::Sprite sprite(texture);
    //sprite.setTextureRect(sf::IntRect({10,10},{32,32}));
    sprite.setScale({0.2f,0.2f});
    //sprite.setColor(sf::Color(0,255,0));
    //sprite.setColor(sf::Color(255,255,255,128));

    sf::Font font("../assets/arial.ttf");

    sf::Text text(font);
    text.setString("Hello world");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.move({100.0f,300.0f});

    sf::CircleShape circle(50.0f);
    circle.setFillColor(sf::Color(100,255,20));
    circle.move({300.0f,300.0f});
    circle.setOutlineThickness(10.f);
    circle.setOutlineColor(sf::Color(250,150,100));
    circle.setTexture(&texture);

    sf::RectangleShape rectangle({120.0f,50.f});
    rectangle.move({200.0f,10.0f});
    rectangle.setFillColor(sf::Color(100,200,255));

    sf::CircleShape triangle(80.f,3);
    triangle.setPosition({300.0f,100.0f});

    sf::CircleShape square(80.f,4);
    square.setPosition({450.0f,100.0f});

    sf::CircleShape hexagon(80.f,8);
    hexagon.setPosition({600.0f,100.0f});
    
   
    while (window.isOpen())
    {
        
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(sprite);
        window.draw(text);
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);
        window.draw(square);
        window.draw(hexagon);

        window.display();
    }

    return 0;
}
