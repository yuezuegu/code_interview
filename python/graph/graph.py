




class Node:
    def __init__(self, _id) -> None:
        self.id = _id
        self.src = []
        self.dst = []

    def add_dst(self, dst):
        if dst not in self.dst:
            self.dst.append(dst)
        if self not in dst.src:
            dst.src.append(self)


class Queue:
    def __init__(self) -> None:
        self.list = []

    def push(self, node):
        self.list.append(node)

    def pop(self):
        return self.list.pop(0)

    def is_empty(self):
        return len(self.list) == 0

class Stack:
    def __init__(self) -> None:
        self.list = []

    def push(self, node):
        self.list.append(node)

    def pop(self):
        return self.list.pop(len(self.list)-1)

    def is_empty(self):
        return len(self.list) == 0


class Graph:
    def __init__(self, adj_list) -> None:
        self.nodes = []

        for _id in range(len(adj_list)):
            self.nodes.append(Node(_id))

        for _id  in range(len(adj_list)):
            for _dst in adj_list[_id]:
                self.nodes[_id].add_dst(self.nodes[_dst])



    def traverse(self, algo='bfs'):
        visited = []

        if algo == 'bfs':
            queue = Queue()
        else:
            queue = Stack()

        queue.push(self.nodes[0])

        while not queue.is_empty():
            node = queue.pop()

            if node in visited:
                continue

            for dst in node.dst:
                queue.push(dst)

            visited.append(node)
            print(node.id)




if __name__=="__main__":
    adj_list = [[1,2,3], [4,5], [], [3,6], [], [4], []]
    g = Graph(adj_list)

    print("bfs:")
    g.traverse(algo='bfs')
    
    print("dfs:")
    g.traverse(algo='dfs')

    exit()