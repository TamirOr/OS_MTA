#include "headers.h"


int main() {

    List list;
    make_empty_list(&list);

    char operator_input[MAX_COMMAND_LEN];
    char operands_input[MAX_COMMAND_LEN];
    while (1) {
        scanf("%[^ ]%*c", operator_input);
        if (strchr(operator_input, 'N') || strchr(operator_input, 'X')) {
            scanf("%[^\n]%*c", operands_input);
        }

        interpret_operator_and_operands(operator_input, operands_input, &list);
        if (check_if_last_input(operator_input)) {
            break;
        }
    }
    free_list(&list);
    system("pause");
    return 0;
}

BOOL check_if_last_input(char *str) {
    return strchr(str, 'L') != NULL;
}

void interpret_operator_and_operands(char *operator, char *operands, List *list) {
    BOOL eval_flag = strchr(operator, 'E') ? EVAL : PRINT;
    BOOL tous_flag = strchr(operator, 'T') ? ALL_EXP : CURRENT;
    if (strchr(operator, 'N')) { // create new Data in List
        Exp *new_expression = (Exp *) malloc(sizeof(Exp));
        new_expression->type = determine_expression_type(operator);
        get_operands(new_expression, operands);
        insert_data_to_end_of_list(list, new_expression);
    } else if (strchr(operator, 'X')) { // assign new val into x var
        x = assign_operator_x(operands);
        print_x_assign(operands);
    }

    if (strchr(operator, 'P') || strchr(operator, 'E')) { // need to print or eval
        finish_output(list, eval_flag, tous_flag);
    }


}

enum EXP_TYPE determine_expression_type(char *operator) {
    if (strchr(operator, 'A')) {
        return ADD;
    } else if (strchr(operator, 'S')) {
        return SUB;
    } else if (strchr(operator, 'M')) {
        return MUL;
    } else if (strchr(operator, 'D')) {
        return DIV;
    } else return BAD_EXP;
}

void print_operator(enum EXP_TYPE operator) {
    switch (operator) {
        case ADD:
            printf(" + ");
            break;
        case SUB:
            printf(" - ");
            break;
        case MUL:
            printf(" * ");
            break;
        default: // case DIV
            printf(" / ");
    }
}

void print_expression(Exp *expression, BOOL eval_flag) {
    print_operand(expression->oper1);
    print_operator(expression->type);
    print_operand(expression->oper2);
    if (eval_flag == TRUE) {
        printf(" = ");
        printf("%d", calc_expression(expression));
    }
    printf("\n");
}

int calc_expression(Exp *exp) {
    int first_oper_holder = exp->oper1.type == VAR_X ? x : exp->oper1.val;
    int second_oper_holder = exp->oper2.type == VAR_X ? x : exp->oper2.val;
    switch (exp->type) {
        case ADD:
            return (first_oper_holder + second_oper_holder);
        case SUB:
            return (first_oper_holder - second_oper_holder);
        case MUL:
            return (first_oper_holder * second_oper_holder);
        default: // case DIV
            return (first_oper_holder / second_oper_holder);
    }
}


void print_operand(Operand operand) {
    if (operand.type == VALUE) {
        printf("%d", operand.val);
    } else {
        printf("X");
    }
}

void get_operands(Exp *exp, char *operands) {
    const char space[2] = " ";
    char *token;

    /* get first operand */
    token = strtok(operands, space);
    assign_operand(&exp->oper1, token);

    /* get second operand */
    token = strtok(NULL, space);
    if (token != NULL) {
        assign_operand(&exp->oper2, token);
    }
}

void assign_operand(Operand *oper, char *val) {
    if ((val[0] == 'X') || (val[0] == 'x')) {
        oper->type = VAR_X;
    } else {
        oper->type = VALUE;
        oper->val = atoi(val);
    }
}

int assign_operator_x(char *str) {
    return atoi(str);
}

void finish_output(List *list, BOOL eval_flag, BOOL tous_flag) {
    if (tous_flag == CURRENT) {
        print_last_output(list, eval_flag);
    } else {
        print_all_output(list->head, eval_flag);
    }
}

void print_last_output(List *list, BOOL eval_flag) {
    Node *last = list->head;
    while (last->next != NULL) last = last->next;
    print_expression(last->expr, eval_flag);
}

void print_all_output(Node *node, BOOL eval_flag) {
    if (node != NULL) {
        print_expression(node->expr, eval_flag);
        print_all_output(node->next, eval_flag);
    }
}

void print_x_assign(char *operands) {
    printf("X = %d", atoi(operands));
    printf("\n");
}


// Linked List basic functions implementation
void make_empty_list(List *lst) {
    lst->head = NULL;
    lst->tail = NULL;
}

void insert_data_to_end_of_list(List *lst, Exp *data) {
    Node *newTail;
    newTail = create_new_list_node(data, NULL);
    insert_node_end_of_list(lst, newTail);
}

Node *create_new_list_node(Exp *data, Node *nxt) {
    Node *newList;
    newList = malloc(sizeof(Node));
    newList->expr = malloc(sizeof(Exp *));

    newList->expr = data;
    newList->next = nxt;

    return newList;
}

void insert_node_end_of_list(List *lst, Node *newTail) {
    if (is_empty_list(lst)) {
        lst->head = newTail;
        lst->tail = newTail;
    } else {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }

}

BOOL is_empty_list(List *lst) {
    if (!lst->head)//the list is empty
        return TRUE;
    else //there is at least one struct at the list
        return FALSE;
}

void free_list(List *lst) {
    free_list_helper(lst->head);
}

void free_list_helper(Node *head) {
    if (head != NULL) {
        free_list_helper(head->next);
        free(head->expr);
        free(head);
    }
}