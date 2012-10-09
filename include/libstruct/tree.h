typedef struct tree_node_t {
	void* data;
	struct tree_node_t* right;
	struct tree_node_t* left;
	struct tree_t* owner;
} tree_node_t;

typedef struct tree_t {
	struct tree_node_t* root;
	size_t length;
	int (*hash_function)(void* data);
	int self_balancing;
} tree_t;

int tree_is_subtree(tree_t* tree1, tree_t* tree2);
