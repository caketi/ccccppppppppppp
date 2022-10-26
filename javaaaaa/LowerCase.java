public class LowerCase {
    public static void main(String[] args){
        String s1 = "abcd";
        System.out.println(s1.toLowerCase().equals("abcd"));
        System.out.println(s1.toLowerCase().contentEquals("abcd"));
        System.out.println(s1.toLowerCase() == "abcd");
        String s2 = "Abcd";
        System.out.println(s2.toLowerCase().contentEquals("abcd"));
        System.out.println(s2.toLowerCase() == "abcd");
    }
}
