import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;
import java.util.concurrent.CopyOnWriteArrayList;

class dm{
    static ArrayList<String> list = new ArrayList<>();
    static CopyOnWriteArrayList<String> copyOnWriteArrayList = new CopyOnWriteArrayList<>();
    static List<String> synList = Collections.synchronizedList(list);
    static Vector<Object> vector = new Vector<>();
    public static void main(String[] args){
        Thread t1 = new Thread(new Runnable() {
            public void run(){
                for(int i = 0;i < 6; i++){
                    copyOnWriteArrayList.add("Thread1--"+i);
                    printAll();
                }
            }
        });
        t1.start();
        Thread t2 = new Thread(()->{
            for(int i = 10; i<16; i++){
                copyOnWriteArrayList.add("Thread2--"+ i);
                printAll();
            }
        });
        t2.start();
    }
    public static void printAll(){
        Iterator<String> iterator = copyOnWriteArrayList.iterator();
        while(iterator.hasNext()){
            String value = iterator.next();
            System.out.println(value + "");
        }
    }
}