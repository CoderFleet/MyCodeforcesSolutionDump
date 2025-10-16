use std::io::{self, Read};

fn main() {
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut it = s.split_whitespace();
    let n: usize = it.next().unwrap().parse().unwrap();
    let x: usize = it.next().unwrap().parse().unwrap();
    let coins: Vec<usize> = (0..n).map(|_| it.next().unwrap().parse().unwrap()).collect();

    const MOD: i64 = 1_000_000_007;
    let mut dp = vec![0i64; x + 1];
    dp[0] = 1;

    for sum in 1..=x {
        for &c in &coins {
            if c <= sum {
                dp[sum] += dp[sum - c];
                if dp[sum] >= MOD { dp[sum] -= MOD; }
            }
        }
    }

    println!("{}", dp[x] % MOD);
}
