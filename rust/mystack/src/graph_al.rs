#[allow(warnings)]
use std::collections::BTreeMap;

#[derive(Debug)]
struct Graph<T> {
    pub matrix: Vec<Vec<Option<usize>>>,
    pub nodes: BTreeMap<usize, Option<T>>,
}
impl<T> Graph<T> {
    fn new() -> Self {
        Self {
            matrix: vec![],
            nodes: BTreeMap::new(),
        }
    }
}
#[test]
fn graph_test() {
    let g: Graph<String> = Graph::new();
    println!("{:?}", g);
}
