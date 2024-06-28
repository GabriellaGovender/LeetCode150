from typing import Optional

# Define the ListNode class (if not already defined)
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# Function to print the linked list (for testing purposes)
def printLinkedList(node):
    while node is not None:
        print(node.val, end=" -> ")
        node = node.next
    print("None")
    
class Solution:
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        result = ListNode(0)
        curr = result
        carry = 0
        
        while (l1 is not None or l2 is not None):
            n1 = l1.val if l1 is not None else 0
            n2 = l2.val if l2 is not None else 0
            
            total = n1 + n2 + carry
            carry = total // 10
            curr.next = ListNode(total % 10)
            curr = curr.next
            
            if l1 is not None: l1 = l1.next
            if l2 is not None: l2 = l2.next
            
        if (carry > 0):
            curr.next = ListNode(carry)
        
        return result.next

# Create the first linked list: l1 = [2 -> 4 -> 3] (which represents the number 342)
l1 = ListNode(2)
l1.next = ListNode(4)
l1.next.next = ListNode(3)

# Create the second linked list: l2 = [5 -> 6 -> 4] (which represents the number 465)
l2 = ListNode(5)
l2.next = ListNode(6)
l2.next.next = ListNode(4)

# Instantiate the Solution class
solution = Solution()

# Call the addTwoNumbers method
result = solution.addTwoNumbers(l1, l2)

# Print the result linked list
printLinkedList(result)
