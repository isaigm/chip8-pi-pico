#include "chip8.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 320), "chip 8");
    sf::Uint8 *pixels = new sf::Uint8[64 * 32 * 4];
    sf::Texture texture;
    sf::Sprite sprite;
    texture.create(64, 32);
    sprite.setScale(10, 10);
    sprite.setTexture(texture);
    window.setVerticalSyncEnabled(true);
    srand(time(nullptr));
    chip8 ch8("c8games/PONG");
    while (window.isOpen())
    {
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }
        if (ch8.wait_key == -1)
        {
            ch8.execute();
        }
        else
        {
            for (int k = 0; k < 16; k++)
            {
                if (sf::Keyboard::isKeyPressed(keys[k]))
                {
                    ch8.v[ch8.wait_key] = k;
                    ch8.wait_key = -1;
                    break;
                }
            }
        }
        if (ch8.dt)
        {
            ch8.dt--;
        }
        if (ch8.draw_flag)
        {
            ch8.draw(pixels);
            texture.update(pixels);
            ch8.draw_flag = false;
            window.clear();
            window.draw(sprite);
            window.display();
        }
    }
    return 0;
}