/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
SymbolTable::SymbolTable(){
    size = 0;
}


SymbolTable::~SymbolTable(){
    delete root;
}

string smaller(string s1, string s2){
    int i1 = s1.length();
    int i2 = s2.length();
    int k = min(i1,i2);
    for (int j=0;j<k;j++){
        if (int(s1[j]) < int(s2[j])){
            return s1;
        }
        else if (int(s2[j])<int(s1[j])) {
            return s2;
        }
    }
    if (i1>k){
        return s2;
    }
    else{
        return s1;
    }
}


void ins(SymEntry* root,string k,UnlimitedRational* v){
    string c = root->key;
    string t = smaller(c,k);
    if (t == k){
        if (root->left == NULL){
            SymEntry* e = new SymEntry(k,v);
            root->left = e;
        }
        else{
            ins(root->left,k,v);
        }
    }
    else{
        if (root->right == NULL){
            SymEntry* e = new SymEntry(k,v);
            root->right = e;
        }
        else{
            ins(root->right,k,v);
        }
    }
}


void SymbolTable::insert(string k,UnlimitedRational* v){
    if (size == 0){
        SymEntry* e = new SymEntry(k,v);
        root = e;
        size++;
    }
    else{
        ins(root,k,v);
        size++;
    }
}

SymEntry* find(SymEntry* root, string k){
    if (root->key == k){
        return root;
    }
    else if (smaller(root->key,k) == k){
        return find(root->left,k);
    }
    else{
        return find(root->right,k);
    }
}

UnlimitedRational* SymbolTable::search(string k){
    SymEntry* s = find(root,k);
    return s->val;
}

int SymbolTable::get_size(){
    return size;
}

SymEntry* SymbolTable::get_root(){
    return root;
}

SymEntry* getparent(SymEntry* root, string k){
    if (smaller(root->key,k) == k){
        if (root->left->key == k){
            return root;
        }
        else{
            return getparent(root->left,k);
        }
    }
    else{
        if (root->right->key == k){
            return root;
        }
        else{
            return getparent(root->right,k);
        }
    }
}

SymEntry* successor(SymEntry* root){
    SymEntry* temp = root->right;
    while (temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}

void rem(SymEntry* root, string k){
    SymEntry* e = find(root,k);
    if (e->right == NULL && e->left == NULL){
        SymEntry* p = getparent(root,k);
        if (p->right->key == k){
            p->right = NULL;
            delete e;
        }
        else{
            p->left = NULL;
            delete e;
        }
    }
    else if (e->right == NULL && e->left != NULL){
        SymEntry* p = getparent(root,k);
        if (p->right->key == k){
            p->right = e->left;
            e->left = NULL;
            delete e;
        }
        else{
            p->left = e->left;
            e->left = NULL;
            delete e;
        }
    }
    else if (e->left == NULL && e->right != NULL){
        SymEntry* p = getparent(root,k);
        if (p->right->key == k){
            p->right = e->right;
            e->right = NULL;
            delete e;
        }
        else{
            p->left = e->right;
            e->right = NULL;
            delete e;
        }
    }
    else{
        SymEntry* suc = successor(e);
        e->key = suc->key;
        e->val = suc->val;
        rem(e->right,k);
    }
}

void SymbolTable::remove(string k){
    rem(root,k);
    size --;
}





