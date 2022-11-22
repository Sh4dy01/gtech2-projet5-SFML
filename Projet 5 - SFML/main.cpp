#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

constexpr auto WINDOW_WIDTH = 1920;
constexpr auto WINDOW_HEIGHT = 1080;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pokemon : Origins");
    sf::Texture texture;
    if (!texture.loadFromFile("Assets/Images/pokemon-title.png"))
        return EXIT_FAILURE;
    sf::Sprite s_title;
    texture.setSmooth(false);

    float s_title_o = 0.0f;
    float s_origins_o = 0.0f;
    s_title.setTexture(texture);
    s_title.setColor(sf::Color(0, 0, 0, 0));
    s_title.setPosition(WINDOW_WIDTH / 2 - s_title.getLocalBounds().width/2, -s_title.getLocalBounds().height);

    sf::Font font;
    if (!font.loadFromFile("Assets/Fonts/Pokemon-Classic.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Origins", font, 50);
    text.setPosition(WINDOW_WIDTH / 2 - text.getLocalBounds().width/2, s_title.getLocalBounds().height);
    text.setFillColor(sf::Color(0, 0, 0, 0));
 

    sf::Clock clock;

    // Load a music to play
    /*sf::Music music;
    if (!music.openFromFile("nice_music.ogg"))
        return EXIT_FAILURE;*/
    //music.play();
    // 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        if (s_title.getPosition().y < 0)
        {
            s_title.move(0, 0.1f);
        }
        if (s_title_o < 255)
        {
            s_title.setColor(sf::Color(255, 255, 255, s_title_o));
            s_title_o += 0.05f;
        }
        else if (s_origins_o < 255) {
            text.setFillColor(sf::Color(255, 255, 255, s_origins_o));
            s_origins_o += 0.05f;
        }

        window.clear();
        window.draw(s_title);
        window.draw(text);
        window.display();
    }

    return EXIT_SUCCESS;
}
