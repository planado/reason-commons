type t('err, 'a);

/* Create a resolved promise */
let resolve: 'a => t('x, 'a);

/* Create a rejected Promise */
let reject: 'err => t('err, 'a);

/* Turn a list of promises into a promise of a list */
let all: list(t('err, 'a)) => t('err, list('a));

let map: ('a => 'b, t('x, 'a)) => t('x, 'b);

let bind: ('a => t('x, 'b), t('x, 'a)) => t('x, 'b);

let (>>=): (t('x, 'a), 'a => t('x, 'b)) => t('x, 'b);

/* map either the error or the value of a promise */
let biMap: ('x => 'y, 'a => 'b, t('x, 'a)) => t('y, 'b);

/* apply a function to a rejected promise */
let mapError: ('x => 'y, t('x, 'a)) => t('y, 'a);

/* Similar to mapError but returns a resolved promise */
let catch: ('x => 'a, t('x, 'a)) => t('x, 'a);

/* Provide handlers for the error and result option of the promise. Use this as the last step in a promise chain. */
let finally: ('x => unit, 'a => unit, t('x, 'a)) => unit;

/* Acts as both map and catch*/
let fold: ('x => 'b, 'a => 'b, t('x, 'a)) => t('x, 'b);

let fromOption: ('x, option('a)) => t('x, 'a);

let fromResult: Result.t('a, 'x) => t('x, 'a);

let fromJs: Js.Promise.t('a) => t('x, 'a);

let make: (('x => unit, 'a => unit) => unit) => t('x, 'a);

let race: list(t('a, 'b)) => t('c, 'd);
