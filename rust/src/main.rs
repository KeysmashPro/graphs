use std::io;

fn find_scc() {
    let mut enter : Vec<u32> = vec![0; n];
    let mut exit : Vec<u32> = vec![0; n];
    let mut cc : u32 = 0;
    let mut stk : Vec<u32> = Vec::with_capacity(n);
    let mut on_stk : Vec<bool> = vec![false, n];
    let mut counter : u32 = 1;
    
    let mut frames : Vec<(u32, u32)> = Vec::new();

    for (start, s_val) in enter {
        if s_val == 0 continue;
        frames.push((start, 0));

        (enter[start], exit[start]) = (counter, counter);
        counter += 1;
        stk.push(start);
        on_stk[start] = true;

        while !stk.empty() {
            let &mut (v, neighbor) = frames.back();
            if neighbor < graph[v].size() {
                let to = graph[v][neighbor];
                neighbor += 1;

                if enter[to] != 0 {
                    (enter[to], exit[to]) = (counter, counter);
                    counter += 1;
                    stak.push(to);
                    on_stk[to] = true;
                } else if on_stk[v] {
                    exit[v] = min(exit[v], exit[to]);
                }
            } else {
                if (enter[v] == exit[v]) {
                    off.push(cc);
                    loop {
                        let s = stk.back();
                        stak.pop();
                        on_stk[s] = false;
                        scc[cc] = s;
                        cc += 1;
                        if s == v break;
                    }
                }

                frames.pop();
                on_stk[v] = 0;

                if !stak.is_empty() {
                    let (parent, _) = frames.back();
                    exit[parent] = min(exit[parent], exit[v]);
                }
            }
        }
    }
}

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
            (   it.next().unwrap().parse().unwrap();
                it.next().unwrap().parse().unwrap();    )

        };
        graph[src - 1].push(sin - 1); 
    }

    // Vars
    let mut scc : Vec<u32> = vec![0; n];
    let mut off : Vec<u32> = Vec::with_capacity(n);

    find_scc();

    }

    let mut res : u32 = 0;
    println!("{res}");
}
