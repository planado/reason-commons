type t('a, 'err);

[@bs.new] external _new : (('a => unit, 'x => unit) => unit) => t('a, 'x) = "Promise";

[@bs.send] external _map : (t('a, 'x), 'a => 'b) => t('b, 'x) = "then";

[@bs.send] external _bind : (t('a, 'x), 'a => t('b, 'x)) => t('b, 'x) = "then";

[@bs.send] external _fold : (t('a, 'x), 'a => 'b, 'x => 'b) => t('b, 'x) = "then";

[@bs.send] external _then : (t('a, 'x), 'a => 'b, 'x => t('b, 'y)) => t('b, 'y) = "then";

[@bs.send] external _finally : (t('a, 'x), 'a => unit, 'x => unit) => unit = "then";

[@bs.send] external _catch : (t('a, 'x), 'x => t('b, 'y)) => t('a, 'x) = "catch";

[@bs.val] [@bs.scope "Promise"] external resolve : 'a => t('a, 'x) = "resolve";

[@bs.val] [@bs.scope "Promise"] external reject : 'x => t('a, 'x) = "reject";

[@bs.val] [@bs.scope "Promise"] external all : array(t('a, 'x)) => t('x, array('a)) = "all";

[@bs.val] [@bs.scope "Promise"] external race : array(t('a, 'x)) => t('a, 'x) = "race";

[@bs.send] external _fromjs : (Js.Promise.t('a), 'a => 'a) => t('a, 'x) = "then";

[@bs.send] [@bs.scope "Promise"]
external bibind : (t('a, 'x), 'a => t('b, 'x), 'x => t('b, 'x)) => t('b, 'x) =
  "then";

module Functor = {
  let map = (f: 'a => 'b, p: t('a, 'x)) : t('b, 'x) => _map(p, f);
};

include Functor;

module Monad = {
  let pure = (x) => resolve(x);
  let bind = (p: t('a, 'x), f: 'a => t('b, 'x)) : t('b, 'x) => _bind(p, f);
  let (>>=) = _bind;
};

include Monad;

let bimap = (success: 'a => 'b, fail: 'x => 'y, p: t('a, 'x)) : t('b, 'y) =>
  _then(p, success, (err) => reject(fail(err)));

let catch = (f: 'x => 'a, p: t('a, 'x)) : t('a, 'y) => _catch(p, (x) => resolve(f(x)));

let mapError = (f: 'x => 'y, p: t('a, 'x)) : t('a, 'y) =>
  _then(p, (x) => x, (err) => reject(f(err)));

let finally = (success: 'a => 'b, fail: 'x => 'y, p: t('a, 'x)) : unit =>
  _finally(p, success, fail) |> ignore;

let fold = (success: 'a => 'b, fail: 'x => 'b, p: t('a, 'x)) : t('b, 'x) =>
  _fold(p, success, fail);

let fromOption = (err: 'x, opt: option('a)) : t('a, 'x) =>
  switch opt {
  | Some(a) => resolve(a)
  | None => reject(err)
  };

let fromResult = (opt: Result.t('a, 'x)) : t('a, 'x) =>
  Result.(
    switch opt {
    | Ok(x) => resolve(x)
    | Error(err) => reject(err)
    }
  );

let fromJs = (p: Js.Promise.t('a)) : t('a, 'x) => _fromjs(p, (x) => x);

let make = (f: ('a => unit, 'x => unit) => unit) : t('a, 'x) => _new(f);
