#pragma once
#include "DataUtil.h"

/*parcurgere:
in order: left, root, right  => sortare crescatoare a cheilor unui arbore
Traverse the left subtree in inorder.
Visit the root node.
Traverse the right subtree in inorder.

preorder: root, left, right => copierea unui arbore
Visit the root node.
Traverse the left subtree in preorder.
Traverse the right subtree in preorder.

postorder: left, right, root => stergerea unui arbore
Traverse the left subtree in postorder.
Traverse the right subtree in postorder.
Visit the root node.

*/

typedef struct NodeBST
{
    Student* info;
    struct NodeBST* lChild;
    struct NodeBST* rChild;
}BinarySearchTree, *PBinarySearchTree;

BinarySearchTree* createTreeNode(Student* stud)
{
    BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
    node->info = stud;
    node->lChild = node->rChild = NULL;
    return node;
}

void upsert(PBinarySearchTree* root, Student* stud)  // insert + update
{
    if (*root == NULL)
    {
        *root = createTreeNode(stud);
    }
    else
    {
       if((*root)->info->reference.intRef > stud->reference.intRef)
       {
           upsert(&(*root)->lChild,stud);
       }
       else if ((*root)->info->reference.intRef < stud->reference.intRef)
       {
           upsert(&(*root)->rChild,stud);
       }
       else 
       {
        printf("Key already present, updating..\n");
        (*root)->info = stud;
        (*root) = NULL;
       }
    }
}

void displayTreeStructure(PBinarySearchTree root,int level) //de la clasa
{
    if(root!=NULL){
        for(int i=0;i<level;i++)
            printf("\t ");
            printf("%s:%d\n",root->info->name,root->info->reference.intRef);
            level++;
            displayTreeStructure(root->lChild,level);
            displayTreeStructure(root->rChild,level);
    } else {
        for (int i = 0; i < level; i++)
            printf("\t ");
        printf("NULL\n");
    }
}

void deleteNodeByKey(PBinarySearchTree* root, unsigned char* key)
{
    if((*root)->info->reference.intRef > key)
      deleteNodeByKey(&(*root)->lChild,key);
    else if((*root)->info->reference.intRef < key)
      deleteNodeByKey(&(*root)->rChild,key);
    else {
        if((*root)->lChild == NULL && (*root)->rChild == NULL) //leaf node
        {
            deleteStudent((*root)->info);
            free(*root);
            *root = NULL;
        }
        else if((*root)->lChild == NULL || (*root)->rChild==NULL) //node with leaf (one descendant only)
        {
            BinarySearchTree* temp = *root;
            /*if(temp->lChild == NULL)
                *root = temp->rChild;
            else
                *root = temp->lChild;
             */
        *root = temp->lChild !=NULL ? temp->lChild : temp->rChild;
        deleteStudent(temp->info);
        free(temp);
    }
    else //node with two descendants TEMA
    {
       //deleteFullNode();

    }
  }
}