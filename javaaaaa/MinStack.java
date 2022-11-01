import java.util.Stack;

//  次小值永远在最小值下面
// 当新加入的元素a为入栈后的最小值， 再讲a入栈前，先将此时的最小元素min入栈
// 再入a，再1更新min
  class MinStack{
    Stack<Integer> stack;
    int min;
    Stack<Integer> min_stack;
    public MinStack(){
      stack = new Stack<>();
      min = Integer.MAX_VALUE;
      min_stack = new Stack<>();
    }
    public void push(int val){
      if(val <= min){
        stack.push(min);
        min = val;
      }
      stack.push(val);
      // if(!min_stack.isEmpty() || val >= min_stack.peek()){
      //   min_stack.push(val);
      // }
    }
    public void pop(){
      int val = stack.pop();
      if(val == min){
        min = stack.pop();
      }
      // if(min_stack.peek() == val){
      //   min_stack.pop();
      // }
    }
    public int top(){
      return stack.peek();
    }
    public int getMin(){
      return min;
      // return min_stack.peek();
    }
  }