#include <stdio.h>
#include <ctype.h>

// Function prototypes
void take_selection_input(char *bp_ptr, int turn);
int white_pawn_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col);
int black_pawn_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col);
int rook_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col);
int knight_movement(char *bp_ptr, int location, int destination);
int bishop_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col);
int queen_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col);
int king_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col);
void take_movement_input(char *bp_ptr, int location, int turn);
int valid_movement(char *bp_ptr, int location, int destination, int turn);

int ret_int(int row, int col)
{
    return (((row - 1) * 5) + (col - 1));
}

void print_board(char *bp_ptr, int turn)
{
    printf("\n--A B C D E--");

    // Loops from 0-24 and prints the int value of the bp_ptr array there
    int i;
    for (i = 0; i < 25; ++i)
    {

        if (i % 5 == 0)
        {
            printf("\n");
            printf("%d ", ((i / 5) + 1));
        }
        printf("%c ", bp_ptr[i]);
    }

    // Information about int -> piece here
    printf("\n-------------");
    printf("\np = pawn, k = king, q = queen, b = bishop, n = knight, r = rook : Lowercase is Black, Caps are White");
    if(turn%2 == 0)
    {
        printf("\nBLACK PLAYER TURN");
    }
    else
    {
        printf("\nWHITE PLAYER TURN");
    }
    // After printing, asks for input
    take_selection_input(bp_ptr, turn);
}

void take_selection_input(char *bp_ptr, int turn)
{
    int row, column, selected;

    printf("\n------");


    char input[3];

    printf("\nChoose a piece to move (EX: A4)\n");

    scanf("%2s", input);

    if (input[0] == 'A')
    {
        column = 1;
    }
    else if (input[0] == 'B')
    {
        column = 2;
    }
    else if (input[0] == 'C')
    {
        column = 3;
    }
    else if (input[0] == 'D')
    {
        column = 4;
    }
    else if (input[0] == 'E')
    {
        column = 5;
    }
    else
    {
        printf("Error with input, choose a piece to move again");
        take_selection_input(bp_ptr, turn);
    }

    row = atoi(&input[1]); // The remaining part is the number

    if (row > 5 || row < 0)
    {
        printf("Error with input, choose a piece to move again");
        take_selection_input(bp_ptr, turn);
    }

    // Use int row and int column to find the piece from 0-24
    selected = bp_ptr[(row - 1) * 5 + (column - 1)];


    if (selected != 'x')
    {

        // Confirmed is a piece

        int temp_int = turn % 2;

        // WHITE TURN
        if (temp_int == 1)
        {
            if (isupper(selected))
            {
                //printf("%c is valid", selected);
                // IF IT IS VALID, MOVE TO NEXT STEP; DECIDING WHERE TO MOVE
                take_movement_input(bp_ptr, ((row - 1) * 5 + (column - 1)), turn);
                return;
            }
        }

        // BLACK TURN
        else
        {
            if (!isupper(selected))
            {
                printf("%c is valid", selected);
                // IF IT IS VALID, MOVE TO NEXT STEP; DECIDING WHERE TO MOVE
                take_movement_input(bp_ptr, ((row - 1) * 5 + (column - 1)), turn);
                return;
            }
        }
    }

    // ONLY ACCESSED IF PIECE WAS NOT VALID
    printf("invalid piece");
    take_selection_input(bp_ptr, turn);
}

void take_movement_input(char *bp_ptr, int location, int turn)
{
    int destination;

    int row;
    int column;

    printf("\nWhere do you want to move? Choose a piece (EX: A3)\n");

    char input[3];

    scanf("%2s", input);

    if (input[0] == 'A')
    {
        column = 1;
    }
    else if (input[0] == 'B')
    {
        column = 2;
    }
    else if (input[0] == 'C')
    {
        column = 3;
    }
    else if (input[0] == 'D')
    {
        column = 4;
    }
    else if (input[0] == 'E')
    {
        column = 5;
    }
    else
    {
        printf("Error with input, choose a piece to move again");
        take_selection_input(bp_ptr, turn);
    }

    row = atoi(&input[1]); // The remaining part is the number

    if (row > 5 || row < 0)
    {
        printf("Error with input, choose a piece to move again");
        take_selection_input(bp_ptr, turn);
    }

    int validity = valid_movement(bp_ptr, location, ret_int(row, column), turn);

    if (validity == 1)
    {
        turn += 1;
        print_board(bp_ptr, turn);
    }
    else if (validity == 0)
    {
        printf("\nError with input, choose a piece to move again");
        take_selection_input(bp_ptr, turn);
    }
    else
    {
        printf("\n ALERT! CODE FAILURE IN MOVEMENT RETURN!");
    }
}

char *set_pieces(char piece, int position, char *bp_ptr, char is_setup)
{
    // First check if being called for setup
    // If yes, then set the entire array to 0
    // Might be able to remove the 'y' branch for optimization

    if (is_setup == 'y')
    {
        int i;
        for (i = 0; i < 25; ++i)
        {
            bp_ptr[i] = 'x';
        }
    }

    // If it's not setup, just set exactly the piece to the position specified

    else if (is_setup == 'n')
    {
        bp_ptr[position] = piece;
    }

    // Return the bp_ptr array with all the pieces

    return bp_ptr;
}

int main(void)
{
    // Switched smtn to remove the buffer from stdout
    setvbuf(stdout, NULL, _IONBF, 0);

    // 0 is top left, 4 is top right, 5 is below top left, 9 is below top right...
    // 20 is the bottom left, 24 is the bottom right
    // Pawn = 1, Rook = 2, Knight = 3, Bishop = 4, Queen = 5, King = 6
    char board_pieces[25];
    char *bp_ptr = board_pieces;
    set_pieces('x', 0, bp_ptr, 'y');

    int turnnumber = 1;

    int i;

    // Setup top & bottom pawns
    for (i = 5; i < 10; ++i)
    {
        set_pieces('p', i, bp_ptr, 'n');
        set_pieces('P', (i + 10), bp_ptr, 'n');
    }

    // Set black top side
    set_pieces('r', 0, bp_ptr, 'n');
    set_pieces('n', 1, bp_ptr, 'n');
    set_pieces('b', 2, bp_ptr, 'n');
    set_pieces('q', 3, bp_ptr, 'n');
    set_pieces('k', 4, bp_ptr, 'n');

    // Set white bot side
    set_pieces('R', 20, bp_ptr, 'n');
    set_pieces('N', 21, bp_ptr, 'n');
    set_pieces('B', 22, bp_ptr, 'n');
    set_pieces('Q', 23, bp_ptr, 'n');
    set_pieces('K', 24, bp_ptr, 'n');

    print_board(bp_ptr, turnnumber);

    return 0;
}

int valid_movement(char *bp_ptr, int location, int destination, int turn)
{

    // We setup "temp_piece" since all pieces move the same for black and white except the pawns
    char temp_piece;

    if (bp_ptr[location] == 'p' || bp_ptr[location] == 'P')
    {
        temp_piece = bp_ptr[location];
    }
    else
    {
        temp_piece = toupper(bp_ptr[location]);
    }

    int location_row = (location / 5) + 1;
    int location_col = (location % 5) + 1;
    int destination_row = (destination / 5) + 1;
    int destination_col = (destination % 5) + 1;

    // CHECK IF DESTINATION IS VALID
    if (location == destination)
    {
        return 0;
    }
    if (24 < destination || 0 > destination)
    {
        return 0;
    }

    switch (temp_piece)
    {
    case 'p':
        return black_pawn_movement(bp_ptr, location_row, location_col, destination_row, destination_col);

    case 'P':
        return white_pawn_movement(bp_ptr, location_row, location_col, destination_row, destination_col);

    case 'R':
        return rook_movement(bp_ptr, location_row, location_col, destination_row, destination_col);

    case 'N':
        return knight_movement(bp_ptr, location, destination);

    case 'B':
        return bishop_movement(bp_ptr, location_row, location_col, destination_row, destination_col);

    case 'Q':
        return queen_movement(bp_ptr, location_row, location_col, destination_row, destination_col);

    case 'K':
        return king_movement(bp_ptr, location_row, location_col, destination_row, destination_col);

    default:
        printf("ERROR: UNMATCHED PIECE MOVEMENT");
    }
}

int white_pawn_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col)
{

    if (d_row + 1 == l_row)
    {
        int location = ret_int(l_row, l_col);
        int destination = ret_int(d_row, d_col);

        int validifier = abs(d_col - l_col);

        if (validifier == 0)
        {
            bp_ptr[destination] = bp_ptr[location];
            bp_ptr[location] = 'x';
            return 1;
        }
        else if (validifier == 1 && bp_ptr[destination] != 'x')
        {
            // THIS STUFF REPEATEDLY GETS CALLED, CAN PROBABLY MOVE IT TO ANOTHER FUNCTION
            // TODO: TIRED TONIGHT <- WILL MOVE TMRW
            
            // CHECK IF IT WAS OWN PIECE THAT WAS SWALLOWED
            if (isupper(bp_ptr[destination]) == isupper(bp_ptr[location]))
            {
                printf("\nCan't attack own pieces!\n");
                return 0;
            }

            // CHECK IF YOU WIN!
            if (bp_ptr[location] == 'K' || bp_ptr[location] == 'k')
            {
                printf("\n WINNER \n");
                return 0;
            }

            bp_ptr[destination] = bp_ptr[location];
            bp_ptr[location] = 'x';
            return 1;
        }
    }

    return 0;
}

int black_pawn_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col)
{
    if (d_row - 1 == l_row)
    {
        int location = ret_int(l_row, l_col);
        int destination = ret_int(d_row, d_col);

        int validifier = abs(d_col - l_col);

        if (validifier == 0)
        {
            bp_ptr[destination] = bp_ptr[location];
            bp_ptr[location] = 'x';
            return 1;
        }
        else if (validifier == 1 && bp_ptr[destination] != 'x')
        {
            // CHECK IF IT WAS OWN PIECE THAT WAS SWALLOWED
            if (isupper(bp_ptr[destination]) == isupper(bp_ptr[location]))
            {
                printf("\nCan't attack own pieces!\n");
                return 0;
            }

            // CHECK IF YOU WIN!
            if (bp_ptr[location] == 'K' || bp_ptr[location] == 'k')
            {
                printf("\n WINNER \n");
                return 0;
            }
            bp_ptr[destination] = bp_ptr[location];
            bp_ptr[location] = 'x';
            return 1;
        }
    }

    return 0;
}

int rook_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col)
{
    int location = ret_int(l_row, l_col);
    int destination = ret_int(d_row, d_col);

    if (l_row == d_row)
    {
        int going_right;
        if (l_col > d_col)
        {
            going_right = 0;
        }
        else
        {
            going_right = 1;
        }

        int i;
        for (i = 1; i <= abs(l_col - d_col); ++i)
        {
            if (going_right)
            {
                if (bp_ptr[ret_int(l_row, l_col + i)] != 'x')
                {
                    return 0;
                }
            }
            else
            {
                if (bp_ptr[ret_int(l_row, l_col - i)] != 'x')
                {
                    return 0;
                }
            }
        }
        // CHECK IF IT WAS OWN PIECE THAT WAS SWALLOWED
        if (isupper(bp_ptr[destination]) == isupper(bp_ptr[location]))
        {
            printf("\nCan't attack own pieces!\n");
            return 0;
        }

        // CHECK IF YOU WIN!
        if (bp_ptr[location] == 'K' || bp_ptr[location] == 'k')
        {
            printf("\n WINNER \n");
            return 0;
        }

        bp_ptr[destination] = bp_ptr[location];
        bp_ptr[location] = 'x';
        return 1;
    }
    else if (l_col == d_col)
    {
        int going_up;
        if (l_row > d_row)
        {
            going_up = 1;
        }
        else
        {
            going_up = 0;
        }

        int i;
        for (i = 1; i < abs(l_row - d_row); ++i)
        {
            if (going_up)
            {
                if (bp_ptr[ret_int(l_row - i, l_col)] != 'x')
                {
                    return 0;
                }
            }
            else
            {
                if (bp_ptr[ret_int(l_row + i, l_col)] != 'x')
                {
                    return 0;
                }
            }
        }
        // CHECK IF IT WAS OWN PIECE THAT WAS SWALLOWED
        if (isupper(bp_ptr[destination]) == isupper(bp_ptr[location]))
        {
            printf("\nCan't attack own pieces!\n");
            return 0;
        }

        // CHECK IF YOU WIN!
        if (bp_ptr[location] == 'K' || bp_ptr[location] == 'k')
        {
            printf("\n WINNER \n");
            return 0;
        }

        bp_ptr[destination] = bp_ptr[location];
        bp_ptr[location] = 'x';
        return 1;
    }
    else
    {
        return 0;
    }
}

int knight_movement(char *bp_ptr, int location, int destination)
{
    // CHECKS IF THAT SPACE IS VALID (MAGIC MATH RIGHT HERE)
    int validation = abs(location - destination);
    if (validation == 3 || validation == 7 || validation == 9 || validation == 11)
    {
        // CHECK IF IT WAS OWN PIECE THAT WAS SWALLOWED
        if (isupper(bp_ptr[destination]) == isupper(bp_ptr[location]))
        {
            printf("\nCan't attack own pieces!\n");
            return 0;
        }

        // CHECK IF YOU WIN!
        if (bp_ptr[location] == 'K' || bp_ptr[location] == 'k')
        {
            printf("\n WINNER \n");
            return 0;
        }

        // IF NO ERRORS HAPPENED IN THE MOVEMENT, YOU CAN MOVE
        bp_ptr[destination] = bp_ptr[location];
        bp_ptr[location] = 'x';
        return 1;
    }
    else
    {
        return 0;
    }
}

int bishop_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col)
{

    int location = ret_int(l_row, l_col);
    int destination = ret_int(d_row, d_col);

    if (abs(d_row - l_row) == abs(d_col - l_col))
    {
        // CHECKING FOR IN BETWEENS
        int going_right;
        int going_down;

        if (d_row > l_row)
        {
            going_down = 1;
        }
        else
        {
            going_down = 0;
        }

        if (d_col > l_col)
        {
            going_right = 1;
        }
        else
        {
            going_right = 0;
        }

        int i;

        for (i = 1; i < abs(l_row - d_row); ++i)
        {
            if (going_right)
            {
                if (going_down)
                {
                    if (bp_ptr[ret_int(l_row + i, l_col + i)] != 'x')
                    {
                        return 0;
                    }
                }
                else
                {
                    if (bp_ptr[ret_int(l_row - i, l_col + i)] != 'x')
                    {
                        return 0;
                    }
                }
            }
            else
            {
                if (going_down)
                {
                    if (bp_ptr[ret_int(l_row + i, l_col - i)] != 'x')
                    {
                        return 0;
                    }
                }
                else
                {
                    if (bp_ptr[ret_int(l_row - i, l_col - i)] != 'x')
                    {
                        return 0;
                    }
                }
            }
        }

        // CHECK IF IT WAS OWN PIECE THAT WAS SWALLOWED
        if (isupper(bp_ptr[destination]) == isupper(bp_ptr[location]))
        {
            printf("\nCan't attack own pieces!\n");
            return 0;
        }

        // CHECK IF YOU WIN!
        if (bp_ptr[location] == 'K' || bp_ptr[location] == 'k')
        {
            printf("\n WINNER \n");
            return 0;
        }

        // IF NO ERRORS HAPPENED IN THE MOVEMENT, YOU CAN MOVE
        bp_ptr[destination] = bp_ptr[location];
        bp_ptr[location] = 'x';

        return 1;
    }

    else
    {
        return 0;
    }
}

int queen_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col)
{
    int location = ret_int(l_row, l_col);
    int destination = ret_int(d_row, d_col);

    // JUST A COPY PASTE OF ROOK AND BISHOP

    if (l_row == d_row)
    {
        int going_right;
        if (l_col > d_col)
        {
            going_right = 0;
        }
        else
        {
            going_right = 1;
        }

        int i;
        for (i = 1; i <= abs(l_col - d_col); ++i)
        {
            if (going_right)
            {
                if (bp_ptr[ret_int(l_row, l_col + i)] != 'x')
                {
                    return 0;
                }
            }
            else
            {
                if (bp_ptr[ret_int(l_row, l_col - i)] != 'x')
                {
                    return 0;
                }
            }
        }
        // CHECK IF IT WAS OWN PIECE THAT WAS SWALLOWED
        if (isupper(bp_ptr[destination]) == isupper(bp_ptr[location]))
        {
            printf("\nCan't attack own pieces!\n");
            return 0;
        }

        // CHECK IF YOU WIN!
        if (bp_ptr[location] == 'K' || bp_ptr[location] == 'k')
        {
            printf("\n WINNER \n");
            return 0;
        }

        bp_ptr[destination] = bp_ptr[location];
        bp_ptr[location] = 'x';
        return 1;
    }
    else if (l_col == d_col)
    {
        int going_up;
        if (l_row > d_row)
        {
            going_up = 1;
        }
        else
        {
            going_up = 0;
        }

        int i;
        for (i = 1; i < abs(l_row - d_row); ++i)
        {
            if (going_up)
            {
                if (bp_ptr[ret_int(l_row - i, l_col)] != 'x')
                {
                    return 0;
                }
            }
            else
            {
                if (bp_ptr[ret_int(l_row + i, l_col)] != 'x')
                {
                    return 0;
                }
            }
        }
        // CHECK IF IT WAS OWN PIECE THAT WAS SWALLOWED
        if (isupper(bp_ptr[destination]) == isupper(bp_ptr[location]))
        {
            printf("\nCan't attack own pieces!\n");
            return 0;
        }

        // CHECK IF YOU WIN!
        if (bp_ptr[location] == 'K' || bp_ptr[location] == 'k')
        {
            printf("\n WINNER \n");
            return 0;
        }

        bp_ptr[destination] = bp_ptr[location];
        bp_ptr[location] = 'x';
        return 1;
    }
    else if (abs(d_row - l_row) == abs(d_col - l_col))
    {
        // CHECKING FOR IN BETWEENS
        int going_right;
        int going_down;

        if (d_row > l_row)
        {
            going_down = 1;
        }
        else
        {
            going_down = 0;
        }

        if (d_col > l_col)
        {
            going_right = 1;
        }
        else
        {
            going_right = 0;
        }

        int i;

        for (i = 1; i < abs(l_row - d_row); ++i)
        {
            if (going_right)
            {
                if (going_down)
                {
                    if (bp_ptr[ret_int(l_row + i, l_col + i)] != 'x')
                    {
                        return 0;
                    }
                }
                else
                {
                    if (bp_ptr[ret_int(l_row - i, l_col + i)] != 'x')
                    {
                        return 0;
                    }
                }
            }
            else
            {
                if (going_down)
                {
                    if (bp_ptr[ret_int(l_row + i, l_col - i)] != 'x')
                    {
                        return 0;
                    }
                }
                else
                {
                    if (bp_ptr[ret_int(l_row - i, l_col - i)] != 'x')
                    {
                        return 0;
                    }
                }
            }
        }

        // CHECK IF IT WAS OWN PIECE THAT WAS SWALLOWED
        if (isupper(bp_ptr[destination]) == isupper(bp_ptr[location]))
        {
            printf("\nCan't attack own pieces!\n");
            return 0;
        }

        // CHECK IF YOU WIN!
        if (bp_ptr[location] == 'K' || bp_ptr[location] == 'k')
        {
            printf("\n WINNER \n");
            return 0;
        }

        // IF NO ERRORS HAPPENED IN THE MOVEMENT, YOU CAN MOVE
        bp_ptr[destination] = bp_ptr[location];
        bp_ptr[location] = 'x';

        return 1;
    }

    else
    {
        return 0;
    }
}

int king_movement(char *bp_ptr, int l_row, int l_col, int d_row, int d_col)
{
    int location = ret_int(l_row, l_col);
    int destination = ret_int(d_row, d_col);
    
    if (((d_col-l_col) == 0 || abs(d_col-l_col) == 1) && ((d_row-l_row) == 0 || abs(d_row-l_row) == 1))
    {
        // CHECK IF IT WAS OWN PIECE THAT WAS SWALLOWED
        if (isupper(bp_ptr[destination]) == isupper(bp_ptr[location]))
        {
            printf("\nCan't attack own pieces!\n");
            return 0;
        }

        // CHECK IF YOU WIN!
        if (bp_ptr[location] == 'K' || bp_ptr[location] == 'k')
        {
            printf("\n WINNER \n");
            return 0;
        }

        // IF NO ERRORS HAPPENED IN THE MOVEMENT, YOU CAN MOVE
        bp_ptr[destination] = bp_ptr[location];
        bp_ptr[location] = 'x';
        return 1;
    }
    else
    {
        return 0;
    }
}