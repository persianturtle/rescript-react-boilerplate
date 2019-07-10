%raw
{| import "../../../src/Index.scss" |};

ReactDOMRe.renderToElementWithId(
  <Router.WithRouter>
    ...{(~currentRoute) => <App currentRoute />}
  </Router.WithRouter>,
  "root",
);