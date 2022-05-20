
class Node:
    def __init__(self, data, parent) -> None:
        self.data = data
        self.left = None
        self.right = None
        self.parent = parent

class Tree:
    def __init__(self) -> None:
        self.root = None 

    def insert(self, data):
        self.root = insert(self, self.root, data)

    def pop(self, data):
        return pop(self.root, data)

    def is_bst(self):
        return is_bst(self.root, max_val=None, min_val=None)

    def _str(self):
        return _str(self.root)

def is_bst(node, max_val, min_val):
    if node is None:
        return True 
    
    if max_val is not None:
        if node.data > max_val:
            return False
    
    if min_val is not None:
        if node.data <= min_val:
            return False

    is_left_bst = is_bst(node.left, max_val=node.data, min_val=min_val)
    is_right_bst = is_bst(node.right, max_val=max_val, min_val=node.data)
    return is_left_bst and is_right_bst

def is_balanced(node, parent_level):
    #stopping conditions
    #if node is None, return max_level, True
    if node is None:
        return parent_level, True 

    #left_max, left_balanced = is_balanced(node.left, max_level+1)
    left_max, balanced = is_balanced(node.left, parent_level+1)

    #if left is not balanced, return _, false
    if not balanced:
        return None, False

    #right_max, right_balanced = is_balanced(node.right, max_level+1)
    right_max, balanced = is_balanced(node.right, parent_level+1)

    #if right is not balanced, return _, false
    if not balanced:
        return None, False

    #if abs(left_max-right_max) > 1 return _, false
    if abs(left_max-right_max) > 1: 
        return None, False 

    #return max(left_max, right_max), true
    return max([left_max, right_max]), True 

def insert(parent, node, data):
    if node is None:
        return Node(data, parent) 

    if data <= node.data:
        node.left = insert(node, node.left, data)
    else:
        node.right = insert(node, node.right, data)
    return node

def pop(node, data):
    if node is None:
        return
    
    if node.data == data:
        if node.left is None or node.right is None:
            detach(node)
        else:
            node.data = pop_max(node.left)
    elif data < node.data:
        pop(node.left, data)
    else:
        pop(node.right, data)

def pop_max(node):
    assert node is not None

    if node.right is None:
        retval = node.data
        detach(node)
        return retval
    else:
        return pop_max(node.right)

def attach(parent, child):
    assert child is not None and parent is not None 

    if child.data <= parent.data:
        parent.left = child
    else:
        parent.right = child 
    child.parent = parent 

def detach(node):
    assert node is not None
    assert node.left is None or node.right is None 

    if node.left is not None:
        attach(node.parent, node.left)
    elif node.right is not None:
        attach(node.parent, node.right)
    else:
        if node.parent.left == node:
            node.parent.left = None
        else:
            node.parent.right = None

def _str(node):
    if node is None:
        return ""

    out = _str(node.left)
    out += str(node.data) + " "
    out += _str(node.right)
    return out 

def breadth_first(root):
    #init out
    out = []

    #init fifo
    fifo = []

    #push node to fifo
    fifo.append(root)

    while len(fifo) > 0:
        #node <- pop fifo
        node = fifo.pop(0)

        #skip if node is none 
        if node is None:
            continue

        #perform action
        #push node.data to out 
        out.append(node.data)

        #push node.left to fifo
        fifo.append(node.left)
        #push node.right to fifo
        fifo.append(node.right)

    return out


def lowest_common_ancestor(node, p, q):
    # stopping condition
    # if node is none, return false, false, none
    if node is None:
        return False, False, None

    # left_p_exist, left_q_exist, lca <- call recursively node.left
    left_p_exist, left_q_exist, lca = lowest_common_ancestor(node.left, p, q)
    # if lca is not None, return _, _, lca
    if lca is not None:
        return None, None, lca 

    # right_p_exist, right_q_exist, lca <- call recursively node.right
    right_p_exist, right_q_exist, lca = lowest_common_ancestor(node.right, p, q)
    # if lca is not none, return _, _, lca
    if lca is not None:
        return None, None, lca

    # if left_p_exist and right_q_exist or right_p_exist and left_q_exist, return _, _, node.data
    # if node.data is p and (left_q_exist or rigth_q_exist) return _,_,node.data
    # if node.data is q and (left_p_exist or right_p_exist) return _,_,node.data
    if (left_p_exist and right_q_exist or right_p_exist and left_q_exist) or \
        (node.data==p and (left_q_exist or right_q_exist)) or \
        (node.data==q and (left_p_exist or right_p_exist)):
        lca = node.data
    
    return left_p_exist or right_p_exist, left_q_exist or right_q_exist, lca

import numpy as np
np.random.seed = 0

dummy = list(np.random.choice(range(10000), 2000))
tree = Tree()

for v in dummy:
    tree.insert(v)

dummy_str = " ".join([str(v) for v in sorted(dummy)]) + " "
assert dummy_str == tree._str()


remove = list(np.random.choice(dummy, int(len(dummy)/2), replace=False))
for r in remove:
    dummy.remove(r)
    tree.pop(r)

dummy_str = " ".join([str(v) for v in sorted(dummy)]) + " "
assert dummy_str == tree._str()    