#[allow(warnings)]
pub mod sort_algorithms_v2 {
    pub fn merge<T: Ord + Copy>(left: &Vec<T>, right: &Vec<T>) -> Vec<T> {
        let mut l = 0;
        let mut r = 0;

        let mut result = vec![];
        while l < left.len() && r < right.len() {
            if left[l] < right[r] {
                result.push(left[l]);
                l += 1;
            } else {
                result.push(right[r]);
                r += 1;
            }
        }
        while l < left.len() {
            result.push(left[l]);
            l += 1;
        }
        while r < right.len() {
            result.push(right[r]);
            r += 1;
        }

        result
    }

    pub fn merge_sort_v2<T: Ord + Copy>(arr: Vec<T>) -> Vec<T> {
        if arr.len() == 1 {
            return arr;
        }
        let mid = arr.len() >> 1;
        let left = arr[0..mid].to_vec();
        let right = arr[mid..].to_vec();
        merge(&merge_sort_v2(left), &merge_sort_v2(right))
    }
}
#[allow(warnings)]
pub mod sort_algorithms {
    use std::vec;

    // worst | best | avg  |
    // O(n^2)| O(n) |O(n^2)| stable
    pub fn bubble_sort(n: &Vec<i32>) -> Vec<i32> {
        let mut nums = n.clone();
        let mut len = nums.len() - 1;
        let mut compare = true;
        while len > 0 && compare {
            compare = false;
            for i in 0..len {
                if nums[i] > nums[i + 1] {
                    nums.swap(i, i + 1);
                    compare = true;
                }
            }
            len -= 1;
        }
        nums
    }

    pub fn quick_sort(n: &Vec<i32>, low: usize, high: usize) -> Vec<i32> {
        let mut nums = n.clone();
        fn patition(nums: &mut [i32], low: usize, high: usize) -> usize {
            let mut lm = low;
            let mut rm = high;
            loop {
                while lm <= rm && nums[lm] <= nums[low] {
                    lm = lm + 1;
                }
                while lm <= rm && nums[rm] >= nums[low] {
                    rm = rm - 1;
                }
                if lm > rm {
                    break;
                } else {
                    nums.swap(lm, rm);
                }
            }
            nums.swap(low, rm);
            rm
        }
        if low < high {
            let split = patition(&mut nums, low, high);
            if split > 1 {
                quick_sort(&mut nums, low, split - 1);
            }
            quick_sort(&mut nums, split + 1, high);
        }
        nums
    }
    pub fn selection_sort(n: &Vec<i32>) -> Vec<i32> {
        let mut nums = n.clone();
        let mut len = nums.len() - 1;
        while len > 0 {
            let mut pos_max = 0 as usize;
            for i in 0..=len {
                if nums[i] > nums[pos_max] {
                    pos_max = i;
                }
            }
            nums.swap(len, pos_max);
            len -= 1;
        }
        nums
    }
    pub fn heap_sort(n: &Vec<i32>) -> Vec<i32> {
        let mut nums = n.clone();
        let len = nums.len();
        if len <= 1 {
            return nums;
        }
        macro_rules! parent {
            ($child:ident) => {
                $child >> 1
            };
        }
        macro_rules! left_child {
            ($child:ident) => {
                ($child << 1) + 1
            };
        }
        macro_rules! right_child {
            ($child:ident) => {
                ($child + 1) << 1
            };
        }

        fn move_down(nums: &mut [i32], mut parent: usize) {
            let last = nums.len() - 1;
            loop {
                let left = left_child!(parent);
                let right = right_child!(parent);
                if left > last {
                    break;
                }
                let child = if right <= last && nums[left] < nums[right] {
                    right
                } else {
                    left
                };
                if nums[child] > nums[parent] {
                    nums.swap(parent, child);
                }
                parent = child;
            }
        }
        let last_parent = parent!(len);
        for i in (0..=last_parent).rev() {
            move_down(&mut nums, i);
        }
        for end in (1..nums.len()).rev() {
            nums.swap(0, end);
            move_down(&mut nums[..end], 0);
        }
        nums
    }

    pub fn insertion_sort(n: &Vec<i32>) -> Vec<i32> {
        let mut nums = n.clone();
        for i in 1..nums.len() {
            let mut pos = i;
            let curr = nums[i];
            while pos > 0 && nums[pos - 1] > curr {
                nums[pos] = nums[pos - 1];
                pos -= 1;
            }
            nums[pos] = curr;
        }
        nums
    }

    pub fn shell_sort(n: &Vec<i32>) -> Vec<i32> {
        let mut nums = n.clone();
        fn in_sort(nums: &mut [i32], start: usize, gap: usize) {
            let mut i = start + gap;
            while nums.len() > i {
                let mut pos = i;
                let curr = nums[pos];
                while pos >= gap && curr < nums[pos - gap] {
                    nums[pos] = nums[pos - gap];
                    pos = pos - gap;
                }
                nums[pos] = curr;
                i += gap;
            }
        }
        let mut gap = nums.len() / 2;
        while gap > 0 {
            for start in 0..gap {
                in_sort(&mut nums, start, gap)
            }
            gap /= 2;
        }
        nums
    }
    pub fn merge_sort(n: &mut [i32]) -> Vec<i32> {
        fn merge(nums: &mut [i32], mid: usize) {
            let mut i = 0;
            let mut k = mid;
            let mut temp = Vec::new();
            for j in 0..nums.len() {
                if k == nums.len() || i == mid {
                    break;
                }
                if nums[i] < nums[k] {
                    temp.push(nums[i]);
                    i += 1;
                } else {
                    temp.push(nums[k]);
                    k += 1;
                }
            }
            if i < mid && k == nums.len() {
                for j in i..mid {
                    temp.push(nums[j]);
                }
            } else if i == mid && k < nums.len() {
                for j in k..nums.len() {
                    temp.push(nums[j]);
                }
            }
            for j in 0..nums.len() {
                nums[j] = temp[j];
            }
        }
        let mut nums = n;
        if nums.len() > 1 {
            let mid = nums.len() >> 1;
            merge_sort(&mut nums[..mid]);
            merge_sort(&mut nums[mid..]);
            merge(&mut nums, mid);
        }

        nums.to_vec()
    }
    pub fn counting_sort(n: &Vec<i32>) -> Vec<i32> {
        let mut nums = n.clone();
        if nums.len() <= 1 {
            return nums;
        }
        let max_num = nums.iter().max().unwrap() + 1;
        let mut counter = vec![0; max_num as usize];
        for &v in nums.iter() {
            counter[v as usize] += 1;
        }
        let mut j = 0;
        for i in 0..max_num {
            while counter[i as usize] > 0 {
                nums[j] = i;
                counter[i as usize] -= 1;
                j += 1;
            }
        }
        nums
    }
    pub fn radix_sort(n: &Vec<i32>) -> Vec<i32> {
        let mut nums = n.clone();
        if nums.len() <= 1 {
            return nums;
        }
        let max_num = match nums.iter().max() {
            Some(&r) => r,
            None => nums[0],
        };
        let radix = nums.len().next_power_of_two();
        let mut digit = 1;
        while digit <= max_num {
            let index_of = |x: i32| (x / digit) as usize % radix;
            let mut counter = vec![0; radix];
            for &x in nums.iter() {
                counter[index_of(x)] += 1;
            }
            for i in 1..radix {
                counter[i] += counter[i - 1];
            }
            for &x in nums.to_owned().iter().rev() {
                counter[index_of(x)] -= 1;
                nums[counter[index_of(x)]] = x;
            }
            digit *= radix as i32;
        }
        nums
    }
}

#[allow(warnings)]
#[cfg(test)]
mod test {
    use crate::sort_algorithms::*;
    use crate::sort_algorithms_v2::*;
    #[test]
    fn test_merge_sort_v2() {
        let left = vec![1, 3, 6];
        let right = vec![2, 4, 5, 1];

        println!("{:?}", merge_sort_v2(merge(&left, &right)));
        println!("{:?}", merge(&left, &right));
    }
    #[test]

    fn test_bubble_sort() {
        let v1 = vec![12, 13, 10];
        assert_eq!(bubble_sort(&v1), vec![10, 12, 13]);
    }
    #[test]
    fn test_quick_sort() {
        let v1 = vec![12, 13, 10];
        assert_eq!(quick_sort(&v1, 0, v1.len() - 1), vec![10, 12, 13]);
    }
    #[test]
    fn test_heap_sort() {
        let v1 = vec![12, 13, 10];
        assert_eq!(heap_sort(&v1), vec![10, 12, 13]);
    }
    #[test]
    fn test_selection_sort() {
        let v1 = vec![12, 13, 10];
        assert_eq!(selection_sort(&v1), vec![10, 12, 13]);
    }
    #[test]
    fn test_insertion_sort() {
        let v1 = vec![12, 13, 10];
        assert_eq!(insertion_sort(&v1), vec![10, 12, 13]);
    }
    #[test]
    fn test_shell_sort() {
        let v1 = vec![12, 13, 10];
        assert_eq!(shell_sort(&v1), vec![10, 12, 13]);
    }
    #[test]
    fn test_merge_sort() {
        let mut v1 = [12, 13, 10];
        assert_eq!(merge_sort(&mut v1), vec![10, 12, 13]);
    }
    #[test]
    fn test_counting_sort() {
        let mut v1 = vec![12, 13, 10];
        assert_eq!(counting_sort(&v1), vec![10, 12, 13]);
    }
}
