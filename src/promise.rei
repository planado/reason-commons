type t('a, 'err);

/* Create a resolved promise */
let resolve: 'a => t('a, 'x);

/* Create a rejected Promise */
let reject: 'x => t('a, 'x);

/* Turn a array of promises into a promise of a array */
let all: array(t('a, 'x)) => t('x, array('a));

let map: ('a => 'b, t('a, 'x)) => t('b, 'x);

let bind: (t('a, 'x), 'a => t('b, 'x)) => t('b, 'x);

let (>>=): (t('a, 'x), 'a => t('b, 'x)) => t('b, 'x);

/* map either the error or the value of a promise */
let bimap: ('a => 'b, 'x => 'y, t('a, 'x)) => t('b, 'y);

/* apply a function to a rejected promise */
let mapError: ('x => 'y, t('a, 'x)) => t('a, 'y);

/* Similar to mapError but returns a resolved promise */
let catch: ('x => 'a, t('a, 'x)) => t('a, 'x);

/* Provide handlers for the error and result option of the promise. Use this as the last step in a promise chain. */
let finally: ('a => unit, 'x => unit, t('a, 'x)) => unit;

/* Acts as both map and catch*/
let fold: ('a => 'b, 'x => 'b, t('a, 'x)) => t('b, 'x);

let fromOption: ('x, option('a)) => t('a, 'x);

let fromResult: Result.t('a, 'x) => t('a, 'x);

let fromJs: Js.Promise.t('a) => t('a, 'x);

let make: (('a => unit, 'x => unit) => unit) => t('a, 'x);

let race: array(t('a, 'x)) => t('a, 'x);

module Functor: {let map: ('a => 'b, t('a, 'c)) => t('b, 'c);};

module Monad: {
  let pure: 'a => t('a, 'c);
  let bind: (t('a, 'c), 'a => t('b, 'c)) => t('b, 'c);
  let (>>=): (t('a, 'c), 'a => t('b, 'c)) => t('b, 'c);
};
