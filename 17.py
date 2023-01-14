import hashlib


class Queue:
    def __init__(self):
        self.container = []
        self.pointer = 0

    def push(self, value):
        self.container.append(value)

    def pop(self):
        assert not self.is_empty()
        self.pointer += 1
        return self.container[self.pointer - 1]

    def is_empty(self):
        return self.pointer >= len(self.container)

moves = [[-1, 0], [1, 0], [0, -1], [0, 1]]

original_code = 'qtetzkpl'

cur = 0, 0
q = Queue()
q.push((0, 0, original_code))
opened_codes = {chr(x) for x in range(ord('b'), ord('g'))}
answer_first = None
answer_second = 0
while not q.is_empty():
    x, y, code = q.pop()
    opened =[x in opened_codes for x in hashlib.md5(code.encode('utf-8')).hexdigest()[:4]]
    for (dx, dy), is_opened, move_letter in zip(moves, opened, 'UDLR'):
        if not is_opened:
            continue
        
        tx, ty = x + dx, y + dy
        if 0 <= tx < 4 and 0 <= ty < 4:
            new_code = code + move_letter
            if tx == 3 and ty == 3:
                if answer_first is None:
                    answer_first = new_code[len(original_code):] 
                answer_second = len(new_code) - len(original_code)
            else:
                q.push((tx, ty, new_code))


print('Part 1:', answer_first)
print('Part 2:', answer_second)