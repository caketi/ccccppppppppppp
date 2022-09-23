 class Outerclass {
    private static String msg = "MEssage";
    public static class NestedStaticClass{
        // Only static members of Outer class is directly accessible in
        // nested static class 
        public void printMessage(){
            // compiler error
            // try making 'msg' a non-static variable 
            System.out.println("Message from nested static class: "+msg);
        }
        private static void printOut(){}
    }
    public class InnerClass{
        // Both static and non-static members of Outer class are accessible 
        // in this Inner class
        public void display(){
            System.out.println("Message from non static nested class: "+msg);
        }
        // can you declare  a static method here
        //  static method can only be declared in a static class or a top-level class
        public static void printOut(){}
        public Outerclass getOuterClass(){
            return Outerclass.this;
        }
    }

    
}

public class OuterClassTest{
    public static void main(String[] args){
        Outerclass.NestedStaticClass printer = new Outerclass.NestedStaticClass();
        // call non static method of nested static class
        printer.printMessage();

        // In order to create instance of Inner class we need an Outer class
        // instance. create Outer class instance for creating non-sta tic nested class
        // 
        Outerclass outer = new Outerclass();
        Outerclass.InnerClass inner = outer.new InnerClass();

    }
}
