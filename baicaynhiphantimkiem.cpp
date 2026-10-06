#include<stdio.h>
#include<stdlib.h>

typedef struct treenode{
    int data;
    struct treenode* left;
    struct treenode* right;
}NODE;
typedef struct treenode NODE;

NODE* createnode(int value){
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    if(!newnode){
        printf("Loi cap phat bo nho!\n");
        exit(1);
    }
    newnode->data = value;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

NODE* insertnode(NODE* root, int value){
    if(root == NULL){
        return createnode(value);
    }
    if(value<root->data){
        root->left = insertnode(root->left, value);
    }else if(value>root->data){
        root->right = insertnode(root->right, value);
    }else{
        printf("Gia tri %d da ton tai trong cay!\n");
    }
    return root;
}

void inordertraversal(NODE* root){
    if(root != NULL){
        inordertraversal(root->left);
        printf("%d-> ", root->data);
        inordertraversal(root->right);
    }
}
//tim nut co gia tri bang value
NODE* searchnode(NODE* root, int value){
    if(root == NULL || root->data == value){
        return root;
    }
    if(value < root->data){
        return searchnode(root->left, value);
    }
    return searchnode(root->right, value);
}
//tim nut co gia tri nho nhat trong cay
NODE* findmin(NODE* root){
    while(root && root->left != NULL){
        root = root->left;
    }
    return root;
}

NODE* deletenode(NODE* root, int value){
     if(root == NULL) return root;
     if(value < root->data){
        root->left = deletenode(root->left, value);
     }else if(value > root->data){
        root->right = deletenode(root->right, value);
     }else{
        if(root->left == NULL){
            NODE* temp = root->right;
            free(root);
            return temp;
        }else if(root->right == NULL){
            NODE* temp = root->left;
            free(root);
            return temp;
        }
        NODE* temp = findmin(root->right);
        root->data = temp->data;
        root->right = deletenode(root->right, temp->data);
     }
     return root;
}
//don dep bo nho
void freetree(NODE* root){
    if(root != NULL){
        freetree(root->left);
        freetree(root->right);
        free(root);
    }
}
//ham xoa bo nho dem
void clearbuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int main(){
    NODE* root = NULL;
    int choice, value, newval;
    do{
        printf("\n=======MENU BINARY SEARCH TREE========\n");
        printf("1. Them mot so vao cay\n");
        printf("2. Xoa mot so vao cay\n");
        printf("3. Cap nhat mot so (Xoa cu, Them moi)\n");
        printf("4. Tim kiem mot so\n");
        printf("5. Hien thi danh sach tang dan (LNR)\n");
        printf("0. Thoat chuong trinh\n");
        printf("=========================================\n");
        printf("Nhap lua chon cua ban: ");

        if(scanf("%d", &choice)!= 1){
            printf("Loi! Vui long nhap so nguyen! \n");
            clearbuffer();
            continue;
        }
        switch(choice){
            case 1:
                printf("Nhap so can them: ");
                scanf("%d", &value);
                root = insertnode(root, value);
                break;
            case 2:
                printf("Nhap so can xoa: ");
                scanf("%d", &value);
                if (searchnode(root, value) != NULL) {
                    root = deletenode(root, value);
                    printf("Da xoa %d khoi cay.\n", value);
                } else {
                    printf("Khong tim thay %d de xoa!\n", value);
                }
                break;
            case 3:
                printf("Nhap gia tri cu can cap nhat: ");
                scanf("%d", &value);
                if (searchnode(root, value) != NULL) {
                    printf("Nhap gia tri moi: ");
                    scanf("%d", &newval);

                    // Tránh trường hợp newVal đã tồn tại sẵn làm mất nút
                    if (newval != value && searchnode(root, newval) != NULL) {
                        printf("Gia tri moi %d da ton tai trong cay! Cap nhat that bai.\n", newval);
                    } else {
                        root = deletenode(root, value);
                        root = insertnode(root, newval);
                        printf("Da cap nhat %d thanh %d.\n", value, newval);
                    }
                } else {
                    printf("Khong tim thay gia tri %d de cap nhat.\n", value);
                }
                break;
            case 4:
                printf("Nhap so can tim: ");
                scanf("%d", &value);
                if (searchnode(root, value) != NULL) {
                    printf("Tim thay %d trong cay.\n", value);
                } else {
                    printf("Khong tim thay %d trong cay.\n", value);
                }
                break;
            case 5:
                if (root == NULL) {
                    printf("Cay dang trong!\n");
                } else {
                    printf("Danh sach tang dan (LNR): ");
                    inordertraversal(root);
                    printf("\n");
                }
                break;
            case 0:
                printf("Dang don dep bo nho cay va thoat...\n");
                freetree(root);
                root = NULL;
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }
    }while (choice != 0);
    return 0;
}