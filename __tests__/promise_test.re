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
         (x) => done_(expect(x) |> toBe(5)),
         (_) => fail("Should not go reject path") |> ignore
       )
);

testAsync(
  "should map resolved promise value",
  (done_) =>
    Promise.resolve(5)
    |> Promise.map((x) => x + 4)
    |> Promise.finally((x) => done_(expect(x) |> toBe(9)), ignore)
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

describe(
  "awaiting all promises",
  () => {
    open Promise;
    let p1 = ref(resolve(1));
    let p2 = ref(resolve(2));
    beforeEach(
      () => {
        p1 := make((res, _) => Js.Global.setTimeout(() => res(3), 50) |> ignore);
        p2 := make((res, _) => Js.Global.setTimeout(() => res(4), 100) |> ignore)
      }
    );
    testAsync(
      "await all passed promises",
      (done_) => {
        let a = Array.of_list([p1^, p2^]);
        Promise.all(a)
        |> Promise.finally((x) => done_(expect(x) |> toEqual([|3, 4|])), (e) => Js.log(e))
        |> ignore
      }
    );
    testAsync(
      "first promise should win the race!",
      (done_) => {
        let a = Array.of_list([p1^, p2^]);
        Promise.race(a)
        |> Promise.finally((x) => done_(expect(x) |> toBe(3)), (e) => Js.log(e))
        |> ignore
      }
    )
  }
);

testAsync(
  "catch should return resolved promise",
  (done_) =>
    Promise.(
      reject(5) |> catch((x) => x + 10) |> finally((x) => done_(expect(x) |> toBe(15)), ignore)
    )
);
