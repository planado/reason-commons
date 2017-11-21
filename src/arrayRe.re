include Js.Array;

type concat;

type context('a) = t('a);

[@bs.get] external _concat : t('a) => concat = "concat";

[@bs.send] external _applyConcat : (concat, context('a), t(t('a))) => t('a) = "apply";

let flatMap = (a: t(t('a))) : t('a) => _applyConcat(_concat([||]), [||], a);

module Functor = {
  let map = Js.Array.map;
};

module Monad = {
  let bind = (m: t('a), f: 'a => t('b)) : t('b) => flatMap(map(f, m))
                                          ;
  let (>>=) = bind;
};

include Monad;
