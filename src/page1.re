let component = ReasonReact.statelessComponent("Page1");

let make = _children => {
  ...component,
  render: _self =>
    <div className="Page1">
      <h1> (ReasonReact.stringToElement("Page1")) </h1>
    </div>
};