#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct ShoppingItem {
    char name[50];
    int quantity;
    struct ShoppingItem* next;
};

struct ShoppingItem* shoppingList = NULL;

//1. 添加商品到购物清单：
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

//2. 从购物清单中移除商品：
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

//3. 查看购物清单：
void displayList() {
    struct ShoppingItem* current = shoppingList;
    printf("购物清单:\n");
    while (current != NULL) {
        printf("%s - 数量：%d\n", current->name, current->quantity);
        current = current->next;
    }
}

//4. 修改购物清单中商品的数量：
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

//5. 清空购物清单：
void clearList() {
    struct ShoppingItem* current = shoppingList;
    while (current != NULL) {
        struct ShoppingItem* temp = current;
        current = current->next;
        free(temp);
    }
    shoppingList = NULL;
}

//6. 计算购物清单中商品的总数量：
int totalQuantity() {
    struct ShoppingItem* current = shoppingList;
    int total = 0;
    while (current != NULL) {
        total += current->quantity;
        current = current->next;
    }
    return total;
}

//7. 查找购物清单中的商品：
void findItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    printf("查找商品 \"%s\" ：\n", itemName);
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            printf("%s - 数量：%d\n", current->name, current->quantity);
            return;
        }
        current = current->next;
    }
    printf("未找到商品 \"%s\"。\n", itemName);
}

//8. 排序购物清单：
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

//9. 合并购物清单：
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

//10. 删除购物清单中的商品：
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
    printf("欢迎使用购物清单管理系统！\n");

    while (1) {
        printf("\n请选择要执行的操作：\n");
        printf("1. 添加商品到清单\n");
        printf("2. 从清单中移除商品\n");
        printf("3. 查看购物清单\n");
        printf("4. 修改商品数量\n");
        printf("5. 清空购物清单\n");
        printf("6. 查找商品\n");
        printf("7. 排序购物清单\n");
        printf("8. 合并另一个清单\n");
        printf("9. 删除商品\n");
        printf("0. 退出程序\n");

        int choice;
        printf("请输入选项：");
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
                printf("购物清单已清空。\n");
                break;

            case 6:
                findItemFromUserInput();
                break;

            case 7:
                sortList();
                printf("购物清单已排序。\n");
                break;

            case 8:
                // 合并操作（根据需要提供详细信息）
                printf("正在合并另一个清单\n");
                break;

            case 9:
                // 按名称删除商品（根据需要提供详细信息）
                printf("正在按名称删除商品\n");
                break;

            case 0:
                printf("正在退出程序。再见！\n");
                return 0;

            default:
                printf("无效选项，请重试。\n");
        }
    }

    return 0;
}
