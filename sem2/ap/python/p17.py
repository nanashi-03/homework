import heapq
from typing import Any


class PriorityQueue:
    def __init__(self):
        self._queue = []
        self._index = 0

    def push(self, item: Any, priority: float):
        heapq.heappush(self._queue, (-priority, self._index, item))
        self._index += 1

    def pop(self) -> Any:
        if self.is_empty():
            raise IndexError("Pop from an empty priority queue")

        _, _, item = heapq.heappop(self._queue)
        return item

    def is_empty(self) -> bool:
        return len(self._queue) == 0

    def __len__(self) -> int:
        return len(self._queue)


pq = PriorityQueue()

pq.push("Write low-priority documentation", priority=1)
pq.push("Fix critical production bug", priority=10)
pq.push("Refactor clean code architecture", priority=5)
pq.push("Answer client emails", priority=5)

print(f"Queue size: {len(pq)}\n")

print("Processing items in order of priority:")
while not pq.is_empty():
    print(f"-> Processing: {pq.pop()}")
