#include <stdio.h>

void take_input();


void print_board(int *bp_ptr)
{
    printf("\n------");

    int i;
    for (i = 0; i < 25; ++i)
    {
        if (i % 5 == 0)
        {
            printf("\n");
        }
        printf("%d", bp_ptr[i]);
    }

    printf("\n------");
    printf("\nPawn = 1, Rook = 2, Knight = 3, Bishop = 4, Queen = 5, King = 6");
    take_input();
}

void take_input()
{    
    int row, column;
    printf("\n------");

    // TODO: Input validation

    printf("\nYou want to move the piece on row... ");
    scanf("%d", &row);

    printf("\nYou want to move the piece on column... ");
    scanf("%d", &column);

    // TODO:
    // Use int row and int column to find the piece from 0-24
    // Return the position of the piece and whether it is valid to move

    printf("%d %d", row, column);

}

int *set_pieces(int piece, int position, int *bp_ptr, char is_setup)
{
    if (is_setup == 'y')
    {
        int i;
        for (i = 0; i < 25; ++i)
        {
            bp_ptr[i] = 0;
        }
    }

    else if (is_setup == 'n')
    {
        bp_ptr[position] = piece;
    }
    return bp_ptr;
}

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("running");
    // 0 is top left, 4 is top right, 5 is below top left, 9 is below top right...
    // 20 is the bottom left, 24 is the bottom right
    // Pawn = 1, Rook = 2, Knight = 3, Bishop = 4, Queen = 5, King = 6
    int board_pieces[25];
    int *bp_ptr = board_pieces;
    set_pieces(0, 0, bp_ptr, 'y');

    int i;

    // Setup top & bottom pawns
    for (i = 5; i < 10; ++i)
    {
        set_pieces(1, i, bp_ptr, 'n');
        set_pieces(1, (i + 10), bp_ptr, 'n');
    }

    // Set top side
    set_pieces(2, 0, bp_ptr, 'n');
    set_pieces(3, 1, bp_ptr, 'n');
    set_pieces(4, 2, bp_ptr, 'n');
    set_pieces(5, 3, bp_ptr, 'n');
    set_pieces(6, 4, bp_ptr, 'n');

    // Set top side
    set_pieces(2, 20, bp_ptr, 'n');
    set_pieces(3, 21, bp_ptr, 'n');
    set_pieces(4, 22, bp_ptr, 'n');
    set_pieces(5, 23, bp_ptr, 'n');
    set_pieces(6, 24, bp_ptr, 'n');

    print_board(bp_ptr);

    return 0;
}
