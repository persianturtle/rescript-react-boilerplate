[@bs.val] [@bs.scope "performance"] external now: unit => float = "now";
[@bs.val]
external addEventListener: (string, unit => unit) => unit = "addEventListener";
[@bs.val]
external removeEventListener: (string, unit => unit) => unit =
  "removeEventListener";

type touches = {
  first: option((float, float)),
  last: option((float, float)),
};

type state = {
  isOpen: bool,
  touches,
};

type action =
  | ToggleMenu(bool)
  | TouchStart(float)
  | TouchMove(float)
  | TouchEnd;

[@react.component]
let make = (~currentRoute: Router.route) => {
  let navRef = React.useRef(Js.Nullable.null);
  let width =
    switch (Js.Nullable.toOption(React.Ref.current(navRef))) {
    | None => 0.0
    | Some(nav) => ReactDOMRe.domElementToObj(nav)##clientWidth
    };
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ToggleMenu(isOpen) => {...state, isOpen}
        | TouchStart(clientX) =>
          if (state.isOpen) {
            {
              ...state,
              touches: {
                first: Some((clientX, now())),
                last: None,
              },
            };
          } else {
            state;
          }
        | TouchMove(clientX) =>
          if (state.isOpen) {
            {
              ...state,
              touches: {
                ...state.touches,
                last: Some((clientX, now())),
              },
            };
          } else {
            state;
          }
        | TouchEnd =>
          if (state.isOpen) {
            let (x, t) =
              Belt.Option.getWithDefault(state.touches.first, (0.0, 0.0));
            let (x', t') =
              Belt.Option.getWithDefault(state.touches.last, (0.0, 0.0));
            let velocity = (x' -. x) /. (t' -. t);
            let state = {
              ...state,
              touches: {
                first: None,
                last: None,
              },
            };
            if (velocity < (-0.3) || x' < width /. 2.0) {
              {...state, isOpen: false};
            } else {
              state;
            };
          } else {
            state;
          }
        },
      {
        isOpen: false,
        touches: {
          first: None,
          last: None,
        },
      },
    );

  React.useEffect(() => {
    let handler = () => dispatch(ToggleMenu(false));
    addEventListener("popstate", handler);
    Some(() => removeEventListener("popstate", handler));
  });

  <Wrapper.sc
    isOpen={state.isOpen}
    onClick={_event =>
      if (state.isOpen) {
        dispatch(ToggleMenu(false));
      }
    }
    onTouchStart={event =>
      dispatch(
        TouchStart(
          ReactEvent.Touch.changedTouches(event)##item(0)##clientX,
        ),
      )
    }
    onTouchMove={event =>
      dispatch(
        TouchMove(ReactEvent.Touch.changedTouches(event)##item(0)##clientX),
      )
    }
    onTouchEnd={_event => dispatch(TouchEnd)}>
    <Header.sc>
      <a
        onClick={event => {
          ReactEvent.Mouse.stopPropagation(event);
          dispatch(ToggleMenu(true));
        }}>
        <img src=[%raw {|require("../../../src/img/icon/hamburger.svg")|}] />
      </a>
      <h1> {ReasonReact.string(currentRoute.title)} </h1>
    </Header.sc>
    <Nav.sc
      isOpen={state.isOpen}
      onClick={event => ReactEvent.Mouse.stopPropagation(event)}
      style={
        switch (state.touches) {
        | {first: Some((x, _)), last: Some((x', _))} =>
          ReactDOMRe.Style.make(
            ~transform=
              "translateX("
              ++ Js.Float.toString(x' -. x > 0.0 ? 0.0 : x' -. x)
              ++ "0px)",
            ~transition="none",
            (),
          )
        | _ => ReactDOMRe.Style.make()
        }
      }
      ref={ReactDOMRe.Ref.domRef(navRef)}>
      <header>
        <a onClick={_event => dispatch(ToggleMenu(false))}>
          <img src=[%raw {|require("../../../src/img/icon/arrow.svg")|}] />
          {ReasonReact.string(currentRoute.title)}
        </a>
      </header>
      <label> {ReasonReact.string("home")} </label>
      <ul>
        <li>
          <Router.NavLink href="/">
            {ReasonReact.string("Home")}
          </Router.NavLink>
        </li>
      </ul>
      <label> {ReasonReact.string("pages")} </label>
      <ul>
        <li>
          <Router.NavLink href="/page1">
            {ReasonReact.string("Page1")}
          </Router.NavLink>
        </li>
        <li>
          <Router.NavLink href="/page2">
            {ReasonReact.string("Page2")}
          </Router.NavLink>
        </li>
        <li>
          <Router.NavLink href="/page3">
            {ReasonReact.string("Page3")}
          </Router.NavLink>
        </li>
      </ul>
    </Nav.sc>
    <main>
      ReactTransitionGroup.(
        <TransitionGroup>
          <CSSTransition
            key={currentRoute.title}
            _in=true
            timeout=900
            classNames="routeTransition">
            {currentRoute.component}
          </CSSTransition>
        </TransitionGroup>
      )
    </main>
  </Wrapper.sc>;
};
