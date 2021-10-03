module TransitionGroup = {
  @module("react-transition-group") @react.component
  external make: (~children: React.element) => React.element = "TransitionGroup"
}

module CSSTransition = {
  @module("react-transition-group") @react.component
  external make: (
    ~_in: bool,
    ~timeout: int,
    ~classNames: string,
    ~children: React.element,
  ) => React.element = "CSSTransition"
}
