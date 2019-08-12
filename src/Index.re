%raw
{| import { createGlobalStyle } from "styled-components" |};

module GlobalStyles = {
  let styles = [%raw
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

  [@react.component]
  let make = () => {
    React.createElementVariadic(styles, makeProps(), [||]);
  };
};

ReactDOMRe.renderToElementWithId(
  <>
    <GlobalStyles />
    <Router.WithRouter>
      ...{(~currentRoute) => <App currentRoute />}
    </Router.WithRouter>
  </>,
  "root",
);