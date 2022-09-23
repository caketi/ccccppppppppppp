public class stackqueue {

    public stackqueue() {
    }
    public static class Node<V>{
        public V value;
        public Node<V> last;
        public Node<V> next;
        public Node(V v){
            value = v;
            last = null;
            next =null;
        }
    }

    public static class MyDeque<V>{
        private Node<V> head;
        private Node<V> tail;
        private int size;

        public MyDeque(){
            head = null;
            tail = null;
            size = 0;
        }
        public boolean isEmpty(){
            return size == 0;
        }
        public int size(){
            return size;
        }
        public void pushHead(V value){
            Node<V> cur = new Node<>(value);
            if(head == null){
                head = cur;
                tail = cur;
            } else {
                cur.next = head;
                head.last = cur;
                head = cur;
            }
            size ++;
        }
        public void pushTail(V value){
                Node<V> cur = new Node<>(value);
                if(head == null){
                    head = cur;
                    tail = cur;
                }else {
                    tail.next = cur;
                    cur.last = tail;
                    tail = cur;
                }
        }
        public V pollHead(){
            V ans = null;
            if(head == null){
                return ans;
            }
            size--;
            ans = head.value;
            if(head == tail){
                head = null;
                tail = null;
            }else{
                head = head.next;
                head.last = null;
            }
            return ans;
        }
        public V pollTail(){
            V ans = null;
            if(head == null){
                return ans;
            }
            size--;
            ans = tail.value;
            if(head == tail){
                head = null;
                tail = null;
            }else{
                tail = tail.last;
                tail.next = null;
            }
            return ans;
        }


    }
}
