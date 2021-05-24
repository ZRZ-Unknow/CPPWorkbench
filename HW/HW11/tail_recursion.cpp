struct Node {
    int val;
    Node *left;
    Node *right;
    Node() : val(0), left(nullptr), right(nullptr) {}
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
    Node(int x, Node *left, Node *right) : val(x), left(left), right(right) {}
};

void tail_recursion(Node *node, bool left, int depth, int &res){
    if(node==nullptr) return ;
    res = res>depth+1?res:depth+1;
    if(left){
        tail_recursion(node->right, false, depth+1, res);
        tail_recursion(node->left, true, 0, res);
    }else{
        tail_recursion(node->left, true, depth+1, res);
        tail_recursion(node->right, false, 0, res);
    }
}

int longest_z(Node *root){
    int res = 0;
    tail_recursion(root->left, true, 0, res);
    tail_recursion(root->right, false, 0, res);
    return res;
}
