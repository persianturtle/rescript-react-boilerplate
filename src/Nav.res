%%raw(`import styled, {css} from 'styled-components'`)

@obj
external scProps: (
  ~isOpen: bool,
  ~onClick: ReactEvent.Mouse.t => unit,
  ~style: ReactDOM.style,
  ~ref: ReactDOM.domRef,
  ~children: React.element,
  unit,
) => {
  "isOpen": bool,
  "onClick": ReactEvent.Mouse.t => unit,
  "style": ReactDOM.style,
  "ref": ReactDOM.domRef,
  "children": React.element,
} = ""

let sc = %raw(`
    styled.nav\`
      transition: transform 450ms cubic-bezier(0.23, 1, 0.32, 1);
      position: absolute;
      top: 0;
      left: 0;
      transform: translateX(calc(-100% - 10px));
      height: 100vh;
      background-color: white;
      box-shadow: rgba(0, 0, 0, 0.16) 0px 3px 10px,
        rgba(0, 0, 0, 0.23) 0px 3px 10px;
      overflow: auto;
      z-index: 2;

      \${props => props.isOpen && css\`
        transform: translateX(0%);
      \`}

      > header {
        position: relative;
        background-color: lavender;
        height: 150px;
        margin: 0;

        > a {
          font-size: 24px;
          line-height: 24px;
          position: absolute;
          top: 0;
          left: 0;
          display: flex;
          align-items: center;
          height: 40px;
          padding: 10px 20px;

          > img {
            width: 20px;
            height: 20px;
            margin-right: 20px;
          }
        }
      }

      > label {
        font-weight: normal;
        font-size: 12px;
        line-height: 24px;
        text-transform: uppercase;
        display: block;
        background-color: rgba(0, 0, 0, 0.32);
        color: white;
        padding: 0 15px;
      }

      > ul {
        margin: 0;
        padding: 0;
        list-style: none;

        > li {
          position: relative;
          border-bottom: 1px solid rgba(0, 0, 0, 0.06);

          &:after {
            content: url(\${require("../../../src/img/icon/chevron.svg")});
            position: absolute;
            top: 0;
            right: 15px;
            bottom: 0;
            margin: auto;
            width: 15px;
            height: 15px;
          }

          > a {
            transition: background-color 450ms cubic-bezier(0.23, 1, 0.32, 1);
            font-size: 18px;
            line-height: 54px;
            text-decoration: none;
            display: block;
            padding: 0 15px;
            color: black;

            &.active {
              background-color: #e9e9e9;
            }
          }

          > img {
            width: 15px;
            height: 15px;
          }
        }
      }

      @media only screen and (max-width: 767px) {
        width: 85vw;
      }

      @media only screen and (min-width: 768px) {
        width: 300px;
      }
    \`
  `)
