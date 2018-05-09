[%bs.raw {|require('../../../src/App.scss')|}];

[@bs.val] [@bs.scope "performance"] external now : unit => float = "";

type user = {
  name: string,
  email: string,
};

type nav = {
  isOpen: bool,
  isSwiping: ref(bool),
  position: list((float, float)),
  width: ref(float),
};

type action =
  | ToggleMenu(bool)
  | TouchStart(float)
  | TouchMove(float)
  | TouchEnd(float);

type state = {
  user,
  nav,
};

let component = ReasonReact.reducerComponent("App");

let make = (~currentRoute, _children) => {
  ...component,
  initialState: () => {
    user: {
      name: "Person Name",
      email: "person@email.com",
    },
    nav: {
      isOpen: false,
      isSwiping: ref(false),
      position: [(0.0, 0.0)],
      width: ref(0.0),
    },
  },
  willReceiveProps: self => {
    ...self.state,
    nav: {
      ...self.state.nav,
      isOpen: false,
    },
  },
  reducer: (action, state) =>
    switch (action) {
    | ToggleMenu(isOpen) =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          nav: {
            ...state.nav,
            isOpen,
          },
        },
        (
          _self =>
            if (isOpen) {
              %bs.raw
              {| document.documentElement.style.overflow = "hidden"|};
              /* ReactDOMRe.domElementToObj(documentElement)##style##overflow#="hidden"; */
            } else {
              %bs.raw
              {| document.documentElement.style.overflow = ""|};
              /* ReactDOMRe.domElementToObj(documentElement)##style##overflow#=""; */
            }
        ),
      )
    | TouchStart(clientX) =>
      if (state.nav.isOpen) {
        state.nav.isSwiping := true;
      };
      ReasonReact.Update({
        ...state,
        nav: {
          ...state.nav,
          position: [(clientX, now())],
        },
      });
    | TouchMove(clientX) =>
      if (state.nav.isSwiping^) {
        ReasonReact.Update({
          ...state,
          nav: {
            ...state.nav,
            position: [(clientX, now()), ...state.nav.position],
          },
        });
      } else {
        ReasonReact.NoUpdate;
      }
    | TouchEnd(clientX) =>
      state.nav.isSwiping := false;
      let velocity =
        switch (state.nav.position) {
        | [] => 0.0
        | [_] => 0.0
        | [(x', t'), (x, t), ..._] => (x' -. x) /. (t' -. t)
        };
      if (velocity < (-0.3)) {
        ReasonReact.Update({
          ...state,
          nav: {
            ...state.nav,
            isOpen: false,
          },
        });
      } else if (clientX < state.nav.width^ /. 2.0) {
        ReasonReact.Update({
          ...state,
          nav: {
            ...state.nav,
            isOpen: false,
          },
        });
      } else {
        ReasonReact.Update(state);
      };
    },
  render: self => {
    let (x, _t) = List.hd(List.rev(self.state.nav.position));
    let (x', _t') = List.hd(self.state.nav.position);
    <div
      className=("App" ++ (self.state.nav.isOpen ? " overlay" : ""))
      onClick=(_event => self.send(ToggleMenu(false)))
      onTouchStart=(
        event =>
          self.send(
            TouchStart(
              Utils.TouchList.first(ReactEventRe.Touch.changedTouches(event))##clientX,
            ),
          )
      )
      onTouchMove=(
        event =>
          self.send(
            TouchMove(
              Utils.TouchList.first(ReactEventRe.Touch.changedTouches(event))##clientX,
            ),
          )
      )
      onTouchEnd=(
        event =>
          self.send(
            TouchEnd(
              Utils.TouchList.first(ReactEventRe.Touch.changedTouches(event))##clientX,
            ),
          )
      )>
      <header>
        <a
          onClick=(
            event => {
              ReactEventRe.Mouse.stopPropagation(event);
              self.send(ToggleMenu(! self.state.nav.isOpen));
            }
          )>
          <svg viewBox="0 0 24 24">
            <path
              d="M21 11h-18c-0.6 0-1 0.4-1 1s0.4 1 1 1h18c0.6 0 1-0.4 1-1s-0.4-1-1-1z"
            />
            <path
              d="M3 7h18c0.6 0 1-0.4 1-1s-0.4-1-1-1h-18c-0.6 0-1 0.4-1 1s0.4 1 1 1z"
            />
            <path
              d="M21 17h-18c-0.6 0-1 0.4-1 1s0.4 1 1 1h18c0.6 0 1-0.4 1-1s-0.4-1-1-1z"
            />
          </svg>
        </a>
        <h1> (ReasonReact.string(Config.routeToTitle(currentRoute))) </h1>
      </header>
      <nav
        className=(self.state.nav.isOpen ? "active" : "")
        onClick=(event => ReactEventRe.Mouse.stopPropagation(event))
        style=(
          self.state.nav.isSwiping^ ?
            ReactDOMRe.Style.make(
              ~transform=
                "translateX("
                ++ string_of_float(x' -. x > 0.0 ? 0.0 : x' -. x)
                ++ "0px)",
              ~transition="none",
              (),
            ) :
            ReactDOMRe.Style.make()
        )
        ref=(
          self.handle((ref, self) =>
            self.state.nav.width :=
              (
                switch (Js.Nullable.toOption(ref)) {
                | None => 0.0
                | Some(r) => ReactDOMRe.domElementToObj(r)##clientWidth
                }
              )
          )
        )>
        <header>
          <a onClick=(_event => self.send(ToggleMenu(false)))>
            <svg viewBox="0 0 32 32">
              <path
                d="M12.586 27.414l-10-10c-0.781-0.781-0.781-2.047 0-2.828l10-10c0.781-0.781 2.047-0.781 2.828 0s0.781 2.047 0 2.828l-6.586 6.586h19.172c1.105 0 2 0.895 2 2s-0.895 2-2 2h-19.172l6.586 6.586c0.39 0.39 0.586 0.902 0.586 1.414s-0.195 1.024-0.586 1.414c-0.781 0.781-2.047 0.781-2.828 0z"
              />
            </svg>
            (ReasonReact.string(Config.routeToTitle(currentRoute)))
          </a>
          <svg viewBox="0 0 32 32">
            <path
              d="M8 10c0-4.418 3.582-8 8-8s8 3.582 8 8c0 4.418-3.582 8-8 8s-8-3.582-8-8zM24 20h-16c-4.418 0-8 3.582-8 8v2h32v-2c0-4.418-3.582-8-8-8z"
            />
          </svg>
          <p> (ReasonReact.string(self.state.user.name)) </p>
          <p> (ReasonReact.string(self.state.user.email)) </p>
        </header>
        <label> (ReasonReact.string("home")) </label>
        <ul>
          <li>
            <Router.NavLink route=Home>
              (ReasonReact.string("Home"))
            </Router.NavLink>
          </li>
        </ul>
        <label> (ReasonReact.string("pages")) </label>
        <ul>
          <li>
            <Router.NavLink route=Page1>
              (ReasonReact.string("Page1"))
            </Router.NavLink>
          </li>
          <li>
            <Router.NavLink route=Page2>
              (ReasonReact.string("Page2"))
            </Router.NavLink>
          </li>
          <li>
            <Router.NavLink route=Page3>
              (ReasonReact.string("Page3"))
            </Router.NavLink>
          </li>
        </ul>
      </nav>
      <main>
        <ReactTransitionGroup.TransitionGroup>
          (Config.routeToComponent(currentRoute))
        </ReactTransitionGroup.TransitionGroup>
      </main>
    </div>;
  },
};