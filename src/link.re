let handleClick = route => ReasonReact.Router.push(route);

let component = ReasonReact.statelessComponent("Link");

let make = (~route, ~label, _children) => {
  ...component,
  render: _self =>
    <a onClick=(_event => handleClick(route))>
      (ReasonReact.stringToElement(label))
    </a>
};