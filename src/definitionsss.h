#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct map_t {
    char name[3];
    int info;
    char second_name[3];
    int second_info;
    int is_on;
} map;

typedef struct game_info_t {
    char game_name[20];
    char detective_name[20];
    char mr_jack_name[20];
    char mr_jack_character[3];
    int round;
    int turn;
} game_info;

typedef struct character_t {
    char name[3];
    struct character_t *next;
} character;

struct character_t *Create_node(FILE *fp) {
    struct character_t *new_node = (struct character_t *) malloc(sizeof(struct character_t));
    fscanf(fp, "%s %*d\n", new_node->name);
    return new_node;
}

void Add_node(struct character_t **head, FILE *fp) {
    if (*head == NULL) {
        (*head) = Create_node(fp);
        (*head)->next = NULL;
        return;
    }
    struct character_t *seek = *head;
    while (seek->next) {
        seek = seek->next;
    }
    struct character_t *new_node = Create_node(fp);
    seek->next = new_node;
    new_node->next = NULL;
}