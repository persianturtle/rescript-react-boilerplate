[@bs.module "react-transition-group"]
external cssTransition : ReasonReact.reactClass = "CSSTransition";

[@bs.module "react-transition-group"]
external transitionGroup : ReasonReact.reactClass = "TransitionGroup";

module CSSTransition = {
  let make = (~show: bool, ~timeout: int, ~classNames: string, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=cssTransition,
      ~props={"in": show, "timeout": timeout, "classNames": classNames},
      children,
    );
};

module TransitionGroup = {
  let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=transitionGroup,
      ~props={"component": Js.null},
      children,
    );
};