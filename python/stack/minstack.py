



class Stack:
    def __init__(self) -> None:
        self.list = []

    def push(self, data):
        self.list.append(data)

    def pop(self):
        return self.list.pop()

    def is_empty(self):
        return len(self.list) == 0


class MinStack:
    def __init__(self) -> None:
        self.stack = Stack()
        self.minval = None

    def push(self, data):
        if self.minval is None:
            self.minval = data

        if data < self.minval:
            self.stack.push(2*data - self.minval)
            self.minval = data
        else:
            self.stack.push(data)

    def pop(self):
        if self.stack.is_empty():
            return None
        else:
            last_item = self.stack.pop()
            if last_item >= self.minval:
                return last_item
            else:
                retval = self.minval
                self.minval = 2*self.minval - last_item
                return retval