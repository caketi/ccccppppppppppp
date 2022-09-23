

public class HashMap {
    public class ListNode{
        String key;
        Integer value;
        ListNode next;
        public ListNode(String key, Integer value){
            this.key = key;
            this.value = value;
        }
    }
    private ListNode[] map;
    private int size; // key-value pairs
    private float loadFactor; // when to rehash

    // static final variable are global constants;
    public static final int DEFAULT_CAPACITY = 16;
    public static final float DEFAULT_LOAD_FACTOR = 0.75f;
    
    public HashMap(int cap, float loadFactor){
        map = new ListNode[cap];
        this.loadFactor = loadFactor;
    }
    public HashMap(){
        this(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR);
    }
    public HashMap(int  cap){
        this(cap, DEFAULT_LOAD_FACTOR);
    }
    public int size(){
        return this.size;
    }
    public void clear(){
        map = new ListNode[map.length];
        this.size = 0;
    }
    private int getIndex(int hashcode){
        return hashcode%DEFAULT_CAPACITY;
    }
    public void put(String key, Integer value){
        int hash = key.hashCode();
        int index = getIndex(hash);
        ListNode node =  map[index];
        if(node == null){
            node = new ListNode(key, value);
            map[index] = node;
        }else{
            while(node.next != null){
                if(node.key.equals(key)){
                    node.value =value;
                    return;
                }
                node = node.next;
            }
            node.next = new ListNode(key, value);
        }
    }

    public int getHashCode(String key){
        if(key == null){
            return 0;
        }
       // int code =key.hashCode();
        // return code >= 0 ? code : -code;
        // int range = [-2^31,2^31-1]
        // -Integer.MIN_VALUE = Integer.MIN_VALUE; -> overflow
        return key.hashCode() & 0x7FFFFFFF;
        // 01111111 11111111 11111111 11111111 
        // guarantee non-negative
        //  java's % return remainder rather than modulus.
    }
    private boolean equalsKey(Object k1, Object k2){
        if(k1 == null && k2 == null){
            return true;
        }
        if(k1 == null || k2 == null){
            return false;
        }
        return k1.equals(k2);
        // or 
        // return k1 == k2 || k1 != null && k1.equals(k2);
    }

    public Integer get(String key){
        int hash = getHashCode(key);
        int index = getIndex(hash);
        ListNode head = map[index];
        while(head != null){
            if(equalsKey(head.key, key)){
                return head.value;
            }
            head = head.next;
        }
        return null;
    }


}
