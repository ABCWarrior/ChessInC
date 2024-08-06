#include <stdio.h>

void take_input(char *bp_ptr);

void print_board(char *bp_ptr)
{
    printf("\n------");

    // Loops from 0-24 and prints the int value of the bp_ptr array there
    int i;
    for (i = 0; i < 25; ++i)
    {
        if (i % 5 == 0)
        {
            printf("\n");
        }
        printf("%c", bp_ptr[i]);
    }

    // Information about int -> piece here
    printf("\n------");
    printf("\n p = pawn, k = king, q = queen, b = bishop, n = knight, r = rook : Lowercase is Black, Caps are White");

    // After printing, asks for input
    take_input(bp_ptr);
}

void take_input(char *bp_ptr)
{
    int row, column, selected;

    printf("\n------");

    // TODO: Input validation

    printf("\nYou want to move the piece on row... ");
    scanf("%d", &row);

    printf("\nYou want to move the piece on column... ");
    scanf("%d", &column);

    // Use int row and int column to find the piece from 0-24
    selected = bp_ptr[(row-1)*5 + (column-1)];
    
    // TODO:
    // Return the position of the piece and whether it is valid to move
    if(selected != 'e'){
        printf("valid until black white stuff comes in")
    }

    // Prints out whatever found (just a test)
    printf("%c", selected);

}

char *set_pieces(char piece, int position, char *bp_ptr, char is_setup)
{
    // First check if being called for setup
    // If yes, then set the entire array to 0
    // TODO: Might be able to remove the 'y' branch for optimization, but unsure right now

    if (is_setup == 'y')
    {
        int i;
        for (i = 0; i < 25; ++i)
        {
            bp_ptr[i] = 'e';
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
    int board_pieces[25];
    char *bp_ptr = board_pieces;
    set_pieces('e', 0, bp_ptr, 'y');

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

    print_board(bp_ptr);

    return 0;
}

void eligible_bishop_moves(){
    //
}