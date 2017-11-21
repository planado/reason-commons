open Jest;

open Expect;

test(
  "array bind should work",
  () =>
    ArrayRe.Monad.(expect([|1, 2, 3|] >>= ((x) => [|x, x + 1|])) |> toEqual([|1, 2, 2, 3, 3, 4|]))
);
