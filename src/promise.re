type t('err, 'a);

[@bs.new] external _new : (('a => unit, 'x => unit) => unit) => t('x, 'a) = "Promise";

[@bs.send] external _map : (t('x, 'a), 'a => 'b) => t('x, 'b) = "then";

[@bs.send] external _bind : (t('x, 'a), 'a => t('x, 'b)) => t('x, 'b) = "then";

[@bs.send] external _fold : (t('x, 'a), 'a => 'b, 'x => 'b) => t('x, 'b) = "then";

[@bs.send] external _then : (t('x, 'a), 'a => 'b, 'x => t('y, 'b)) => t('y, 'b) = "then";

[@bs.send] external _finally : (t('x, 'a), 'a => unit, 'x => unit) => unit = "then";

[@bs.send] external _catch : (t('x, 'a), 'x => t('y, 'b)) => t('x, 'a) = "catch";

[@bs.val] [@bs.scope "Promise"] external resolve : 'a => t('x, 'a) = "resolve";

[@bs.val] [@bs.scope "Promise"] external reject : 'err => t('err, 'a) = "reject";

[@bs.val] [@bs.scope "Promise"] external all : list(t('err, 'a)) => t('err, list('a)) = "all";

[@bs.send] external _fromjs : (Js.Promise.t('a), 'a => 'a) => t('x, 'a) = "then";

let map = (f, p) => _map(p, f);

let bind = (f, p) => _bind(p, f);

let (>>=) = _bind;

let catch = (f, p) => _catch(p, (x) => resolve(f(x)));

let biMap = (fail, success, p) => _then(p, success, (err) => reject(fail(err)));

let mapError = (f, p) => _then(p, (x) => x, (err) => reject(f(err)));

let finally = (f, g, p) => _finally(p, g, f) |> ignore;

let fold = (f, g, p) => _fold(p, g, f);

let fromOption = (err, opt) =>
  switch opt {
  | Some(a) => resolve(a)
  | None => reject(err)
  };

let fromResult = (opt) =>
  Result.(
    switch opt {
    | Ok(x) => resolve(x)
    | Error(err) => reject(err)
    }
  );

let fromJs = (p) => _fromjs(p, (x) => x);

let make = (f) => _new((resolve, reject) => f(reject, resolve));
