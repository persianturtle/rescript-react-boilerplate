@val external window: 'a = "window"
@val external require: string => string = "require"

require("../../../src/App.scss")->ignore
require("../../../src/ReactTransitionGroup.scss")->ignore

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

  <div
    className={`App ${state.isOpen ? "overlay" : ""}`}
    onClick={_event =>
      if state.isOpen {
        dispatch(ToggleMenu(false))
      }}
    onTouchStart={event =>
      dispatch(TouchStart(ReactEvent.Touch.changedTouches(event)["item"](. 0)["clientX"]))}
    onTouchMove={event =>
      dispatch(TouchMove(ReactEvent.Touch.changedTouches(event)["item"](. 0)["clientX"]))}
    onTouchEnd={_event => dispatch(TouchEnd)}>
    <header>
      <a
        onClick={event => {
          ReactEvent.Mouse.stopPropagation(event)
          dispatch(ToggleMenu(true))
        }}>
        <img src={require("../../../src/img/icon/hamburger.svg")} />
      </a>
      <h1> {title->React.string} </h1>
    </header>
    <nav
      className={state.isOpen ? "active" : ""}
      style={switch state.touches {
      | {first: Some((x, _)), last: Some((x', _))} =>
        ReactDOM.Style.make(
          ~transform="translateX(" ++ (Js.Float.toString(x' -. x > 0.0 ? 0.0 : x' -. x) ++ "0px)"),
          ~transition="none",
          (),
        )
      | _ => ReactDOM.Style.make()
      }}
      onClick={event => ReactEvent.Mouse.stopPropagation(event)}
      ref={ReactDOM.Ref.domRef(navRef)}>
      <header>
        <a onClick={_event => dispatch(ToggleMenu(false))}>
          <img src={require("../../../src/img/icon/arrow.svg")} /> {title->React.string}
        </a>
      </header>
      <label> {React.string("home")} </label>
      <ul> <li> <Link href="/" isNavLink=true> {React.string("Home")} </Link> </li> </ul>
      <label> {React.string("pages")} </label>
      <ul>
        <li> <Link href="/page1" isNavLink=true> {React.string("Page1")} </Link> </li>
        <li> <Link href="/page2" isNavLink=true> {React.string("Page2")} </Link> </li>
        <li> <Link href="/page3" isNavLink=true> {React.string("Page3")} </Link> </li>
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