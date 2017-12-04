type t('a, 'b) =
  | Ok('a)
  | Error('b);

let catch = (f: 'a => 'b, x: 'a) : t('b, exn) =>
  try (Ok(f(x))) {
  | e => Error(e)
  };

let catch2 = (f: ('a, 'b) => 'c, x: 'a, y: 'b) : t('c, exn) =>
  try (Ok(f(x, y))) {
  | e => Error(e)
  };

let catch3 = (f: ('a, 'b, 'c) => 'd, x: 'a, y: 'b, z: 'c) : t('d, exn) =>
  try (Ok(f(x, y, z))) {
  | e => Error(e)
  };

let getExn = (v: t('a, 'b)) : 'a =>
  switch v {
  | Ok(x) => x
  | Error(e) => raise(e)
  };

let default = (d: 'a, v: t('a, 'b)) : 'a =>
  switch v {
  | Ok(x) => x
  | Error(_) => d
  };

module Functor = {
  let map = (f: 'a => 'b, v: t('a, 'c)) : t('b, 'c) =>
    switch v {
    | Error(e) => Error(e)
    | Ok(x) => Ok(f(x))
    };
};

include Functor;

module Monad = {
  let pure = (x) => Ok(x);
  let bind = (v: t('a, 'c), f: 'a => t('b, 'c)) : t('b, 'c) =>
    switch v {
    | Ok(x) => f(x)
    | Error(_) as e => e
    };
  let (>>=) = bind;
};

include Monad;

let bimap = (f: 'a1 => 'a2, g: 'b1 => 'b2, v: t('a, 'b)) : t('a2, 'b2) =>
  switch v {
  | Error(e) => Error(g(e))
  | Ok(x) => Ok(f(x))
  };

let mapDefault = (d: 'b, f: 'a => 'b, v: t('a, 'c)) : 'b =>
  switch v {
  | Ok(x) => f(x)
  | Error(_) => d
  };

let isOk = (v: t('a, 'b)) : bool =>
  switch v {
  | Ok(_) => true
  | Error(_) => false
  };

let isBad = (v: t('a, 'b)) : bool =>
  switch v {
  | Ok(_) => false
  | Error(_) => true
  };

let isExn = (e: exn, v: t('a, 'b)) : bool =>
  switch v {
  | Error(exn) => exn == e
  | Ok(_) => false
  };

let ofOption = (v: option('a)) : t('a, unit) =>
  switch v {
  | Some(x) => Ok(x)
  | None => Error()
  };

let toOption = (v: t('a, 'b)) : option('a) =>
  switch v {
  | Ok(x) => Some(x)
  | Error(_) => None
  };
