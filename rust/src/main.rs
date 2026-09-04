use std::io;

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n = input.trim().parse().unwrap();

    // Cost
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let mut cost : Vec<u32> = input
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();

    // Graph
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let m = input.trim().parse().unwrap();
    let mut graph : Vec<Vec<u32>> = vec![Vec::new(); n];

    for _ in 0..m {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let (src, sin) = {
            let mut it = input.split_whitespace();
            (
                it.next().unwrap().parse().unwrap();
                it.next().unwrap().parse().unwrap();
            )

        };

        graph[src - 1].push(sin - 1); 
    }

    // Vars
    let mut enter : Vec<u32> = vec![0; n];
    let mut exit : Vec<u32> = vec![0; n];
    let mut scc : Vec<u32> = vec![0; n];
    let mut off : Vec<u32> = Vec::with_capacity(n);
    let mut stk : Vec<u32> = Vec::with_capacity(n);
    let mut on_stk : Vec<bool> = vec![false, n];
    let mut counter : u32 = 1;
    
    let mut frames : Vec<(u32, u32)> = Vec::new();

    for (start, s_val) in enter{
        if s_val == 0 continue;
        frames.push((start, 0));

        (enter[start], exit[start]) = (counter, counter);
        counter += 1;
        stk.push(start);
        on_stk[start] = true;

        while !stk.empty() {
            let &mut (v, neighbor) = frames.back();
        }
    }

    let mut res : u32 = 0;
    println!("{res}");
}
