#define _3BC_SCU_FIX_2
#include "3bc.h"

data_3bc_t ds_memory_llrbt_data_get(app_3bc_id app_id, address_3bc_t address)
{
    struct app_3bc_s* const app = ds_hypervisor_darray_get_one(app_id);
    struct memory_node_s* node = ds_memory_llrbt_access(app, address);
    return node->data;
}

data_3bc_t ds_memory_llrbt_conf_get(app_3bc_id app_id, address_3bc_t address)
{
    struct app_3bc_s* const app = ds_hypervisor_darray_get_one(app_id);
    struct memory_node_s* node = ds_memory_llrbt_access(app, address);
    return node->conf;
}

void ds_memory_llrbt_data_set(
    app_3bc_id app_id, address_3bc_t address, data_3bc_t value)
{
    struct app_3bc_s* const app = ds_hypervisor_darray_get_one(app_id);
    struct memory_node_s* node = ds_memory_llrbt_access(app, address);
    node->data = value;
}

void ds_memory_llrbt_conf_set(
    app_3bc_id app_id, address_3bc_t address, data_3bc_t conf)
{
    struct app_3bc_s* const app = ds_hypervisor_darray_get_one(app_id);
    struct memory_node_s* node = ds_memory_llrbt_access(app, address);
    node->conf = conf;
}

struct memory_node_s* ds_memory_llrbt_create_node(address_3bc_t address)
{
    /** utility function to create a node. **/
    struct memory_node_s* new_node
        = (struct memory_node_s*)malloc(sizeof(struct memory_node_s));

    /** prevent wild pointers **/
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->conf = 0;
    new_node->data = 0;
    new_node->address = address;

    /** New Node which is created is always red in color. **/
    new_node->color = LLRBT_RED;

    return new_node;
}

struct memory_node_s* ds_memory_llrbt_rotate_left(struct memory_node_s* node)
{
    struct memory_node_s* child = node->right;
    struct memory_node_s* child_left = child->left;

    child->left = node;
    node->right = child_left;

    return child;
}

struct memory_node_s* ds_memory_llrbt_rotate_right(struct memory_node_s* node)
{
    struct memory_node_s* child = node->left;
    struct memory_node_s* child_right = child->right;

    child->right = node;
    node->left = child_right;

    return child;
}

struct memory_node_s* ds_memory_llrbt_smallest_child(struct memory_node_s* node)
{
    struct memory_node_s* current = node;

    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

struct memory_node_s* ds_memory_llrbt_clear(
    address_3bc_t address, struct memory_node_s* node)
{
    if (node == NULL)
        return NULL;

    /**
     * If the key to be deleted is smaller than the root's key,
     * then it lies in left subtree
     */
    if (node->address > address) {
        node->left = ds_memory_llrbt_clear(address, node->left);
    }

    /**
     * If the key to be deleted is greater than the root's key,
     * then it lies in right subtree
     */
    else if (node->address < address) {
        node->right = ds_memory_llrbt_clear(address, node->right);
    }

    /**
     * if key is same as root's key, then This is the node to be deleted
     */
    else if (node->left == NULL) {
        /** node with only one child or no child **/
        struct memory_node_s* temp = node->right;
        free(node);
        return temp;
    } else if (node->right == NULL) {
        /** node with only one child or no child **/
        struct memory_node_s* temp = node->left;
        free(node);
        return temp;
    } else {
        /** node with two children:
         * Get the inorder successor
         * (smallest in the right subtree)
         */
        struct memory_node_s* temp
            = ds_memory_llrbt_smallest_child(node->right);

        /** Copy the inorder successor's content to this node **/
        node->address = temp->address;

        /** Delete the inorder successor **/
        node->right = ds_memory_llrbt_clear(temp->address, node->right);
    }

    return node;
}

/**
 * JOKE: deliver us from recursive functions, a main();
 * OPT1: cache node for reaccess same address.
 *
 */
struct memory_node_s* ds_memory_llrbt_access(
    struct app_3bc_s* const app, address_3bc_t address)
{
    struct memory_node_s* node = app->memory.root;

    /** consult cache level 0 reused address (OPT1) **/
    if (app->memory.cache != NULL && app->memory.cache->address == address) {
        return app->memory.cache;
    }

    /** first access **/
    if (node == NULL) {
        /** insert **/
        node = ds_memory_llrbt_create_node(address);
        app->memory.root = node;
    }
    /** another accesses **/
    else {
        /** search by address **/
        do {
            /** less then actual node **/
            if (address > node->address) {
                /** insert **/
                if (node->right == NULL) {
                    node->right = ds_memory_llrbt_create_node(address);
                    node = node->right;
                }
                /** next **/
                else {
                    node = node->right;
                    //ds_memory_llrbt_balancer(node);
                }
            }
            /** greater then actual node **/
            else if (address < node->address) {
                /** insert **/
                if (node->left == NULL) {
                    node->left = ds_memory_llrbt_create_node(address);
                    node = node;
                }
                /** next **/
                else {
                    node = node->left;
                    ds_memory_llrbt_balancer(node);
                }
            } 
        }
        while (node->address != address);
    }

    /** OPT1 storage**/
    app->memory.cache = node;

    return node;
}

void ds_memory_llrbt_balancer(struct memory_node_s* node)
{
    /**
     * case 1.
     * when right child is Red but left child is
     * Black or doesn't exist.
     */
    if (LLRBT_IS_RED(node->right) && !LLRBT_IS_RED(node->left)) {
        /** left rotate the node to make it into valid structure. **/
        node = ds_memory_llrbt_rotate_left(node);

        /** swap the colors as the child node should always be red **/
        //ds_memory_llrbt_swap_colors(node, node->left);
    }

    /**
     *  case 2
     * when left child as well as left grand child in Red
     */
    if (LLRBT_IS_RED(node->left) && LLRBT_IS_RED(node->left->left)) {
        /** right rotate the current node to make it into a valid structure. **/
        node = ds_memory_llrbt_rotate_right(node);
        ds_memory_llrbt_swap_colors(node, node->right);
    }

    /**
     *  case 3
     * when both left and right child are Red in color.
     */
    if (LLRBT_IS_RED(node->left) && LLRBT_IS_RED(node->right)) {
        /** invert the color of node as well it's left and right child.**/
        node->color ^= true;

        /** change the color to black. **/
        node->left->color = LLRBT_BLACK;
        node->right->color = LLRBT_BLACK;
    }
}

void ds_memory_llrbt_swap_colors(
    struct memory_node_s* node1, struct memory_node_s* node2)
{
    char color = node1->color;
    node1->color = node2->color;
    node2->color = color;
}

void ds_memory_llrbt_destroy(struct app_3bc_s* const app)
{
    ds_memory_llrbt_delete(app->memory.root);
}

void ds_memory_llrbt_delete(struct memory_node_s* node)
{
    if (node != NULL) {
        ds_memory_llrbt_delete(node->left);
        ds_memory_llrbt_delete(node->right);
    }
}
