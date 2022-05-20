





class Node:
    def __init__(self, data, parent) -> None:
        self.data = data
        self.left = None
        self.right = None
        self.parent = parent

    def insert(self, data):
        if self.left is None:
            _node = Node(data, self)
            self.left = _node
        elif self.right is None:
            _node = Node(data, self)
            self.right = _node
        else:
            _node = self.left.insert(data)

        self.heapify()

        return _node
        
    def swap(node1, node2):
        _data = node1.data
        node1.data = node2.data
        node2.data = _data

    def is_root(self):
        return isinstance(self.parent, MinHeap)

    def heapify(self):
        if self.left is not None:
            if self.left.data < self.data:
                Node.swap(self.left, self)
                self.left.heapify()

        if self.right is not None:
            if self.right.data < self.data:
                Node.swap(self.right, self)
                self.right.heapify()

    def detach(self):
        assert self.left is None and self.right is None, "Cannot detach a non-leaf node"

        if self.is_root():
            self.parent.root = None
            self.parent = None
        else:
            if self == self.parent.left:
                self.parent.left = None
            else:
                self.parent.right = None
            self.parent = None




class MinHeap:
    def __init__(self) -> None:
        self.root = None

    def insert(self, data):
        if self.root is None:
            _node = Node(data, self)
            self.root = _node
        else:
            _node = self.root.insert(data)

    def pop(self):
        if self.root is None:
            return None
        else:
            _data = self.root.data
            leaf_node = self.get_leaf()
            self.root.data = leaf_node.data
            self.root.heapify()

            leaf_node.detach()
            return _data

    def is_empty(self):
        return self.root is None

    def get_leaf(self):
        if self.root is None:
            return None
        else:
            node = self.root
            while node.left is not None or node.right is not None:
                if node.left is None:
                    node=node.right
                else:
                    node = node.left
            return node

if __name__=="__main__":
    import numpy as np

    rnd_list = np.random.choice(range(1000), 200, replace=False)

    heap = MinHeap()

    for data in rnd_list:
        heap.insert(data)

    out = []
    while not heap.is_empty():
        out.append(heap.pop())

    assert sorted(rnd_list) == out, "Results are not correct!"
