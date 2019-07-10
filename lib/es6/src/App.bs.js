// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE

import * as Block from "bs-platform/lib/es6/block.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Router$ReasonCarousel from "./Router.bs.js";
import * as ReactTransitionGroup from "react-transition-group";


  require("../../../src/App.scss")
  require("../../../src/ReactTransitionGroup.scss")

;

function App(Props) {
  var currentRoute = Props.currentRoute;
  var navRef = React.useRef(null);
  var match = navRef.current;
  var width = (match == null) ? 0.0 : match.clientWidth;
  var match$1 = React.useReducer((function (state, action) {
          if (typeof action === "number") {
            if (state[/* isOpen */0]) {
              var match = Belt_Option.getWithDefault(state[/* touches */1][/* first */0], /* tuple */[
                    0.0,
                    0.0
                  ]);
              var match$1 = Belt_Option.getWithDefault(state[/* touches */1][/* last */1], /* tuple */[
                    0.0,
                    0.0
                  ]);
              var x$prime = match$1[0];
              var velocity = (x$prime - match[0]) / (match$1[1] - match[1]);
              var state_000 = /* isOpen */state[/* isOpen */0];
              var state_001 = /* touches : record */[
                /* first */undefined,
                /* last */undefined
              ];
              var state$1 = /* record */[
                state_000,
                state_001
              ];
              if (velocity < -0.3 || x$prime < width / 2.0) {
                return /* record */[
                        /* isOpen */false,
                        /* touches : record */[
                          /* first */undefined,
                          /* last */undefined
                        ]
                      ];
              } else {
                return state$1;
              }
            } else {
              return state;
            }
          } else {
            switch (action.tag | 0) {
              case 0 : 
                  return /* record */[
                          /* isOpen */action[0],
                          /* touches */state[/* touches */1]
                        ];
              case 1 : 
                  if (state[/* isOpen */0]) {
                    return /* record */[
                            /* isOpen */state[/* isOpen */0],
                            /* touches : record */[
                              /* first *//* tuple */[
                                action[0],
                                performance.now()
                              ],
                              /* last */undefined
                            ]
                          ];
                  } else {
                    return state;
                  }
              case 2 : 
                  if (state[/* isOpen */0]) {
                    var init = state[/* touches */1];
                    return /* record */[
                            /* isOpen */state[/* isOpen */0],
                            /* touches : record */[
                              /* first */init[/* first */0],
                              /* last *//* tuple */[
                                action[0],
                                performance.now()
                              ]
                            ]
                          ];
                  } else {
                    return state;
                  }
              
            }
          }
        }), /* record */[
        /* isOpen */false,
        /* touches : record */[
          /* first */undefined,
          /* last */undefined
        ]
      ]);
  var dispatch = match$1[1];
  var state = match$1[0];
  React.useEffect((function () {
          var handler = function (param) {
            return Curry._1(dispatch, /* ToggleMenu */Block.__(0, [false]));
          };
          addEventListener("popstate", handler);
          return (function (param) {
                    removeEventListener("popstate", handler);
                    return /* () */0;
                  });
        }));
  var match$2 = state[/* isOpen */0];
  var match$3 = state[/* isOpen */0];
  var match$4 = state[/* touches */1];
  var match$5 = match$4[/* first */0];
  var tmp;
  var exit = 0;
  if (match$5 !== undefined) {
    var match$6 = match$4[/* last */1];
    if (match$6 !== undefined) {
      var x$prime = match$6[0];
      var x = match$5[0];
      var match$7 = x$prime - x > 0.0;
      tmp = {
        transition: "none",
        transform: "translateX(" + ((
              match$7 ? 0.0 : x$prime - x
            ).toString() + "0px)")
      };
    } else {
      exit = 1;
    }
  } else {
    exit = 1;
  }
  if (exit === 1) {
    tmp = { };
  }
  return React.createElement("div", {
              className: "App" + (
                match$2 ? " overlay" : ""
              ),
              onClick: (function (_event) {
                  if (state[/* isOpen */0]) {
                    return Curry._1(dispatch, /* ToggleMenu */Block.__(0, [false]));
                  } else {
                    return 0;
                  }
                }),
              onTouchEnd: (function (_event) {
                  return Curry._1(dispatch, /* TouchEnd */0);
                }),
              onTouchMove: (function ($$event) {
                  return Curry._1(dispatch, /* TouchMove */Block.__(2, [$$event.changedTouches.item(0).clientX]));
                }),
              onTouchStart: (function ($$event) {
                  return Curry._1(dispatch, /* TouchStart */Block.__(1, [$$event.changedTouches.item(0).clientX]));
                })
            }, React.createElement("header", undefined, React.createElement("a", {
                      onClick: (function ($$event) {
                          $$event.stopPropagation();
                          return Curry._1(dispatch, /* ToggleMenu */Block.__(0, [true]));
                        })
                    }, React.createElement("img", {
                          src: (require("../../../src/img/icon/hamburger.svg"))
                        })), React.createElement("h1", undefined, currentRoute[/* title */1])), React.createElement("nav", {
                  ref: navRef,
                  className: match$3 ? "active" : "",
                  style: tmp,
                  onClick: (function ($$event) {
                      $$event.stopPropagation();
                      return /* () */0;
                    })
                }, React.createElement("header", undefined, React.createElement("a", {
                          onClick: (function (_event) {
                              return Curry._1(dispatch, /* ToggleMenu */Block.__(0, [false]));
                            })
                        }, React.createElement("img", {
                              src: (require("../../../src/img/icon/arrow.svg"))
                            }), currentRoute[/* title */1])), React.createElement("label", undefined, "home"), React.createElement("ul", undefined, React.createElement("li", undefined, React.createElement(Router$ReasonCarousel.NavLink[/* make */0], {
                              href: "/",
                              children: "Home"
                            }))), React.createElement("label", undefined, "pages"), React.createElement("ul", undefined, React.createElement("li", undefined, React.createElement(Router$ReasonCarousel.NavLink[/* make */0], {
                              href: "/page1",
                              children: "Page1"
                            })), React.createElement("li", undefined, React.createElement(Router$ReasonCarousel.NavLink[/* make */0], {
                              href: "/page2",
                              children: "Page2"
                            })), React.createElement("li", undefined, React.createElement(Router$ReasonCarousel.NavLink[/* make */0], {
                              href: "/page3",
                              children: "Page3"
                            })))), React.createElement("main", undefined, React.createElement(ReactTransitionGroup.TransitionGroup, {
                      children: React.createElement(ReactTransitionGroup.CSSTransition, {
                            in: true,
                            timeout: 900,
                            classNames: "routeTransition",
                            children: currentRoute[/* component */2],
                            key: currentRoute[/* title */1]
                          })
                    })));
}

var make = App;

export {
  make ,
  
}
/*  Not a pure module */