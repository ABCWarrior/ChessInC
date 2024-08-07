#include <stdio.h>
#include <ctype.h>

// Function prototypes
void take_selection_input(char *bp_ptr, int turn);
int white_pawn_movement(char *bp_ptr, int location, int destination);
int black_pawn_movement(char *bp_ptr, int location, int destination);
int rook_movement(char *bp_ptr, int location, int destination);
int knight_movement(char *bp_ptr, int location, int destination);
int bishop_movement(char *bp_ptr, int location, int destination);
int queen_movement(char *bp_ptr, int location, int destination);
int king_movement(char *bp_ptr, int location, int destination);
void take_movement_input(char *bp_ptr, int location, int turn);
int valid_movement(char *bp_ptr, int location, int destination, int turn);

void print_board(char *bp_ptr, int turn)
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
    take_selection_input(bp_ptr, turn);
}

void take_selection_input(char *bp_ptr, int turn)
{
    int row, column, selected;

    printf("\n------");

    // TODO: Input validation

    printf("\nYou want to move the piece on row... ");
    scanf("%d", &row);

    printf("\nYou want to move the piece on column... ");
    scanf("%d", &column);

    // Use int row and int column to find the piece from 0-24
    selected = bp_ptr[(row - 1) * 5 + (column - 1)];

    // TODO:
    // Return the position of the piece and whether it is valid to move

    if (selected != 'e')
    {

        // Confirmed is a piece

        int temp_int = turn % 2;

        // WHITE TURN
        if (temp_int == 1)
        {
            if (isupper(selected))
            {
                printf("%c is valid", selected);
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

    printf("\nWhere do you want to move? (Using int for now for simplicity)\n");

    scanf("%d", &destination);

    int validity = valid_movement(bp_ptr, location, destination, turn);

    if (validity == 1)
    {
        printf("\nMovement success, change to next turn\n");
        turn += 1;
        print_board(bp_ptr, turn);
    }
    else if (validity == 0)
    {
        printf("\nMovement failure, retry");
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
    char board_pieces[25];
    char *bp_ptr = board_pieces;
    set_pieces('e', 0, bp_ptr, 'y');

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

    // TODO: CHECK AND MAKE SURE DESTINATION IS WITHIN 0 TO 24

    switch (temp_piece)
    {
    case 'p':
        return black_pawn_movement(bp_ptr, location, destination);

    case 'P':
        return white_pawn_movement(bp_ptr, location, destination);

    case 'R':
        return rook_movement(bp_ptr, location, destination);

    case 'N':
        return knight_movement(bp_ptr, location, destination);

    case 'B':
        return bishop_movement(bp_ptr, location, destination);

    case 'Q':
        return queen_movement(bp_ptr, location, destination);

    case 'K':
        return king_movement(bp_ptr, location, destination);

    default:
        printf("ERROR: UNMATCHED PIECE MOVEMENT");
    }
}

int white_pawn_movement(char *bp_ptr, int location, int destination)
{
    // CHECK IF DESTINATION IS LOGICAL (STRAIGHT UP), IF IT IS WITHIN BOUNDS, AND IF IT IS EMPTY
    if (destination == location - 5 && 0 <= (location - 5) && (location - 5) <= 24 && bp_ptr[location - 5] == 'e')
    {
        bp_ptr[location] = 'e';
        bp_ptr[destination] = 'P';
        return 1;
    }
    // CHECK IF DESTINATION IS LOGICAL (DIAGONAL RIGHT), IF IT IS WITHIN BOUNDS, AND IF IT HAS A PIECE
    else if (destination == location - 4 && 0 <= (location - 4) && (location - 4) <= 24 && bp_ptr[location - 4] != 'e')
    {
        // TODO: ADD A CHECK IF IT WAS KING THAT WAS SWALLOWED
        bp_ptr[location] = 'e';
        bp_ptr[destination] = 'P';
        return 1;
    }
    // CHECK IF DESTINATION IS LOGICAL (DIAGONAL LEFT), IF IT IS WITHIN BOUNDS, AND IF IT HAS A PIECE
    else if (destination == location - 6 && 0 <= (location - 6) && (location - 6) <= 24 && bp_ptr[location - 6] != 'e')
    {
        // TODO: ADD A CHECK IF IT WAS KING THAT WAS SWALLOWED
        bp_ptr[location] = 'e';
        bp_ptr[destination] = 'P';
        return 1;
    }
    else
    {
        return 0;
    }
}

int black_pawn_movement(char *bp_ptr, int location, int destination)
{
    // CHECK IF DESTINATION IS LOGICAL (STRAIGHT DOWN), IF IT IS WITHIN BOUNDS, AND IF IT IS EMPTY
    if (destination == location + 5 && 0 <= (location + 5) && (location + 5) <= 24 && bp_ptr[location + 5] == 'e')
    {
        bp_ptr[location] = 'e';
        bp_ptr[destination] = 'p';
        return 1;
    }
    // CHECK IF DESTINATION IS LOGICAL (DIAGONAL LEFT), IF IT IS WITHIN BOUNDS, AND IF IT HAS A PIECE
    else if (destination == location + 4 && 0 <= (location + 4) && (location + 4) <= 24 && bp_ptr[location + 4] != 'e')
    {
        // TODO: ADD A CHECK IF IT WAS KING OR AN OWN PIECE THAT WAS SWALLOWED
        bp_ptr[location] = 'e';
        bp_ptr[destination] = 'p';
        return 1;
    }
    // CHECK IF DESTINATION IS LOGICAL (DIAGONAL RIGHT), IF IT IS WITHIN BOUNDS, AND IF IT HAS A PIECE
    else if (destination == location + 6 && 0 <= (location + 6) && (location + 6) <= 24 && bp_ptr[location + 6] != 'e')
    {
        // TODO: ADD A CHECK IF IT WAS KING OR AN OWN PIECE THAT WAS SWALLOWED
        bp_ptr[location] = 'e';
        bp_ptr[destination] = 'p';
        return 1;
    }
    else
    {
        return 0;
    }
}

int rook_movement(char *bp_ptr, int location, int destination)
{
    // VERTICAL CHECK
    if (destination % 5 == location % 5 && destination != location)
    {
        // CHECK FOR OBSTACLES IN THE PATH HERE
        int i;
        for (i = -6; i < 6; ++i)
        {
            //IDK WHY BUT NOT SURE IF ABS IS WORKING HERE
            int unabs_temp_location = location + (5 * i);
            int temp_location = abs(unabs_temp_location);

            if (location > destination)
            {
                if (location > temp_location && temp_location > destination)
                {
                    if (bp_ptr[temp_location] != 'e')
                    {
                        printf("error, path not empty");
                        return 0;
                    }
                }
            }
            else
            {
                if (location < temp_location && temp_location < destination)
                {
                    if (bp_ptr[temp_location] != 'e')
                    {
                        printf("error, path not empty");
                        return 0;
                    }
                }
            }
        }

        // TODO: CHECK IF YOU ARE EATING YOUR OWN PIECE OR KING AND THROW ERROR
        

        // IF NO ERRORS HAPPENED IN THE VERTICAL MOVEMENT, YOU CAN MOVE
        bp_ptr[destination] = bp_ptr[location];
        bp_ptr[location] = 'e';

        // RETURN SUCCESS
        return 1;
    }

    // TODO: HORIZONTAL CHECK
    else if (destination != location && ((location/5) == (destination/5)))
    {
        // TODO: CHECK FOR IN BETWEENS

        // TODO: CHECK IF YOU ARE EATING YOUR OWN PIECE OR KING AND THROW ERROR

        // IF NO ERRORS HAPPENED IN THE VERTICAL MOVEMENT, YOU CAN MOVE
        bp_ptr[destination] = bp_ptr[location];
        bp_ptr[location] = 'e';

        // RETURN SUCCESS
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
        // TODO: CHECK IF YOU ARE EATING YOUR OWN PIECE OR KING AND THROW ERROR

        // IF NO ERRORS HAPPENED IN THE MOVEMENT, YOU CAN MOVE
        bp_ptr[destination] = bp_ptr[location];
        bp_ptr[location] = 'e';
        return 1;
    }
    else
    {
        return 0;
    }
}

int bishop_movement(char *bp_ptr, int location, int destination)
{

    int location_row = location/5;
    int location_col = location%5;
    int destination_row = destination/5;
    int destination_col = destination%5;;

    if(abs(destination_row - location_row) == abs(destination_col-location_col))
    {
    // TODO: CHECK FOR IN BETWEENS

    // TODO: CHECK IF YOU ARE EATING YOUR OWN PIECE OR KING AND THROW ERROR

    // IF NO ERRORS HAPPENED IN THE MOVEMENT, YOU CAN MOVE
    bp_ptr[destination] = bp_ptr[location];
    bp_ptr[location] = 'e';

    return 1;
    }

    else
    {
        return 0;
    }

}

int queen_movement(char *bp_ptr, int location, int destination)
{
}

int king_movement(char *bp_ptr, int location, int destination)
{
}