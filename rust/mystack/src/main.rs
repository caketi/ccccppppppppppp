pub struct Node {
    elem: i32,
    next: Option<Box<Node>>,
}

pub struct Stack {
    head: Option<Box<Node>>,
}

impl Stack {
    pub fn new() -> Stack {
        Stack { head: None }
    }
    pub fn push(&mut self, elem: i32) {
        let new_node = Some(Box::new(Node {
            elem,
            next: self.head.take(), //  none<-1<-2
        }));
        self.head = new_node;
    }
    pub fn pop(&mut self) -> Option<i32> {
        self.head.take().map(|node| {
            self.head = node.next;
            node.elem
        })
    }

    pub fn peek(&mut self) -> Option<&i32> {
        self.head.as_ref().map(|node| &node.elem)
    }
}

#[cfg(test)]
mod test {
    use super::Stack;
    #[test]
    fn test_basic_operation() {
        let mut stk = Stack::new();
        stk.push(1);
        stk.push(2);
        stk.push(3);

        assert_eq!(stk.pop(), Some(3));
    }
    #[test]
    fn test_take() {
        let mut x = Some(2);
        let y = x.take();
        assert_eq!(x, None);
        assert_eq!(y, Some(2));

        let mut x: Option<u32> = None;
        let y = x.take();
        assert_eq!(x, None);
        assert_eq!(y, None);
    }
}

pub fn get_next(next: &mut Vec<usize>, s: &Vec<char>) {
    let len = s.len();
    let mut j = 0;
    for i in 1..len {
        while j > 0 && s[i] != s[j] {
            j = next[j - 1];
        }
        if s[i] == s[j] {
            j += 1;
        }
        next[i] = j;
    }
}

pub fn str_str(haystack: String, needle: String) -> i32 {
    let (haystack_len, needle_len) = (haystack.len(), needle.len());
    if haystack_len == 0 {
        return 0;
    }
    if haystack_len < needle_len {
        return -1;
    }
    let (haystack, needle) = (
        haystack.chars().collect::<Vec<char>>(),
        needle.chars().collect::<Vec<char>>(),
    );
    let mut next: Vec<usize> = vec![0; haystack_len];
    get_next(&mut next, &needle);
    let mut j = 0;
    for i in 0..haystack_len {
        while j > 0 && haystack[i] != needle[j] {
            j = next[j - 1];
        }
        if haystack[i] == needle[j] {
            j += 1;
        }
        if j == needle_len {
            return (i - needle_len + 1) as i32;
        }
    }
    return -1;
}
pub struct Solution{}
impl Solution {
    pub fn get_next(needle:&Vec<u8>, mut next: Vec<usize>)->Vec<usize>{
        let mut i = 1;
        let mut j = 0;
        while i < needle.len()
        {
            if needle[i] == needle[j]
            {
                j=j+1;
                next[i]=j;
                i=i+1;
            }
            else{
                if j!=0{
                    j = next[j-1];
                }
                else{
                    next[i]=0;
                    i=i+1;
                }
            }
        }
        next
    }
 
    pub fn kmp(haystack:&Vec<u8>,needle:&Vec<u8>) -> i32{
        let m = needle.len();
        if m == 0 {
            return 0;
        }
        if haystack.len()<needle.len(){
            return -1;
        }
        let mut next = Solution::get_next(needle,vec![0usize;m]);
        let mut i=0;
        let mut j=0;
        while i<haystack.len() && j<needle.len(){
            if haystack[i]==needle[j]
            {
                i=i+1;
                j=j+1;
            }else
            {
                if j!=0{
                    j=next[j-1];
                }
                else { i=i+1;}
            }
        }
        if j == needle.len(){
            (i-j) as i32
        }
        else{
            -1
        }
    }
 
    pub fn str_str(haystack: String, needle: String) -> i32 {
        return Solution::kmp(&haystack.as_bytes().to_vec(),&needle.as_bytes().to_vec());
    }
}


fn kmp(s: Vec<i32>, p: Vec<i32>) -> (bool, usize) {
    let length_p = p.len();
    let mut next = vec![0];
    // 生成next数组
    for i in 1..length_p {
        if p[next[i - 1]] == p[i] {
            next.push(next[i - 1] + 1);
        } else {
            next.push(0);
        }
    }
    let length_s = s.len();
    let (mut i, mut j) = (0, 0);
    // i是指向原数组,j是指向匹配数组
    while i < length_s {
        if s[i] == p[j] {
            i += 1;
            j += 1;
        } else if j != 0 {
            j = next[j - 1];
        } else {
            i += 1
        }
        if j == length_p {
            return (true, i - j);
        }
    }
    (false, 0)
}


#[cfg(test)]
mod test_kpm {
    use super::kmp;
    use super::str_str;

    #[test]
    fn test_fff(){
        let s = vec![78,43,2,43,12,5,43,321,76,48,3,45,24,5,5,5,5,5,5,5,5,6,5,5,52,0];
        let a = vec![5, 5, 6, 5, 5, 52];
        println!("{:?}",kmp(s, a));
    }
    #[test]
    fn test_str_str() {
        let haystack = "holo".to_string();
        let needle = "o".to_string();
        let res = str_str(haystack, needle);
        println!("result : {}", res);
    }
}
fn kmp_next(str: &Vec<u8>) -> Vec<Option<usize>> {
    let mut k = Some(0);
    let n = str.len();
    // using Option because usize not supported -1
    let mut next = vec![Some(0); n];
    next[0] = None;
    for i in 1..n {
        next[i] = k;
        while k.is_some() && str[i] != str[k.unwrap()] {
            k = next[k.unwrap()];
        }
        k = match k {
            Some(k) => Some(k + 1),
            None => Some(0),
        }
    }
    return next;
}
fn kmp_index(input: (&Vec<u8>, &Vec<u8>)) -> Option<usize> {
    let next = kmp_next(input.1);
    println!("{:?}", next);
    let n = input
        .0
        .len()
        .checked_sub(input.1.len())
        .expect("Invalid input, the first string should be longer than the second string");
    let mut j = Some(0);
    for i in 0..n {
        if j == Some(input.1.len()) {
            return Some(i - j.unwrap());
        }
        while j.is_some() && input.0[i] != input.1[j.unwrap()] {
            j = next[j.unwrap()];
        }
        j = match j {
            Some(j) => Some(j + 1),
            None => Some(0),
        }
    }
    None
}
fn main() -> std::io::Result<()> {
    let stdin = std::io::stdin();
    let mut str: (String, String) = Default::default();
    println!("insert one string");
    stdin
        .read_line(&mut str.0)
        .expect("failed to parse console input");
    println!("insert another string");
    stdin
        .read_line(&mut str.1)
        .expect("failed to parse console input");
    // index into a string is unsafe in rust
    // using vec<u8> for this algorithm
    // please using find function provider by standard library
    // for real world project
    // or try it with chars instead
    let str = (
        &str.0.trim().bytes().collect(),
        &str.1.trim().bytes().collect(),
    );
    match kmp_index(str) {
        Some(index) => {
            println!("{}", index);
        }
        None => {
            println!("not match")
        }
    }
    Ok(())
}