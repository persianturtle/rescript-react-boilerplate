module Wrapper = %styled.div(
  (~transition, ~transform, ~opacity) =>
    `
      min-height: 100vh;

      &::after {
        content: "";
        transition: $(transition);
        position: fixed;
        top: 0;
        right: 0;
        bottom: 0;
        left: 0;
        background-color: rgba(0, 0, 0, 0.33);
        transform: $(transform);
        opacity: $(opacity);
        z-index: 1;
      }

      .routeTransition-enter.routeTransition-enter-active {
        animation: enter 500ms ease 400ms both;
      }

      .routeTransition-exit.routeTransition-exit-active {
        animation: exit 400ms ease both;
      }

      > main {
        padding: 30px;

        img {
          max-width: 700px;

          @media (max-width: 767px) {
            max-width: 100%;
          }
        }
      }
    `
)

module Header = %styled.header(`
  display: flex;
  align-items: center;
  width: 100vw;
  height: 60px;
  background-color: dodgerblue;
  color: white;
  box-shadow: 0 4px 5px 0 rgba(15, 74, 133, 0.14),
    0 2px 9px 1px rgba(15, 74, 133, 0.12),
    0 4px 2px -2px rgba(15, 74, 133, 0.2);
  > a {
    display: flex;
    align-items: center;
    width: 32px;
    height: 100%;
    padding: 0 10px;
    cursor: pointer;
    > svg {
      width: 100%;
      height: 100%;
    }
  }
  > h1 {
    font-size: 26px;
    line-height: 26px;
    margin-left: 10px;
  }
`)

module Nav = %styled.nav(
  (~transform) => {
    `
    transition: transform 450ms cubic-bezier(0.23, 1, 0.32, 1);
    position: fixed;
    top: 0;
    left: 0;
    height: 100vh;
    background-color: white;
    box-shadow: 0px 3px 10px 0 rgba(0, 0, 0, 0.16),
      0px 3px 10px 0 rgba(0, 0, 0, 0.23);
    overflow: auto;
    z-index: 2;
    transform: $(transform);

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

        > svg {
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

        svg {
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

    @media (max-width: 767px) {
      width: 85vw;
    }

    @media (min-width: 768px) {
      width: 300px;
    }
  `
  }
)
