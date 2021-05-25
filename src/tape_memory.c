#include "3bc.h"

struct memory_node_s* tape_memory_llrbt_create_node(address_3bc_t address)
{
    /** utility function to create a node. **/
    struct memory_node_s* new_node = (struct memory_node_s*) malloc(sizeof(struct memory_node_s));

    /** prevent wild pointers **/
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->conf = 0;
    new_node->data = 0;
    new_node->vmax = 0;
    new_node->vmin = 0;
    new_node->address = address;
  
    /** New Node which is created is always red in color. **/
    new_node->color = LLRBT_RED;

    return new_node;
}

struct memory_node_s* tape_memory_llrbt_rotate_left(struct memory_node_s* node)
{
    struct memory_node_s* child = node->right;
    struct memory_node_s* child_left = child->left;
  
    child->left = node;
    node->right = child_left;
  
    return child;
}

struct memory_node_s* tape_memory_llrbt_rotate_right(struct memory_node_s* node)
{
    struct memory_node_s* child = node->left;
    struct memory_node_s* child_right =  child->right;
  
    child->right = node;
    node->left = child_right;
      
    return child; 
}

struct memory_node_s* tape_memory_llrbt_smallest_child(struct memory_node_s* node)
{
    struct memory_node_s* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL) {
        current = current->left;
    }
 
    return current;
}

struct memory_node_s* tape_memory_llrbt_clear(address_3bc_t address, struct memory_node_s* node)
{
    if (node == NULL)
        return NULL;
 
    /**
     * If the key to be deleted is smaller than the root's key,
     * then it lies in left subtree
     */
    if (node->address > address) {
        node->left = tape_memory_llrbt_clear(address, node->left);
    }
 
    /**
     * If the key to be deleted is greater than the root's key,
     * then it lies in right subtree
     */
    else if (node->address < address) {
        node->right = tape_memory_llrbt_clear(address, node->right);
    }
 
    /**
     * if key is same as root's key, then This is the node to be deleted
     */
    else if (node->left == NULL) {
        /** node with only one child or no child **/
        struct memory_node_s* temp = node->right;
        free(node);
        return temp;
    }
    else if (node->right == NULL) {
        /** node with only one child or no child **/
        struct memory_node_s* temp = node->left;
        free(node);
        return temp;
    }
    else
    {
        /** node with two children:
         * Get the inorder successor
         * (smallest in the right subtree)
         */
        struct memory_node_s* temp = tape_memory_llrbt_smallest_child(node->right);
 
        /** Copy the inorder successor's content to this node **/
        node->address = temp->address;
 
        /** Delete the inorder successor **/
        node->right = tape_memory_llrbt_clear(temp->address, node->right);
    }

    return node;
}

struct memory_node_s* tape_memory_llrbt_access(address_3bc_t address)
{
    struct memory_node_s* node = APP_3BC->memory.root;

    /** consult cache level 0 reused address **/
    if (APP_3BC->cache_l0 != NULL && APP_3BC->cache_l0->address == address) {
        return APP_3BC->cache_l0;
    }

    while (node != NULL && node->address != address) {
        
        if (node->address < address) {
            node = node->right;
        }

        else if (node->address > address) {
            node = node->left;
        }
    }

    if (node == NULL) {
        APP_3BC->memory.root = tape_memory_llrbt_insert(address, APP_3BC->memory.root);
        return tape_memory_llrbt_access(address);
    }

    APP_3BC->cache_l0 = node;
    return APP_3BC->cache_l0;
}

struct memory_node_s* tape_memory_llrbt_insert(address_3bc_t address, struct memory_node_s* node)
{
    /**
     * NORMAL INSERTION BINARY TREE ALGORITHM
     */
    if (node == NULL) {
        return tape_memory_llrbt_create_node(address);
    }
    /** address smaller than the parent **/
    if (node->address > address) {
        node->left = tape_memory_llrbt_insert(address, node->left);
    }
    /** address greater than the parent **/
    else if (node->address < address) {
        node->right = tape_memory_llrbt_insert(address, node->right);
    }
    /** address exists **/
    else {
        return node;
    }
    
    /**
     * case 1.
     * when right child is Red but left child is
     * Black or doesn't exist.
     */
    if (LLRBT_IS_RED(node->right) && !LLRBT_IS_RED(node->left))
    {
        /** left rotate the node to make it into valid structure. **/
        node = tape_memory_llrbt_rotate_left(node);
  
        /** swap the colors as the child node should always be red **/
        tape_memory_llrbt_swap_colors(node, node->left);
    }
      
    /**
     *  case 2
     * when left child as well as left grand child in Red
     */
    if (LLRBT_IS_RED(node->left) && LLRBT_IS_RED(node->left->left))
    {   
        /** right rotate the current node to make it into a valid structure. **/
        node = tape_memory_llrbt_rotate_right(node);
        tape_memory_llrbt_swap_colors(node, node->right);
    }
      
    /**
     *  case 3
     * when both left and right child are Red in color.
     */
    if (LLRBT_IS_RED(node->left) && LLRBT_IS_RED(node->right))
    {
        /** invert the color of node as well it's left and right child.**/
        node->color ^= true;
  
        /** change the color to black. **/
        node->left->color = LLRBT_BLACK;
        node->right->color = LLRBT_BLACK; 
    }
  
    return node;
}

void tape_memory_llrbt_swap_colors(struct memory_node_s* node1, struct memory_node_s* node2)
{
    char color = node1->color;
    node1->color = node2->color;
    node2->color = color;
}

void tape_memory_data_set(address_3bc_t address, data_3bc_t value)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    node->data = value;
    tape_memory_lineup(node);
}

void tape_memory_vmax_set(address_3bc_t address, data_3bc_t value)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    node->conf |= MEM_CONFIG_MAX_VALUE;
    node->vmax = value;
    tape_memory_lineup(node);
}

void tape_memory_vmin_set(address_3bc_t address, data_3bc_t value)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    node->conf |= MEM_CONFIG_MIN_VALUE;
    node->vmin = value;
    tape_memory_lineup(node);
}

void tape_memory_conf_set(address_3bc_t address, data_3bc_t value)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    node->conf = value;
    tape_memory_lineup(node);
}

data_3bc_t tape_memory_data_get(address_3bc_t address)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    return node->data;
}

data_3bc_t tape_memory_vmax_get(address_3bc_t address)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    return node->vmax;
}

data_3bc_t tape_memory_vmin_get(address_3bc_t address)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    return node->vmin;
}

data_3bc_t tape_memory_conf_get(address_3bc_t address)
{
    struct memory_node_s* node = tape_memory_llrbt_access(address);
    return node->conf;
}

void tape_memory_lineup(struct memory_node_s* node)
{
    /** default configuration **/
    if (node->conf == 0) {
        return;
    }

    /** cache configuration **/
    bool conf_normalize = (MEM_CONFIG_NORMALIZE == (node->conf & MEM_CONFIG_NORMALIZE));
    bool conf_max_value = (MEM_CONFIG_MAX_VALUE == (node->conf & MEM_CONFIG_MAX_VALUE));
    bool conf_min_value = (MEM_CONFIG_MIN_VALUE == (node->conf & MEM_CONFIG_MIN_VALUE));
    bool conf_min_max = conf_max_value && conf_min_value;

    /** not allow normalize whitout clamp (limit max & min) **/
    if (conf_normalize && !conf_min_max) {
        lang_driver_error(ERROR_INVALID_MEMORY_CONFIG);
    }

    /** verifiy valid value between max & min **/
    if (node->vmin > node->vmax && conf_min_max) {
        lang_driver_error(ERROR_INVALID_MEMORY_CLAMP);
    }
    
    /** maximum without normalize **/
    if(node->data > node->vmax && conf_max_value && !conf_normalize) {
        node->data = node->vmax;
    }
    /** minimum without normalize **/
    else if (node->data < node->vmin && conf_min_value && !conf_normalize) {
        node->data = node->vmin;
    }
    /** custom underflow/overflow **/
    else if ((node->vmin > node->data || node->data > node->vmax) && conf_normalize) {
        node->data = ((node->data + node->vmin + 2) % (node->vmax - node->vmin + 1)) + node->vmin;
    }
}

void tape_memory_free(address_3bc_t address)
{
    /** clear cache level 0 **/
    if (APP_3BC->cache_l0 != NULL && APP_3BC->cache_l0->address == address) {
        APP_3BC->cache_l0 = NULL;
    }

    /** clear memory node **/
    APP_3BC->memory.root = tape_memory_llrbt_clear(address, APP_3BC->memory.root);
}

void tape_memory_destroy()
{
    /** TODO: this **/
}