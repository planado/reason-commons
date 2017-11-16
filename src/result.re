type t('a, 'b) =
  | Ok('a)
  | Error('b);

let catch = (f, x) =>
  try (Ok(f(x))) {
  | e => Error(e)
  };

let catch2 = (f, x, y) =>
  try (Ok(f(x, y))) {
  | e => Error(e)
  };

let catch3 = (f, x, y, z) =>
  try (Ok(f(x, y, z))) {
  | e => Error(e)
  };

let get =
  fun
  | Ok(x) => x
  | Error(e) => raise(e);

let default = (def) =>
  fun
  | Ok(x) => x
  | Error(_) => def;

let map = (f) =>
  fun
  | Error(e) => Error(e)
  | Ok(x) => Ok(f(x));

let map_both = (f, g) =>
  fun
  | Error(e) => Error(g(e))
  | Ok(x) => Ok(f(x));

let map_default = (def, f) =>
  fun
  | Ok(x) => f(x)
  | Error(_) => def;

let is_ok =
  fun
  | Ok(_) => true
  | Error(_) => false;

let is_bad =
  fun
  | Ok(_) => false
  | Error(_) => true;

let is_exn = (e) =>
  fun
  | Error(exn) => exn == e
  | Ok(_) => false;

let of_option =
  fun
  | Some(x) => Ok(x)
  | None => Error();

let to_option =
  fun
  | Ok(x) => Some(x)
  | Error(_) => None;

let bind = (v, f) =>
  switch v {
  | Ok(x) => f(x)
  | Error(_) as e => e
  };

let (>>=) = bind;
