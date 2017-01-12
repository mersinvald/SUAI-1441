use std::cmp::{Ord, PartialOrd, PartialEq, Ordering};
use std::fmt::{Display, Debug, Formatter, Result};

pub fn split(source: String, n: usize) -> Vec<String> {
    let len = source.chars().count() - (n - 1);
    let mut all = Vec::with_capacity(len);

    for i in 0..len {
        let mut unit = String::with_capacity(n);
        for ui in 0..n {
            unit.push(source.chars().nth(i+ui).unwrap());
        }

        all.push(unit);
    }

    return all;
}

pub struct Unit {
    pub s: String,
    pub f: usize
}

impl Display for Unit {
    fn fmt(&self, f: &mut Formatter) -> Result {
        write!(f, "{}: {}", self.s, self.f)
    }
}

impl Debug for Unit {
    fn fmt(&self, f: &mut Formatter) -> Result {
        write!(f, "{}: {}", self.s, self.f)
    }
}

impl Ord for Unit {
    fn cmp(&self, other: &Self) -> Ordering {
        self.f.cmp(&other.f).reverse()
    }
}

impl PartialOrd for Unit {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl PartialEq for Unit {
    fn eq(&self, other: &Self) -> bool {
        self.f == other.f
    }
}

impl Eq for Unit {}

pub fn split_uniques(source: String, n: usize) -> Vec<Unit> {
    use std::cmp::Ordering::Equal;

    let mut result : Vec<Unit> = Vec::with_capacity(source.len());
    let words = split(source, n);

'sloop:
    for w in words {
        for wr in &mut result {
            if w.cmp(&wr.s) == Equal {
                wr.f += 1;
                continue 'sloop;
            }
        }

        result.push(
            Unit {
                s: w,
                f: 1
            }
        );
    }

    println!("{:?}", result);

    return result;
}
