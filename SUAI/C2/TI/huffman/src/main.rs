extern crate huffman;
use std::env;
mod splitter;

use std::fmt::{Debug,Formatter,Result};
use huffman::{HuffmanNode, HuffmanLeaf, HuffmanBranch};

fn main() {
    if env::args().count() != 3  {
        println!("Usage: {} \"[sentence]\" [n]", env::args().nth(0).unwrap());
        return;
    }

    let sentence = env::args().nth(1).unwrap();
    let n        = env::args().nth(2).unwrap().parse::<usize>().unwrap();

    let mut uniques = splitter::split_uniques(sentence, n);
    uniques.sort_by(|a, b| {
        a.f.cmp(&b.f).reverse()
    });

    let mut v = Vec::new();
    for u in &uniques {
        v.push(
            HuffmanLeaf::new(
                u.s.clone(),
                u.f as u32
            )
        )
    }

    let t = huffman::code(v).unwrap();
    let info = to_list(&t);

    for u in &uniques {
        println!("{}: {}", u.s, bits2string(&info.iter().find(|&l| l.leaf.item == u.s).unwrap().bits));
    }
}

fn bits2string(bits: &Vec<bool>) -> String {
    let mut s = String::new();
    for bit in bits {
        s.push(
            match bit {
                &true  => '1',
                &false => '0'
            }
        );
    }

    return s;
}

struct LeafInfo<'a, T> where T: 'a {
    leaf: &'a HuffmanLeaf<T>,
    bits: Vec<bool>
}

impl<'a, T> Debug for LeafInfo<'a, T> where T: Debug {
    fn fmt(&self, f: &mut Formatter) -> Result {
        let mut bits = String::new();
        for &b in self.bits.iter() {
            bits.push(if b {'1'} else {'0'});
        }

        write!(f, "{}: {:?}", bits, self.leaf)
    }
}

fn to_list<'a, T>(tree: &'a HuffmanBranch<T>) -> Vec<LeafInfo<'a, T>> {
    let mut result: Vec<LeafInfo<T>> = Vec::new();
    to_list_inner_branch(tree, Vec::new(), &mut result);
    result
}



fn to_list_inner_leaf<'a, T>(leaf: &'a HuffmanLeaf<T>, bits: Vec<bool>, result: & mut Vec<LeafInfo<'a, T>>) {
    result.push(LeafInfo { leaf: leaf, bits: bits });
}

fn to_list_inner_branch<'a, T>(tree: &'a HuffmanBranch<T>, bits: Vec<bool>, result: & mut Vec<LeafInfo<'a, T>>) {


    let mut left_bits = bits.clone();
    left_bits.push(false);

    match *tree.left {
        HuffmanNode::HuffmanLeaf(ref l) => to_list_inner_leaf(l, left_bits, result),
        HuffmanNode::HuffmanBranch(ref b) => to_list_inner_branch(b, left_bits, result),
    };


    let mut right_bits = bits.clone();
    right_bits.push(true);

    match *tree.right {
        HuffmanNode::HuffmanLeaf(ref l) => to_list_inner_leaf(l, right_bits, result),
        HuffmanNode::HuffmanBranch(ref b) => to_list_inner_branch(b, right_bits, result),
    };

}
