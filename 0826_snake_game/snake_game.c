// Snake Game v0.19
    // requirement:
    // * rectangular game board
    // * snake represented by array of coordinates
    // * keyboard-controlled movement
    // * continous game loop
    // * food spawning
    // * collision with walls
    // * collision with itself
    // * score
    // * increasing difficulty
    // * game-over state
    // * clean separation between game state, input, update logic, and rendering
//////

// allows printf function
#include <stdio.h>

// allows usleep function
#include <unistd.h>

// allows terminal configuration
#include <termios.h>

// allows file-control operations
#include <fcntl.h>

// allows random number generation
#include <stdlib.h>

// allows access to system time
#include <time.h>

// constructs rectangular game board
#define WIDTH 20
#define HEIGHT 10

// creates an array capable of holding the snake
#define MAX_SNAKE_LENGTH 100

// defines keyboard inputs
#define INPUT_NONE 0
#define INPUT_UP 1
#define INPUT_DOWN 2
#define INPUT_LEFT 3
#define INPUT_RIGHT 4

// represents snake's possible directions
enum Direction
{
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
};

// represents a coordinate on the game board
struct Position
{
    int x;
    int y;
};

struct GameState
{
    struct Position snake[MAX_SNAKE_LENGTH];
    int snake_length;
    struct Position food;
    enum Direction direction;
    int score;
    int game_over;
};

int get_input(void)
{   
    // creates variable called "oldt" capable of storing terminal configuration
    struct termios oldt;

    // stores the configuration we're going to modify
    struct termios newt;

    int oldf;
    int ch;

    // gives current configuration of standard input and stores it in "oldt"
    tcgetattr(STDIN_FILENO, &oldt); // STDIN_FILENO refers to the standard input file descriptor

    // makes "newt" initially identical to "oldt"
    newt = oldt;

    // turns off canonical input and terminal echo
    newt.c_lflag &= ~(ICANON | ECHO);

    // applies new terminal config
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // gets current file-status flags for standard input
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);

    // makes standard iput non-blocking
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    //reads keyboard input
    ch = getchar();

    // restores original terminal config
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    // restores original terminal config
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    // converts keyboard characters into program-level input
    if (ch == 'w')
    {
        return INPUT_UP;
    }
    else if (ch == 's')
    {
        return INPUT_DOWN;
    }
    else if (ch == 'a')
    {
        return INPUT_LEFT;
    }
    else if (ch == 'd')
    {
        return INPUT_RIGHT;
    }

    return INPUT_NONE;
}

// moves the snake according to its current direction
void move_snake(struct Position snake[],
                int snake_length,
                enum Direction direction)
{
    // moves each body segment into the previous
    // position of the segment in fron of it
    for (int i = snake_length - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    // moves snake head based on current direction
    if (direction == DIRECTION_UP)
    {
        snake[0].y--;
    }
    else if (direction == DIRECTION_DOWN)
    {
        snake[0].y++;
    }
    else if (direction == DIRECTION_LEFT)
    {
        snake[0].x--;
    }
    else if (direction == DIRECTION_RIGHT)
    {
        snake[0].x++;
    }

}

// checks whether snake occupies a given coordinate
int is_snake_at(struct Position snake[],
                int snake_length,
                int x,
                int y)
{
    // searches through every active snake segment
    for (int i = 0; i < snake_length; i++)
    {
        // checks whether this segment occupies the coordinates
        if (snake[i].x == x &&
            snake[i].y == y)
            {
                // coordinate is occupiedby snake
                return 1;
            }
    }

    // coordinate is not occupied by snake
    return 0;
}

// generates a valid random food position
void spawn_food(struct Position *food,
                struct Position snake[],
                int snake_length)
{
    // repeatedly generates food until it does not occupy a snake segment
    do
    {
        // generates a random playable x coordinate
        food->x = 1 + rand() % (WIDTH - 2);

        // generates a random playable y coordinate
        food->y = 1 + rand() % (HEIGHT - 2);
    } while (is_snake_at(snake,
                        snake_length,
                        food->x,
                        food->y));
}

// checks whether the snake's head has collided with the wall
int hit_wall(struct Position head)
{
    if (head.x <= 0 ||
        head.x >= WIDTH - 1 ||
        head.y <= 0 ||
        head.y >= HEIGHT - 1)
    {
        return 1;
    }

    return 0;
}

// checks whether the snake's head has collided with its body
int hit_self(struct Position snake[],
            int snake_length)
{
    // starts at segment 1 because head is segment 0
    for (int i = 1; i < snake_length; i++)
    {
        // checks whether the head and body segment
        // occupy the same coordinates
        if (snake[0].x == snake[i].x &&
            snake[0].y == snake[i].y)
        {
            return 1;
        }
    }

    // no body segment occupies the head's position
    return 0;
}

// renders current game state
void render(struct Position snake[],
            int snake_length,
            struct Position food,
            int score)
{
    // clears the terminal and moves cursor to the top left
    printf("\033[H\033[J");

    // loops through every row
    for (int y = 0; y < HEIGHT; y++)
    {
        // loops through every column
        for (int x = 0; x < WIDTH; x++)
        {
            // checks whether cell is on the border
            if (y == 0 || y == HEIGHT - 1 ||
                x == 0 || x == WIDTH - 1)
                {
                    printf("#");
                }
                else
                {
                    // assumes this cell does not contain snake
                    int is_snake = 0;

                    // stores which snake segment occupies cell
                    int snake_segment = -1;

                    // searches every active snake segment
                    for (int i = 0; i < snake_length; i++)
                    {
                        // checks whether this segment occupies the cell
                        if (x == snake[i].x &&
                            y == snake[i].y)
                        {
                            is_snake = 1;
                            snake_segment = i;
                        }
                    }

                    // determines what should be rendered
                    if (is_snake)
                    {
                        // segment 0 is the head
                        if (snake_segment == 0)
                        {
                            printf("H");
                        }
                        // all other segments are body
                        else
                        {
                            printf("O");
                        }
                    }
                    // checks whether food occupies the cell
                    else if (x == food.x && 
                             y == food.y)
                    {
                        printf("*");
                    }
                    //empty playable cell
                    else
                    {
                        printf(".");
                    }
                }
        }
        // moves terminal cursor to next row
        printf("\n");
    }

    // displays current score
    printf("Score: %d\n", score);
}

// determines game speed based on score
int get_delay(int score)
{
    // starting delay in microseconds
    int delay = 200000;

    // increase speed every 50 points
    delay -= (score / 50) * 20000;

    // prevents the game from become excessively fast
    if (delay < 60000)
    {
        delay = 60000;
    }
    return delay;
}

// calls main function
int main(void)
{   
    // initializes random number generator
    srand(time(NULL));

    // represents snake's current length
    int snake_length = 5;

    // represents player's current score
    int score = 0;

    // creates an array of five positions representing snake
    struct Position snake[MAX_SNAKE_LENGTH];

    // zero-based indexing
    // segment 0 is the head
    snake[0].x = 5;
    snake[0].y = 3;

    snake[1].x = 4;
    snake[1].y = 3;

    snake[2].x = 3;
    snake[2].y = 3;

    snake[3].x = 2;
    snake[3].y = 3;

    snake[4].x = 1;
    snake[4].y = 3;

    // represents food's position
    struct Position food;

    // generates initial food position and prevents it from spawning on the snake
    spawn_food(&food, snake, snake_length);

    // represents snake's current direction
    enum Direction direction = DIRECTION_RIGHT;

    // represents whether the game has ended
    int game_over = 0;

    // continuous game loop
    while (!game_over)
    {   
        // check for keyboard input
        int input = get_input();

        // updates snake direction based on input
        if (input == INPUT_UP) // moves snake "up"
        {
            // prevents reversing directly from down to up
            if (direction != DIRECTION_DOWN)
            {
                direction = DIRECTION_UP;
            }
        }
        else if (input == INPUT_DOWN) // moves snake "down"
        {
            // prevents reversing directly from up to down
            if (direction != DIRECTION_UP)
            {
                direction = DIRECTION_DOWN;
            }
        }
        else if (input == INPUT_LEFT) // moves snake "left"
        {
            // prevents reversing directly from right to left
            if (direction != DIRECTION_RIGHT)
            {
                direction = DIRECTION_LEFT;
            }
        }
        else if (input == INPUT_RIGHT) // moves snake "right"
        {
            // prevents reversing directly from left to right
            if (direction != DIRECTION_LEFT)
            {
                direction = DIRECTION_RIGHT;
            }
        }

        // moves the snake
        move_snake(snake, snake_length, direction);

        // checks whether snake has hit wall
        if (hit_wall(snake[0]))
        {
            game_over = 1;
        }

        // checks whether snake has collided with its body
        if (hit_self(snake, snake_length))
            {
                game_over = 1;
            }
        
        // checks whether snake head has reached food
        if (snake[0].x == food.x &&
            snake[0].y == food.y)
        {
            if (snake_length < MAX_SNAKE_LENGTH)
            {
                snake_length++;
            }

            // increases score when food is eaten
            score += 10;

            // generates a new food position and prevents it from spawning on the snake
            spawn_food(&food, snake, snake_length);
        }

        // renders current game state
        render(snake, snake_length, food, score);

        // pauses before next game-loop iteration
        usleep(200000);
    }

    // prints snake length total (TEMP)
    printf("Length: %d\n", snake_length);

    // game over message to user / explicit terminal state
    printf("GAME OVER!\n");

    return 0;
}