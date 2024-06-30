/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
Evaluator::~Evaluator(){
    for (int i =0; i<expr_trees.size();i++){
        delete expr_trees[i];
    }
}

Evaluator::Evaluator(){
    SymbolTable* s = new SymbolTable();
    symtable = s;
}

ExprTreeNode* getparent(vector<vector <ExprTreeNode*>> P,ExprTreeNode* child){
    for (int i=0;i<P.size();i++){
        if (P[i][0] == child){
            return P[i][1];
        }
    }
    return NULL;
}

ExprTreeNode* buildtree(vector <string> v){
    ExprTreeNode* root = new ExprTreeNode();
    vector <vector<ExprTreeNode*>> P;
    ExprTreeNode* cur = root;
    for (int i=0;i<v.size();i++){
        string s = v[i];
        if (s=="("){
            ExprTreeNode* l = new ExprTreeNode();
            cur->left = l;
            P.push_back({l,cur});
            
            cur = cur->left;
        }
        else if (s == "+" || s == "-" || s == "*" || s == "/"){
            if (s=="+"){
                cur->type = "ADD";
            }
            else if (s=="-"){
                cur->type = "SUB";
            }
            else if (s=="*"){
                cur->type = "MUL";
            }
            else if (s=="/"){
                cur->type = "DIV";
            }

            ExprTreeNode* r = new ExprTreeNode();
            cur->right = r;
            P.push_back({r,cur});
            cur = cur->right;
        }

        else if (s == ")"){
            ExprTreeNode* p = getparent(P,cur);
            cur = p;
        }

        else{
            bool isval = true;
            for (int i=0;i<s.length();i++){
                if (!isdigit(s[i])){
                    isval = false;
                    break;
                }
            }

            if (isval){
                cur->type = "VAL";
                UnlimitedInt* I = new UnlimitedInt(s);
                UnlimitedInt* i = new UnlimitedInt("1");
                UnlimitedRational* r = new UnlimitedRational(I,i);
                cur->val = r;
                ExprTreeNode* p = getparent(P,cur);
                cur = p;
            }
            else{
                cur->type = "VAR";
                cur->id = s;
                
                ExprTreeNode* p = getparent(P,cur);
                cur = p;
            }
        }

    }
    
    for (vector <ExprTreeNode*> e:P){
    }

    return root;
}

void Evaluator::parse(vector <string> code){
    vector <string> v = code;
    
    string l = code[0];
    string f = code[1];
    v.erase(v.begin());
    v.erase(v.begin());
    ExprTreeNode* lv = new ExprTreeNode();
    lv->id = l;
    lv->type = "VAR";
    ExprTreeNode* o = new ExprTreeNode();
    o->type = "VAL";
    o->left = lv;
    o->right = buildtree(v);
    expr_trees.push_back(o);


}

void update(ExprTreeNode* root,SymbolTable* s){
    if (root->left == NULL && root->right == NULL){
        if (root->type == "VAL"){
            root->evaluated_value = root->val;
        }

        else if (root->type == "VAR"){
            string iid = root->id;
            root->evaluated_value = s->search(iid);
        }
    }

    else{
        update(root->left,s);
        update(root->right,s);
        if (root->type == "ADD"){
            root->evaluated_value = UnlimitedRational::add(root->left->evaluated_value,root->right->evaluated_value);
        }
        else if (root->type == "SUB"){
            root->evaluated_value = UnlimitedRational::sub(root->left->evaluated_value,root->right->evaluated_value);
            
        }

        else if (root->type == "MUL"){

            root->evaluated_value = UnlimitedRational::mul(root->left->evaluated_value,root->right->evaluated_value);
            
        }
        else if (root->type == "DIV"){
            root->evaluated_value = UnlimitedRational::div(root->left->evaluated_value,root->right->evaluated_value);
            
        }
    }
    

}


void Evaluator::eval(){
    ExprTreeNode* root = expr_trees[expr_trees.size()-1];
    update (root->right,symtable);
    ExprTreeNode* lv = root->left;
    string k = lv->id;
    UnlimitedRational* r = root->right->evaluated_value;
    symtable->insert(k,r);
    lv->evaluated_value = root->right->evaluated_value;
}