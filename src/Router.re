module WithRouter = {
  type state = {currentRoute: Config.routes};
  type action =
    | ChangeUrl(Config.routes);
  let component = ReasonReact.reducerComponent("WithRouter");
  let make = children => {
    ...component,
    initialState: () => {
      currentRoute:
        ReasonReact.Router.dangerouslyGetInitialUrl() |> Config.urlToRoute,
    },
    reducer: (action, _state) =>
      switch (action) {
      | ChangeUrl(route) => ReasonReact.Update({currentRoute: route})
      },
    subscriptions: ({send}) => [
      Sub(
        () =>
          ReasonReact.Router.watchUrl(url =>
            send(ChangeUrl(url |> Config.urlToRoute))
          ),
        ReasonReact.Router.unwatchUrl,
      ),
    ],
    render: ({state}) => children(~currentRoute=state.currentRoute),
  };
};

module Link = {
  let component = ReasonReact.statelessComponent("Link");
  let make = (~route, ~className="", children) => {
    ...component,
    render: self => {
      let href = Config.routeToString(route);
      ReasonReact.createDomElement(
        "a",
        ~props={
          "className": className,
          "href": href,
          "onClick":
            self.handle((event, _self) => {
              ReactEventRe.Mouse.preventDefault(event);
              ReasonReact.Router.push(href);
            }),
        },
        children,
      );
    },
  };
};

module NavLink = {
  let component = ReasonReact.statelessComponent("NavLink");
  let make = (~route, ~activeRoute=?, ~className=?, children) => {
    ...component,
    render: _self =>
      <WithRouter>
        ...(
             (~currentRoute) => {
               let activeRoute =
                 switch (activeRoute) {
                 | None => route
                 | Some(route) => route
                 };
               let className =
                 Cn.make([
                   Cn.unwrap(className),
                   Cn.ifTrue(activeRoute == currentRoute, "active"),
                 ]);
               <Link route className> ...children </Link>;
             }
           )
      </WithRouter>,
  };
};