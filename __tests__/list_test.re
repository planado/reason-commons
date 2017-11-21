open Jest;

open Expect;

test(
  "list bind should work",
  () =>
    ListRe.Monad.(expect([1, 2, 3] >>= [@bs] ((x) => [x, x + 1])) |> toEqual([1, 2, 2, 3, 3, 4]))
);
