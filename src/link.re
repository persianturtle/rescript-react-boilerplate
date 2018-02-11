let handleClick = href => ReasonReact.Router.push(href);

let component = ReasonReact.statelessComponent("Link");

let make = (~href, ~label, _children) => {
  ...component,
  render: _self =>
    <a onClick=(_event => handleClick(href))>
      (ReasonReact.stringToElement(label))
    </a>
};