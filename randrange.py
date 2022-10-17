import random
import sys

many = int(sys.argv[1])
rang0 = -2147483648
rang1 = 2147483647
if len(sys.argv) == 4:
    rang0 = int(sys.argv[2])
    rang1 = int(sys.argv[3])
for i in range(many):
    print(random.randint(rang0, rang1), end=' ')