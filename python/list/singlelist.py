

class Node:
    def __init__(self, data) -> None:
        self.data = data
        self.next = None

    def insert_after(self, _next):
        if self.next is None:
            self.next = _next 
        else:
            old_next = self.next
            self.next = _next
            self.next.next = old_next

    def pop_next(self):
        if self.next is None:
            return None 
        else:
            retval = self.next.data
            self.next = self.next.next
            return retval

class List:
    def __init__(self) -> None:
        self.head = None
        self.length = 0

    def push_back(self, data):
        self.insert_at(data, self.length)

    def pop_front(self):
        return self.pop_at(0)

    def insert_at(self, data, index):
        self.length += 1

        if self.head is None:
            self.head = Node(data)
            return
        
        if index == 0:
            new_node = Node(data)
            new_node.insert_after(self.head)
            self.head = new_node
        else:
            node = self.head 
            cnt = 0
            while cnt < index - 1:
                node = node.next
                cnt += 1
            node.insert_after(Node(data))
        
    def pop_at(self, index):
        if self.head is None:
            return None
        
        self.length -= 1
        if index == 0:
            retval = self.head.data
            self.head = self.head.next
            return retval
        else:
            node = self.head
            cnt = 0
            while cnt < index - 1:
                node = node.next
                cnt += 1
            return node.pop_next()


    def _str(self):
        if self.head is None:
            return ""
        else:
            out = ""
            node = self.head 
            while node is not None:
                out += str(node.data) + " "
                node = node.next 
            return out


def reverse(head):
    if head is None:
        return None

    curr, _next = head, head.next 
    head.next = None

    while _next is not None:
        next_next = _next.next
        _next.next = curr 

        curr, _next = _next, next_next 

    return curr



import numpy as np
from multiprocessing.pool import ThreadPool
import time 

np.random.seed(0)

if __name__=="__main__":
    gt = list(np.random.choice(range(1000), 10))

    pool = ThreadPool(10)

    l = List()
    for d in gt:
        pool.apply_async(l.push_back, (d,))
    
    pool.close()
    pool.join()

    lstr = l._str()
    gtstr = " ".join([str(v) for v in gt]) + " "
    print(lstr)
    print(gtstr)
    assert lstr == gtstr



