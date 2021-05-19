# Multiplayer PACMAN
Find exact project details [here](https://www.cse.iitd.ac.in/~rijurekha/cop290_2021.html) under task 2.

## Compilation and Execution
1. From the project root, type `sh scripts/build.sh` in the terminal
2. To host the game, type `sh scripts/run.sh server`
3. To play the game, type `sh scripts/run.sh client`
4. Type `make clean` to remove the compiled objects and binaries

## Project Structure
- **assets:** All non-code files required for program execution go here. These are static files and needn't be compiled.
- **bin:** The output executables go here, both for the app and for any tests and spikes.
- **build:** This folder contains all object files, and is removed on a clean.
- **doc:** Any notes, like my assembly notes and configuration files, are here. I decided to create the development and production config files in here instead of in a separate config folder as they “document” the configuration.
- **include:** All project header files. All necessary third-party header files that do not exist under /usr/local/include are also placed here.
- **lib:** Any libs that get compiled by the project, third party or any needed in development. Prior to deployment, third party libraries get moved to /usr/local/lib where they belong, leaving the project clean enough to compile on our Linux deployment servers. I really use this to test different library versions than the standard.
- **server:** Server's source files and include files.
- **client:** Client's source files and include files.

## Dependencies
1. SFML: Installation Instructions - [Link 1](https://www.sfml-dev.org/tutorials/2.5/start-linux.php), [Link 2](https://laptrinhx.com/install-sfml-2-5-1-on-ubuntu-18-04-and-clion-184157703/)

## Resources
1. [Sprite Cow](http://www.spritecow.com/): Very useful for extracting spriteFile from the sprite sheet
2. The [ghosts in PacMan](https://villains.fandom.com/wiki/Ghosts_(Pac-Man) have names: Inky (Blue), Pinky (Pink), Blinky (Red), Sue (Purple) and Clyde (Orange), and they each have different behaviours which must be coded in the game. Read more [here](https://dev.to/code2bits/pac-man-patterns--ghost-movement-strategy-pattern-1k1a).
3. The dots are called PacDots/Cookies/Pellets and large flashing dots called "Power Pellets". 

## Miscellaneous
1. Name Classes as `CamelCase` format and functions/variables as `camelCase` (first letter small). Constants are named as `FIRST_LAST`.