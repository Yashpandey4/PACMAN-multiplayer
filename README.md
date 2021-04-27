# Multiplayer PACMAN
Find exact project details [here](https://www.cse.iitd.ac.in/~rijurekha/cop290_2021.html) under task 2.

## Project Structure
- **assets:** All non-code files required for program execution go here. These are static files and needn't be compiled.
- **bin:** The output executables go here, both for the app and for any tests and spikes.
- **build:** This folder contains all object files, and is removed on a clean.
- **doc:** Any notes, like my assembly notes and configuration files, are here. I decided to create the development and production config files in here instead of in a separate config folder as they “document” the configuration.
- **include:** All project header files. All necessary third-party header files that do not exist under /usr/local/include are also placed here.
- **lib:** Any libs that get compiled by the project, third party or any needed in development. Prior to deployment, third party libraries get moved to /usr/local/lib where they belong, leaving the project clean enough to compile on our Linux deployment servers. I really use this to test different library versions than the standard.
- **src:** The application and only the application’s source files.

## Dependencies
1. SFML: Installation Instructions - [Link 1](https://www.sfml-dev.org/tutorials/2.5/start-linux.php), [Link 2](https://laptrinhx.com/install-sfml-2-5-1-on-ubuntu-18-04-and-clion-184157703/)

## Resources
1. [Sprite Cow](http://www.spritecow.com/): Very useful for extracting spriteFile from the sprite sheet

## Miscellaneous
1. Name functions as `CamelCase` format and variables with `camelCase` (first letter small)