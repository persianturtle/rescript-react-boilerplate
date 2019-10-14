%raw
{| import { createGlobalStyle } from "styled-components" |};

module GlobalStyles = {
  [@bs.obj] external scProps: unit => React.element = "";

  let sc = [%raw
    {|
      createGlobalStyle`
        body {
          margin: 0;
          font-family: Helvetica, Arial, sans-serif;
        }

        h1, h2, h3 {
          font-weight: normal;
        }

        img {
          display: block;
          max-width: 100%;
        }

        a {
          cursor: pointer;
        }
      `
    |}
  ];
};

ReactDOMRe.renderToElementWithId(
  <>
    <GlobalStyles.sc />
    <Router.WithRouter>
      ...{(~currentRoute) => <App currentRoute />}
    </Router.WithRouter>
  </>,
  "root",
);
