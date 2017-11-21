include Js.Array;

module Functor = {
  let map = Js.Array.map;
};

module Monad = {
  let bind = (f: 'a => t('b), m: t('a)) : t('b) => concatMany(map(f, m));
  let (>>=) = bind;
};

include Monad;
