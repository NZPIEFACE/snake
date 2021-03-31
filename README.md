# snake

Snake in C. Seriously, that's basically it.

## Things to work on

- Engine
  - Coordinate grid (?)
    - Search up memory allocation for array of arrays.
    - Reasoning:
      Currently, the usage of coordinates is very much create-and-forget, despite the fact that there will only exist a finite amount of coordinates.  
      The idea was that by using an array of arrays, which contain coordinates, the coordinates could be reused and it would be simple to check if there are overlapping coordinates. However now that I think about it, they're already super simple.
    - Cons:
      The amount of memory that it could take up in the runtime of the program could simply bloat. Even thought it's only int[2] per coordinate. It's not a lot though.
  - Update() function
    - Instead of having the update to the game tied to the input/time-out logic, have it a separate function that is called by that logic.
  - Multithreading
    - Using multithreading for input and logic would probably work a lot better than leaving everything to the same thread.

- Inefficiencies
  - Private SnakeBody means that to interface the list of coordinates from the Snake object, it's required to call a funciton that allocates memory and will generally loop over the same things twice.
    - Examples:
      - board.c:97 - find_empty_cell():
        - Grabs the list to use it's coordinates to find indices of another array.
      - snake.c:166 - snake_head_overlap_itself():
        - Iterates over the whole list after creating it, then deletes it.
    - These examples can be solved if there was a yield-like function that would return the values one after another, as the examples only iterate through the whole list. Making such a function would be great, however I have the sneaking feeling that it would require goto or jump or some other arcane arts.

- Issues
  - Sometimes the directions won't change. Find and fix it.
  - Cygwin can't compile it to run on Windows' native environment. MinGW can't compile this because of termios.h and sys/times.h. Slowly phase this into WinAPI.
  
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

- Implement instant direction changing when pressing a valid arrow key.
  - I feel that this sort of gameplay would feel more natural than the current queued commands.
    - This requires a way to reset the timer for updates whenever the update function is run.cd

## UNIX or POSIX headers

- io.c
  - termios.h
    - Terminal setting control. Removing echo (see what you type) and canonical (pressing Enter for characters to be sent to buffer).
  - unistd.h
    - For read() which reads the STDIN character buffer.

- main.c
  - sys/time.h
    - Used to determine start time of the polling to count the polling duration with the times() function.

- polling.c
  - poll.h
  - unistd.h
  - sys/times.h
    - Used for the times() function similar to above.
