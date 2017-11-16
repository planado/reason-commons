type t('a) = option('a);

let some = (x) => Some(x);

let may = (f) =>
  fun
  | None => ()
  | Some(x) => f(x);

let map = (f) =>
  fun
  | None => None
  | Some(x) => Some(f(x));

let bind = (m, f) =>
  switch m {
  | None => None
  | Some(x) => f(x)
  };

let (>>=) = bind;

let apply =
  fun
  | None => ((x) => x)
  | Some(f) => f;

let filter = (f) =>
  fun
  | Some(x) when f(x) => Some(x)
  | _ => None;

let default = (d) =>
  fun
  | None => d
  | Some(v) => v;

let default_delayed = (l) =>
  fun
  | None => l()
  | Some(x) => x;

let map_default = (f, d) =>
  fun
  | None => d
  | Some(x) => f(x);

let map_default_delayed = (f, l, v) =>
  switch v {
  | None => l()
  | Some(v) => f(v)
  };

let is_none =
  fun
  | None => true
  | _ => false;

let is_some =
  fun
  | None => false
  | _ => true;

let get_exn = (s, e) =>
  switch s {
  | None => raise(e)
  | Some(x) => x
  };

let get = (s) => get_exn(s, Invalid_argument("Option.get"));

let both = (v1, v2) =>
  switch (v1, v2) {
  | (_, None)
  | (None, _) => None
  | (Some(a), Some(b)) => Some((a, b))
  };
