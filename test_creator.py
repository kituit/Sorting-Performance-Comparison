# Creates a test input to be used by sorting algorithms
# Prints a list of SIZE numbers in descending order
SIZE = 10000000
print(SIZE)

l = [x for x in range(SIZE, 0, -1)]
for num in l:
    print(num, end=' ')
print('')