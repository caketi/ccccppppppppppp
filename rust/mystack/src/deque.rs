#[derive(Debug)]
struct Deque<T>{
    cap: size,
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
mod tests{
 use super::*;
 #[test]
 fn it_works(){
    let mut q = Deque::new();
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