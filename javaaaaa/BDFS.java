import java.util.LinkedList;
import java.util.Queue;

class BDFS{
    class Node{
        public Node root;
        public Node left;
        public Node right;
        public int val;

    }
    public void BFS1(Node root){
        if(root == null){
            return;
        }
        Queue<Node> q = new LinkedList<Node>();
        q.offer(root);
        while(!q.isEmpty()){
            int size = q.size();
            for(int i  =0; i < size; i++){
                Node n = q.remove();
                if(n.left!=null){
                    q.offer(n.left);
                }
                if(n.right!=null){
                    q.offer(n.right);
                }
                System.out.println(n.val + " ");
            }
            System.out.println();
        }
    }
}