# snake

Snake in C. Seriously, that's basically it.

## Things to work on

- Engine
  - Coordinate grid (?)
    - Search up memory allocation for array of arrays.
    - Reasoning:
      Currently, the usage of coordinates is very much create-and-forget, despite the fact that there will only exist a finite amount of coordinates.  
      The idea was that by using an array of arrays, which contain coordinates, the coordinates could be reused and it would be simple to check if there are overlapping coordinates. However now that I think about it, they're already super simple.

- Inefficiencies
  - Private SnakeBody means that to interface the list of coordinates from the Snake object, it's required to call a funciton that allocates memory and will generally loop over the same things twice.

- Issues
  - Sometimes the directions won't change. Find and fix it.
  - Cygwin can't compile it to run on Windows' native environment. MinGW can't compile this because of termios.h and sys/times.h.
  
## Things that are finished

- Engine
  - Food spawning
    - Random selection on unoccupied coordinates.

  - User input
    - Change directions
    - Input polling
    - Read user input from buffer.
    - Need to remove echo from typing.
    - Need to make it so typing something adds to buffer even when the program is sleeping, or through another way.
      - Was done using a non-blocking input method.

  - Kill the snake if it hits a wall or itself.

- Rendering
  - Output w/ steady frame rate.
  - Changing character grid.

- Game logic
  - Needs to know what to do between frames, and the order of how the game happens.
    - Order:  
      Read input.  
      See where head is.  
      Render the game.  
      Wait till next time.

- Issues
  - Sometimes the directions won't change. Find and fix it.
    - Was done by adding a return statement in the polling function after a successful poll.

## Things I could do

- termios.h
  - Alternatives for this exist if I want to port to MinGW. Something like ncurses or pdcurses could work if I learn how to install packages. A definite way that could work would be to use the WinAPI.

- sys/times.h
  - As I'm only using this for the times() function as it gives a relatively accurate system clock, I could instead use clock_gettime from the time.h header.
