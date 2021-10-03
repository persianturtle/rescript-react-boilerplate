%%raw(`import styled, { css } from "styled-components"`)

@obj
external scProps: (
  ~isOpen: bool,
  ~onClick: ReactEvent.Mouse.t => unit,
  ~onTouchStart: ReactEvent.Touch.t => unit,
  ~onTouchMove: ReactEvent.Touch.t => unit,
  ~onTouchEnd: ReactEvent.Touch.t => unit,
  ~children: React.element,
  unit,
) => {
  "isOpen": bool,
  "onClick": ReactEvent.Mouse.t => unit,
  "onTouchStart": ReactEvent.Touch.t => unit,
  "onTouchMove": ReactEvent.Touch.t => unit,
  "onTouchEnd": ReactEvent.Touch.t => unit,
  "children": React.element,
} = ""

let sc = %raw(`
    styled.div\`
      min-height: 100vh;

      &:after {
        content: "";
        transition: opacity 450ms cubic-bezier(0.23, 1, 0.32, 1),
          transform 0ms cubic-bezier(0.23, 1, 0.32, 1) 450ms;
        position: fixed;
        top: 0;
        right: 0;
        bottom: 0;
        left: 0;
        background-color: rgba(0, 0, 0, 0.33);
        transform: translateX(-100%);
        opacity: 0;
        z-index: 1;

        \${props => props.isOpen && css\`
          transition: opacity 450ms cubic-bezier(0.23, 1, 0.32, 1);
          transform: translateX(0%);
          opacity: 1;
        \`}
      }

      /* ReactTransitionGroup */
      @keyframes enter {
        from {
          opacity: 0;
          transform: translateY(50px);
        }
      }

      @keyframes exit {
        to {
          opacity: 0;
          transform: translateY(50px);
        }
      }

      .routeTransition-enter.routeTransition-enter-active {
        animation: enter 500ms ease 400ms both;
      }

      .routeTransition-exit.routeTransition-exit-active {
        animation: exit 400ms ease both;
      }
    \`
  `)
