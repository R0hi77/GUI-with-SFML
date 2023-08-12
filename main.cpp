#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Menu
{
public:
    Menu(float width,float height);
    void Draw(RenderWindow &window);
    void moveUp();
    void moveDown();
    int getPressedItem();
   void playMusic(Music &music);


private:
    Image image;
    Texture texture;
    Sprite sprite;
    Font font;
    Music music;
    Text listItems[4];
    int selectionIndex=0;
    Color color=Color(36,179,20);
};
Menu::Menu(float width,float height)
{

    if(!font.loadFromFile("AmaticSC-Regular.ttf"))
    {
        cout<<"Unable to load"<<endl;
    }


    listItems[0].setFont(font);
    listItems[0].setColor(color);
    listItems[0].setString("BUBBlE SORT");
    listItems[0].setPosition(width/2.4,height/5*1);
    listItems[0].setCharacterSize(50);

    listItems[1].setFont(font);
    listItems[1].setColor(Color::White);
    listItems[1].setString("SElECTION SORT");
    listItems[1].setPosition(width/2.4,height/5*2);
    listItems[1].setCharacterSize(50);

    listItems[2].setFont(font);
    listItems[2].setColor(Color::White);
    listItems[2].setString("INSERTION SORT");
    listItems[2].setPosition(width/2.4,height/5*3);
    listItems[2].setCharacterSize(50);

    listItems[3].setFont(font);
    listItems[3].setColor(Color::White);
    listItems[3].setString("QUIT");
    listItems[3].setPosition(width/2.4,height/5*4);
    listItems[3].setCharacterSize(50);


    image.create(width,height,Color(203,185,60));
    texture.loadFromImage(image);
    sprite.setTexture(texture);

}
void Menu::Draw(RenderWindow &window)
{
    window.draw(sprite);
    for(int i=0;i<4;i++)
        window.draw(listItems[i]);
}
void Menu::moveUp()
{
    if(selectionIndex-1>=0)
    {
        listItems[selectionIndex].setColor(Color::White);
        selectionIndex--;
        listItems[selectionIndex].setColor(color);
    }
}
void Menu::moveDown()
{
    if(selectionIndex+1<4)
    {
        listItems[selectionIndex].setColor(Color::White);
        selectionIndex++;
        listItems[selectionIndex].setColor(color);
    }
}
int Menu::getPressedItem()
{
    return selectionIndex;
}

void Menu::playMusic(Music &music)
{
    if (!music.openFromFile("pain in m4a.ogg"))
        {
            cout<<"music could not load"<<endl;

        }

    music.setVolume(80);
    music.setLoop(true);

    music.play();
}

int main()
{
    RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");

    Menu menu(window.getSize().x,window.getSize().y);
    Music music;
    if(!music.openFromFile("m4a to ogg.ogg"))
        cout<<"not playing"<<endl;
    music.play();



    while (window.isOpen())
    {

        menu.playMusic(music);

        Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case Event::Closed:
                window.close();
                break;

            case Event::KeyReleased:
                switch(event.key.code)
                {
                    case Keyboard::Up:
                        menu.moveUp();
                        break;
                    case Keyboard::Down:
                        menu.moveDown();
                        break;
                    case Keyboard::Return:
                        switch(menu.getPressedItem())
                        {
                        case 0:
                            cout<<"BUBBLE SORT"<<endl;
                            break;
                        case 1:
                            cout<<"SELECTION SORT"<<endl;
                            break;
                        case 2:
                            cout<<"INSERTION SORT"<<endl;
                            break;
                        case 3:
                            window.close();
                            break;
                        }
                }
                break;

            }

        }

        window.clear();
        menu.Draw(window);
        window.display();
    }

    return 0;
}
