
class Node:
    def __init__(self, _data) -> None:
        self.data = _data
        self.prev = None
        self.next = None

    def attach(self, _prev, _next):
        if _prev is not None:
            _prev.next = self
        self.prev = _prev

        if _next is not None:
            _next.prev = self 
        self.next = _next

    def detach(self):
        if self.prev is not None:
            self.prev.next = self.next

        if self.next is not None:
            self.next.prev = self.prev

        self.prev = None
        self.next = None 

class List:
    def __init__(self) -> None:
        self.head = None
        self.tail = None

    def push_back(self, data):
        if self.head is None:
            self.head = Node(data)
            self.tail = self.head 
        else:
            new_node = Node(data)
            new_node.attach(self.tail, None)
            self.tail = new_node

    def push_front(self, data):
        if self.head is None:
            self.head = Node(data)
            self.tail = self.head
        else:
            new_node = Node(data)
            new_node.attach(None, self.head)
            self.head = new_node

    def pop_back(self):
        if self.tail is None:
            return None
        else:
            _data = self.tail.data
            _tail = self.tail
            self.tail = self.tail.prev
            _tail.detach()
            return _data
            
    def pop_front(self):
        if self.head is None:
            return None 
        else:
            _data = self.head.data
            _head = self.head
            self.head = self.head.next
            _head.detach()
            return _data

    def remove(self, data):
        if self.head is None:
            return
        else:
            node = self.head
            while node is not None:
                if node.data == data:
                    node.detach()
                    return
                else:
                    node = node.next

    def _str(self):
        out = ""

        node = self.head
        while node is not None:
            out += str(node.data) + " - "
            node = node.next

        return out

import numpy as np

if __name__=="__main__":
    rnd_list = list(np.random.choice(range(1000), 200))
    rnd_list_str = " - ".join([str(v) for v in rnd_list]) + " - "

    l = List()
    for v in rnd_list:
        l.push_back(v)

    assert l._str()==rnd_list_str, "List is not the same as ground truth"

    for v in list(np.random.choice(rnd_list, 50)):
        if v in rnd_list:
            rnd_list.remove(v)
        l.remove(v)

    rnd_list_str = " - ".join([str(v) for v in rnd_list]) + " - "
    assert l._str()==rnd_list_str, "List is not the same as ground truth"


    