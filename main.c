//mexer sem ser na diagonal - controles - fruta ok
//frutas diferentes e frutas negativas - ainda falta (struct switch p cada caso)
//outros mapas - modos como no tictactoe - ainda falta
//problema: velocidade de resposta ao comando
//adicionar score e mostrar na tela
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define HEAD 0
#define BODY_LENGTH 2

#define SNAKE_HEAD '@'
#define SNAKE_BODY_PIECE '#'

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define FRUIT '$'
//#define ROTTEN_FRUIT '¢' -> struct

#define GRID_DIMENSION 24
#define bool char
#define true 1
#define false 0
//pegando com pointer
void spawn_fruit(int *fruit_init_x, int *fruit_init_y) // pode usar com outras frutas ao mesmo tempo passando tipo da fruta
{
    *fruit_init_x = rand() % GRID_DIMENSION;
    *fruit_init_y = rand() % GRID_DIMENSION;
}

int main(void)
{
    int snake_length = BODY_LENGTH + 1;
    int i;
    int snake[GRID_DIMENSION * GRID_DIMENSION];

    srand(time(NULL));
    int snake_init_x = rand() % GRID_DIMENSION;
    int snake_init_y = rand() % GRID_DIMENSION;
    snake[HEAD] = (snake_init_y * GRID_DIMENSION) + snake_init_x;

    for (i = 1; i < snake_length; ++i)
    {
        snake[i] = snake[HEAD] - i;
    }

    int direction_x = 1;
    int direction_y = 0;
    //função colocando na gaveta
    int fruit_init_x;
    int fruit_init_y;
    spawn_fruit(&fruit_init_x, &fruit_init_y);


    while (true)
    {
    system("cls");

    for(int r = 0; r < GRID_DIMENSION; ++r)
    {
        for(int c = 0; c < GRID_DIMENSION; ++c)
        {
            bool is_snake = false; // pra liberar o que era else de ponto do grid
            if(r == snake[HEAD] / GRID_DIMENSION && c == snake[HEAD] % GRID_DIMENSION)
            {
                printf("%c", SNAKE_HEAD);
                is_snake = true;
            } else
            {
                for(i = 1; i < snake_length; ++i)
                {
                    if(r == snake[i] / GRID_DIMENSION && c == snake[i] % GRID_DIMENSION)
                    {
                        printf("%c", SNAKE_BODY_PIECE);
                        is_snake = true;
                    }
                }
            }

            if(r == fruit_init_y && c == fruit_init_y) //outras frutas
            {
                printf("%c", FRUIT); //duvida: aqui poderia cair dentro da cobra?
            }
            
            if(!is_snake && !(r == fruit_init_y && c == fruit_init_y)) //n pode ser nenhum dos dois
            {
                printf(".");
            }
            
            if(c != GRID_DIMENSION - 1)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    //pegar comandos
    if (kbhit())
        {
            int key = getch();
            switch(key)
            {
                case KEY_UP:
                    direction_x = 0;
                    direction_y = -1;
                    break;
                case KEY_DOWN:
                    direction_x = 0;
                    direction_y = 1;
                    break;
                case KEY_LEFT:
                    direction_x = -1;
                    direction_y = 0;
                    break;
                case KEY_RIGHT:
                    direction_x = 1;
                    direction_y = 0;
                    break;
                default:
                    break;
            }
        }
    //movimentando a cabela
    int head_x = snake[HEAD] % GRID_DIMENSION; 
    int head_y = snake[HEAD] / GRID_DIMENSION;
    int mov_head_x = head_x + direction_x; 
    int mov_head_y = head_y + direction_y;
    //o corpo
    for(i = snake_length - 1; i > 0; --i)
    {
        snake[i] = snake[i - 1];
    }

    snake[HEAD] = (mov_head_y * GRID_DIMENSION) + mov_head_x;
    //a cabeça come a fruta e aumenta o corpo
    if(mov_head_x == fruit_init_x && mov_head_y == fruit_init_y)
    {
        snake_length++; //cresce o corpo - lembrar de diminuir corpo na prox fruta
        spawn_fruit(&fruit_init_x, &fruit_init_y); //mais fruta
    }

    //ao encostar em bordas:
    if(mov_head_x < 0 || mov_head_x >= GRID_DIMENSION)
    {
        break;
    }

    Sleep(1000);
    }
    
    return 0;
}