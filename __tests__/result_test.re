open Jest;

open Expect;


testAsync(
  "re",
  (done_) =>
    Result.(
      toOption(Ok(Some(5)))
      |> Option.ofNativeOption
      |> Option.may((_) => done_(expect(true) |> toBe(true)) |> ignore)
    )
);
