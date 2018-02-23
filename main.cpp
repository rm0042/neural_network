#include "aimodule.h"




matrix GetMask(matrix field){
    matrix mask = matrix(1, 9);
    for (int i = 0; i < 9; i++)
        if (roundpos(field[0][i]) == 0)
            mask[0][i] = 1.0;
        else
            mask[0][i] = 0;
    return mask;
}

matrix discretise(matrix x){
    int maxind = 0;
    for (int i = 1; i < 9; i++)
        if (x[0][i] > x[0][maxind]) maxind = i;
    matrix diskr_x = matrix(1, 9);
    diskr_x[0][maxind] = 1.0;
    return diskr_x;
}

void MakeTurn(matrix &field, matrix turn, int player){
    for (int i = 0; i < 9; i++)
        if (roundpos(turn[0][i]) == 1) field[0][i] = player;
}


void print_field(matrix field){
    for (int i = 0; i < 9; i++){
        if ((i > 0) && (i % 3 == 0)) printf("\n");
        printf("%ld", roundpos(field[0][i]));
    }
    printf("\n\n");
}


int GameOver(matrix field){
    int i;
    for (i = 0; i < 3; i++)
        if ((roundpos(field[0][i * 3]) > 0) &&
            (roundpos(field[0][i * 3]) == roundpos(field[0][i * 3 + 1]))
            && (roundpos(field[0][i * 3]) == roundpos(field[0][i * 3 + 2]))) return 2;
    for (i = 0; i < 3; i++)
        if ((roundpos(field[0][i]) > 0) &&
            (roundpos(field[0][i]) == roundpos(field[0][i + 3]))
            && (roundpos(field[0][i]) == roundpos(field[0][i + 6]))) return 2;

    if ((roundpos(field[0][0]) > 0)
        && (roundpos(field[0][0]) == roundpos(field[0][4]))
            && (roundpos(field[0][0]) == roundpos(field[0][8]))) return 2;
    if ((roundpos(field[0][2]) > 0)
        && (roundpos(field[0][2]) == roundpos(field[0][4]))
            && (roundpos(field[0][2]) == roundpos(field[0][6]))) return 2;
    for (i = 0; i < 9; i++)
        if (roundpos(field[0][i]) == 0) return 0;
    return 1;
}


matrix coords_to_turn(int x, int y){
    matrix turn = matrix(1, 9);
    turn[0][x * 3 + y] = 1.0;
    return turn;
}

void turn_to_coords(matrix turn, int &x, int &y){
    int ind;
    for (int i = 0; i < 9; i++)
        if (roundpos(turn[0][i]) == 1) ind = i;
    x = ind / 3;
    y = ind % 3;
}


int IsValidTurn(matrix field, matrix turn){
    int ind = -1;
    for (int i = 0; i < 9; i++)
        if (roundpos(turn[0][i]) == 1) ind = i;
    if (ind == -1) return 0;
    if (roundpos(field[0][ind]) > 0) return 0;
    return 1;
}



int main()
{
    // Инициализация ИИ
    aimodule<> ai1(5);
    ai1.AttachMemory(nullptr, 1000);
    ai1.SetLearnParams(20, 0.2);

    auto lambdahashf = [](long x)->int { return x % 1000; };
    ai1.SetCodeParams(3, lambdahashf, encode_matl, decode_datal);

    ai1.AddNeuralBlock(20);
    ai1.networks[0].AddLayers(1, 9, NO_BIAS);
    ai1.networks[0].AddLayers(2, 30, NO_BIAS);
    ai1.networks[0].AddLayers(1, 9, NO_BIAS);

    //Начало цикла игры

game_start:

    int status;
    printf("Play tic-tac-toe: enter '1'\n");
    printf("Exit: enter '0'\n");
    printf("Command: ");
    scanf("%d", &status);
    if (status != 1)
        if (status == 0) return 0;
            else goto game_start;


    int x, y, total;
    matrix field = matrix(1, 9);
    matrix prev = matrix(1, 9);
    matrix turn = matrix(1, 9);
    matrix mask = matrix(1, 9);

    while (true){
        mask = GetMask(field);
        turn = ai1.GetAction(0, field);
        turn = discretise(turn & mask);

        prev = field;
        MakeTurn(field, turn, 1);
        ai1.RemActResChain(prev, turn, field);
        turn_to_coords(turn, x, y);
        printf("AI turn: %d %d\n", x, y);
        print_field(field);

        if ((total = GameOver(field)) != 0){
            if (total == 1){
                ai1.RewardStateAction(0, field, 0.3, 0.8, 5);
                printf("Game over: Draw\n");
            } else {
                ai1.RewardStateAction(0, field, 0.5, 0.8, 5);
                printf("Game over: You Lost\n");
            }
            break;
        }

    user_turn:
        printf("Your turn: ");
        scanf("%d %d", &x, &y);
        turn = coords_to_turn(x, y);
        if (!IsValidTurn(field, turn)){
            printf("Invalid turn!\n");
            goto user_turn;
        }
        MakeTurn(field, turn, 2);
        print_field(field);

        if ((total = GameOver(field)) != 0){
            if (total == 1){
                ai1.RewardStateAction(0, field, 0.3, 0.8, 5);
                printf("Game over: Draw\n");
            } else {
                ai1.RewardStateAction(0, field, -0.1, 0.8, 5);
                printf("Game over: You Won\n");
            }
            break;
        }
    }

    goto game_start;



    return 0;
}





