#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_COMMAND_LEN 10

enum EXP_TYPE {
    ADD, SUB, MUL, DIV, BAD_EXP
};
enum OPERAND_TYPE {
    VALUE, VAR_X, BAD_OPERAND
};
enum WHOM_TO_OUTPUT {
    CURRENT, ALL_EXP, NONE
};
enum ACTION {
    PRINT, EVAL
};

typedef int BOOL;
#define TRUE 1
#define FALSE 0

int x = 0;


typedef struct Operand {
    enum OPERAND_TYPE type;
    int val; // value, valid if this is not a variable
} Operand;


typedef struct Exp { // binary expression
    enum EXP_TYPE type;
    struct Operand oper1, oper2;
} Exp;


typedef struct Node {
    struct Exp *expr;
    struct Node *next;
} Node;

typedef struct list {
    Node *head;
    Node *tail;
} List;


//list functions:
BOOL is_empty_list(List *lst);

void make_empty_list(List *lst);

void insert_data_to_end_of_list(List *lst, Exp *data);

Node *create_new_list_node(Exp *data, Node *nxt);

void insert_node_end_of_list(List *lst, Node *newTail);

void free_list(List *lst);

void free_list_helper(Node *head);


//generic functions:
void interpret_operator_and_operands(char *operator, char *operands, List* list);

BOOL check_if_last_input(char *str);

enum EXP_TYPE determine_expression_type(char *operator);

void print_operand(Operand operand);

int calc_expression(Exp *exp);

void get_operands(Exp *exp, char *operand);

void assign_operand(Operand *oper, char *val);

int assign_operator_x(char *str);

void finish_output(List *list, BOOL eval_flag, BOOL tous_flag);

void print_last_output(List *list, BOOL eval_flag);

void print_all_output(Node *node, BOOL eval_flag);

void print_x_assign(char *operands);

