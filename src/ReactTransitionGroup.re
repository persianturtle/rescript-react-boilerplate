[@bs.val] external require : string => string = "";
require("../../../src/ReactTransitionGroup.scss");

[@bs.module "react-transition-group"]
external transitionGroup : ReasonReact.reactClass = "TransitionGroup";

[@bs.module "react-transition-group"]
external cssTransition : ReasonReact.reactClass = "CSSTransition";

module TransitionGroup = {
  let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=transitionGroup,
      ~props=Js.Obj.empty(),
      children,
    );
};

[@bs.deriving abstract]
type cssTransitionProps = {
  [@bs.as "in"]
  _in: bool,
  timeout: int,
  classNames: string,
};

module CSSTransition = {
  let make = (~_in: bool, ~timeout: int, ~classNames: string, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=cssTransition,
      ~props=cssTransitionProps(~_in, ~timeout, ~classNames),
      children,
    );
};
