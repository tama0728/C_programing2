#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1024
#define path "/Users/gimdong-yun/Desktop/SynologyDrive/F/ShortCut/Uni/2023/1학기/C프로그래밍2/C2/project/p1/data.txt"

typedef struct TreeNode {
    char name[30];
    char tel[20];
    char memo[40];
    struct TreeNode *left, *right;
} TreeNode;

void *search (TreeNode *node, char *key, int n){
    if (node) {
        search(node->left, key, n);
        if (strstr(node->name, key) != 0 || strstr(node->tel, key) != 0 || strstr(node->memo, key) != 0) {
            printf("%d %s %s %s\n", n, node->name, node->tel, node->memo);
            n++;
        }
        search(node->right, key, n);
    }
}

TreeNode *new_node(char *name, char *tel, char *memo){
    TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
    strcpy(temp->name, name);
    strcpy(temp->tel, tel);
    strcpy(temp->memo, memo);
    temp->left = temp->right = NULL;
    return temp;
}

TreeNode *insert_node(TreeNode *node, char *name, char *tel, char *memo){
    if (node == NULL){
        return new_node(name, tel, memo);
    }
    else if (strcmp(name, node->name) < 0)
        node->left = insert_node(node->left, name, tel, memo);
    else if (strcmp(name, node->name) > 0)
        node->right = insert_node(node->right, name, tel, memo);
    return node;
}

TreeNode *min_value_node(TreeNode *node){
    TreeNode *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

TreeNode *delete_node(TreeNode *root, char *key){
    if (root == NULL) return root;

    if (strcmp(key, root->name) < 0)
        root->left = delete_node(root->left, key);
    else if (strcmp(key, root->name) > 0)
        root->right = delete_node(root->right, key);
    else{
        if (root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        else if (root->left == NULL){
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL){
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        TreeNode *temp = min_value_node(root->right);

        strcpy(root->name, temp->name);
        root->right = delete_node(root->right, temp->name);
    }
    return root;
}

void inorder(TreeNode *root) {
    if (root) {
        inorder(root->left);
        printf("%s : %s\n", root->name, root->tel);
        inorder(root->right);
    }
}

TreeNode *searchDelete(TreeNode *node, char *key, int n) {
    struct TreeNode *temp[MAX];
    if (node) {
        searchDelete(node->left, key, n);
        if (strstr(node->name, key) != 0 || strstr(node->tel, key) != 0 || strstr(node->memo, key) != 0) {
            printf("%d %s %s %s\n", n, node->name, node->tel, node->memo);
            temp[n - 1] = node;
            n++;
        }
        searchDelete(node->right, key, n);
    }
}
TreeNode *delete(TreeNode *node, int n){
    printf("which one? ");
    int c = getchar();
    if (!isdigit(c)) exit(1);
    c -= '0';
    if (c > n-2) exit(1);
    delete_node(node, temp[c]->name);
}

TreeNode *init(TreeNode *head, char *buf, char *name, char *tel, char *memo){
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        exit(1);
    }
    while (fgets(buf, MAX, fp) != NULL){
        char *ptr = strtok(buf, ":\n");
        int i = 0;
        while (ptr != NULL) {
            if (i == 0)
                strcpy(name, ptr);
            else if (i == 1)
                strcpy(tel, ptr);
            else
                strcpy(memo, ptr);
            ptr = strtok(NULL, ":\n");
            i++;
        }
        head = insert_node(head, name, tel, memo);
    }
    fclose(fp);
    return head;
}

int main(void) {
    TreeNode *root = NULL;
    TreeNode *temp = NULL;
    char buf[MAX], name[30], tel[20], memo[40];
    int c;

    root = init(root, buf, name, tel, memo);
    search(root, "Bae", 1);

//    inorder(root);
    searchDelete(root, "Bae", 1);
//    inorder(root);
    return 0;
}
