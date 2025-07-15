#include "chip8.h"
#include <chrono>
#include <thread>
int main()
{
    sf::RenderWindow window(sf::VideoMode({640, 320}), "chip 8");
    uint8_t *pixels = new uint8_t[64 * 32 * 4];
    sf::Texture texture({64, 32});
    sf::Sprite sprite(texture);
    sprite.setScale({10, 10});
    sprite.setTexture(texture);
    window.setVerticalSyncEnabled(true);
    srand(time(nullptr));
    chip8 ch8("c8games/INVADERS");
    auto last_cycle_time = std::chrono::high_resolution_clock::now();
    while (window.isOpen())
    {
        auto current_time = std::chrono::high_resolution_clock::now();
        float dt_chrono = std::chrono::duration<float, std::chrono::milliseconds::period>(current_time - last_cycle_time).count();
        if (dt_chrono > 1000.0f / 60.0f) // 60 Hz update
        {
            last_cycle_time = current_time;
            while (auto ev = window.pollEvent())
            {
                if (ev->is<sf::Event::Closed>())
                {
                    window.close();
                    break;
                }
            }
            if (ch8.wait_key == -1)
            {
                for (int i = 0; i < 15; ++i) // Execute 15 CPU cycles per frame 
                {
                    ch8.execute();
                }
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
            ch8.update_timers(); // New method to update timers
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Small sleep to prevent busy-waiting
    }
    delete [] pixels;
    return 0;
}