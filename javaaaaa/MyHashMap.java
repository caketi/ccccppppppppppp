import java.util.Arrays;

public class MyHashMap<K,V>{
    // MyHashMap.Node
    public static class Node<K,V>{
        final K key;
        V value;
        Node<K,V> next;
        Node(K key, V value){
            this.key = key;
            this.value = value;
        }
        public K getKey(){
            return key;
        }
        public V getValue(){
            return value;
        }
        public void setValue(V value){
            this.value = value;
        }
    }
    public static final int DEFAULT_CAPACITY = 16;
    public static final float DEFAULT_LOAD_FACTOR = 0.75f;

    private Node<K,V>[] array;
    private int size;
    private float loadFactor;

    public MyHashMap(){
        this(DEFAULT_CAPACITY, DEFAULT_LOAD_FACTOR);
    }

    public MyHashMap(int cap, float loadFactor){
        if(cap <= 0){
            throw new IllegalArgumentException("cap can not be <=0");
        }
        this.array = (Node<K,V>[])(new Node[cap]);
        this.size = 0;
        this.loadFactor = loadFactor;
    }

    public int size(){
        return size;
    }
    public boolean isEmpty(){
        return size == 0;
    }
    public void clear(){
        Arrays.fill(this.array, null);
        size = 0;
    }

    private int hash(K key){
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
        //  java's % return remainder rather than modulus.it can be negative;
    }
    private int getIndex(K key){
        return hash(key) % array.length;
    }

    private boolean equalsValue(V value, V value2){
        // v1, v2 all possibly to be null
        if(value==null && value2 == null){
            return true;
        }
        if(value==null || value2 == null){
            return false;
        }
        return value.equals(value2);
        // return v1 == v2 || v1 != null && v1.equals(v2);
    }
    private boolean equalsKey(K key, K key2){
        if(key == null && key2 == null){
            return true;
        }
        if(key == null || key2 == null){
            return false;
        }
        return key.equals(key2);
        // or 
        // return k1 == k2 || k1 != null && k1.equals(k2);
    }

    public boolean containsValue(V value){
        if(isEmpty()){
            return false;
        }
        for(Node<K,V> node : array){
            while(node != null){
                if(equalsValue(node.value, value)){
                    return true;
                }
                node = node.next;
            }
        }
        return false;
    }

    public V get(K key){
        int index = getIndex(key);
        Node<K,V> node = array[index];
        while(node !=null){
            if(equalsKey(node.key, key)){
                return node.value;
            }
            node = node.next;
        }
        return null;
    }

    public V put(K key,V value){
        int index = getIndex(key);
        Node<K,V>  head = array[index];
        Node<K,V> node = head;
        while(node != null){
            if(equalsKey(node.key, key)){
                V result = node.value;
                node.value = value;
                return result;
            }
            node = node.next;
        }
        Node<K, V> newNode = new Node(key, value);
        newNode.next = head;
        array[index] = newNode;
        size++;
        if(needRehashing()){
        //     rehashing();
         }
        return null;
    }
    private boolean needRehashing(){
        float ratio = (size+0.0f)/array.length;
        return ratio >= loadFactor;
    }
}
//     private boolean rehashing(){
//         // new double sized array
//         // for each node in  the old arary
//         // do the put() operation in the new larger array
//     }
//     //  if the key exists, remove the <key, value> from the
//     // HashMap, return the value
//     //  if the key not exists, return null.
//     public V remove(K key){
//         // get index
//         // delete operation on the linked list
//         //  size--
//     }
// }