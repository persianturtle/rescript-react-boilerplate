[%bs.raw {|require('./app.css')|}];

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

type position = {
  initial: float,
  current: float
};

type nav = {
  isOpen: bool,
  isSwiping: ref(bool),
  clientX: position
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
      clientX: {
        initial: 0.0,
        current: 0.0
      }
    }
  },
  reducer: (action, state) =>
    switch action {
    | Navigate(routeWithTitle) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, routeWithTitle},
        (self => self.send(ToggleMenu(false)))
      )
    | ToggleMenu(isOpen) =>
      ReasonReact.Update({
        ...state,
        nav: {
          ...state.nav,
          isOpen
        }
      })
    | TouchStart(clientX) =>
      if (state.nav.isOpen) {
        state.nav.isSwiping := true;
      };
      ReasonReact.Update({
        ...state,
        nav: {
          ...state.nav,
          clientX: {
            initial: clientX,
            current: clientX
          }
        }
      });
    | TouchMove(clientX) =>
      if (state.nav.isSwiping^) {
        ReasonReact.Update({
          ...state,
          nav: {
            ...state.nav,
            clientX: {
              ...state.nav.clientX,
              current: clientX
            }
          }
        });
      } else {
        ReasonReact.NoUpdate;
      }
    | TouchEnd(clientX) =>
      state.nav.isSwiping := false;
      if (clientX -. state.nav.clientX.initial > (-150.0)) {
        ReasonReact.Update(state);
      } else {
        ReasonReact.UpdateWithSideEffects(
          state,
          (self => self.send(ToggleMenu(false)))
        );
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
    let swipe =
      self.state.nav.clientX.current -. self.state.nav.clientX.initial;
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
                ++ string_of_float(swipe > 0.0 ? 0.0 : swipe)
                ++ "px)",
              ~transition="none",
              ()
            ) :
            ReactDOMRe.Style.make()
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
        <ul> <li> <Link route="/" label="Home" /> </li> </ul>
        <label> (ReasonReact.stringToElement("pages")) </label>
        <ul>
          <li> <Link route="/page1" label="Page1" /> </li>
          <li> <Link route="/page2" label="Page2" /> </li>
          <li> <Link route="/page3" label="Page3" /> </li>
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