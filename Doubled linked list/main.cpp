#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 50

typedef struct FruitNode {
    char data[50];
    struct FruitNode* llink;
    struct FruitNode* rlink;
}FruitNode;

void init(FruitNode* phead)
{
    phead->llink = phead;
    phead->rlink = phead;
}

void print_fruit_list(FruitNode* phead, FruitNode* current_fruit)
{
    FruitNode* p;
    for (p = phead->rlink; p != phead; p = p->rlink)
    {
        if (p == current_fruit)
        {
            printf("%s [0]\n", p->data);
        }
        else
        {
            printf("%s\n", p->data);
        }
    }

    // current_fruit가 첫 번째 노드인 경우
    if (current_fruit == phead->rlink)
    {
        printf("Current Fruit: %s\n", current_fruit->data);
        printf("Next Fruit: %s\n", current_fruit->rlink->data);
        printf("Previous Fruit: %s\n", phead->llink->data);
    }
    else
    {
        // current_fruit가 마지막 노드인 경우
        if (current_fruit == phead->llink)
        {
            printf("Current Fruit: %s\n", current_fruit->data);
            printf("Next Fruit: %s\n", phead->rlink->data);
            printf("Previous Fruit: %s\n", current_fruit->llink->data);
        }
        else
        {
            printf("Current Fruit: %s\n", current_fruit->data);
            printf("Next Fruit: %s\n", current_fruit->rlink->data);
            printf("Previous Fruit: %s\n", current_fruit->llink->data);
        }
    }
    printf("\n");
}


void dinsert(FruitNode* before, char* fruit_data)
{
    FruitNode* newnode = (FruitNode*)malloc(sizeof(FruitNode));
    strcpy_s(newnode->data, fruit_data);
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

void ddelete(FruitNode* head, FruitNode* removed)
{
    if (removed == head)
    {
        return;
    }
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

int main()
{
    FruitNode head;
    init(&head);
    FruitNode* current_fruit = NULL;

    char menu;
    char fruit_data[MAX_NAME_LENGTH];

    while (1)
    {
        printf("\n==== Menu ====\n");
        printf("n) next fruit\n");
        printf("p) previous fruit\n");
        printf("d) delete the current fruit\n");
        printf("i) insert fruit after current fruit int\n");
        printf("o) output the fruit list(Output [0] at the end of the currently selected fruit)\n");
        printf("e) exit the program\n");
        printf("===============\n");
        printf("Select a menu: ");
        scanf_s(" %c", &menu);

        if (menu == 'n')
        {
            if (current_fruit != NULL && current_fruit->rlink != &head)
            {
                current_fruit = current_fruit->rlink;
            }
            /*else if (current_fruit->rlink->rlink == &head)
            {
                current_fruit = current_fruit->rlink->rlink;
            }*/
            else
            {
                printf("fruit list is empty.\n");
            }
        }

        else if (menu == 'p')
        {
            if (current_fruit != NULL && current_fruit->llink != &head)
            {
                current_fruit = current_fruit->llink;
            }
            /*else if (current_fruit == &head)
            {
                current_fruit = current_fruit->llink->llink;
            }*/
            else
            {
                printf("fruit list is empty.\n");
            }
        }

        else if (menu == 'd')
        {
            if (current_fruit != NULL)
            {
                FruitNode* temp = current_fruit;
                current_fruit = current_fruit->rlink;
                ddelete(&head, temp);
                free(temp);
            }
            else
            {
                printf("fruit list is empty.\n");
            }
        }

        else if (menu == 'i')
        {
            printf("Enter the name mof the fruit to add: ");
            scanf_s("%s", fruit_data, MAX_NAME_LENGTH);
            if (current_fruit == NULL)
            {
                dinsert(&head, fruit_data);
                current_fruit = head.rlink;
            }
            else
            {
                dinsert(current_fruit, fruit_data);
                current_fruit = current_fruit->rlink;
            }
        }
        else if (menu == 'o')
        {
            print_fruit_list(&head, current_fruit);
        }
        else if (menu == 'e')
        {
            printf("Exit the program\n");
            return 0;
        }
        else
        {
            printf("Invalid menu.\n");
        }
    }
}
