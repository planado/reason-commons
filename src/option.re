type t('a) = option('a);

let some = (x: 'a) : t('a) => Some(x);

let may = (f: 'a => unit, v: t('a)) : unit =>
  switch v {
  | None => ()
  | Some(x) => f(x)
  };

module Functor = {
  let map = (f: 'a => 'b, v: t('a)) : t('b) =>
    switch v {
    | None => None
    | Some(x) => Some(f(x))
    };
};

include Functor;

module Monad = {
  let pure = some;
  let bind = (v: t('a), f: 'a => t('b)) : t('b) =>
    switch v {
    | Some(x) => f(x)
    | None => None
    };
  let (>>=) = bind;
};

include Monad;

let filter = (f: 'a => bool, v: t('a)) : t('a) =>
  switch v {
  | Some(x) when f(x) => Some(x)
  | _ => None
  };

let default = (d: 'a, v: t('a)) : 'a =>
  switch v {
  | None => d
  | Some(v) => v
  };

let defaultDelayed = (l: unit => 'a, v: t('a)) : 'a =>
  switch v {
  | None => l()
  | Some(x) => x
  };

let mapDefault = (f: 'a => 'b, d: 'b, v: t('a)) : 'b =>
  switch v {
  | None => d
  | Some(x) => f(x)
  };

let mapDefaultDelayed = (f: 'a => 'b, l: unit => 'b, v: t('a)) =>
  switch v {
  | None => l()
  | Some(v) => f(v)
  };

let isNone = (v: t('a)) : bool =>
  switch v {
  | None => true
  | _ => false
  };

let isSome = (v: t('a)) : bool =>
  switch v {
  | None => false
  | _ => true
  };

let getExn = (s: t('a), e: exn) : 'a =>
  switch s {
  | None => raise(e)
  | Some(x) => x
  };

let get = (s: t('a)) : 'a => getExn(s, Invalid_argument("Option.get"));

let both = (v1: t('a), v2: t('b)) : t('c) =>
  switch (v1, v2) {
  | (_, None)
  | (None, _) => None
  | (Some(a), Some(b)) => Some((a, b))
  };
