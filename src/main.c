#include "definitionsss.h"
#include "start_game.h"

void main_menu();

void about_us();

int main() {
    printf("\nWELCOME TO MR JACK GAME\n\n");
    int menu;
    while (1) {
        main_menu();
        scanf("%d", &menu);
        switch (menu) {
            case 1: {
                initialize_game();
                break;
            }
            case 2:
                break;
            case 3:
                about_us();
                break;
            case 4:
                printf("SEE YOU SOON!");
                exit(0);
            default:
                printf("WRONG INPUT! TRY AGAIN\n\n");
        }
        system("cls");
    }
}

void main_menu() {
    printf("\n\t1-START GAME\n\t2-GAME PLAY VIDEOS\n\t3-ABOUT US\n\t4-EXIT\n");
}

void about_us() {
    system("cls");
    printf("\n\tAMIRKABIR UNIVERSITY OF TECHNOLOGY FINAL PROJECT\n\n");
    printf("\tPROFESSOR : DOCTOR ZEYNALEE\n\n\tCREATOR : POOYA TOOFANIAN\n\n\tSTUDENT ID : 40031034\n\n\tWINTER 1400\n\n");
    printf("ENTER ANY CHARACTER TO CONTINUE\n");
    scanf("%*c%*c");
}