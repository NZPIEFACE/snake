# snake

 Snake in C. Seriously, that's basically it.

## Things to work on

- Engine
  - Food spawning
    - Random selection on unoccupied coordinates.

  - Coordinate grid (?)
    - Search up memory allocation for array of arrays.
    - Reasoning:
      Currently, the usage of coordinates is very much create-and-forget, despite the fact that there will only exist a finite amount of coordinates.  
      The idea was that by using an array of arrays, which contain coordinates, the coordinates could be reused and it would be simple to check if there are overlapping coordinates. However now that I think about it, they're already super simple.

  - User input
    - Change directions

  - Changing character grid.

- Rendering
  - Output w/ steady frame rate
