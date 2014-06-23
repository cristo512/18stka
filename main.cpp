#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <cstdlib>
#define SFML_STATIC
#include <SFML/Network.hpp>

using namespace std;

bool enable = true;
bool choose=0;

void waiting()
{
    sf::Http http("http://www.bezludnawyspa.cba.pl/");
    sf::Http::Request request;
    request.setUri("/shutdown");
    sf::Http::Response resp;
    std::string response;
    bool sleeping=true;
    while(sleeping)
    {
        resp = http.sendRequest(request);

        if(resp.getStatus() == sf::Http::Response::Ok && enable)
        {
            response = resp.getBody();
            if(response == "1")
            {
                sleeping = false;
                enable = false;
            }
        }
        if(response!="1")
            sf::sleep(sf::seconds(3.f));
    }
}

void checkEvent(sf::Event &event, sf::RenderWindow &window, sf::Mouse &mouse)
{
    if(event.type==sf::Event::Closed)
        window.close();

    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }
    }
    if(event.type==sf::Event::MouseButtonPressed)
    {
        //choose=!choose;
    }
}


int main()
{
    waiting();

    sf::VideoMode DesktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(DesktopMode.width, DesktopMode.height), "Zaproszenie", sf::Style::Fullscreen);
    sf::Texture background_texture;
    sf::Sprite background;
    sf::RectangleShape prostokat(sf::Vector2f((1520*window.getSize().x)/1920,(920*window.getSize().y)/1080));
    prostokat.setPosition((200*window.getSize().x)/1920,(80*window.getSize().x)/1920);
    sf::Color color(0,0,0,180);
    prostokat.setFillColor(color);
    sf::Font czcionka;
    if(!czcionka.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
        return -1;
    if(!background_texture.loadFromFile("./data/tlo.jpg"))
        return -2;
    sf::Text text[5];
    float scale, bg_scale;
    float scale_x = window.getSize().x/1920.f;
    float scale_y = window.getSize().y/1080.f;
    scale = scale_x;
    if(scale_x>scale_y)
        bg_scale = scale_x;
    else
        bg_scale = scale_y;

    background.setTexture(background_texture);
    background.setPosition(0,0);
    background.setScale(bg_scale,bg_scale);
    text[0].setString(L"Zapraszam Was");    // Cię");
    text[1].setString(L"Tomku, Marzenko i Kamilku");    //IMIE");
    text[2].setString(L"Na moją 18-stkę, która");
    text[3].setString(L"odbędzie się 19 lipca.");    //[chyba] 2 sierpnia.");
    text[4].setString(L"Krystian Jabłoński :)");
    for(int i=0;i<5;i++)
    {
         text[i].setColor(sf::Color::Yellow);
         text[i].setFont(czcionka);
         text[i].setCharacterSize(92);
         text[i].setScale(scale,scale);
         text[i].setPosition((window.getSize().x-text[i].getGlobalBounds().width)/2, 70+i*(text[0].getGlobalBounds().height+(window.getSize().x*100.f)/1920.f));
    }
    text[3].move(0,-1*((window.getSize().x*70.f)/1920.f));
    text[4].setPosition( ((window.getSize().x-text[4].getGlobalBounds().width)/4)*3 , text[4].getPosition().y);
    sf::Event event;
    sf::Mouse mouse;
    window.setFramerateLimit(60);
    while(window.isOpen())
    {
        window.clear(sf::Color::Blue);
        while(window.pollEvent(event))
        {
            checkEvent(event, window, mouse);
        }
        switch(choose)
        {
            case 0:
            {
                window.draw(background);
                window.draw(prostokat);
                for(int i=0;i<5;i++)
                {
                    window.draw(text[i]);
                }
                break;
            }
            case 1:
            {

            }
        }

        window.display();

    }
    return 0;
}
