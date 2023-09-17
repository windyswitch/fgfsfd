#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct ShoppingItem {
    char name[50];
    int quantity;
    struct ShoppingItem* next;
};

struct ShoppingItem* shoppingList = NULL;

//1. �����Ʒ�������嵥��
void addItem(char itemName[], int itemQuantity) {
    struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
    strcpy(newItem->name, itemName);
    newItem->quantity = itemQuantity;
    newItem->next = NULL;

    if (shoppingList == NULL) {
        shoppingList = newItem;
    } else {
        struct ShoppingItem* current = shoppingList;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newItem;
    }
}

//2. �ӹ����嵥���Ƴ���Ʒ��
void removeItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* previous = NULL;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                shoppingList = current->next;
            }
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }
}

//3. �鿴�����嵥��
void displayList() {
    struct ShoppingItem* current = shoppingList;
    printf("�����嵥:\n");
    while (current != NULL) {
        printf("%s - ������%d\n", current->name, current->quantity);
        current = current->next;
    }
}

//4. �޸Ĺ����嵥����Ʒ��������
void updateQuantity(char itemName[], int newItemQuantity) {
    struct ShoppingItem* current = shoppingList;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            current->quantity = newItemQuantity;
            break;
        }
        current = current->next;
    }
}

//5. ��չ����嵥��
void clearList() {
    struct ShoppingItem* current = shoppingList;
    while (current != NULL) {
        struct ShoppingItem* temp = current;
        current = current->next;
        free(temp);
    }
    shoppingList = NULL;
}

//6. ���㹺���嵥����Ʒ����������
int totalQuantity() {
    struct ShoppingItem* current = shoppingList;
    int total = 0;
    while (current != NULL) {
        total += current->quantity;
        current = current->next;
    }
    return total;
}

//7. ���ҹ����嵥�е���Ʒ��
void findItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    printf("������Ʒ \"%s\" ��\n", itemName);
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            printf("%s - ������%d\n", current->name, current->quantity);
            return;
        }
        current = current->next;
    }
    printf("δ�ҵ���Ʒ \"%s\"��\n", itemName);
}

//8. �������嵥��
void sortList() {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* nextItem = NULL;
    char tempName[50];
    int tempQuantity;
    while (current != NULL) {
        nextItem = current->next;
        while (nextItem != NULL) {
            if (strcmp(current->name, nextItem->name) > 0) {
                strcpy(tempName, current->name);
                tempQuantity = current->quantity;

                strcpy(current->name, nextItem->name);
                current->quantity = nextItem->quantity;

                strcpy(nextItem->name, tempName);
                nextItem->quantity = tempQuantity;
            }
            nextItem = nextItem->next;
        }
        current = current->next;
    }
}

//9. �ϲ������嵥��
void mergeLists(struct ShoppingItem** list1, struct ShoppingItem** list2) {
    if (*list1 == NULL) {
        *list1 = *list2;
    } else {
        struct ShoppingItem* current = *list1;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = *list2;
    }
    *list2 = NULL;
}

//10. ɾ�������嵥�е���Ʒ��
void deleteItem(char itemName[], int deleteAll) {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            if (prev == NULL) {
                struct ShoppingItem* temp = shoppingList;
                shoppingList = shoppingList->next;
                free(temp);
                if (!deleteAll) break;
            } else {
                struct ShoppingItem* temp = current;
                prev->next = current->next;
                current = current->next;
                free(temp);
                if (!deleteAll) break;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

int main() {
    printf("��ӭʹ�ù����嵥����ϵͳ��\n");

    while (1) {
        printf("\n��ѡ��Ҫִ�еĲ�����\n");
        printf("1. �����Ʒ���嵥\n");
        printf("2. ���嵥���Ƴ���Ʒ\n");
        printf("3. �鿴�����嵥\n");
        printf("4. �޸���Ʒ����\n");
        printf("5. ��չ����嵥\n");
        printf("6. ������Ʒ\n");
        printf("7. �������嵥\n");
        printf("8. �ϲ���һ���嵥\n");
        printf("9. ɾ����Ʒ\n");
        printf("0. �˳�����\n");

        int choice;
        printf("������ѡ�");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItemFromUserInput();
                break;

            case 2:
                removeItemFromUserInput();
                break;

            case 3:
                displayList();
                break;

            case 4:
                updateQuantityFromUserInput();
                break;

            case 5:
                clearList();
                printf("�����嵥����ա�\n");
                break;

            case 6:
                findItemFromUserInput();
                break;

            case 7:
                sortList();
                printf("�����嵥������\n");
                break;

            case 8:
                // �ϲ�������������Ҫ�ṩ��ϸ��Ϣ��
                printf("���ںϲ���һ���嵥\n");
                break;

            case 9:
                // ������ɾ����Ʒ��������Ҫ�ṩ��ϸ��Ϣ��
                printf("���ڰ�����ɾ����Ʒ\n");
                break;

            case 0:
                printf("�����˳������ټ���\n");
                return 0;

            default:
                printf("��Чѡ������ԡ�\n");
        }
    }

    return 0;
}
