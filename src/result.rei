type t('a, 'b) =
  | Ok('a)
  | Error('b);

let catch: ('a => 'b, 'a) => t('b, exn);

let catch2: (('a, 'b) => 'c, 'a, 'b) => t('c, exn);

let catch3: (('a, 'b, 'c) => 'd, 'a, 'b, 'c) => t('d, exn);

let getExn: t('a, exn) => 'a;

let default: ('a, t('a, _)) => 'a;

let map: ('a => 'b, t('a, 'c)) => t('b, 'c);

let bimap: ('a1 => 'a2, 'b1 => 'b2, t('a1, 'b1)) => t('a2, 'b2);

let mapDefault: ('b, 'a => 'b, t('a, _)) => 'b;

let isOk: t('a, 'b) => bool;

let isBad: t('a, 'b) => bool;

let isExn: (exn, t('a, exn)) => bool;

let ofOption: option('a) => t('a, unit);

let toOption: t('a, _) => option('a);

let bind: (t('a, 'b), 'a => t('c, 'b)) => t('c, 'b);

let (>>=): (t('a, 'b), 'a => t('c, 'b)) => t('c, 'b);

module Functor: {let map: ('a => 'b, t('a, 'c)) => t('b, 'c);};

module Monad: {
  let pure: 'a => t('a, 'c);
  let bind: (t('a, 'c), 'a => t('b, 'c)) => t('b, 'c);
  let (>>=): (t('a, 'c), 'a => t('b, 'c)) => t('b, 'c);
};
