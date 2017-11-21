include Js.List;

module Functor = {
  let map = Js.List.map;
};

module Monad = {
  let bind = (m: t('a), f: [@bs] 'a => t('b)) : t('b) => flatten(map(f, m));
  let (>>=) = bind;
};

include Monad;
