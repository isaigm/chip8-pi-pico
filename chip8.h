#ifndef CHIP8_H
#define CHIP8_H
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <functional>
#include <SFML/Graphics.hpp>
#include <map>
static uint8_t fontset[80] =
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
static sf::Keyboard::Key keys[] =
    {
        sf::Keyboard::Key::X,
        sf::Keyboard::Key::Num1,
        sf::Keyboard::Key::Num2,
        sf::Keyboard::Key::Num3,
        sf::Keyboard::Key::Q,
        sf::Keyboard::Key::W,
        sf::Keyboard::Key::E,
        sf::Keyboard::Key::A,
        sf::Keyboard::Key::S,
        sf::Keyboard::Key::D,
        sf::Keyboard::Key::Z,
        sf::Keyboard::Key::C,
        sf::Keyboard::Key::Num4,
        sf::Keyboard::Key::R,
        sf::Keyboard::Key::F,
        sf::Keyboard::Key::V

};
class chip8
{
public:
    chip8(const std::string path);
    uint8_t get_x(uint16_t);
    uint8_t get_y(uint16_t);
    void execute();
    void draw(uint8_t *pixels);
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
    void i_fx18(uint16_t);
    void i_fx1e(uint16_t);
    void i_fx29(uint16_t);
    void i_fx33(uint16_t);
    void i_fx55(uint16_t);
    void i_fx65(uint16_t);
    bool draw_flag = true;
    int wait_key = -1;

    uint8_t dt, st;
    void update_timers();
    uint8_t v[16];

private:
    void clear_screen();
    uint8_t ram[4096];
    uint16_t stack[16];
    uint16_t pc, sp;
    uint16_t I;
    uint8_t gfx[32][64];
    std::map<uint16_t, std::function<void(uint16_t)>> opcodes;
};

#endif

