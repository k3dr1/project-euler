fn main() {
    let concatenated_prod = |a: i32, upper: i32| 
        (1..=upper).map(|m| (a*m).to_string()).fold(String::new(), |acc, x| format!("{acc}{x}"));
    let is_pandigital = |s: String|
        s.len() == 9 &&
        (1..=9).map(|e| e.to_string()).map(|e| s.contains(&e)).fold(true, |a,b| a&&b);

    let res = (2..=9).map(|n| (1..=1_000_00)
        .map(|a| concatenated_prod(a, n))
        .filter(|c| c.len() <= 9)
        .filter(|c| is_pandigital(c.to_string()))
        .map(|c| c.parse::<i64>().unwrap_or(0))
        .fold(0, |l,r| l.max(r))
    ).fold(0, |l,r| l.max(r));

    println!("Result {}", res);
}
