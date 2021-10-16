// Generated by ReScript, PLEASE EDIT WITH CARE

import * as React from "react";
import * as ReactDom from "react-dom";
import * as App$ReasonCarousel from "./App.bs.js";

import { createGlobalStyle } from "styled-components"
;

var sc = (createGlobalStyle`

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

      `);

var GlobalStyles = {
  sc: sc
};

var root = document.querySelector("#root");

if (!(root == null)) {
  ReactDom.render(React.createElement(React.Fragment, undefined, React.createElement(sc, {}), React.createElement(App$ReasonCarousel.make, {})), root);
}

export {
  GlobalStyles ,
  
}
/*  Not a pure module */