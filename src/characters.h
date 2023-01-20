#include "map.h"

struct character_t *create_odd_even_node(struct character_t *head);

void add_odd_even_node(character **first, character **second, character *head);

void char_action(char name[3], int row, int column, map map_info[row][column], character *suspects, game_info gameInfo, int *is_end);

void swap_map(int x1, int y1, int x2, int y2, int row, int column, map map_info[row][column], game_info *gameInfo, int *is_end);

void delete_node(struct character_t **head, int index);

void shuffle_list(character *head);

void swap_char_struct(character *head, int index);

void odd_even_round_characters(character *head, int turn);

void char_info_print(char name[2]);

void character_actions(int row, int column, map map_info[row][column], game_info gameInfo, character *suspects);

void character_actions(int row, int column, map map_info[row][column], game_info gameInfo, character *suspects) {
    FILE *fp = fopen("action_characters.txt", "r"), *saved_game;

    if (fp == NULL) {
        printf("CAN'T OPEN action_characters!");
        exit(-1);
    }
    int int_suspect = 0;
    character *tmp_index = suspects;
    while (tmp_index != NULL) {
        int_suspect++;
        tmp_index = tmp_index->next;
    }
    if (int_suspect == 8) {
        shuffle_list(suspects);
        shuffle_list(suspects);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        printf("\nMR JACK IS ");
        SetConsoleTextAttribute(hConsole, 4);
        printf("%s\n", suspects->name);
        strcpy(gameInfo.mr_jack_character, suspects->name);
        SetConsoleTextAttribute(hConsole, 7);
        delete_node(&suspects, 0);
    }
    character *head = NULL;
    for (int i = 0; i < 8; ++i) {
        Add_node(&head, fp);
    }
    fclose(fp);

    character *first = NULL;
    character *second = NULL;
    int char_num, save = 1, is_end = 0;
    for (; gameInfo.round <= 8; ++gameInfo.round) {
        if (gameInfo.round % 2 != 0) {
            shuffle_list(head);
            add_odd_even_node(&first, &second, head);
        }
        for (gameInfo.turn = 1; gameInfo.turn <= 4; ++gameInfo.turn) {
            insert_map(row, column, map_info);
            if (gameInfo.round % 2 == 1) {
                if (gameInfo.turn == 1 || gameInfo.turn == 4) {
                    printf("\nROUND %d. TURN %d. CHOOSE A CHARACTER %s:\n\n", gameInfo.round, gameInfo.turn,
                           gameInfo.detective_name);
                } else {
                    printf("\nROUND %d. TURN %d. CHOOSE A CHARACTER %s:\n\n", gameInfo.round, gameInfo.turn,
                           gameInfo.mr_jack_name);
                }
            } else if (gameInfo.turn == 1 || gameInfo.turn == 4) {
                printf("\nROUND %d. TURN %d. CHOOSE A CHARACTER %s:\n\n", gameInfo.round, gameInfo.turn,
                       gameInfo.mr_jack_name);
            } else {
                printf("\nROUND %d. TURN %d. CHOOSE A CHARACTER %s:\n\n", gameInfo.round, gameInfo.turn,
                       gameInfo.detective_name);
            }
            if (gameInfo.round % 2 != 0) {
                odd_even_round_characters(first, gameInfo.turn);
            } else {
                odd_even_round_characters(second, gameInfo.turn);
            }
            scanf("%d", &char_num);
            if (gameInfo.round % 2 != 0) {
                character *tmp = first;
                for (int i = 1; i < char_num; ++i) {
                    tmp = tmp->next;
                }
                char_action(tmp->name, row, column, map_info, suspects, gameInfo, &is_end);
                if (is_end == 1){
                    printf("ENTER ANY CHARACTER TO GO TO MAIN MENU\n");
                    scanf("%*c%*c");
                    goto end_label;
                }
                delete_node(&first, char_num - 1);
            } else {
                character *tmp = second;
                for (int i = 1; i < char_num; ++i) {
                    tmp = tmp->next;
                }
                char_action(tmp->name, row, column, map_info, suspects, gameInfo, &is_end);
                if (is_end == 1){
                    printf("ENTER ANY CHARACTER TO GO TO MAIN MENU\n");
                    scanf("%*c");
                    goto end_label;
                }
                delete_node(&second, char_num - 1);
            }
            printf("\n");
            printf("ENTER ANY CHARACTER TO CONTINUE\n");
            scanf("%*c%*c");
            system("cls");
        }
        printf("DO YO WANT TO SAVE GAME TILL NOW ?\n1) YES\n2) NO\n");
        scanf("%d", &int_suspect);
        if (int_suspect == 1) {
            if (save == 1) {
                printf("ENTER THE FILE NAME THAT YOU WANT TO SAVE GAME IN :\n");
                fflush(stdin);
                gets(gameInfo.game_name);
                strcat(gameInfo.game_name, ".txt");
                saved_game = fopen(gameInfo.game_name, "w");
                save = 2;
            }
            fprintf(saved_game, "%s %s %s %d %d\n", gameInfo.detective_name, gameInfo.mr_jack_name,
                    gameInfo.mr_jack_character, gameInfo.round, gameInfo.turn);
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < column; ++j) {
                    fprintf(saved_game, "%s %d  ", map_info[i][j].name, map_info[i][j].info);
                }
                fprintf(saved_game, "\n");
            }
            fclose(saved_game);
        }
    }
    end_label :{}
}

struct character_t *create_odd_even_node(struct character_t *head) {
    struct character_t *new_node = (struct character_t *) malloc(sizeof(character));
    strcpy(new_node->name, head->name);
    return new_node;
}

void add_odd_even_node(character **first, character **second, character *head) {
    character *seek = head;
    (*first) = create_odd_even_node(seek);
    seek = seek->next;
    (*first)->next = create_odd_even_node(seek);
    seek = seek->next;
    (*first)->next->next = create_odd_even_node(seek);
    seek = seek->next;
    (*first)->next->next->next = create_odd_even_node(seek);
    seek = seek->next;
    (*second) = create_odd_even_node(seek);
    seek = seek->next;
    (*second)->next = create_odd_even_node(seek);
    seek = seek->next;
    (*second)->next->next = create_odd_even_node(seek);
    seek = seek->next;
    (*second)->next->next->next = create_odd_even_node(seek);
}

void delete_node(struct character_t **head, int index) {
    character *current = *head;
    if (index == 0) {
        *head = (*head)->next;
        free(current);
        return;
    }
    for (int i = 0; i < index - 1; ++i, current = current->next);
    character *hold = current->next;
    current->next = current->next->next;
    free(hold);
}

void shuffle_list(character *head) {
    int rand_num;
    character *tmp = head;
    srand(time(NULL));
    for (int i = 8; i > 1; --i) {
        rand_num = rand() % i;
        swap_char_struct(tmp, rand_num);
        tmp = tmp->next;
    }
}

void swap_char_struct(character *head, int index) {
    character tmp;
    character *seek = head;
    for (int i = 0; i < index; ++i) {
        seek = seek->next;
    }
    strcpy(tmp.name, seek->name);
    strcpy(seek->name, head->name);
    strcpy(head->name, tmp.name);
}

void odd_even_round_characters(character *head, int turn) {
    character *seek = head;
    for (int i = 0; i < 5 - turn; ++i) {
        printf("%d- ", i + 1);
        char_info_print(seek->name);
        seek = seek->next;
    }
}

void char_info_print(char name[2]) {
    if (!strcmp(name, "SH")) {
        printf("SH: 1) MOVE 1 TO 3 HOUSES. 2) KNOWING THE IDENTITY OF A SUSPECT\n");
    } else if (!strcmp(name, "JW")) {
        printf("JW: 1) MOVE 1 TO 3 HOUSES. 2) GIVE DIRECTION TO THE LANTERN\n");
    } else if (!strcmp(name, "JS")) {
        printf("JS: 1) MOVE 1 TO 3 HOUSES. 2) MOVE THE LIGHTS\n");
    } else if (!strcmp(name, "IL")) {
        printf("IL: 1) MOVE 1 TO 3 HOUSES. 2) BLOCK OR OPEN A WAY OUT\n");
    } else if (!strcmp(name, "MS")) {
        printf("MS: 1) MOVE 1 TO 4 HOUSES. 2) SHE CAN PASS OVER BUILDINGS\n");
    } else if (!strcmp(name, "SG")) {
        printf("SG: 1) MOVE 1 TO 3 HOUSES. 2) BRING OTHER CHARACTERS TOTALLY 3 MOVEMENT CLOSER TO HIMSELF\n");
    } else if (!strcmp(name, "WG")) {
        printf("WG: 1) MOVE 1 TO 3 HOUSES OR EXCHANGE HIS LOCATION WITH THE LOCATION OF ANY OTHER CHARACTER.\n");
    } else if (!strcmp(name, "JB")) {
        printf("JB: 1) MOVE 1 TO 3 HOUSES. 2)  OPENS A MANHOLE AND CLOSES ANOTHER\n");
    }
}

void char_action(char name[3], int row, int column, map map_info[row][column], character *suspects, game_info gameInfo, int *is_end) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x1, y1, x2, y2, x_ability, y_ability, opt, tmp;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (!strcmp(name, map_info[i][j].name)) {
                x1 = j;
                y1 = i;
                break;
            }
        }
    }
    if (!strcmp(name, "SH")) {
        printf("WHERE DO YOU WANT TO GO ? ENTER COORDINATES x y:\n");
        scanf("%d%d", &x2, &y2);
        swap_map(x1, y1, x2, y2, row, column, map_info, &gameInfo, is_end);
        SetConsoleTextAttribute(hConsole, 4);
        printf("\n%s ", suspects->name);
        SetConsoleTextAttribute(hConsole, 7);
        printf("IS NOT MR JACK!\n");
        delete_node(&suspects, 1);
    } else if (!strcmp(name, "JW")) {
        printf("WHERE DO YOU WANT TO GO ? ENTER COORDINATES x y:\n");
        scanf("%d%d", &x2, &y2);
        swap_map(x1, y1, x2, y2, row, column, map_info, &gameInfo, is_end);
    } else if (!strcmp(name, "JS")) {
        printf("1- MOVE\n2- USE ABILITY\n");
        scanf("%d", &opt);
        switch (opt) {
            case 1: {
                label_JS :
                printf("WHERE DO YOU WANT TO GO ? ENTER COORDINATES x y:\n");
                scanf("%d%d", &x2, &y2);
                swap_map(x1, y1, x2, y2, row, column, map_info, &gameInfo, is_end);
                if (opt == 2) {
                    break;
                }
            }
            case 2: {
                printf("WHICH LIGHT DO YOU WANT TO TURN OFF ? ENTER COORDINATES X Y:\n");
                scanf("%d%d", &x_ability, &y_ability);
                printf("WHICH LIGHT DO YOU WANT TO TURN ON ? ENTER COORDINATES X Y:\n");
                scanf("%d%d", &x2, &y2);
                swap_map(x_ability, y_ability, x2, y2, row, column, map_info, &gameInfo, is_end);
                if (opt == 2) {
                    goto label_JS;
                }
            }
        }
    } else if (!strcmp(name, "IL")) {
        printf("WHERE DO YOU WANT TO GO ? ENTER COORDINATES x y:\n");
        scanf("%d%d", &x2, &y2);
        swap_map(x1, y1, x2, y2, row, column, map_info, &gameInfo, is_end);
        printf("WHICH WAY OUT DO YOU WANT TO CLOSE ? ENTER COORDINATES X Y:\n");
        scanf("%d%d", &x_ability, &y_ability);
        printf("WHICH WAY OUT DO YOU WANT TO OPEN ? ENTER COORDINATES X Y:\n");
        scanf("%d%d", &x2, &y2);
        swap_map(x_ability, y_ability, x2, y2, row, column, map_info, &gameInfo, is_end);
    } else if (!strcmp(name, "MS")) {
        printf("WHERE DO YOU WANT TO GO  ? (YOU CAN PASS OVER BUILDINGS) ENTER COORDINATES x y:\n");
        scanf("%d%d", &x2, &y2);
        swap_map(x1, y1, x2, y2, row, column, map_info, &gameInfo, is_end);
    } else if (!strcmp(name, "SG")) {
        printf("1- MOVE\n2- USE ABILITY\n");
        scanf("%d", &opt);
        switch (opt) {
            case 1: {
                SG_label :
                printf("WHERE DO YOU WANT TO GO ? ENTER COORDINATES x y:\n");
                scanf("%d%d", &x2, &y2);
                swap_map(x1, y1, x2, y2, row, column, map_info, &gameInfo, is_end);
                if (opt == 2){
                    break;
                }
            }
            case 2: {
                for (int i = 0; i < 3; ++i) {
                    printf("ENTER THE COORDINATES OF A CHARACTER YOU WANT TO MOVE :\n");
                    scanf("%d%d",&x2,&y2);
                    printf("ENTER DESTINATION'S COORDINATES x y :\n");
                    scanf("%d%d",&x_ability, &y_ability);
                    swap_map(x2,y2,x_ability,y_ability,row,column,map_info,&gameInfo,is_end);
                    if (i != 2) {
                        printf("IS YOUR MOVE OVER :\n1) YES\n2) NO\n");
                        scanf("%d",&tmp);
                        if (tmp == 2){
                            goto sss;
                        }
                        else {
                            break;
                        }
                    }
                    sss :{}
                }
                if (opt == 2 ){
                    goto SG_label;
                }
            }
        }
    } else if (!strcmp(name, "WG")) {
        printf("WHERE DO YOU WANT TO GO ? (YOU CAN EXCHANGE YOUR LOCATION WITH ANY OTHER CHARACTER'S)\n");
        scanf("%d%d", &x2, &y2);
        swap_map(x1, y1, x2, y2, row, column, map_info, &gameInfo, is_end);
    } else {
        printf("1- MOVE\n2- USE ABILITY\n");
        scanf("%d", &opt);
        switch (opt) {
            case 1: {
                label_JB :
                printf("WHERE DO YOU WANT TO GO ? ENTER COORDINATES x y:\n");
                scanf("%d%d", &x2, &y2);
                swap_map(x1, y1, x2, y2, row, column, map_info, &gameInfo, is_end);
                if (opt == 2) {
                    break;
                }
            }
            case 2: {
                printf("WHICH MANHOLE DO YOU WANT TO CLOSE ? ENTER COORDINATES x y :\n");
                scanf("%d%d", &x_ability, &y_ability);
                printf("WHICH MANHOLE DO YOU WANT TO OPEN ? ENTER COORDINATES x y :\n");
                scanf("%d%d", &x2, &y2);
                swap_map(x_ability, y_ability, x2, y2, row, column, map_info, &gameInfo, is_end);
                if (opt == 2) {
                    goto label_JB;
                }
            }
        }
    }
}

void swap_map(int x1, int y1, int x2, int y2, int row, int column, map map_info[row][column], game_info *gameInfo, int *is_end) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!strcmp(map_info[y2][x2].name, "##") || !strcmp(map_info[y2][x2].name, "#_")) {
        printf("\nCAN'T MOVE BUILDINGS !\n");
        return;
    }
    if (!strcmp(map_info[y2][x2].name, "SH") || !strcmp(map_info[y2][x2].name, "JW") ||
        !strcmp(map_info[y2][x2].name, "JS") || !strcmp(map_info[y2][x2].name, "IL") ||
        !strcmp(map_info[y2][x2].name, "MS") || !strcmp(map_info[y2][x2].name, "SG") ||
        !strcmp(map_info[y2][x2].name, "WG") || !strcmp(map_info[y2][x2].name, "JB")) {
        int yes_no;
        printf("DO YOU WANT TO ARREST ");
        SetConsoleTextAttribute(hConsole, 4);
        printf("%s ", map_info[y2][x2].name);
        SetConsoleTextAttribute(hConsole, 7);
        printf("?\n1) YES\n2) NO\n");
        scanf("%d",&yes_no);
        if (yes_no == 1){
            if (!strcmp(map_info[y2][x2].name,gameInfo->mr_jack_character)){
                printf("THE DETECTIVE ARRESTED THE MR JACK !\n%s WIN THE GAME ...\n", gameInfo->detective_name);
                *is_end = 1;
                return;
            }
            else {
                printf("THE DETECTIVE MISIDENTIFIED THE MR JACK !\n%s WIN THE GAME ...\n", gameInfo->mr_jack_name);
                *is_end = 1;
                return;
            }
        }
    }
    if (!strcmp(map_info[y2][x2].name, "!!") && strcmp(map_info[y1][x1].name, "!!")){
        if (!strcmp(map_info[y1][x1].name,gameInfo->mr_jack_character) && map_info[y2][x2].info == 1){
            printf("\nMR JACK ESCAPED !\n%s WIN THE GAME ...\n",gameInfo->mr_jack_name);
            *is_end = 1;
            return;
        }
        else {
            printf("\nTHIS ACTION CAN BE DONE!\n");
            return;
        }
    }
    map tmp;
    strcpy(tmp.name, map_info[y1][x1].name);
    tmp.info = map_info[y1][x1].info;
    tmp.second_info = map_info[y1][x1].second_info;
    strcpy(tmp.second_name, map_info[y1][x1].second_name);
    strcpy(map_info[y1][x1].name, map_info[y2][x2].name);
    map_info[y1][x1].info = map_info[y2][x2].info;
    map_info[y1][x1].second_info = map_info[y2][x2].second_info;
    strcpy(map_info[y1][x1].second_name, map_info[y2][x2].second_name);
    strcpy(map_info[y2][x2].name, tmp.name);
    strcpy(map_info[y2][x2].second_name, tmp.second_name);
    map_info[y2][x2].info = tmp.info;
    map_info[y2][x2].second_info = tmp.second_info;
}