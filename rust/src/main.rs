use std::cmp;
use std::io;

fn mushrooms(mut v : u32) -> u32{
    let mut res : u32 = 0;
    let mut cnt = 1;
    while v > 0 {
        res += v;
        v -= cnt;
        cnt += 1;
    }
    return res;
}


fn find_scc(graph : &Vec<Vec<(u32, u32)>>, scc : &mut Vec<u32>) -> usize {
    let n = graph.len();
    let mut enter : Vec<u32> = vec![0; n];
    let mut exit : Vec<u32> = vec![0; n];
    let mut stk : Vec<u32> = Vec::with_capacity(n);
    let mut on_stk : Vec<bool> = vec![false; n];
    let mut counter : u32 = 1;
    
    let mut frames : Vec<(usize, usize)> = Vec::new();
    let mut cc : usize = 0; // scc index

    for start in 0..n {
        if enter[start] != 0 { continue; }
        frames.push((start, 0));
        (enter[start], exit[start]) = (counter, counter);
        counter += 1;
        stk.push(start as u32);
        on_stk[start] = true;

        while !frames.is_empty() {
            let frame = frames.last_mut().unwrap();
            let v = frame.0;
            let neighbor = frame.1;

            if neighbor < graph[v].len() {
                let to = graph[v][neighbor].0 as usize;
                frame.1 += 1;

                if enter[to] == 0 {
                    enter[to] = counter;
                    exit[to] = counter;
                    counter += 1;
                    stk.push(to as u32);
                    on_stk[to] = true;
                    frames.push((to, 0));
                } else if on_stk[to] {
                    exit[v] = cmp::min(exit[v], exit[to]);
                }
            } else {
                if enter[v] == exit[v] {
                    loop {
                        let s = stk.pop().unwrap() as usize;
                        on_stk[s] = false;
                        scc[s] = cc as u32;
                        if s == v { break; }
                    }
                    cc += 1;
                }

                frames.pop();
                if !frames.is_empty() {
                    let parent = frames.last().unwrap().0;
                    exit[parent] = cmp::min(exit[parent], exit[v]);
                }
            }
        }
    }
    return cc - 1;
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let nm : Vec<usize> = input
        .split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    input.clear();
    
    let (n, m) = (nm[0], nm[1]);

    // Graph
    let mut graph : Vec<Vec<(u32, u32)>> = vec![vec![]; n];
    for _ in 0..m {
        input.clear();
        io::stdin().read_line(&mut input).unwrap();
        let mut it = input.split_whitespace();
        let src : usize = it.next().unwrap().parse().unwrap();
        let sin : u32 = it.next().unwrap().parse().unwrap();
        let msh : u32 = it.next().unwrap().parse().unwrap();
        graph[src - 1].push((sin - 1, mushrooms(msh))); 
    }
    
    io::stdin().read_line(&mut input).unwrap();
    //let start : u32 = input.trim().parse().unwrap();

    // Strong Conection Components
    let mut scc : Vec<u32> = vec![0; n];
    let _scc_count = find_scc(&graph, &mut scc);

    let mut ccc : Vec<bool> = vec![false; n];
    let _mut_res : u64 = 0;


    /* From Theare */
    for isit in 0..n {
        if ccc[isit] { continue; }
        ccc[isit] = true;
    }
}

