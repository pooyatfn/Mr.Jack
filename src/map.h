void insert_map(int row, int column, map map_info[row][column]);

void set_color(int row, int column, int x, int y, map map_info[row][column]);

void insert_map(int row, int column, map map_info[row][column]) {
    printf("  ");
    for (int i = 0; i < column; ++i) {
        if (i % 2 == 0) {
            printf("_____");
        } else {
            printf("         ");
        }
    }
    printf("\n");
    static int x, y;
    for (int i = 0; i < row * 4 + 2; ++i) {
        for (int j = 0; j < column; ++j) {
            x = j;
            int tmp;
            if (j % 2 == 0) {
                tmp = i;
            } else {
                tmp = i - 2;
            }
            y = tmp / 4;
            if (y < 0)
                y = 0;
            if (j == 0) {
                if (i % 4 == 0 || i % 4 == 3) {
                    printf(" ");
                }
            }
            if (i % 4 == 0) {
                if (j % 2 == 0) {
                    if (i == row * 4 && j == 0) {
                        printf("      \\");
                    } else {
                        if (i != row * 4 || j != column - 1) {
                            printf("/     \\");
                        } else {
                            printf("/      ");
                        }
                    }
                } else {
                    printf("       ");
                }
            } else if (i % 4 == 1) {
                if (j % 2 == 0) {
                    if (i != 4 * row + 1 || j != 0) {
                        printf("/  ");
                    } else {
                        printf("   ");
                    }
                    set_color(row, column, x, y, map_info);
                    if (i != 4 * row + 1 || j != column - 1) {
                        printf("  \\");
                    } else {
                        printf("   ");
                    }
                } else {
                    if (i == 1) {
                        printf("_____");
                    } else if (x >= 10) {
                        printf("%d_%d_", x, y);
                    } else {
                        printf("_%d_%d_", x, y);
                    }
                }
            } else if (i % 4 == 2) {
                if (j % 2 == 0) {
                    printf("\\       /");
                } else {
                    printf("     ");
                }
            } else {
                if (j % 2 == 0) {
                    if (x >= 10) {
                        printf("\\%d_%d_/", x, y);
                    } else {
                        printf("\\_%d_%d_/", x, y);
                    }
                } else {
                    printf("  ");
                    set_color(row, column, x, y, map_info);
                    printf("  ");
                }
            }
            if (column % 2 == 0 && j == column - 1) {
                if ((i % 4 == 0 && i != 0) || (i % 4 == 1 && i != 1)) {
                    printf("/");
                } else if (i % 4 == 2 || i % 4 == 3) {
                    printf("\\");
                }
            }
        }
        printf("\n");
    }
}

void set_color(int row, int column, int x, int y, map map_info[row][column]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!strcmp(map_info[y][x].name, "SH") || !strcmp(map_info[y][x].name, "JW") || !strcmp(map_info[y][x].name, "JS")
        || !strcmp(map_info[y][x].name, "IL") || !strcmp(map_info[y][x].name, "MS") ||
        !strcmp(map_info[y][x].name, "SG")
        || !strcmp(map_info[y][x].name, "WG") || !strcmp(map_info[y][x].name, "JB")) {
        SetConsoleTextAttribute(hConsole, 9);
        printf("%-2s%d", map_info[y][x].name, map_info[y][x].info);
    } else if (!strcmp(map_info[y][x].name, "##")) {
        SetConsoleTextAttribute(hConsole, 2);
        printf("# #");
    } else if (!strcmp(map_info[y][x].name, "#_")) {
        SetConsoleTextAttribute(hConsole, 10);
        printf(" # ");
    } else if (!strcmp(map_info[y][x].name, "**")) {
        SetConsoleTextAttribute(hConsole, 14);
        printf("%-2s%d", map_info[y][x].name, map_info[y][x].info);
    } else if (!strcmp(map_info[y][x].name, "!!")) {
        SetConsoleTextAttribute(hConsole, 4);
        printf("%-2s%d", map_info[y][x].name, map_info[y][x].info);
    } else if (!strcmp(map_info[y][x].name, "OO")) {
        printf("()%d", map_info[y][x].info);
    } else {
        printf("   ");
    }
    SetConsoleTextAttribute(hConsole, 7);
}