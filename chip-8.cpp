#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <functional>
#include <SFML/Graphics.hpp>
#include <map>

uint8_t fontset[80] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};
sf::Keyboard::Key keys[] =
    {
        sf::Keyboard::X,
        sf::Keyboard::Num1,
        sf::Keyboard::Num2,
        sf::Keyboard::Num3,
        sf::Keyboard::Q,
        sf::Keyboard::W,
        sf::Keyboard::E,
        sf::Keyboard::A,
        sf::Keyboard::S,
        sf::Keyboard::D,
        sf::Keyboard::Z,
        sf::Keyboard::C,
        sf::Keyboard::Num4,
        sf::Keyboard::R,
        sf::Keyboard::F,
        sf::Keyboard::V

};
class chip8
{
public:
    chip8(const std::string path);
    uint8_t get_x(uint16_t);
    uint8_t get_y(uint16_t);
    void execute();
    void draw(sf::RenderTarget &window, sf::Uint8 *pixels, sf::Texture &texture, sf::Sprite &sprite);
    void i_0xee();
    void i_1nnn(uint16_t);
    void i_2nnn(uint16_t);
    void i_3xkk(uint16_t);
    void i_4xkk(uint16_t);
    void i_5xy0(uint16_t);
    void i_6xkk(uint16_t);
    void i_7xkk(uint16_t);
    void i_8xy0(uint16_t);
    void i_8xy1(uint16_t);
    void i_8xy2(uint16_t);
    void i_8xy3(uint16_t);
    void i_8xy4(uint16_t);
    void i_8xy5(uint16_t);
    void i_8xy6(uint16_t);
    void i_8xy7(uint16_t);
    void i_8xye(uint16_t);
    void i_9xy0(uint16_t);
    void i_annn(uint16_t);
    void i_bnnn(uint16_t);
    void i_cxkk(uint16_t);
    void i_dxyn(uint16_t);
    void i_ex9e(uint16_t);
    void i_exa1(uint16_t);

    void i_fx07(uint16_t);
    void i_fx0a(uint16_t);
    void i_fx15(uint16_t);
    void i_fx1e(uint16_t);
    void i_fx29(uint16_t);
    void i_fx33(uint16_t);
    void i_fx55(uint16_t);
    void i_fx65(uint16_t);
    bool draw_flag = true;
    char wait_key = -1;

    uint8_t dt, st;
    uint8_t v[16];

private:
    void clear_screen();
    bool update_pc = true;
    uint8_t ram[4096];
    uint16_t stack[16];
    uint16_t pc, sp;
    uint16_t I;
    uint8_t gfx[32][64];
    std::map<uint16_t, std::function<void(uint16_t)>> opcodes;
};
chip8::chip8(const std::string path)
{
    std::ifstream rom(path);
    rom.seekg(0, std::ios::end);
    size_t length = rom.tellg();
    rom.seekg(0, std::ios::beg);
    rom.read((char *)(ram + 512), length);
    for (int i = 0; i < 80; i++)
    {
        ram[i + 0x50] = fontset[i];
    }
    for (int i = 0; i < 16; i++)
    {
        v[i] = 0;
        stack[i] = 0;
    }
    clear_screen();
    dt = 0;
    pc = 512;
    sp = 0;
    I = 0;
    opcodes[0x1] = std::bind(&chip8::i_1nnn, this, std::placeholders::_1);
    opcodes[0x2] = std::bind(&chip8::i_2nnn, this, std::placeholders::_1);
    opcodes[0x3] = std::bind(&chip8::i_3xkk, this, std::placeholders::_1);
    opcodes[0x4] = std::bind(&chip8::i_4xkk, this, std::placeholders::_1);
    opcodes[0x5] = std::bind(&chip8::i_5xy0, this, std::placeholders::_1);
    opcodes[0x6] = std::bind(&chip8::i_6xkk, this, std::placeholders::_1);
    opcodes[0x7] = std::bind(&chip8::i_7xkk, this, std::placeholders::_1);
    opcodes[0x80] = std::bind(&chip8::i_8xy0, this, std::placeholders::_1);
    opcodes[0x81] = std::bind(&chip8::i_8xy1, this, std::placeholders::_1);
    opcodes[0x82] = std::bind(&chip8::i_8xy2, this, std::placeholders::_1);
    opcodes[0x83] = std::bind(&chip8::i_8xy3, this, std::placeholders::_1);
    opcodes[0x84] = std::bind(&chip8::i_8xy4, this, std::placeholders::_1);
    opcodes[0x85] = std::bind(&chip8::i_8xy5, this, std::placeholders::_1);
    opcodes[0x86] = std::bind(&chip8::i_8xy6, this, std::placeholders::_1);
    opcodes[0x87] = std::bind(&chip8::i_8xy7, this, std::placeholders::_1);
    opcodes[0x8E] = std::bind(&chip8::i_8xye, this, std::placeholders::_1);
    opcodes[0x9] = std::bind(&chip8::i_9xy0, this, std::placeholders::_1);
    opcodes[0xA] = std::bind(&chip8::i_annn, this, std::placeholders::_1);
    opcodes[0xB] = std::bind(&chip8::i_bnnn, this, std::placeholders::_1);
    opcodes[0xC] = std::bind(&chip8::i_cxkk, this, std::placeholders::_1);
    opcodes[0xD] = std::bind(&chip8::i_dxyn, this, std::placeholders::_1);
    opcodes[0x9E] = std::bind(&chip8::i_ex9e, this, std::placeholders::_1);
    opcodes[0xA1] = std::bind(&chip8::i_exa1, this, std::placeholders::_1);
    opcodes[0xF07] = std::bind(&chip8::i_fx07, this, std::placeholders::_1);
    opcodes[0xF0A] = std::bind(&chip8::i_fx0a, this, std::placeholders::_1);
    opcodes[0xF15] = std::bind(&chip8::i_fx15, this, std::placeholders::_1);
    opcodes[0xF1E] = std::bind(&chip8::i_fx1e, this, std::placeholders::_1);
    opcodes[0xF29] = std::bind(&chip8::i_fx29, this, std::placeholders::_1);
    opcodes[0xF33] = std::bind(&chip8::i_fx33, this, std::placeholders::_1);
    opcodes[0xF55] = std::bind(&chip8::i_fx55, this, std::placeholders::_1);
    opcodes[0xF65] = std::bind(&chip8::i_fx65, this, std::placeholders::_1);
}
void chip8::draw(sf::RenderTarget &window, sf::Uint8 *pixels, sf::Texture &texture, sf::Sprite &sprite)
{
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if (gfx[i][j] == 1)
            {
                pixels[(j + i * 64) * 4] = 255;
                pixels[(j + i * 64) * 4 + 1] = 255;
                pixels[(j + i * 64) * 4 + 2] = 255;
                pixels[(j + i * 64) * 4 + 3] = 255;
            }
            else
            {
                pixels[(j + i * 64) * 4] = 0;
                pixels[(j + i * 64) * 4 + 1] = 0;
                pixels[(j + i * 64) * 4 + 2] = 0;
                pixels[(j + i * 64) * 4 + 3] = 0;
            }
        }
    }
    texture.update(pixels);
    window.draw(sprite);
}
void chip8::clear_screen()
{
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            gfx[i][j] = 0;
        }
    }
}
uint8_t chip8::get_x(uint16_t opcode)
{
    return (opcode & 0xF00) >> 8;
}
uint8_t chip8::get_y(uint16_t opcode)
{
    return (opcode & 0xF0) >> 4;
}
void chip8::i_0xee()
{
    if (sp > 0)
    {
        sp--;
        pc = stack[sp];
    }
}
void chip8::i_1nnn(uint16_t opcode)
{
    pc = opcode & 0xFFF;
}
void chip8::i_2nnn(uint16_t opcode)
{
    stack[sp] = pc;
    sp++;
    pc = opcode & 0xFFF;
}
void chip8::i_3xkk(uint16_t opcode)
{
    if (v[get_x(opcode)] == (opcode & 0xFF))
    {
        pc = (pc + 2) & 0xFFF;
    }
}
void chip8::i_4xkk(uint16_t opcode)
{
    if (v[get_x(opcode)] != (opcode & 0xFF))
    {
        pc = (pc + 2) & 0xFFF;
    }
}
void chip8::i_5xy0(uint16_t opcode)
{
    if (v[get_x(opcode)] == v[get_y(opcode)])
    {
        pc = (pc + 2) & 0xFFF;
    }
}
void chip8::i_6xkk(uint16_t opcode)
{
    v[get_x(opcode)] = opcode & 0xFF;
}
void chip8::i_7xkk(uint16_t opcode)
{
    v[get_x(opcode)] += opcode & 0xFF;
}
void chip8::i_8xy0(uint16_t opcode)
{
    v[get_x(opcode)] = v[get_y(opcode)];
}
void chip8::i_8xy1(uint16_t opcode)
{
    v[get_x(opcode)] |= v[get_y(opcode)];
}
void chip8::i_8xy2(uint16_t opcode)
{
    v[get_x(opcode)] &= v[get_y(opcode)];
}
void chip8::i_8xy3(uint16_t opcode)
{
    v[get_x(opcode)] ^= v[get_y(opcode)];
}
void chip8::i_8xy4(uint16_t opcode)
{
    uint16_t sum = v[get_x(opcode)] + v[get_y(opcode)];
    v[0xF] = sum > 255;
    v[get_x(opcode)] = sum & 0xFF;
}
void chip8::i_8xy5(uint16_t opcode)
{
    v[0xF] = v[get_x(opcode)] > v[get_y(opcode)];
    v[get_x(opcode)] -= v[get_y(opcode)];
}
void chip8::i_8xy6(uint16_t opcode)
{
    v[0xF] = v[get_x(opcode)] & 1;
    v[get_x(opcode)] >>= 1;
}
void chip8::i_8xy7(uint16_t opcode)
{
    v[0xF] = v[get_y(opcode)] > v[get_x(opcode)];
    v[get_x(opcode)] = v[get_y(opcode)] - v[get_x(opcode)];
}
void chip8::i_8xye(uint16_t opcode)
{
    v[0xF] = (v[get_x(opcode)] & 0x80) >> 7;
    v[get_x(opcode)] <<= 1;
}
void chip8::i_9xy0(uint16_t opcode)
{
    if (v[get_x(opcode)] != v[get_y(opcode)])
    {
        pc = (pc + 2) & 0xFFF;
    }
}
void chip8::i_annn(uint16_t opcode)
{
    I = opcode & 0xFFF;
}
void chip8::i_bnnn(uint16_t opcode)
{
    pc = (opcode & 0xFFF) + v[0];
}
void chip8::i_cxkk(uint16_t opcode)
{
    uint8_t random_byte = rand() % 256;
    v[get_x(opcode)] = random_byte & (opcode & 0xFF);
}
void chip8::i_dxyn(uint16_t opcode)
{
   
    draw_flag = true;
    uint8_t x = v[get_x(opcode)];
    uint8_t y = v[get_y(opcode)];
    int rows = opcode & 0xF;
    v[0xF] = 0;
    for (int i = 0; i < rows; i++)
    {
        uint8_t sp_row = ram[I + i];
        for (int j = 0; j < 8; j++)
        {
            int pixel = (sp_row >> (7 - j)) & 1;
            if (pixel != 0)
            {
                if (gfx[(y + i) % 32][(x + j) % 64] == 1)
                {
                    v[0xF] = 1;
                }
                gfx[(y + i) % 32][(x + j) % 64] ^= 1;
            }
        }
    }
}
void chip8::i_ex9e(uint16_t opcode)
{
    auto key = keys[v[get_x(opcode)]];
    if (sf::Keyboard::isKeyPressed(key))
    {
        pc += 2;
    }
}
void chip8::i_exa1(uint16_t opcode)
{
    auto key = keys[v[get_x(opcode)]];
    if (!sf::Keyboard::isKeyPressed(key))
    {
        pc += 2;
    }
}
void chip8::i_fx07(uint16_t opcode)
{
    v[get_x(opcode)] = dt;
}
void chip8::i_fx0a(uint16_t opcode)
{
    wait_key = get_x(opcode);
}
void chip8::i_fx15(uint16_t opcode)
{
    dt = v[get_x(opcode)];
}
void chip8::i_fx1e(uint16_t opcode)
{
    I += v[get_x(opcode)];
}
void chip8::i_fx29(uint16_t opcode)
{
    I = 0x50 + v[get_x(opcode)] * 5;
}
void chip8::i_fx33(uint16_t opcode)
{
    uint8_t vx = v[get_x(opcode)];
    ram[I + 2] = vx % 10;
    ram[I + 1] = (vx / 10) % 10;
    ram[I] = (vx / 100) % 10;
}
void chip8::i_fx55(uint16_t opcode)
{
    for (int i = 0; i <= get_x(opcode); i++)
    {
        ram[I + i] = v[i];
    }
}
void chip8::i_fx65(uint16_t opcode)
{
    for (int i = 0; i <= get_x(opcode); i++)
    {
        v[i] = ram[I + i];
    }
}
void chip8::execute()
{
    uint16_t opcode = (ram[pc] << 8) | ram[pc + 1];
    uint8_t mn = opcode >> 12;  //nibble mas significativo
    uint8_t ln = opcode & 0xF;  //nibble menos significativo
    uint8_t lb = opcode & 0xFF; //byte menos significativo
    uint16_t k;
    pc = (pc + 2) & 0xFFF;
    if (opcode == 0xEE)
    {
        i_0xee();
        return;
    }
    if (opcode == 0xE0)
    {
        clear_screen();
        return;
    }
    switch (mn)
    {
    case 8:
        k = (uint16_t)(mn << 4) | (uint16_t)ln;
        if (opcodes.find(k) != opcodes.end())
        {
            opcodes[k](opcode);
        }else printf("%X\n", k);
        break;
    case 0xE:
        k = (uint16_t)lb;
        if (opcodes.find(k) != opcodes.end())
        {
            opcodes[k](opcode);
        }else printf("%X\n", k);
        break;
    case 0xF:
        k = (uint16_t)(mn << 8) | (uint16_t)lb;
        if (opcodes.find(k) != opcodes.end())
        {
            opcodes[k](opcode);
        }else printf("%X\n", k);
        break;
    default:
        k = (uint16_t)mn;
        if (opcodes.find(k) != opcodes.end())
        {
            opcodes[k](opcode);
        }else printf("%X\n", k);
        break;
    }
}
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
    chip8 ch8("c8games/INVADERS");
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
            window.clear();
            ch8.draw(window, pixels, texture, sprite);
            window.display();

            ch8.draw_flag = false;
        }
    }
    return 0;
}