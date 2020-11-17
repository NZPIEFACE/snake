# snake

 Snake in C. Seriously, that's basically it.

## Things to work on

- Engine
  - Coordinate grid (?)
    - Search up memory allocation for array of arrays.
    - Reasoning:
      Currently, the usage of coordinates is very much create-and-forget, despite the fact that there will only exist a finite amount of coordinates.  
      The idea was that by using an array of arrays, which contain coordinates, the coordinates could be reused and it would be simple to check if there are overlapping coordinates. However now that I think about it, they're already super simple.

  - User input
    - Change directions
    - Read user input from buffer.
    - Need to remove echo from typing.
    - Need to make it so typing something adds to buffer even when the program is sleeping, or through another way.

  - Game logic
    - Needs to know what to do between frames, and the order of how the game happens.

- Inefficiencies
  - Private SnakeBody means that to interface the list of coordinates from the Snake object, it's required to call a funciton that allocates memory and will generally loop over the same things twice.
  
## Things that are finished

- Engine
  - Food spawning
    - Random selection on unoccupied coordinates.

- Rendering
  - Output w/ steady frame rate.
  - Changing character grid.
