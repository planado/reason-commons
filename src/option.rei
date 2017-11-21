type t('a) = option('a);

let some: 'a => t('a);

let may: ('a => unit, t('a)) => unit;

let map: ('a => 'b, t('a)) => t('b);

let bind: (t('a), 'a => t('b)) => t('b);

let (>>=): (t('a), 'a => t('b)) => t('b);

let apply: (t(('a => 'a)), 'a) => 'a;

let filter: ('a => bool, t('a)) => t('a);

let default: ('a, t('a)) => 'a;

let defaultDelayed: (unit => 'a, t('a)) => 'a;

let mapDefault: ('a => 'b, 'b, t('a)) => 'b;

let mapDefaultDelayed: ('a => 'b, unit => 'b, t('a)) => 'b;

let isNone: t('a) => bool;

let isSome: t('a) => bool;

let get: t('a) => 'a;

let getExn: (t('a), exn) => 'a;

let both: (t('a), t('b)) => t(('a, 'b));

module Functor: {let map: ('a => 'b, t('a)) => t('b);};


module Monad: {
  let pure: 'a => t('a);
  let bind: (t('a), 'a => t('b)) => t('b);
  let (>>=): (t('a), 'a => t('b)) => t('b);
};
