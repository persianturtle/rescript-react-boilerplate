@val external window: 'a = "window"

module HamburgerIcon = {
  @module("../../../img/icon/hamburger.svg") @react.component
  external make: unit => React.element = "default"
}

module ArrowIcon = {
  @module("../../../img/icon/arrow.svg") @react.component
  external make: unit => React.element = "default"
}

module ChevronIcon = {
  @module("../../../img/icon/chevron.svg") @react.component
  external make: unit => React.element = "default"
}

type touches = {
  first: option<(float, float)>,
  last: option<(float, float)>,
}

type state = {
  isOpen: bool,
  touches: touches,
}

type action =
  | ToggleMenu(bool)
  | TouchStart(float)
  | TouchMove(float)
  | TouchEnd

@react.component
let make = () => {
  let url = RescriptReactRouter.useUrl()
  let title = switch url.path {
  | list{} => "Home"
  | list{"page1"} => "Page 1"
  | list{"page2"} => "Page 2"
  | list{"page3"} => "Page 3"
  | _ => "Not Found"
  }
  let navRef = React.useRef(Js.Nullable.null)
  let width = switch Js.Nullable.toOption(navRef.current) {
  | None => 0.0
  | Some(nav) => ReactDOM.domElementToObj(nav)["clientWidth"]
  }
  let (state, dispatch) = React.useReducer(
    (state, action) =>
      switch action {
      | ToggleMenu(isOpen) => {...state, isOpen: isOpen}
      | TouchStart(clientX) =>
        if state.isOpen {
          {
            ...state,
            touches: {
              first: Some((clientX, window["performance"]["now"](.))),
              last: None,
            },
          }
        } else {
          state
        }
      | TouchMove(clientX) =>
        if state.isOpen {
          {
            ...state,
            touches: {
              ...state.touches,
              last: Some((clientX, window["performance"]["now"](.))),
            },
          }
        } else {
          state
        }
      | TouchEnd =>
        if state.isOpen {
          let (x, t) = Belt.Option.getWithDefault(state.touches.first, (0.0, 0.0))
          let (x', t') = Belt.Option.getWithDefault(state.touches.last, (0.0, 0.0))
          let velocity = (x' -. x) /. (t' -. t)
          let state = {
            ...state,
            touches: {
              first: None,
              last: None,
            },
          }
          if velocity < -0.3 || x' < width /. 2.0 {
            {
              ...state,
              isOpen: false,
            }
          } else {
            state
          }
        } else {
          state
        }
      },
    {
      isOpen: false,
      touches: {
        first: None,
        last: None,
      },
    },
  )

  React.useEffect(() => {
    let handler = () => dispatch(ToggleMenu(false))
    window["addEventListener"](. "popstate", handler)->ignore
    Some(() => window["removeEventListener"](. "popstate", handler))
  })

  React.useEffect1(() => {
    // disable scrolling when the nav is open
    if state.isOpen {
      window["document"]["documentElement"]["style"]["cssText"] = `
        position: fixed;
        overflow: hidden;
      `
    } else {
      window["document"]["documentElement"]["style"]["cssText"] = ""
    }

    None
  }, [state.isOpen])

  let keyframes = {
    "enter": Emotion.keyframes(`
      from {
        opacity: 0;
        transform: translateY(50px);
      }
    `),
    "exit": Emotion.keyframes(`
      to {
        opacity: 0;
        transform: translateY(50px);
      }
    `),
  }

  let wrapper = `
    min-height: 100vh;

    &::after {
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

      ${state.isOpen
      ? `
          transition: opacity 450ms cubic-bezier(0.23, 1, 0.32, 1);
          transform: translateX(0%);
          opacity: 1;
        `
      : ""}
    }

    .routeTransition-enter.routeTransition-enter-active {
      animation: ${keyframes["enter"]} 500ms ease 400ms both;
    }

    .routeTransition-exit.routeTransition-exit-active {
      animation: ${keyframes["exit"]} 400ms ease both;
    }
  `

  let header = `
    display: flex;
    align-items: center;
    width: 100vw;
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

      > svg {
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

  let nav = `
    transition: transform 450ms cubic-bezier(0.23, 1, 0.32, 1);
    position: fixed;
    top: 0;
    left: 0;
    height: 100vh;
    background-color: white;
    box-shadow: 0px 3px 10px 0 rgba(0, 0, 0, 0.16),
      0px 3px 10px 0 rgba(0, 0, 0, 0.23);
    overflow: auto;
    z-index: 2;

    transform: ${state.isOpen ? "translateX(0)" : "translateX(calc(-100% - 10px))"};

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

        > svg {
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

        svg {
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

    @media (max-width: 767px) {
      width: 85vw;
    }

    @media (min-width: 768px) {
      width: 300px;
    }
  `

  <div
    className={Emotion.css(wrapper)}
    onClick={_event =>
      if state.isOpen {
        dispatch(ToggleMenu(false))
      }}
    onTouchStart={event =>
      dispatch(TouchStart(ReactEvent.Touch.changedTouches(event)["item"](. 0)["clientX"]))}
    onTouchMove={event =>
      dispatch(TouchMove(ReactEvent.Touch.changedTouches(event)["item"](. 0)["clientX"]))}
    onTouchEnd={_event => dispatch(TouchEnd)}>
    <header className={Emotion.css(header)}>
      <a
        onClick={event => {
          ReactEvent.Mouse.stopPropagation(event)
          dispatch(ToggleMenu(true))
        }}>
        <HamburgerIcon />
      </a>
      <h1> {title->React.string} </h1>
    </header>
    <nav
      className={Emotion.css(nav)}
      style={switch state.touches {
      | {first: Some((x, _)), last: Some((x', _))} =>
        ReactDOM.Style.make(
          ~transform=`translateX(${Js.Float.toString(x' -. x > 0.0 ? 0.0 : x' -. x)}px)`,
          ~transition="none",
          (),
        )
      | _ => ReactDOM.Style.make()
      }}
      onClick={event => ReactEvent.Mouse.stopPropagation(event)}
      ref={ReactDOM.Ref.domRef(navRef)}>
      <header>
        <a onClick={_event => dispatch(ToggleMenu(false))}> <ArrowIcon /> {title->React.string} </a>
      </header>
      <label> {React.string("home")} </label>
      <ul> <li> <Link href="/" isNavLink=true> {React.string("Home")} </Link> </li> </ul>
      <label> {React.string("pages")} </label>
      <ul>
        <li>
          <Link href="/page1" isNavLink=true> {React.string("Page1")} </Link> <ChevronIcon />
        </li>
        <li>
          <Link href="/page2" isNavLink=true> {React.string("Page2")} </Link> <ChevronIcon />
        </li>
        <li>
          <Link href="/page3" isNavLink=true> {React.string("Page3")} </Link> <ChevronIcon />
        </li>
      </ul>
    </nav>
    <main>
      {
        open ReactTransitionGroup
        <TransitionGroup>
          <CSSTransition key=title _in=true timeout=900 classNames="routeTransition">
            {switch url.path {
            | list{} => <Home />
            | list{"page1"} => <Page1 />
            | list{"page2"} => <Page2 />
            | list{"page3"} => <Page3 />
            | _ => <Redirect to_="/" />
            }}
          </CSSTransition>
        </TransitionGroup>
      }
    </main>
  </div>
}
