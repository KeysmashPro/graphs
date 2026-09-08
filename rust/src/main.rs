use std::cmp;
use std::io;

fn find_scc(graph : &Vec<Vec<u32>>, scc : &mut Vec<u32>, off : &mut Vec<usize>) {
    let n = graph.len();
    let mut enter : Vec<u32> = vec![0; n];
    let mut exit : Vec<u32> = vec![0; n];
    let mut stk : Vec<u32> = Vec::with_capacity(n);
    let mut on_stk : Vec<bool> = vec![false; n];
    let mut counter : u32 = 1;
    
    let mut frames : Vec<(usize, usize)> = Vec::new();
    let mut cc : usize = 0;

    for start in 0..n {
        if enter[start] != 0 { continue; } frames.push((start, 0)); (enter[start], exit[start]) = (counter, counter); counter += 1; stk.push(start as u32); on_stk[start] = true;

        while !frames.is_empty() {
            let frame = frames.last_mut().unwrap();
            let v = frame.0;
            let neighbor = frame.1;

            if neighbor < graph[v].len() {
                let to = graph[v][neighbor] as usize;
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
                    off.push(cc);
                    loop {
                        let s = stk.pop().unwrap() as usize;
                        on_stk[s] = false;
                        scc[cc] = s as u32;
                        cc += 1;
                        if s == v { break; }
                    }
                }

                frames.pop();

                if !frames.is_empty() {
                    let parent = frames.last().unwrap().0;
                    exit[parent] = cmp::min(exit[parent], exit[v]);
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
    let cost : Vec<u32> = input
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
        let mut it = input.split_whitespace();
        let src : usize = it.next().unwrap().parse().unwrap();
        let sin : u32 = it.next().unwrap().parse().unwrap();
        graph[src - 1].push(sin - 1); 
    }

    // Vars
    let mut scc : Vec<u32> = vec![0; n];
    let mut off : Vec<usize> = Vec::with_capacity(n);
    find_scc(&graph, &mut scc, &mut off);

    let mut total_ways : u64 = 1;
    let mut total_cost : u64 = 0;

    let mut start;
    let mut end = n;
    for i in (0..off.len()).rev() {
        let mut min_cost : u32 = u32::MAX;
        let mut count : u64 = 0;
        start = off[i];
        for j in (start..end).rev() {
            if cost[scc[j] as usize] < min_cost {
                min_cost = cost[scc[j] as usize];
                count = 1;
            } else if cost[scc[j] as usize] == min_cost {
                count += 1;
            }
        }
        total_cost += min_cost as u64;
        total_ways = (total_ways * count) % 1_000_000_007;
        end = start;
    }

    println!("{} {}", total_cost, total_ways);
}
