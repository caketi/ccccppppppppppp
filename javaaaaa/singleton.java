//a singleton implementation may use lazy initialization.
// ensure a class has only one instance provide a global point of access to it
public final class singleton{
    private static volatile singleton instance = null;
    private singleton(){}
    public static singleton getInstance(){
        if(instance == null){
            synchronized(singleton.class){
                if(instance == null){
                    instance = new singleton();
                }
            }
        }
        return instance;
    }
}