use std::env;

struct LwzDict {
    words: Vec<String>
}

impl LwzDict {
    pub fn add_chain(&mut self, s: &str) {
        if s.len() < 1 {
            return;
        }

        let next = match self.find(s) {
            Some(c) => {
                self.words.push(
                    format!("{}{}", c, s)
                );
                s[c.len()..s.len()]
            },
            None => {
                self.words.push(s[0..1].to_string());
                s[1..s.len()]
            }
        };

        self.add_chain(&next);
    }

    fn find(&self, s: &str) -> Option<String> {
        for word in self.words {
            if(word == s) {
                Some(word.clone())
            }
        }
        None
    }
}

impl From<String> for LwzDict {
    fn from(from: String) -> Self {

    }
}

fn main() {
    let sentence = env::args().nth(1).unwrap();


}
