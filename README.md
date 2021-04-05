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

  - Update() function
    - Instead of having the update to the game tied to the input/time-out logic, have it a separate function that is called by that logic.

  - Multithreading
    - Using multithreading for input and logic would probably work a lot better than leaving everything to the same thread.
      - This fucks with the current output method way too much. It takes too long to update to use a while(1) loop properly without fucking everything over. That, and also output is de-synced from inputs and logic, so sometimes the Snake's tail isn't printed since it's already been moved to the head while the screen was printing.

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
  - Cygwin can't compile it to run on Windows' native environment. MinGW can't compile this because of termios.h and sys/times.h. Slowly phase this into WinAPI.
  - Sometimes snake will not eat food.
    - The issue was that it may have spawned the food on the exact location that the new head was also about to spawn at.
  - Sometimes the head of the snake is invisible. I'm assuming this is because of how the queue works (first in, first out). Swapping the order around only changes the issue to having an extra tail.
    - This was fixed by doubling up on the second request.

- Inefficiencies
  - Private SnakeBody means that to interface the list of coordinates from the Snake object, it's required to call a funciton that allocates memory and will generally loop over the same things twice.
    - If it was public, it would be possible to iterate over the struct.
    - Examples:
      - main.c:181 - turn_logic():
        - It updates the string every frame. It really doesn't need to.
      - board.c:97 - find_empty_cell():
        - Grabs the list to use it's coordinates to find indices of another array.
      - snake.c:166 - snake_head_overlap_itself():
        - Iterates over the whole list after creating it, then deletes it.
    - These examples can be solved if there was a yield-like function that would return the values one after another, as the examples only iterate through the whole list. Making such a function would be great, however I have the sneaking feeling that it would require goto or jump or some other arcane arts.
      - I was originally planning on making a function that would use the static variable declaration but then I realized that I could just make SnakeBody public.

  - Frame output is inefficient.
    - board->apply_to_grid(board) and bw_render are used every single frame.
      - Using a single string to output just exacerbates this issue. I think the only way to mitigate this is to move the console cursor to a specific location before printing.

## Things I could do

- Implement instant direction changing when pressing a valid arrow key.
  - I feel that this sort of gameplay would feel more natural than the current queued commands.
    - This requires a way to reset the timer for updates whenever the update function is run.
    - I'll seriously consider implementing this once the output of the game is much more stable.
