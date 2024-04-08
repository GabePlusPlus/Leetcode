/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
   public:
    inline void carryAdjust(unsigned short int& subtotal,
                            unsigned short int& carry) {
        /*
         * If the subtotal (sum of the current place value digit(s) and carry)
         * is greater than 9 (contains more than 1 digit), places all digits
         * above the ones place in the carry variable (shifted one place down),
         * and retains the least significant digit in the subtotal variable.
         *
         * Otherwise, leaves the subtotal variable untouched and sets the carry
         * variable to 0.
         */
        if (subtotal > 9) {
            carry = subtotal / 10;
            subtotal = subtotal % 10;
        } else {
            carry = 0;
        }
    }

    inline void incrementTotal(ListNode*& current_node,
                               unsigned short int const& subtotal) {
        current_node->next = new ListNode;
        current_node = current_node->next;
        current_node->val = subtotal;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *precursor, *current_node,
            *t1 = l1,
            *t2 = l2;  // Good practice not to modify l1 and l2 directly
        precursor = current_node = new ListNode;
        unsigned short int subtotal = 0,
                           carry = 0;

        while ((t1 != nullptr || t2 != nullptr) || carry) {
            subtotal = carry;
            if (t1) subtotal += (unsigned short int)t1->val;
            if (t2) subtotal += (unsigned short int)t2->val;

            carryAdjust(subtotal, carry);
            incrementTotal(current_node, subtotal);

            t1 = t1 ? t1->next : nullptr;
            t2 = t2 ? t2->next : nullptr;
        }

        current_node = precursor->next;
        delete precursor;
        return current_node;
    }
};
