#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FAILED NULL
#define STACK TREE

typedef struct NODE *TREE;
struct NODE
{
    char label;
    TREE leftmostChild, rightSibling;
};

// ⟨E⟩ → ⟨T⟩ ⟨ET⟩
// ⟨ET⟩ → | ⟨E⟩ | ϵ
// ⟨T⟩ → ⟨F⟩ ⟨TT⟩
// ⟨TT⟩ → & ⟨T⟩ | ϵ
// ⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
// ⟨S⟩ → ⟨B⟩ ⟨ST⟩
// ⟨ST⟩ → ⟨S⟩ | ϵ
// ⟨B⟩ → 0 | 1

// convert for easier use

// ⟨E⟩ → ⟨T⟩ ⟨Z⟩
// ⟨Z⟩ → | ⟨E⟩ | ϵ
// ⟨T⟩ → ⟨F⟩ ⟨Y⟩
// ⟨Y⟩ → & ⟨T⟩ | ϵ
// ⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
// ⟨S⟩ → ⟨B⟩ ⟨X⟩
// ⟨X⟩ → ⟨S⟩ | ϵ
// ⟨B⟩ → 0 | 1

TREE makeNode0(char x);
TREE makeNode1(char x, TREE t);
TREE makeNode2(char x, TREE t1, TREE t2);
TREE makeNode3(char x, TREE t1, TREE t2, TREE t3);
TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4);
TREE B();
TREE X();
TREE S();
TREE F();
TREE Y();
TREE T();
TREE Z();
TREE E();
TREE tableDrivenParse();
void printTree();
void prettyPrint();
int** createParseTable();

TREE parseTree;   
TREE parseTree2;  /* holds the result of the parse */
char *nextTerminal; /* current position in input string */

/**
 * Returns true if the current input symbol is the given char, otherwise false.
 */
bool lookahead(char c)
{
    return *nextTerminal == c;
}

/**
 * If the current input symbol is the given char, advance to the next
 * character of the input and return true, otherwise leave it and return false.
 */
bool match(char c)
{
    if (lookahead(c))
    {
        nextTerminal += 1;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Attempt to parse the given string as a string of balanced parentheses.
 * If the parse succeeds, return the parse tree, else return FAILED (NULL).
 */

TREE makeNode0(char x)
{
    TREE root;
    root = (TREE)malloc(sizeof(struct NODE));
    root->label = x;
    root->leftmostChild = NULL;
    root->rightSibling = NULL;
    return root;
}

TREE makeNode1(char x, TREE t)
{
    TREE root;
    root = makeNode0(x);
    root->leftmostChild = t;
    return root;
}

TREE makeNode2(char x, TREE t1, TREE t2)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    return root;
}

TREE makeNode3(char x, TREE t1, TREE t2, TREE t3)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    return root;
}

TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4)
{
    TREE root;
    root = makeNode1(x, t1);
    t1->rightSibling = t2;
    t2->rightSibling = t3;
    t3->rightSibling = t4;
    return root;
}

//Part 1

// ⟨E⟩ → ⟨T⟩ ⟨Z⟩
// ⟨Z⟩ → | ⟨E⟩ | ϵ
// ⟨T⟩ → ⟨F⟩ ⟨Y⟩
// ⟨Y⟩ → & ⟨T⟩ | ϵ
// ⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
// ⟨S⟩ → ⟨B⟩ ⟨X⟩
// ⟨X⟩ → ⟨S⟩ | ϵ
// ⟨B⟩ → 0 | 1

TREE B()
{
    // printf("Entered B\n");
    // printf("%c\n", *nextTerminal);
    if (lookahead('0'))
    { 
        if (match('0')){
            return makeNode1('B', makeNode0('0'));
        }    
    }
    else if (lookahead('1'))
    {
        if (match('1')){
            return makeNode1('B', makeNode0('1'));
        }
    }
    return FAILED;
}

// ⟨E⟩ → ⟨T⟩ ⟨Z⟩
// ⟨Z⟩ → | ⟨E⟩ | ϵ
// ⟨T⟩ → ⟨F⟩ ⟨Y⟩
// ⟨Y⟩ → & ⟨T⟩ | ϵ
// ⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
// ⟨S⟩ → ⟨B⟩ ⟨X⟩
// ⟨X⟩ → ⟨S⟩ | ϵ
// ⟨B⟩ → 0 | 1

TREE X() //ST
{
    // printf("Entered X\n");
    TREE check = S();
    if (check == NULL){
        return makeNode1('X', makeNode0('e'));
    } else {
        return makeNode1('X', check);
    }
}

// ⟨E⟩ → ⟨T⟩ ⟨Z⟩
// ⟨Z⟩ → | ⟨E⟩ | ϵ
// ⟨T⟩ → ⟨F⟩ ⟨Y⟩
// ⟨Y⟩ → & ⟨T⟩ | ϵ
// ⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
// ⟨S⟩ → ⟨B⟩ ⟨X⟩
// ⟨X⟩ → ⟨S⟩ | ϵ
// ⟨B⟩ → 0 | 1

TREE S()
{
    // printf("Entered S\n");
    TREE check1 = B();
    if (check1 == NULL)
    {
        return FAILED;
    }
    else
    {
        TREE check2 = X();
        if (check2 == NULL)
        {
            return FAILED;
        }
        else
        {
            return makeNode2('S', check1, check2);
        }
    }
}

// ⟨E⟩ → ⟨T⟩ ⟨Z⟩
// ⟨Z⟩ → | ⟨E⟩ | ϵ
// ⟨T⟩ → ⟨F⟩ ⟨Y⟩
// ⟨Y⟩ → & ⟨T⟩ | ϵ
// ⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
// ⟨S⟩ → ⟨B⟩ ⟨X⟩
// ⟨X⟩ → ⟨S⟩ | ϵ
// ⟨B⟩ → 0 | 1

TREE F()
{
    // printf("Entered F\n");
    if (lookahead('~'))
    {
        if (match('~'))
        {
            TREE check = F();
            if (check == NULL)
            {
                return FAILED;
            }
            return makeNode2('F', makeNode0('~'), check);
        }
        return FAILED;
    }
    else if (lookahead('('))
    {
        if (match('('))
        {
            TREE check = E();
            if (check == NULL)
            {
                return FAILED;
            }
            if (!match(')'))
            {
                return FAILED;
            }
            return makeNode3('F', makeNode0('('), check, makeNode0(')'));
        }

        return FAILED;
    }
    else
    {
        TREE check = S();
        if (check == NULL)
        {
            return FAILED;
            
        }
        return makeNode1('F', check);
    }
}

// ⟨E⟩ → ⟨T⟩ ⟨Z⟩
// ⟨Z⟩ → | ⟨E⟩ | ϵ
// ⟨T⟩ → ⟨F⟩ ⟨Y⟩
// ⟨Y⟩ → & ⟨T⟩ | ϵ
// ⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
// ⟨S⟩ → ⟨B⟩ ⟨X⟩
// ⟨X⟩ → ⟨S⟩ | ϵ
// ⟨B⟩ → 0 | 1

TREE Y() //TT
{
    // printf("Entered Y\n");
    if (!lookahead('&'))
    {
        return makeNode1('Y', makeNode0('e'));
    }
    else
    {
        if (!match('&'))
        {
            return FAILED;
        }
        else
        {
            TREE check = T();
            if (check == NULL)
            {
                return FAILED;
            }
            return makeNode2('Y', makeNode0('&'), check);
        }
    }
}

// ⟨E⟩ → ⟨T⟩ ⟨Z⟩
// ⟨Z⟩ → | ⟨E⟩ | ϵ
// ⟨T⟩ → ⟨F⟩ ⟨Y⟩
// ⟨Y⟩ → & ⟨T⟩ | ϵ
// ⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
// ⟨S⟩ → ⟨B⟩ ⟨X⟩
// ⟨X⟩ → ⟨S⟩ | ϵ
// ⟨B⟩ → 0 | 1

TREE T()
{
    // printf("Entered T\n");
    TREE check1 = F();
    if (check1 == NULL)
    {
        return FAILED;
    }
    else
    {
        TREE check2 = Y();
        if (check2 == NULL)
        {
            return FAILED;
        }
        else
        {
            return makeNode2('T', check1, check2);
        }
    }
}
// ⟨E⟩ → ⟨T⟩ ⟨Z⟩
// ⟨Z⟩ → | ⟨E⟩ | ϵ
// ⟨T⟩ → ⟨F⟩ ⟨Y⟩
// ⟨Y⟩ → & ⟨T⟩ | ϵ
// ⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
// ⟨S⟩ → ⟨B⟩ ⟨X⟩
// ⟨X⟩ → ⟨S⟩ | ϵ
// ⟨B⟩ → 0 | 1

TREE Z() //ET
{
    // printf("Entered Z\n");
    if (!lookahead('|'))
    {
        return makeNode1('Z', makeNode0('e'));
    }
    else
    {
        if (match('|'))
        {
            TREE check = E();
            if (check == NULL)
            {
                return FAILED;
            }
            return makeNode2('Z', makeNode0('|'), check);
        }
        return FAILED;
    }
}

// ⟨E⟩ → ⟨T⟩ ⟨Z⟩
// ⟨Z⟩ → | ⟨E⟩ | ϵ
// ⟨T⟩ → ⟨F⟩ ⟨Y⟩
// ⟨Y⟩ → & ⟨T⟩ | ϵ
// ⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
// ⟨S⟩ → ⟨B⟩ ⟨X⟩
// ⟨X⟩ → ⟨S⟩ | ϵ
// ⟨B⟩ → 0 | 1

TREE E()
{
    // printf("Entered E\n");
    TREE check1 = T();
    if (check1 == NULL)
    {
        return FAILED;
    }
    else
    {
        TREE check2 = Z();
        if (check2 == NULL)
        {
            return FAILED;
        }
        else
        {
            return makeNode2('E', check1, check2);
        }
    }
}

TREE parse(char *input)
{
    nextTerminal = input;
    TREE parseTree = E();
    if (parseTree != NULL && lookahead('\0'))
    {
        return parseTree;
    }
    else
    {
        return FAILED;
    }
}

void printTree(TREE final){
    int level = 0;

    if (final == NULL){
        printf("Null tree");
    } else {
        prettyPrint(final, level);
    } 
}

void prettyPrint(TREE tree, int level){
    for (int i = 0; i < level; i++){
        printf("  ");
    }
    printf("%c\n", tree->label);
    if(tree->leftmostChild!=NULL)
    {
        prettyPrint(tree->leftmostChild,level+1);
    }
    if(tree->rightSibling!=NULL)
    {
        prettyPrint(tree->rightSibling,level);
    }
}

void freeTree(TREE tree){
    if (tree == NULL){
        free(tree);
        return;
    } else {
        freeTree(tree -> leftmostChild);
        freeTree(tree -> rightSibling);
        free(tree);
    }
}

//Part 2

// 1: ⟨E⟩ → ⟨T⟩ ⟨Z⟩ 
// 2: ⟨Z⟩ → | ⟨E⟩
// 3: ⟨Z⟩ → ϵ
// 4: ⟨T⟩ → ⟨F⟩ ⟨Y⟩
// 5: ⟨Y⟩ → & ⟨T⟩
// 6: ⟨Y⟩ → ϵ
// 7: ⟨F⟩ → ~ ⟨F⟩
// 8: ⟨F⟩ → ( ⟨E⟩ )
// 9: ⟨F⟩ → ⟨S⟩
// 10: ⟨S⟩ → ⟨B⟩ ⟨X⟩
// 11: ⟨X⟩ → ⟨S⟩
// 12: ⟨X⟩ → ϵ
// 13: ⟨B⟩ → 0
// 14: ⟨B⟩ → 1

STACK stack[500];
int top = -1;
void push(STACK new){
    top++;
    stack[top] = new;
}

bool isEmpty(){
    if (top < 0){
        return true;
    }
    return false;
}
STACK pop(){
    if (isEmpty()){
        return NULL;
    }
    STACK new = stack[top];
    top--;
    return new;
}

int** createParseTable(){
    int** parseTable = (int**)malloc(8*sizeof(int*));
    for (int i = 0; i < 8; i++){
        parseTable[i] = (int*)malloc(9*sizeof(int));
    }

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 9; j++){
            parseTable[i][j] = 0;
        }
    }

    parseTable[0][0] = 1;
    parseTable[0][1] = 1;
    parseTable[0][2] = 1;
    parseTable[0][4] = 1;

    parseTable[1][6] = 2;
    parseTable[1][3] = 3;
    parseTable[1][7] = 3;
    parseTable[1][8] = 3;

    parseTable[2][0] = 4;
    parseTable[2][1] = 4;
    parseTable[2][2] = 4;
    parseTable[2][4] = 4;

    parseTable[3][5] = 5;
    parseTable[3][3] = 6;
    parseTable[3][6] = 6;
    parseTable[3][7] = 6;
    parseTable[3][8] = 6;

    parseTable[4][0] = 9;
    parseTable[4][1] = 9;
    parseTable[4][2] = 8;
    parseTable[4][4] = 7;

    parseTable[5][0] = 10;
    parseTable[5][1] = 10;

    parseTable[6][0] = 11;
    parseTable[6][1] = 11;
    parseTable[6][3] = 12;
    parseTable[6][5] = 12;
    parseTable[6][6] = 12;
    parseTable[6][7] = 12;
    parseTable[6][8] = 12;

    parseTable[7][0] = 13;
    parseTable[7][1] = 14;

    return parseTable;
}

void freeTable(int** table){
    for (int i = 0; i < 8; i++){
        free(table[i]);
    }
    free(table);
}

bool isTerminal(char label){
    if (label == '0' || label == '1' || label == '(' || label == ')'
    || label == '~' || label == '&' || label == '|'){
        return true;
    }
    return false;
}

int getRow(char label){
    if (label == 'E'){
        return 0;
    } else if (label == 'Z'){
        return 1;
    } else if (label == 'T'){
        return 2;
    } else if (label == 'Y'){
        return 3;
    } else if (label == 'F'){
        return 4;
    } else if (label == 'S'){
        return 5;
    } else if (label == 'X'){
        return 6;
    } else{
        return 7;
    }
}

int getColumn(char terminal){
    if (terminal == '0'){
        return 0;
    } else if (terminal == '1'){
        return 1;
    } else if (terminal == '('){
        return 2;
    } else if (terminal == ')'){
        return 3;
    } else if (terminal == '~'){
        return 4;
    } else if (terminal == '&'){
        return 5;
    } else if (terminal == '|'){
        return 6;
    } else if (terminal == 'e'){
        return 7;
    } else {
        return 8;
    }
}

TREE tableDrivenParse(char *input){
    int** parseTable = createParseTable();
    nextTerminal = input;
    TREE parseTree2 = makeNode0('E');
    push(parseTree2);
    while (!isEmpty()){
        TREE Y = pop();
        char check = Y->label;
        if (isTerminal(check)){
            if (!match(check) && check != 'e'){
                return FAILED;
            }
        } else {
            int row = getRow(check);
            int column = getColumn(*nextTerminal);
            // printf("Row: %d + Column: %d + Production: %d\n", row, column, parseTable[row][column]); 
            if (parseTable[row][column] == 1){
                TREE c1 = makeNode0('T');
                TREE c2 = makeNode0('Z');
                Y -> leftmostChild = c1;
                c1 -> rightSibling = c2;
                push(c2);
                push(c1);
                // printf("Z pushed\n");
            } else if (parseTable[row][column] == 2){
                TREE c1 = makeNode0('|');
                TREE c2 = makeNode0('E');
                Y -> leftmostChild = c1;
                c1 -> rightSibling = c2;
                push(c2);
                push(c1);
            } else if (parseTable[row][column] == 3){
                TREE c1 = makeNode0('e');
                Y -> leftmostChild = c1;
                push(c1);
                // printf("pushed e\n");
            } else if (parseTable[row][column] == 4){
                TREE c1 = makeNode0('F');
                TREE c2 = makeNode0('Y');
                Y -> leftmostChild = c1;
                c1 -> rightSibling = c2;
                push(c2);
                push(c1);
                // printf("Y pushed\n");
            } else if (parseTable[row][column] == 5){
                TREE c1 = makeNode0('&');
                TREE c2 = makeNode0('T');
                Y -> leftmostChild = c1;
                c1 -> rightSibling = c2;
                push(c2);
                push(c1);
            } else if (parseTable[row][column] == 6){
                TREE c1 = makeNode0('e');
                Y -> leftmostChild = c1;
                push(c1);
                // printf("pushed e\n");
            } else if (parseTable[row][column] == 7){
                TREE c1 = makeNode0('~');
                TREE c2 = makeNode0('F');
                Y -> leftmostChild = c1;
                c1 -> rightSibling = c2;
                push(c2);
                push(c1);   
            } else if (parseTable[row][column] == 8){
                TREE c1 = makeNode0('(');
                TREE c2 = makeNode0('E');
                TREE c3 = makeNode0(')');
                Y -> leftmostChild = c1;
                c1 -> rightSibling = c2;
                c2 -> rightSibling = c3;
                push(c3);
                push(c2);
                push(c1);   
            } else if (parseTable[row][column] == 9){
                TREE c1 = makeNode0('S');
                Y -> leftmostChild = c1;
                push(c1);
            } else if (parseTable[row][column] == 10){
                TREE c1 = makeNode0('B');
                TREE c2 = makeNode0('X');
                Y -> leftmostChild = c1;
                c1 -> rightSibling = c2;
                push(c2);
                push(c1);   
                // printf("X pushed\n");
            } else if (parseTable[row][column] == 11){
                TREE c1 = makeNode0('S');
                Y -> leftmostChild = c1;
                push(c1);
            } else if (parseTable[row][column] == 12){
                TREE c1 = makeNode0('e');
                Y -> leftmostChild = c1;
                push(c1);
                // printf("pushed e\n");
            } else if (parseTable[row][column] == 13){
                TREE c1 = makeNode0('0');
                Y -> leftmostChild = c1;
                push(c1);
            } else if (parseTable[row][column] == 14){
                TREE c1 = makeNode0('1');
                Y -> leftmostChild = c1;
                push(c1);
            }
        }
    }
    freeTable(parseTable);
    return parseTree2;
}

void repl(){
    printf("Enter a well-formed input (\"quit\" to quit): \n");
    char input[255];
    fgets(input, 255, stdin);
    input[strcspn(input, "\n")] = 0;
    bool well_formed = false;
    while (strcmp(input, "quit") != 0 && !well_formed){
        parseTree = parse(input);
        parseTree2 = tableDrivenParse(input);
        if (parseTree == NULL){
            printf("Not a well-formed input. Please enter again: \n");
            fgets(input, 255, stdin);
            input[strcspn(input, "\n")] = 0;
        } else {
            printf("Resulting tree from recursive-descent parsing: \n\n");
            printTree(parseTree);
            // printf("\nTree address: %p\n", parseTree);

            printf("\nResulting tree from table-driven parsing: \n\n");
            printTree(parseTree2);

            well_formed = true;
        }
        freeTree(parseTree);
        freeTree(parseTree2);
    }
}

int main()
{
    repl();
}