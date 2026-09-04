use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();

    let nums: Vec<i32> = input
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    let (n, m) : (i32, i32) = (nums[0], nums[1]);

    


    println!("N - {n} \nM - {m} ");
}
