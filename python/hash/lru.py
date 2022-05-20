
class LRU:
    def __init__(self, capacity) -> None:
        self.items = {}
        self.keys = []

        self.capacity = capacity
        self.no_items = 0

    def evict_last(self):
        evict_key = self.keys.pop(0)
        self.items.remove(evict_key)
        self.no_items -= 1

    def put(self, key, val):
        if self.no_items == self.capacity:
            self.evict_last()

        self.items[key] = val
        self.keys.append(key)
        self.no_items += 1

    def get(self, key):
        if key in self.keys:
            self.keys.remove(key)
            self.keys.append(key)
            return self.items[key]
        return None

    