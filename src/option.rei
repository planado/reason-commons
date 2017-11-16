type t('a) = option('a);

let some: 'a => option('a);

let may: ('a => unit, option('a)) => unit;

let map: ('a => 'b, option('a)) => option('b);

let bind: (option('a), 'a => option('b)) => option('b);
let (>>=): (option('a), 'a => option('b)) => option('b);

let apply: (option(('a => 'a)), 'a) => 'a;

let filter: ('a => bool, option('a)) => option('a);

let default: ('a, option('a)) => 'a;

let default_delayed: (unit => 'a, option('a)) => 'a;

let map_default: ('a => 'b, 'b, option('a)) => 'b;

let map_default_delayed: ('a => 'b, unit => 'b, option('a)) => 'b;

let is_none: option('a) => bool;

let is_some: option('a) => bool;

let get: option('a) => 'a;

let get_exn: (option('a), exn) => 'a;

let both: (t('a), t('b)) => t(('a, 'b));
