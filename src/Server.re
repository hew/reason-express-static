open Express;

let app = express();

let onListen = (port, e) =>
  switch e {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1)
  | _ => Js.log @@ "Listening at http://127.0.0.1:" ++ string_of_int(port)
  };

App.useOnPath(
  app,
  ~path="/",
  {
    let options = Static.defaultOptions();
    Static.make("public", options) |> Static.asMiddleware
    }
);

[@bs.module "body-parser"] external bodyParserJson : unit => Express.Middleware.t = "json";

App.use(app, bodyParserJson());

App.listen(app, ~onListen=onListen(3000), ());
