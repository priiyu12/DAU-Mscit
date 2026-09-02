import random

# 500 random numbers
random_keys = [random.randint(1, 10000) for _ in range(500)]
# print(random_keys)

# insert into binary tree
class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.val = key

def insert(root, key):
    if root is None:
        return Node(key)
    if key < root.val:
        root.left = insert(root.left, key)
    else:
        root.right = insert(root.right, key)
    return root

# Build BST
root = None
for key in random_keys:
    root = insert(root, key)

# height
def height(root):
    if root is None:
        return -1
    return 1 + max(height(root.left), height(root.right))

print("Height of BST:", height(root))

# sorted tree
sorted_keys = sorted(random_keys)

root_sorted = None
for key in sorted_keys:
    root_sorted = insert(root_sorted, key)

print("Height of BST (sorted input):", height(root_sorted))
