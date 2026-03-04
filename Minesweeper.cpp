#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;

void fill_user_grid(char grid[9][9])
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            grid[i][j] = '0';
}
char count_mines(char grid[9][9], int r, int c)
{
    int r_ind, c_ind, mine_count = 0;

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0)
                continue;

            r_ind = r + i;
            c_ind = c + j;

            if (r_ind >= 0 && c_ind >= 0 && r_ind <= 8 && c_ind <= 8)
            {
                if (grid[r_ind][c_ind] == '*')
                    mine_count++;
            }
        }
    }
    return char(mine_count + '0');
}
void fill_main_grid(char grid[9][9])
{
    fill_user_grid(grid);

    int mines = 0;
    int r_ind, c_ind;

    while (mines < 20)
    {
        r_ind = rand() % 9;
        c_ind = rand() % 9;

        if (grid[r_ind][c_ind] != '*')
        {
            grid[r_ind][c_ind] = '*';
            mines++;
        }
    }

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (grid[i][j] != '*')
                grid[i][j] = count_mines(grid, i, j);
}
void print_grid(char grid[][9])
{
    cout << "\n      ";
    for (int i = 1; i <= 9; i++)
        cout << i << " ";
    cout << "\n\n";

    for (int i = 0; i < 9; i++)
    {
        cout << "  " << i + 1 << "   ";
        for (int j = 0; j < 9; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}
void mark_grid(char user_grid[9][9], char main_grid[9][9], int r, int c)
{
    if (main_grid[r][c] == '0')
    {
        int r_ind, c_ind;
        user_grid[r][c] = ' ';

        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                r_ind = r + i;
                c_ind = c + j;

                if (r_ind >= 0 && c_ind >= 0 && r_ind <= 8 && c_ind <= 8)
                {
                    if (user_grid[r_ind][c_ind] == '0' &&
                        main_grid[r_ind][c_ind] != '*')
                        mark_grid(user_grid, main_grid, r_ind, c_ind);
                }
            }
        }
    }
    else
    {
        user_grid[r][c] = main_grid[r][c];
    }
}
void take_input(char user_grid[9][9], char main_grid[9][9], bool &game_over)
{
    cout << "Enter row and column number (1-9): ";
    int r_ind, c_ind;
    cin >> r_ind >> c_ind;

    while (r_ind < 1 || c_ind < 1 || r_ind > 9 || c_ind > 9)
    {
        cout << "Invalid input. Please enter values between 1 and 9: ";
        cin >> r_ind >> c_ind;
    }

    r_ind--;
    c_ind--;

    while (user_grid[r_ind][c_ind] != '0')
    {
        cout << "This cell is already opened. Choose another cell: ";
        cin >> r_ind >> c_ind;
        r_ind--;
        c_ind--;
    }

    if (main_grid[r_ind][c_ind] != '*')
        mark_grid(user_grid, main_grid, r_ind, c_ind);
    else
        game_over = true;
}
void greeting()
{
    cout << "\n==============================================\n";
    cout << "              MINESWEEPER GAME\n";
    cout << "==============================================\n";
    cout << "Reveal all safe cells to win.\n";
    cout << "Avoid the mines!\n\n";
}
void check_win(char user_grid[9][9], char main_grid[9][9], bool &game_won)
{
    int count = 0;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (user_grid[i][j] == '0')
                count++;

    game_won = (count == 20);
}
void print_with_mines(char user_grid[9][9], char main_grid[9][9])
{
    cout << "\nFinal Board:\n\n";

    cout << "\n      ";
    for (int i = 1; i <= 9; i++)
        cout << i << " ";
    cout << "\n\n";

    for (int i = 0; i < 9; i++)
    {
        cout << "  " << i + 1 << "   ";
        for (int j = 0; j < 9; j++)
            if (main_grid[i][j] == '*')
                cout << "* ";
            else
                cout << user_grid[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}
int main()
{
    srand(time(0));
    char user_grid[9][9];
    char main_grid[9][9];

    bool game_over = false;
    bool game_won = false;

    fill_user_grid(user_grid);
    fill_main_grid(main_grid);

    while (!game_over && !game_won){
        system("cls");
        greeting();
        print_grid(user_grid);
        take_input(user_grid, main_grid, game_over);
        check_win(user_grid, main_grid, game_won);
    }

    if (game_won)
    {
        cout << "\n Congratulations! You successfully cleared the minefield.\n";
    }
    else
    {
        cout << "\n Boom! You stepped on a mine.\n";
        print_with_mines(user_grid, main_grid);
    }

    return 0;
}