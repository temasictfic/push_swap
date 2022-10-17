import random
import sys

many = int(sys.argv[1])
start = -2147483648
end = 2147483647
if len(sys.argv) == 4:
    start = int(sys.argv[2])
    end = int(sys.argv[3])

candidates = set((random.randint(start, end) for i in range(many)))

if len(candidates) < many:
    while (many - len(candidates) != 0):
        candidates.add(random.randint(start, end))

candidates = list(candidates)
random.shuffle(candidates)

for n in candidates:
    print(n, end=' ')