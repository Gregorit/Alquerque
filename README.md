# Alquerque

Alquerque is a project in command line environment written in C++.
Previously I was using MSVC compiler for it.
I reworked the code, so now it works also on gcc.

It's a game similar to checkers.
You can play it with friend or with CPU.
The game make save file which saves after every move. You can load it in the menu.
It also includes scoreboard.

### Rules:
```
https://en.wikipedia.org/wiki/Alquerque
```
Simplified rules are also included in program. Please read them before play.


## Prerequisites

You need to compile this project by yourself in any C++ compiler.
gcc example:

```
$ gcc Main.cpp [rest of .cpp and .h files] -o output
$ ./output
```

## How to use

### Moving in game menu

Every option in menu is preceded by number it represents. Just simply type exact number and press Enter.

### Movement

To move you need to type coordinates of piece and coordinates of empty field.

For example:

```
B3
**pressing Enter**
C2
**pressing Enter**
```

Every rule about moving piece is explained in in-game rules.


## Tools used to create this project

### Before gcc compatibility
* [Windows 7 Ultimate](https://www.microsoft.com/en-us/windows/) - System used to make this project
* [Visual Studio Professional 2013](https://msdn.microsoft.com/en-us/library/dd831853(v=vs.120)) - C++ IDE and compiler

### After gcc compatibility
* [Antergos 17.10](https://antergos.com) - System used to make this project
* [Code::Blocks](http://www.codeblocks.org) - C++ IDE
* [gcc](https://gcc.gnu.org) - C++ compiler
