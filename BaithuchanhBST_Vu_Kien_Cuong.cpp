#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct sv{
    int id;
    char name[51];
    float gpa;
}SV;

typedef struct treenode{
    SV info;
    struct treenode* left;
    struct treenode* right;
}NODE;
typedef struct treenode NODE;
//ham xoa ky tu thua
void removenewline(char* str){
    int len = strlen(str);
    if(len > 0 && str[len - 1] == '\n'){
        str[len-1] = '\0';
    }
}
//ham xoa bo nho dem
void clearkbd(void){
    int c;
    while((c = getchar ()) != '\0' && c != EOF);
}
//tao node moi
NODE* createnode(SV sv){
    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    if(newnode == NULL){
        printf("Loi cap phat bo nho!");
        exit(1);
    }
    newnode->info = sv;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
//ham them sv moi
NODE* insertnode(NODE* root, SV sv){
    if(root == NULL){
        return createnode(sv);
    }
    if(sv.id < root->info.id){
        root->left = insertnode(root->left, sv);
    }else if(sv.id > root->info.id){
        root->right = insertnode(root->right, sv);
    }else{
        printf("Loi: Ma sinh vien %d da ton tai trong he thong!\n", sv.id);
    }
    return root;
}
//ham tim kiem sv theo id
NODE* searchnode(NODE* root, int id){
    if(root == NULL || root->info.id == id){
        return root;
    }
    if(id < root->info.id){
        return searchnode(root->left, id);
    }
    return searchnode(root->right, id);
}
//duyet theo ma sv tang dan
void inordertraversal(NODE* root){
    if(root != NULL){
        inordertraversal(root->left);
        printf("%-8d |%-25s | %-5.2f\n", root->info.id, root->info.name, root->info.gpa);
        inordertraversal(root->right);
    }
}
//tim node co id nho nhat
NODE* findmin(NODE* root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}
//ham xoa sinh vien theo ID
NODE* deletenode(NODE* root, int id){
    if(root == NULL) return NULL;
    if(id < root->info.id){
        root->left = deletenode(root->left, id);
    }else if(id > root->info.id){
        root->right = deletenode(root->right, id);
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
        root->info = temp->info;
        root->right = deletenode(root->right, temp->info.id);
    }
    return root;
}
//giai phong bo nho
void freetree(NODE* root){
    if(root != NULL){
        freetree(root->left);
        freetree(root->right);
        free(root);
    }
}
int main(){
    NODE* root = NULL;
    int choice, searchid;
    SV sv;

    do{
        printf("\n===============QUAN LY SINH VIEN(BST)==============\n");
        printf("1. Them sinh vien moi\n");
        printf("2. Xoa sinh vien theo ma SV\n");
        printf("3. Cap nhat thong tin (Ten, Diem) theo ma SV\n");
        printf("4. Tim kiem sinh vien theo ma sv\n");
        printf("5. Hien thi danh sach(Tang dan theo ma sv)\n");
        printf("0. Thoat chuong trinh\n");
        printf("======================================================\n");
        printf("Nhap lua chon cua ban:");
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:
                printf("Nhap ma SV:");
                scanf("%d", &sv.id);
                getchar();

                printf("Nhap ho ten SV:");
                fgets(sv.name, sizeof(sv.name), stdin);
                removenewline(sv.name);
                
                printf("Nhap diem GPA: ");
                scanf("%f", &sv.gpa);

                root = insertnode(root, sv);
                printf("Da them sinh vien thanh cong.\n");
                break;
            case 2:
                printf("Nhap Ma SV can xoa: ");
                scanf("%d", &searchid);
                if (searchnode(root, searchid) != NULL) {
                root = deletenode(root, searchid);
                printf("Da xoa sinh vien %d.\n", searchid);
                } else {
                    printf("Khong tim thay sinh vien voi ma %d.\n", searchid);
                }
                break;
            case 3:{
                printf("Nhap Ma SV can cap nhat: ");
                scanf("%d", &searchid);
                getchar();
                NODE* target = searchnode(root, searchid);
                if (target != NULL) {
                printf("Tim thay: %s (GPA: %.2f)\n", target->info.name, target->info.gpa);
                printf("Nhap Ten moi: ");
                fgets(target->info.name, sizeof(target->info.name), stdin);
                removenewline(target->info.name);
                printf("Nhap Diem GPA moi: ");
                scanf("%f", &target->info.gpa);
                printf("Cap nhat thanh cong!\n");
                } else {
                printf("Khong tim thay Ma SV nay.\n");
                }
                break;
            }
            case 4:{
                printf("Nhap Ma SV can tim: ");
                scanf("%d", &searchid);
                NODE* found = searchnode(root, searchid);
                if (found != NULL) {
                printf("=> KET QUA: ID: %d | Ten: %s | GPA: %.2f\n",
                found->info.id, found->info.name, found->info.gpa);
                } else {
                    printf("=> KHONG TIM THAY!\n");
                }
                break;
            }
            case 5:
                if (root == NULL) {
                printf("Danh sach hien dang trong!\n");
                } else {
                printf("\n-------------------------------------------------\n");
                printf("| %-8s | %-25s | %-5s |\n", "MA SV", "HO VA TEN", "GPA");
                printf("-------------------------------------------------\n");
                inordertraversal(root);
                printf("-------------------------------------------------\n");
                }
                break;
            case 0:
                printf("Dang don dep bo nho va thoat...\n");
                freetree(root);
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    }while(choice != 0);
    return 0;
}
