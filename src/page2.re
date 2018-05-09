let component = ReasonReact.statelessComponent("Page2");

let make = _children => {
  ...component,
  render: _self =>
    <div className="Page2">
      <h1> (ReasonReact.string("Page2")) </h1>
    </div>
};