```Java
public static void pre(Node head){
    System.out.print("pre-order: ");
    if(head != null){
        Stack<Node> stack = new Stack<Node>();
        stack.add(head);
        while(!stack.isEmpty()){
            head = stack.pop();
            System.out.print(head.value+" ");
            if(head.right != null){
                stack.push(head.right);
            }if(head.left != null){
                stack.push(head.left);
            }
        }
    }
    System.out.println();
}
public static void pos1(Node head){
    System.out.print("pos-order: ");
    if(head != null){
        Stack<Node> s1 = new Stack<Node>();
        Stack<Node> s2 = new Stack<Node>();
        s1.push(head);
        while(!s1.isEmpty()){
            head = s1.pop(); // 头右左
            s2.push(head);
            if(head.left != null){
                s1.push(head.left);
            }
            if(head.right != null){
                s1.push(head.right);
            }
        }
        // 左右头
        while(!s2.isEmpty()){
            System.out.print(s2.pop().value + " ");
        }
    }
}
public static void pos2(Node h){
    System.out.print("pos-order: ");
    if(h!= null){
        Stack<Node> stack = new Stack<Node>();
        stack.push(h);
        Node c = null;
        while(!stack.isEmpty()){
            c = stack.peek();
            if(c.left!=null && h!=c.left && h!=c.right){
                stack.push(c.left);
            }else if(c.right!=null&&h!=c.right){
                stack.push(c.right);
            }else{
                System.out.print(stack.pop().value + " ");
                h = c;
            }
        }
    }
    System.out.println();
}

public static void in(Node head){
    System.out.print("in-order: ");
    if(head != null){
        Stack<Node> stack = new Stack<Node>();
        while(!stack.isEmpty() || head != null){
            if(head != null){
                stack.push(head);
                head = head.left;
            }else {
                head = stack.pop();
                System.out.print(head.value + " ");
                head = head.right;
            }
        }
    }
    System.out.pritnln();
}
```

