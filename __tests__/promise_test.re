open Jest;

open Expect;

[%%bs.raw {|
  jest.setTimeout(500);
|}];

testAsync(
  "resolve should return a resolved promise",
  (done_) =>
    Promise.resolve(5)
    |> Promise.finally(
         (_) => fail("Should not go reject path") |> ignore,
         (x) => done_(expect(x) |> toBe(5))
       )
);

testAsync(
  "should map resolved promise value",
  (done_) =>
    Promise.resolve(5)
    |> Promise.map((x) => x + 4)
    |> Promise.finally(ignore, (x) => done_(expect(x) |> toBe(9)))
);

testAsync(
  "bind promises",
  (done_) =>
    Promise.(
      resolve(5)
      >>= ((x) => resolve({j|$x test|j}))
      |> map((x) => done_(expect(x) |> toBe("5 test")))
    )
    |> ignore
);

/* describe( */
/*   "awaiting all promises", */
/*   () => { */
/*     open Promise; */
/*     let p1 = resolve(1); */
/*     let p2 = resolve(2); */
/*     beforeEach(() => p1 := make((res, _) => Js.Global.setTimeout(10, () => res(3)))); */
/*     testAsync( */
/*       "await all passed promises", */
/*       (done_) => */
/*         Promise.( */
/*           resolve(5) */
/*           >>= ((x) => resolve({j|$x test|j})) */
/*           |> map((x) => done_(expect(x) |> toBe("5 test"))) */
/*         ) */
/*         |> ignore */
/*     ) */
/*   } */
/* ); */
