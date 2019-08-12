[@bs.val] [@bs.scope "performance"] external now: unit => float = "now";
[@bs.val]
external addEventListener: (string, unit => unit) => unit = "addEventListener";
[@bs.val]
external removeEventListener: (string, unit => unit) => unit =
  "removeEventListener";

%raw
{|import styled, { css } from "styled-components"|};

module Wrapper = {
  let wrapper = [%raw
    {|
      styled.div`
        min-height: 100vh;

        &:after {
          content: "";
          transition: opacity 450ms cubic-bezier(0.23, 1, 0.32, 1),
            transform 0ms cubic-bezier(0.23, 1, 0.32, 1) 450ms;
          position: fixed;
          top: 0;
          right: 0;
          bottom: 0;
          left: 0;
          background-color: rgba(0, 0, 0, 0.33);
          transform: translateX(-100%);
          opacity: 0;
          z-index: 1;

          ${props => props.isOpen && css`
            transition: opacity 450ms cubic-bezier(0.23, 1, 0.32, 1);
            transform: translateX(0%);
            opacity: 1;
          `}
        }

        /* ReactTransitionGroup */
        @keyframes enter {
          from {
            opacity: 0;
            transform: translateY(50px);
          }
        }

        @keyframes exit {
          to {
            opacity: 0;
            transform: translateY(50px);
          }
        }

        .routeTransition-enter.routeTransition-enter-active {
          animation: enter 500ms ease 400ms both;
        }

        .routeTransition-exit.routeTransition-exit-active {
          animation: exit 400ms ease both;
        }
      `
    |}
  ];

  [@react.component]
  let make =
      (~isOpen, ~onClick, ~onTouchStart, ~onTouchMove, ~onTouchEnd, ~children) => {
    React.createElementVariadic(
      wrapper,
      makeProps(
        ~isOpen,
        ~onClick,
        ~onTouchStart,
        ~onTouchMove,
        ~onTouchEnd,
        ~children,
        (),
      ),
      [||],
    );
  };
};

module Header = {
  let header = [%raw
    {|
      styled.header`
        display: flex;
        align-items: center;
        height: 60px;
        background-color: dodgerblue;
        color: white;
        box-shadow: 0 4px 5px 0 rgba(15, 74, 133, 0.14),
          0 2px 9px 1px rgba(15, 74, 133, 0.12),
          0 4px 2px -2px rgba(15, 74, 133, 0.2);

        > a {
          display: flex;
          align-items: center;
          width: 32px;
          height: 100%;
          padding: 0 10px;
          cursor: pointer;

          > img {
            width: 100%;
            height: 100%;
          }
        }

        > h1 {
          font-size: 26px;
          line-height: 26px;
          margin-left: 10px;
        }
      `
    |}
  ];

  [@react.component]
  let make = (~children) => {
    React.createElementVariadic(header, makeProps(~children, ()), [||]);
  };
};

module Nav = {
  let nav = [%raw
    {|
      styled.nav`
        transition: transform 450ms cubic-bezier(0.23, 1, 0.32, 1);
        position: absolute;
        top: 0;
        left: 0;
        transform: translateX(calc(-100% - 10px));
        height: 100vh;
        background-color: white;
        box-shadow: rgba(0, 0, 0, 0.16) 0px 3px 10px,
          rgba(0, 0, 0, 0.23) 0px 3px 10px;
        overflow: auto;
        z-index: 2;

        ${props => props.isOpen && css`
          transform: translateX(0%);
        `}

        > header {
          position: relative;
          background-color: lavender;
          height: 150px;
          margin: 0;

          > a {
            font-size: 24px;
            line-height: 24px;
            position: absolute;
            top: 0;
            left: 0;
            display: flex;
            align-items: center;
            height: 40px;
            padding: 10px 20px;

            > img {
              width: 20px;
              height: 20px;
              margin-right: 20px;
            }
          }
        }

        > label {
          font-weight: normal;
          font-size: 12px;
          line-height: 24px;
          text-transform: uppercase;
          display: block;
          background-color: rgba(0, 0, 0, 0.32);
          color: white;
          padding: 0 15px;
        }

        > ul {
          margin: 0;
          padding: 0;
          list-style: none;

          > li {
            position: relative;
            border-bottom: 1px solid rgba(0, 0, 0, 0.06);

            &:after {
              content: url(${require("../../../src/img/icon/chevron.svg")});
              position: absolute;
              top: 0;
              right: 15px;
              bottom: 0;
              margin: auto;
              width: 15px;
              height: 15px;
            }

            > a {
              transition: background-color 450ms cubic-bezier(0.23, 1, 0.32, 1);
              font-size: 18px;
              line-height: 54px;
              text-decoration: none;
              display: block;
              padding: 0 15px;
              color: black;

              &.active {
                background-color: #e9e9e9;
              }
            }

            > img {
              width: 15px;
              height: 15px;
            }
          }
        }

        @media only screen and (max-width: 767px) {
          width: 85vw;
        }

        @media only screen and (min-width: 768px) {
          width: 300px;
        }
      `
    |}
  ];

  [@react.component]
  let make =
    React.forwardRef((~isOpen, ~onClick, ~style, ~children, ref) =>
      React.createElementVariadic(
        nav,
        makeProps(~isOpen, ~onClick, ~style, ~ref, ~children, ()),
        [||],
      )
    );
};

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

  <Wrapper
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
    <Header>
      <a
        onClick={event => {
          ReactEvent.Mouse.stopPropagation(event);
          dispatch(ToggleMenu(true));
        }}>
        <img src=[%raw {|require("../../../src/img/icon/hamburger.svg")|}] />
      </a>
      <h1> {ReasonReact.string(currentRoute.title)} </h1>
    </Header>
    <Nav
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
    </Nav>
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
  </Wrapper>;
};