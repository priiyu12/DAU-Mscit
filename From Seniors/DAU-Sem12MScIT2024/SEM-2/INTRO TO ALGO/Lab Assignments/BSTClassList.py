class Node:
    def __init__(self, key, name):
        self.left = None
        self.right = None
        self.val = (key, name)

class BST:
    def __init__(self):
        self.root = None
    
    def insert(self, root, key, name):
        if root is None:
            return Node(key, name)
        if key < root.val[0]:
            root.left = self.insert(root.left, key, name)
        else:
            root.right = self.insert(root.right, key, name)
        return root
    
    def search(self, root, key):
        if root is None or root.val[0] == key:
            return root
        if key < root.val[0]:
            return self.search(root.left, key)
        return self.search(root.right, key)
    
    def inorder(self, root):
        if root:
            self.inorder(root.left)
            print(root.val[0], root.val[1])
            self.inorder(root.right)

bst = BST()
with open("class_list.txt", "r") as file:
    lines = file.readlines()[1:]
    for line in lines:
        parts = line.strip().split('\t')
        if len(parts) == 2:
            student_id, name = parts
            student_id = int(student_id)
            bst.root = bst.insert(bst.root, student_id, name)

print("Inorder of Student BST: from teh given file ")
bst.inorder(bst.root)

search_id = int(input("Enter Id to find the student")) 
found = bst.search(bst.root, search_id)
if found:
    print(f"Student Found: {found.val[1]}")
else:
    print("Student Not Found")