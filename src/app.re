[%bs.raw {|require('./app.css')|}];

[@bs.val] [@bs.scope "document"] external documentElement : Dom.element = "";

[@bs.val] [@bs.scope "performance"] external now : unit => float = "";

type route =
  | Home
  | Page1
  | Page2
  | Page3;

type routeWithTitle = (route, string);

type user = {
  name: string,
  email: string
};

type nav = {
  isOpen: bool,
  isSwiping: ref(bool),
  position: list((float, float)),
  width: ref(float)
};

type action =
  | Navigate(routeWithTitle)
  | ToggleMenu(bool)
  | TouchStart(float)
  | TouchMove(float)
  | TouchEnd(float);

type state = {
  routeWithTitle,
  user,
  nav
};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {
    routeWithTitle: (Home, "Home"),
    user: {
      name: "Person Name",
      email: "person@email.com"
    },
    nav: {
      isOpen: false,
      isSwiping: ref(false),
      position: [(0.0, 0.0)],
      width: ref(0.0)
    }
  },
  reducer: (action, state) =>
    switch action {
    | Navigate(routeWithTitle) =>
      ReasonReact.Update({
        ...state,
        routeWithTitle,
        nav: {
          ...state.nav,
          isOpen: false
        }
      })
    | ToggleMenu(isOpen) =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          nav: {
            ...state.nav,
            isOpen
          }
        },
        (
          _self =>
            if (isOpen) {
              /* [%bs.raw {| document.documentElement.style.overflow = "hidden"|}]; */
              ReactDOMRe.domElementToObj(documentElement)##style##overflow#="hidden";
            } else {
              /* [%bs.raw {| document.documentElement.style.overflow = ""|}]; */
              ReactDOMRe.domElementToObj(documentElement)##style##overflow#="";
            }
        )
      )
    | TouchStart(clientX) =>
      if (state.nav.isOpen) {
        state.nav.isSwiping := true;
      };
      ReasonReact.Update({
        ...state,
        nav: {
          ...state.nav,
          position: [(clientX, now())]
        }
      });
    | TouchMove(clientX) =>
      if (state.nav.isSwiping^) {
        ReasonReact.Update({
          ...state,
          nav: {
            ...state.nav,
            position: [(clientX, now()), ...state.nav.position]
          }
        });
      } else {
        ReasonReact.NoUpdate;
      }
    | TouchEnd(clientX) =>
      state.nav.isSwiping := false;
      let velocity =
        switch state.nav.position {
        | [] => 0.0
        | [_] => 0.0
        | [(x', t'), (x, t), ..._] => (x' -. x) /. (t' -. t)
        };
      if (velocity < (-0.3)) {
        ReasonReact.Update({
          ...state,
          nav: {
            ...state.nav,
            isOpen: false
          }
        });
      } else if (clientX < state.nav.width^ /. 2.0) {
        ReasonReact.Update({
          ...state,
          nav: {
            ...state.nav,
            isOpen: false
          }
        });
      } else {
        ReasonReact.Update(state);
      };
    },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url =>
          switch url.path {
          | ["page1"] => self.send(Navigate((Page1, "Page1")))
          | ["page2"] => self.send(Navigate((Page2, "Page2")))
          | ["page3"] => self.send(Navigate((Page3, "Page3")))
          | _ => self.send(Navigate((Home, "Home")))
          }
        ),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: self => {
    let (route, title) = self.state.routeWithTitle;
    let (x, _t) = List.hd(List.rev(self.state.nav.position));
    let (x', _t') = List.hd(self.state.nav.position);
    <div
      className=("App" ++ (self.state.nav.isOpen ? " overlay" : ""))
      onClick=(_event => self.send(ToggleMenu(false)))
      onTouchStart=(
        event =>
          self.send(
            TouchStart(
              TouchList.first(ReactEventRe.Touch.changedTouches(event))##clientX
            )
          )
      )
      onTouchMove=(
        event =>
          self.send(
            TouchMove(
              TouchList.first(ReactEventRe.Touch.changedTouches(event))##clientX
            )
          )
      )
      onTouchEnd=(
        event =>
          self.send(
            TouchEnd(
              TouchList.first(ReactEventRe.Touch.changedTouches(event))##clientX
            )
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
        <h1> (ReasonReact.stringToElement(title)) </h1>
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
              ()
            ) :
            ReactDOMRe.Style.make()
        )
        ref=(
          self.handle((ref, self) =>
            self.state.nav.width :=
              (
                switch (Js.Nullable.to_opt(ref)) {
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
            (ReasonReact.stringToElement(title))
          </a>
          <svg viewBox="0 0 32 32">
            <path
              d="M8 10c0-4.418 3.582-8 8-8s8 3.582 8 8c0 4.418-3.582 8-8 8s-8-3.582-8-8zM24 20h-16c-4.418 0-8 3.582-8 8v2h32v-2c0-4.418-3.582-8-8-8z"
            />
          </svg>
          <p> (ReasonReact.stringToElement(self.state.user.name)) </p>
          <p> (ReasonReact.stringToElement(self.state.user.email)) </p>
        </header>
        <label> (ReasonReact.stringToElement("home")) </label>
        <ul> <li> <Link href="/" label="Home" /> </li> </ul>
        <label> (ReasonReact.stringToElement("pages")) </label>
        <ul>
          <li> <Link href="/page1" label="Page1" /> </li>
          <li> <Link href="/page2" label="Page2" /> </li>
          <li> <Link href="/page3" label="Page3" /> </li>
        </ul>
      </nav>
      <main>
        (
          switch route {
          | Home => <Home />
          | Page1 => <Page1 />
          | Page2 => <Page2 />
          | Page3 => <Page3 />
          }
        )
      </main>
    </div>;
  }
};