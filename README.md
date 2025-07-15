# Chip-8 Emulator

This is a Chip-8 emulator written in C++ using the SFML library for graphics and input.

## How to Compile and Run

To compile this emulator, you will need `g++` and the SFML libraries installed on your system.

1.  **Compile:**
    Open a terminal in the project's root directory and run the following command:

    ```bash
    g++ main.cpp chip8.cpp -o chip8_emulator -lsfml-graphics -lsfml-window -lsfml-system
    ```

2.  **Run:**
    Once compiled, you can run the emulator with:

    ```bash
    ./chip8_emulator
    ```

    Make sure you have Chip-8 ROMs in the `c8games/` directory for the emulator to load them. The emulator is configured to load `c8games/INVADERS` by default.

    **To try a different ROM**, you need to modify the `main.cpp` file where the ROM is loaded. Look for the line similar to `chip8 ch8("c8games/INVADERS");` and change the ROM path accordingly.

## Demo Video

A demonstration video of the emulator in action can be found in the `videos/` directory: [demo.mkv](videos/demo.mkv).

## Note on Raspberry Pi Pico Code

Within this repository, you might find files or references to code related to Raspberry Pi Pico (e.g., `chip-8-pi-pico.cpp`). This code corresponds to a previous attempt to port and run the Chip-8 emulator directly on a Raspberry Pi Pico, using an OLED screen. Unfortunately, the project could not be continued because the OLED screen used broke down. Therefore, the Raspberry Pi Pico code is not functional or maintained as part of this desktop emulator.
