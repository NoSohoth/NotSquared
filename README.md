# NotSquared
NotSquared is my first C++ project.
It is a simple manic shooter (Shoot'Em Up) that uses and requires the `SFML` library.
	
## Dependencies
NotSquared uses the `SFML` library. It has been made under the 2.2-3 version but I think that it'll work fine as long as
you have version 2.

If you're using ArchLinux, you'll only need to install SFML using `pacman -S sfml` and it should work out-of-the-box.
On other distros, you might have to set the `SFMLDIR` variable to the path towards the library.

## How-to
	Before compiling, you can modify some game parameters in src/Main.cpp, to disable the music, modify difficulty settings, ...

`make` to compile, then run the game with `./NotSquared`.

## Commands

`Escape` : Pause game
`Space` : Shoot
`/\` `\/` `<-` `->` : Move around

## TODO

- Display score

- Game Over screen

- More ennemies, formations, bosses
