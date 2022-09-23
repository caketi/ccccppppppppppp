public class length {
    
    public static class ListNode {
        public int val;
        public ListNode next;

        public ListNode(int data) {
            val = data;
        }
    }
    public static int listLength(ListNode head) {
        int len = 0;
        while (head != null) {
            // len++;
            head = head.next;
            len++;
        }
        return len;
    }
    public static void main(String[] args){
        ListNode l = null;
        
        System.out.println(listLength(l));
    }

}
