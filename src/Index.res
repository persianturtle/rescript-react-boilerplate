@val external require: string => string = "require"

require("../../../src/Index.scss")->ignore

switch ReactDOM.querySelector("#root") {
| Some(root) => ReactDOM.render(<App />, root)
| None => () // do nothing
}
