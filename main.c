#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define HEIGHT 15
#define WIDTH 15

void clear_screen()
{
    printf("\033[2J");
    fflush(stdout);
}

void move_cursor(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

int count_alive_neighbours(const uint8_t grid[HEIGHT][WIDTH], size_t xpos, size_t ypos)
{
    int count = 0;
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++){

            if ((x == 0 && y == 0) ||
                    (xpos + x < 0) ||
                    (ypos + y < 0) ||
                    (xpos + x > WIDTH - 1) ||
                    (ypos + y > HEIGHT - 1)) {
                continue;
            }

            if (grid[ypos + y][xpos + x] == 1) {
                count++;
            }
        }
    }
    return count;
}

void print_r(const uint8_t grid[HEIGHT][WIDTH])
{
    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            if (grid[y][x] == 1) {
                printf("X ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void game_of_life(uint8_t grid[HEIGHT][WIDTH])
{
    uint8_t next_grid[HEIGHT][WIDTH] = {0};

    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            int count = count_alive_neighbours(grid, x, y);
            if (grid[y][x] == 1) {
                next_grid[y][x] = 1;

                if (count < 2 || count > 3) {
                    next_grid[y][x] = 0;
                }
            } else {
                if (count == 3) {
                    next_grid[y][x] = 1;
                }
            }
        }
    }

    for (size_t y = 0; y < HEIGHT; y++) {
        for (size_t x = 0; x < WIDTH; x++) {
            grid[y][x] = next_grid[y][x];
        }
    }
}

int main()
{
    uint8_t grid[HEIGHT][WIDTH] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    int cycles = 100;

    while (cycles--) {
        clear_screen();
        move_cursor(0, 0);
        print_r(grid);
        printf("\n");
        game_of_life(grid);
        usleep(1000000 / 4);
    }

    return 0;
}
