/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode(){
    right = NULL;
    left = NULL;

}


ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    type = t;
    UnlimitedInt* I = new UnlimitedInt("1");
    UnlimitedRational* r = new UnlimitedRational(v,I);
    val = r;
    right = NULL;
    left = NULL;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    type = t;
    val = v;
    right = NULL;
    left = NULL;
}

ExprTreeNode::~ExprTreeNode(){
    // right = NULL;
    // left = NULL;
    // delete val;
}

