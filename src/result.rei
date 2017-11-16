type t('a, 'b) =
  | Ok('a)
  | Error('b);

let catch: ('a => 'b, 'a) => t('b, exn);

let catch2: (('a, 'b) => 'c, 'a, 'b) => t('c, exn);

let catch3: (('a, 'b, 'c) => 'd, 'a, 'b, 'c) => t('d, exn);

let get: t('a, exn) => 'a;

let default: ('a, t('a, _)) => 'a;

let map: ('a => 'b, t('a, 'c)) => t('b, 'c);

let map_both: ('a1 => 'a2, 'b1 => 'b2, t('a1, 'b1)) => t('a2, 'b2);

let map_default: ('b, 'a => 'b, t('a, _)) => 'b;

let is_ok: t('a, 'b) => bool;

let is_bad: t('a, 'b) => bool;

let is_exn: (exn, t('a, exn)) => bool;

let of_option: option('a) => t('a, unit);

let to_option: t('a, _) => option('a);

let bind: (t('a, 'b), 'a => t('c, 'b)) => t('c, 'b);

let (>>=): (t('a, 'b), 'a => t('c, 'b)) => t('c, 'b);
