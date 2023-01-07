#[derive(Debug)]
struct Stack<T> {
    top: usize,
    data: Vec<T>,
}

impl<T> Stack<T> {
    fn new() -> Self {
        Self {
            top: 0,
            data: Vec::new(),
        }
    }

    fn push(&mut self, val: T) {
        self.data.push(val);
        self.top += 1;
    }

    fn pop(&mut self) -> Option<T> {
        if self.top == 0 {
            return None;
        }
        self.top -= 1;
        self.data.pop()
    }

    fn peek(&self) -> Option<&T> {
        if self.top == 0 {
            return None;
        }
        self.data.get(self.top - 1)
    }
    fn is_empty(&self) -> bool {
        self.top == 0
    }

    fn size(&self) -> usize {
        self.top
    }
}

fn convert_to_base7(mut num: i32) -> String {
    if num == 0 {
        return "0".to_string();
    }
    let mut stack = Vec::new();
    let sign = num.signum();
    num = num.abs();
    // 余数入栈
    while num != 0 {
        let rem = num % 7;
        stack.push(rem);
        num /= 7;
    }
    let mut base7 = "".to_string();
    while !stack.is_empty() {
        base7 += &stack.pop().unwrap().to_string();
    }

    if sign < 0 {
        return "-".to_string() + &base7;
    }
    base7
}

fn eval_rpn(tokens: Vec<String>) -> i32 {
    // 存放数字的栈
    let mut nums = Vec::new();

    for token in tokens.into_iter() {
        match token.parse() {
            Ok(n) => nums.push(n),
            Err(_) => {
                // 当匹配到运算符时弹出数字计算
                let r = nums.pop().unwrap();
                let l = nums.pop().unwrap();
                nums.push(do_calc(&token, l, r));
            }
        }
    }
    nums[0]
}
// 执行计算逻辑
fn do_calc(op: &str, a: i32, b: i32) -> i32 {
    match op {
        "*" => a * b,
        "/" => a / b,
        "+" => a + b,
        _ => a - b,
    }
}

fn is_valid(s: String) -> bool {
    let mut stack = Vec::new();
    for c in s.chars() {
        match c {
            '(' | '[' | '{' => {
                stack.push(c);
            }
            ')' | '}' | ']' => {
                if stack.is_empty() {
                    return false;
                }
                let top = stack.pop().unwrap();
                let res = || "([{".find(top) == ")]}".find(c);
                if !res() {
                    return false;
                }
            }
            _ => (),
        }
    }
    stack.is_empty()
}
#[derive(Debug)]
struct Deque<T>{
    cap: usize,
    data: Vec<T>,
}

impl<T> Deque<T>{
    fn new(size: usize) -> Self{
        Deque{
            cap: size,
            data: Vec::with_capacity(size)
        }
    }
    fn add_front(&mut self, val: T) -> Result<(),String>{
        if Self::size(&self) == self.cap{
            return Err(String::from("No space available"));
        }
        self.data.push(val);
        Ok(())
    }
    fn add_rear(&mut self, val: T) -> Result<(),String>{
        if Self::size(&self) == self.cap{
            return Err(String::from("No space available"));
        }
        self.data.insert(0, val);
        Ok(())
    }
    fn remove_front(&mut self) -> Option<T>{
        if Self::size(&self) > 0{
            self.data.pop()
        }else{
            None
        }
    }
    fn remove_rear(&mut self) -> Option<T>{
        if Self::size(&self) > 0{
            self.data.pop()
        }else{
            None
        }
    }
    fn is_empty(&self) -> bool {
        Self::size(&self) == 0
    }
    fn size(&self) -> usize {
        self.data.len()
    }
}
#[cfg(test)]
mod tests1{
 use super::*;
 #[test]
 fn it_works(){
    let mut q = Deque::new(4);
    let _r1 = q.add_front(1);
    let _r2 = q.add_front(1);
    let _r3 = q.add_rear(11);
    let _r4 = q.add_rear(23);

    println!("size: {}, empty: {}",q.size(), q.is_empty());
    println!("content: {:?}", q);
 }
}
fn is_palindrome(s: String) -> bool{
    let mut d = Vec::new();

    let s = s.chars().filter(|x| x.is_alphabetic()).map(|x| x.to_lowercase().nth(0).unwrap()).collect::<String>();

    for c in s.chars(){
        d.push(c);
    }

    let mut flag = true;
    while d.len() > 1 && flag {
        let head = d.pop().unwrap();
        let tail = d.remove(0);

        if head != tail{
            flag = false;
        }
    }
    flag
}
#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn isit_valid() {
        let s = "(){}[]}".to_string();
        let res = is_valid(s.clone());
        println!("string s \"{}\" is valid: {}", s.clone(), res);
    }
    #[test]
    fn it_works() {
        // 在 Rust 中，unwrap 意味着发出以下命令：给我计算结果，如果有错误，恐慌并停止程序。
        let mut stack = Stack::new();
        stack.push(1);
        stack.push(2);
        stack.push(3);
        println!("top: {:?}, size: {:?}", stack.peek().unwrap(), stack.size());
        println!("pop: {:?}, size: {:?}", stack.pop().unwrap(), stack.size());
        println!("is_empty: {:?}, stack: {:?}", stack.is_empty(), stack);
    }
}
