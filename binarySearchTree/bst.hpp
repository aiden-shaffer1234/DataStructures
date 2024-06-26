

using namespace cop4530; 

template <typename T>
BST<T>::BST(int th)
{
    root  = nullptr;
    limit = th;
}

template <typename T>
BST<T>::BST(const std::string input, int th)
{
    limit = th;
    root  = nullptr;
    buildFromInputString(input);
}

template <typename T>
BST<T>::BST(const BST & tree)
{
    root        = clone(tree.root);
    limit       = tree.limit;
}

template <typename T>
BST<T>::BST(BST && tree) : root{tree.root}, limit{tree.limit}
{
    tree.root  = nullptr;
    tree.limit = 0;
}

template <typename T>
BST<T>::~BST<T>()
{
    makeEmpty();
}

template<typename T>
void BST<T>::buildFromInputString(const std::string input)
{
    makeEmpty();

    std::stringstream line(input);
    T temp;
    bool rootBool = false;

    while(line >> temp)
    {
        if(!rootBool)
        {
            rootBool = true;
            root = new BSTNode{temp, nullptr, nullptr};
        } else{
            insert(temp);
        }
    }
}

template <typename T>
const BST<T>& BST<T>::operator=(const BST & tree)
{
    makeEmpty();
    BST<T> temp(tree);
    std::swap(*this, temp);
    return *this;
}

template <typename T>
const BST<T>& BST<T>::operator=(BST && tree)
{
    makeEmpty();
    std::swap(root, tree.root);
    limit = tree.limit;
    return *this;
}

template <typename T>
bool BST<T>::empty()
{
    return root == nullptr;
}

template <typename T>
int BST<T>::numOfNodes() const
{
    return numOfNodes(root);
}

template <typename T>
int BST<T>::height() const
{
    return height(root);
}

template <typename T>
void BST<T>::makeEmpty()
{
    makeEmpty(root);
}

template <typename T>
void BST<T>::insert(const T &v)
{
    // if(root == nullptr) root = new BSTNode{ v, nullptr, nullptr };
    // else{
        insert(v, root);
    // }
}

template <typename T>
void BST<T>::insert(T &&v)
{
    // if(root == nullptr) root = new BSTNode{ std::move(v), nullptr, nullptr };
    // else {
        insert(v, root);
    // }
    
}

template <typename T>
void BST<T>::remove(const T &v)
{
    remove(v,root);
}

template <typename T>
bool BST<T>::contains(const T &v)
{
    BSTNode* temp = nullptr;
    return contains(v, root, temp);
}

template <typename T>
void BST<T>::printLevelOrder() const
{
    printLevelOrder(root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::printInOrder() const
{
    printInOrder(root);
    std::cout << std::endl;
}


//privates

template <typename T>
void BST<T>::printInOrder(BSTNode *t) const
{
    if(t != nullptr)
    {
        printInOrder(t->left);
        std::cout << t->element << " ";
        printInOrder(t->right);
    }
}

template <typename T>
void BST<T>::printLevelOrder(BSTNode *t) const
{
    std::queue<BSTNode*> q;
    std::unordered_map<BSTNode*, int> seen;

    if(root != nullptr)
    {
        int size = numOfNodes();
        q.push(root);
        while(!q.empty())
        {
            BSTNode* parent = q.front();
            if(parent->left != nullptr && seen.find(parent->left) == seen.end())
            {
                q.push(parent->left);
                seen[parent->left] = 1;
            }
            
            if(parent->right != nullptr && seen.find(parent->right) == seen.end())
            {
                q.push(parent->right);
                seen[parent->right] = 1;
            }
            std::cout << q.front()->element << " ";
            q.pop();
        }
        
    }
}

template <typename T>
void BST<T>::makeEmpty(BSTNode* &t)
{
    if( t != nullptr )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullptr;
}

template <typename T>
void BST<T>::insert(const T& x, BSTNode *&t)
{
    if( t == nullptr )
        t = new BSTNode{ x, nullptr, nullptr };
    else if( x < t->element )
        insert( x, t->left );
    else if( t->element < x )
        insert( x, t->right );
    
}

template <typename T>
void BST<T>::insert(T&& v, BSTNode *&t)
{
    if( t == nullptr )
        t = new BSTNode{ std::move(v), nullptr, nullptr };
    else if( v < t->element )
        insert( v, t->left );
    else if( t->element < v )
        insert( v, t->right );
    
}

template <typename T>
void BST<T>::remove(const T& v, BSTNode *&t)
{
    if( t == nullptr ){
        return;   // Item not found; do nothing
    }if( v < t->element ) {
        remove( v, t->left );
    } else if( t->element < v )
    {
        remove( v, t->right );
    } else if( t->left != nullptr && t->right != nullptr )  { // two children
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    } else {
        BSTNode *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right;
        delete oldNode;
    }
}

template <typename T>
bool BST<T>::contains(const T &x, BSTNode *&t, BSTNode *&prev) const
{   
    if( t == nullptr )
        return false;
    else if( x < t->element )
        return contains( x, t->left, t);
    else if( t->element < x )
        return contains( x, t->right, t);
    else
    {
        t->count++;
        if(t->count == limit && prev != nullptr)
        {
            t->count = 0;
            if(t == prev->left)
            {
                rotateLeftChild(prev, t);
            } else {
                rotateRightChild(prev, t);
            }
        } else if(prev == nullptr && t->count == limit)
        {
            t->count = 0;
        }
        return true;    // Match
    }
}

template <typename T>
int BST<T>::numOfNodes(BSTNode *t) const
{
    if (t == nullptr) {
        
        return 0;
    } else {
        return 1 + numOfNodes(t->left) + numOfNodes(t->right);
    }
}

template <typename T>
int BST<T>::height(BSTNode *t) const
{
    if(t == nullptr)
    {
        return 0;
    } else {
        int leftHeight  = height(t->left);
        int rightHeight = height(t->right);
        return 1 + std::max(leftHeight, rightHeight);
    }
}

template <typename T>
typename BST<T>::BSTNode* BST<T>::clone(BSTNode *t) const
{
    if( t == nullptr )
        return nullptr;
    else
        return new BSTNode{ t->element, clone( t->left ), clone( t->right ) };

}

template<typename T>
typename BST<T>::BSTNode* BST<T>::findMin(BSTNode *t ) const
{
    if( t == nullptr )
        return nullptr;
    if( t->left == nullptr )
        return t;
    return findMin( t->left );
}

template<typename T>
void BST<T>::rotateRightChild(BSTNode* parent, BSTNode* child) const
{
    BSTNode* tempRight  = child->right;
    BSTNode* temp       = child;
    child->right        = parent;
    parent->left        = tempRight;
    parent              = temp;
}

template<typename T>
void BST<T>::rotateLeftChild(BSTNode* parent, BSTNode* child) const
{
    BSTNode* tempLeft       = child->left;
    BSTNode* temp           = child;
    child->left             = parent;
    parent->right           = tempLeft;
    parent                  = temp;
}

