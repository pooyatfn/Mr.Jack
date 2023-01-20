#include <characters.h>

void start_game(int row, int column, map map_info[row][column], game_info gameInfo, character *suspects) {
    int round = 0 + gameInfo.round;
    int turn = 0 + gameInfo.turn;
    character_actions(row, column, map_info, gameInfo, suspects);
}

void initialize_game() {
    FILE *fp, *cfp;
    int menu, row = 9, column = 13;
    label :
    printf("\n\t1- PLAY NEW GAME\n\t2- LOAD GAME\n\t3- CUSTOMIZE MAP\n\t4- BACK TO MAIN MENU\n");
    scanf("%d", &menu);
    switch (menu) {
        case 1: {
            fp = fopen("default_map.txt", "r");
            if (!fp) {
                printf("CAN'T OPEN default_map!");
                goto label;
            }
            map map_info[row][column];
            fscanf(fp, "%*[^\n]%*c");
            for (int i = 0; i < row; ++i) {
                fscanf(fp, "%*c%*c%*c");
                for (int j = 0; j < column; ++j) {
                    fscanf(fp, " %s %d", map_info[i][j].name, &map_info[i][j].info);
                }
            }
            fclose(fp);
            game_info gameInfo;
            printf("ENTER FIRST PLAYER'S NAME,THE DETECTIVE:\n");
            fflush(stdin);
            gets(gameInfo.detective_name);
            fflush(stdin);
            printf("ENTER SECOND PLAYER'S NAME, MR JACK:\n");
            gets(gameInfo.mr_jack_name);
            gameInfo.turn = 1;
            gameInfo.round = 1;
            fp = fopen("action_characters.txt", "r");
            if (fp == NULL) {
                printf("CAN'T OPEN action_characters!");
                exit(-1);
            }
            character *suspects = NULL;
            for (int i = 0; i < 8; ++i) {
                Add_node(&suspects, fp);
            }
            fclose(fp);
            start_game(row, column, map_info, gameInfo, suspects);
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            printf("ENTER MAP SIZE :\nROW:");
            scanf("%d", &row);
            printf("COLUMN:");
            scanf("%d", &column);
            cfp = fopen("custom_map.txt", "w+");
            fprintf(cfp, "   ");
            for (int i = 0; i < column; ++i) {
                fprintf(cfp, "%-6d", i);
            }
            fprintf(cfp, "\n");
            for (int i = 0; i < row; ++i) {
                fprintf(cfp, "%d- \n", i);
            }
            printf("ENTER THE MAP YOU WANT IN custom_map TEXT FILE IN PROGRAM'S DIRECTORY\nENTER ANY CHARACTER WHEN IT'S READY\n");
            fclose(cfp);
            scanf("%*c%*c");
            cfp = fopen("custom_map.txt", "r");
            if (!cfp) {
                printf("CAN'T OPEN custom_map!");
                exit(-1);
            }
            map map_info[row][column];
            fscanf(cfp, "%*[^\n]%*c");
            for (int i = 0; i < row; ++i) {
                fscanf(cfp, "%*c%*c%*c");
                for (int j = 0; j < column; ++j) {
                    fscanf(cfp, " %s %d", map_info[i][j].name, &map_info[i][j].info);
                }
            }
            fclose(cfp);
            game_info gameInfo;
            printf("ENTER FIRST PLAYER'S NAME,THE DETECTIVE:\n");
            fflush(stdin);
            gets(gameInfo.detective_name);
            fflush(stdin);
            printf("ENTER SECOND PLAYER'S NAME, MR JACK:\n");
            gets(gameInfo.mr_jack_name);
            gameInfo.turn = 1;
            gameInfo.round = 1;
            fp = fopen("action_characters.txt", "r");
            if (fp == NULL) {
                printf("CAN'T OPEN action_characters!");
                exit(-1);
            }
            character *suspects = NULL;
            for (int i = 0; i < 8; ++i) {
                Add_node(&suspects, fp);
            }
            fclose(fp);
            start_game(row,column,map_info,gameInfo,suspects);
            break;
        }
        case 4:
            goto end;
        default:
            printf("WRONG INPUT! TRY AGAIN\n");
            goto label;
    }
    end :
    return;
}