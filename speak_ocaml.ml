let do_speak () =
  print_endline "This called from OCaml!!";
  flush stdout

let () =
  Callback.register "speak" do_speak
